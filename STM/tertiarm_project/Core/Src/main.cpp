
/* 		TERTIARM ROBOTIC ARM STM32 MAIN ROUTINE		 */

/*		INCLUDES		*/
#include "main.h"
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int32.h>
#include <sensor_msgs/JointState.h>
extern "C" {
#include "SERVO.h"
#include "JOYSTICK.h"
#include "button.h"
#include <stdint.h>
#include "DWT_Delay.h"
}

#define BTN_PRESSED   1
#define BTN_RELEASED  0

/*		SERVO CONSTANTS		*/
#define SERVO_Motor1    0
#define SERVO_Motor2    1
#define SERVO_Motor3    2
#define SERVO_Motor4    3
#define SERVO_Motor5    4
// SERVO BASES
#define BASE_base   110  			// 90 + 20
#define BASE_axis1  70				// 90 - 20
#define BASE_axis2  80 				// 90 - 10
#define BASE_thingy 80				// 90 - 10
#define BASE_tip    75
// SERVO DIRECTION
#define DIR_base   -1
#define DIR_axis1   1
#define DIR_axis2  -1
#define DIR_thingy -1
#define DIR_tip    -1

TIM_HandleTypeDef htim1;
UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;

/*		PROTOTYPES		*/
void SystemClock_Config(void);
static void GPIO_Init(void);
static void DMA_Init(void);
static void USART_UART_Init(void);
static void TIM1_Init(void);
void dbg_cb( const std_msgs::Float32& cmd_msg);
void move_axis( const sensor_msgs::JointState& virt_joints);

/*		ROS OBJECTS		*/
ros::NodeHandle nh;
std_msgs::String str_msg;
std_msgs::Int32 int_msg;
std_msgs::Float32 flt_msg;
ros::Publisher chatter("chatter", &str_msg);
ros::Publisher servoTelemetry("serv_tele", &int_msg);
ros::Publisher translatorTelemetry("angle_tele", &flt_msg);
ros::Subscriber<std_msgs::Float32> sub("led", dbg_cb);
ros::Subscriber<sensor_msgs::JointState> joint("/move_group/fake_controller_joint_states", move_axis);

uint8_t MODE = 1;
/* MODES:  0 - manual control
 * 		   1 - ROS control    */

// A debug callback for servo testing purposes
void dbg_cb( const std_msgs::Float32& cmd_msg){
          HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);

          if (cmd_msg.data == 11.0) {SERVO_Sweep(SERVO_Motor1); }
          else if (cmd_msg.data == 22.0)
          {
				SERVO_Sweep(SERVO_Motor2);
          }
          else
          {
				SERVO_MoveTo(SERVO_Motor1, cmd_msg.data);
				SERVO_MoveTo(SERVO_Motor2, cmd_msg.data);
				SERVO_MoveTo(SERVO_Motor3, cmd_msg.data);
				SERVO_MoveTo(SERVO_Motor4, cmd_msg.data);
				SERVO_MoveTo(SERVO_Motor5, cmd_msg.data);
          }

}

// A callback for joint operatiion in response to ROS msg
#define TO_DEGREES 57.3		//	180 / Pi
void move_axis( const sensor_msgs::JointState& virt_joints){
          double base   = DIR_base * virt_joints.position[0] * TO_DEGREES + BASE_base;
          double axis1  = DIR_axis1 * virt_joints.position[1] * TO_DEGREES + BASE_axis1;
          double axis2  = DIR_axis2 * virt_joints.position[2] * TO_DEGREES + BASE_axis2;
          double thingy = DIR_thingy * virt_joints.position[3] * TO_DEGREES + BASE_thingy;
          double tip 	= DIR_tip * virt_joints.position[4] * TO_DEGREES + BASE_tip;

          SERVO_MoveTo(SERVO_Motor1, base);
          SERVO_MoveTo(SERVO_Motor2, axis1);
          SERVO_MoveTo(SERVO_Motor3, axis2);
          SERVO_MoveTo(SERVO_Motor4, thingy);
          SERVO_MoveTo(SERVO_Motor5, tip);
}

uint32_t MAP(uint32_t IN, uint32_t INmin, uint32_t INmax, uint32_t OUTmin, uint32_t OUTmax)
{
	return ((	((IN - INmin)*(OUTmax - OUTmin)) / (INmax - INmin)	) + OUTmin);
}

//uint8_t BTN_State[1] = {0};		replaced with global variable in button.c

int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Configure the system clock */
  SystemClock_Config();
  GPIO_Init();
  DMA_Init();
  USART_UART_Init();
  HW_Init();

  nh.initNode();
  nh.advertise(chatter);
  nh.advertise(servoTelemetry);
  nh.advertise(translatorTelemetry);
  nh.subscribe(sub);
  nh.subscribe(joint);


  const char * hello = "Hello World!!";

  int chatter_interval = 1000.0 / 10;
  int chatter_last = HAL_GetTick();

  /*	 PRE-LAUNCH HOMING		*/
  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
  SERVO_MoveTo(SERVO_Motor1, BASE_base);
  SERVO_MoveTo(SERVO_Motor2, BASE_axis1);
  SERVO_MoveTo(SERVO_Motor3, BASE_axis2);
  SERVO_MoveTo(SERVO_Motor4, BASE_thingy);
  SERVO_MoveTo(SERVO_Motor5, BASE_tip);
  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);


  uint16_t JoyStick_XY[2] = {0};
  uint16_t ServoIndex = 1;
  uint16_t CurServoMinPulse = SERVO_Get_MinPulse(ServoIndex);
  uint16_t CurServoMaxPulse = SERVO_Get_MaxPulse(ServoIndex);
  uint16_t ServoPulse = 0;
  bool BeenPressed = false;

  uint8_t dbg = 0;

  while (1)
  {
	  //dbg = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14);
	  if (BTN_State== BTN_PRESSED)
	  {
		  BeenPressed = true;
	  }
	  if (BTN_State == BTN_RELEASED && BeenPressed == true)
	  {
		  ServoIndex++;
		  if (ServoIndex >= 4)
		  {
			  ServoIndex = 0;
		  }
		  BeenPressed = false;
	  }
	  if (MODE == 0)
	  {
		  JoyStick_Read(JoyStick_XY);
		  ServoPulse = MAP(JoyStick_XY[0], 0, 4095, CurServoMinPulse, CurServoMaxPulse);
		  SERVO_RawMove(ServoIndex, ServoPulse);
		  //SERVO_MoveTo(ServoIndex, ServoPulse);
		  HAL_Delay(10);
	  }
	  else if (nh.connected())		// ROS control mode
	  {
		  if(HAL_GetTick() - chatter_last > chatter_interval)
		  {

			  //TODO: proper telemetry publishing for manual mode
			  chatter_last = HAL_GetTick();
		  }
	  }

	  nh.spinOnce();
  }

}


void HW_Init()
{
	  JoyStick_Init();
	  SERVO_Init(SERVO_Motor1);
	  SERVO_Init(SERVO_Motor2);
	  SERVO_Init(SERVO_Motor3);
	  SERVO_Init(SERVO_Motor4);
	  SERVO_Init(SERVO_Motor5);
	  BTN_Init(BTN_State);
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}


static void TIM1_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};


  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 900-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 1000;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_TIM_MspPostInit(&htim1);

}

//USART1 Initialization Function
static void USART_UART_Init(void)
{
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;//57600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

}


//	Enable DMA controller clock
static void DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);
  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);
}

//	GPIO Initialization Function
static void GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  // GPIO clock
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  //
  //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);

  //	Onboard LED
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


  /*	MODE BUTTON		*/
  GPIO_InitStruct.Pin = GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}


void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
	  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);

  }
  /* USER CODE END Error_Handler_Debug */
}

void SysTick_CallBack()
{
    // Each SysTick: Call BTN_Main()
    BTN_Main();
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
