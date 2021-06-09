# Stop Sensors:
- Obstacle Detector
- Cross Detector
- Room Detector

GPIO_Pins in use:
- Obstacle Detector:
ADC - triggered by timer
Ex: TIM6 (0.5sec interrupt)
    PC3 (CN9)

- Cross Detector
- Room Detector
EXTI GPIO pin A
GPIO pin B
Ex: PinA = PD0 (EXTI)(CN9)
    PinB = PD1 (CN9)