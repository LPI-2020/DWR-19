https://github.com/xtrinch/stm32f7-demos/tree/master/07-rfid-rc522 - source code for SPI communication with MFRC522

//---------------------------------------------------------------------//
	To use RC522 with SPI select which SPI to use in the STM32CUBEMX.
	Define corresponding SPI pins and CLKs in main.h file like this.
	
/* Definition for SPIx clock resources */
#define SPIx                             SPI3
#define SPIx_CLK_ENABLE()                __HAL_RCC_SPI3_CLK_ENABLE()
#define SPIx_SCK_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOC_CLK_ENABLE()
#define SPIx_NSS_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOC_CLK_ENABLE()
#define SPIx_MISO_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()
#define SPIx_MOSI_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()
#define SPIx_CS_GPIO_CLK_ENABLE()		 __HAL_RCC_GPIOF_CLK_ENABLE()

#define SPIx_FORCE_RESET()               __HAL_RCC_SPI3_FORCE_RESET()
#define SPIx_RELEASE_RESET()             __HAL_RCC_SPI3_RELEASE_RESET()

/* Definition for SPIx Pins */
#define SPIx_SCK_PIN                     GPIO_PIN_10 // A5 -> PC10
#define SPIx_SCK_GPIO_PORT               GPIOC
#define SPIx_SCK_AF                      GPIO_AF6_SPI3
#define SPIx_MISO_PIN                    GPIO_PIN_11 // A6 -> PC11
#define SPIx_MISO_GPIO_PORT              GPIOC
#define SPIx_MISO_AF                     GPIO_AF6_SPI3
#define SPIx_MOSI_PIN                    GPIO_PIN_12 // A7 -> PC12
#define SPIx_MOSI_GPIO_PORT              GPIOC
#define SPIx_MOSI_AF                     GPIO_AF6_SPI3
#define SPIx_NSS_PIN					 GPIO_PIN_11 // A11
#define SPIx_NSS_GPIO_PORT				 GPIOA
#define SPIx_NSS_AF						 GPIO_AF5_SPI1
#define SPIx_CS_PIN                      GPIO_PIN_1 // F1
#define SPIx_CS_GPIO_PORT                GPIOF

	SPI CLK, MISO, MOSI are defined automatically by CUBE software, CS pin needs
to be specified manually as GPIO_OUTPUT in software and then declared above.

In main.c:

 /* USER CODE BEGIN 1 */
	
	uint8_t CardID[4];
	
 /* USER CODE END 1 */
 
 /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  
  MX_GPIO_Init();
  MX_SPI1_Init();
  
  /* USER CODE BEGIN 2 */
	
	RFID_RC522_Init();
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
		int status = TM_MFRC522_Check(CardID, &type);
		if (status == MI_OK) {
			//------------------------------------------------------------------------------------------------------------------//
			//Copy contents of CardId to another array because CardId will get "corrupted" upon calling TM_MFRC522_Check() again//
			//------------------------------------------------------------------------------------------------------------------//
		}
		else {							//------------------------//
        if (status == MI_TIMEOUT) {		//						  //
            str = "timeout";			// This part is optcional //
        }								//                        //
        if (status == MI_ERR) {			//------------------------//
            str = "error";
        }
    }
			
    /* USER CODE BEGIN 3 */
  }
  
//----------------------------------------------------------------------------------------------------------------------------------//  
  
  //----------------------------------------------------//
  // MX_SPI3_Init() - Configure SPI interface as below //
  //----------------------------------------------------//
  
vvoid MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 7;
  hspi3.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi3.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}