STM32L476 Peripheral Driver
A lightweight, portable, and educational peripheral driver library for STM32L476-based microcontrollers, written in C from the ground up.

This repository is intended to help you understand how STM32 peripherals work at the register level, how drivers are layered from low-level access to higher-level abstractions, and how to build clean, reusable firmware for embedded systems.

The project follows the philosophy of:

register-level peripheral access
clear abstraction layers
reusable driver APIs
practical embedded examples
learning-first firmware development
Overview
The STM32L476 series is a power-efficient MCU family from STMicroelectronics, commonly used in IoT, sensor, battery-powered, and industrial applications. This repository focuses on building custom peripheral drivers for the STM32L476 using direct register access and structured C APIs.

This project is useful for:

learning how STM32 peripherals are initialized
understanding register maps and bitfields
writing firmware without depending entirely on HAL
creating custom driver layers for real projects
improving embedded software architecture
Features
This driver stack is designed to cover the common embedded development workflow, including:

MCU clock configuration
GPIO driver
UART communication
SPI communication
I2C communication
Timers and delays
ADC drivers
DMA support concepts
interrupt-based peripheral handling
reusable peripheral headers and source files
example applications for each major peripheral
The implementation is intentionally straightforward so you can read the code, understand the hardware behavior, and extend it easily.

Project Goals
This repository aims to demonstrate a gradual build-up from:

Bare-metal register definitions
Low-level peripheral configuration
Driver abstraction layers
Controlled application-level APIs
Example firmware using the drivers
In other words, it is not just a collection of functions; it is a practical reference for how drivers are structured in embedded C.

Supported MCU
The project targets STM32L476xx family devices, especially:

STM32L476RG
STM32L476VG
STM32L476JG
other STM32L476 derivatives with compatible peripheral blocks
If you are using a different STM32 family, much of the structure and approach will still apply, but the device-specific headers and register addresses must be adjusted accordingly.

Repository Structure
A typical structure for this project may look like this:

STM32L476_Periph_Driver/
├── Drivers/
│   ├── Inc/
│   │   ├── stm32l476xx.h
│   │   ├── gpio_driver.h
│   │   ├── uart_driver.h
│   │   ├── spi_driver.h
│   │   ├── i2c_driver.h
│   │   ├── timer_driver.h
│   │   └── adc_driver.h
│   └── Src/
│       ├── gpio_driver.c
│       ├── uart_driver.c
│       ├── spi_driver.c
│       ├── i2c_driver.c
│       ├── timer_driver.c
│       └── adc_driver.c
├── Core/
│   ├── Inc/
│   └── Src/
├── Examples/
│   ├── led_blink/
│   ├── uart_echo/
│   ├── spi_slave/
│   └── adc_read/
├── startup/
│   └── startup_stm32l476xx.s
├── linker/
│   └── stm32l476xx.ld
├── Makefile
├── README.md
├── LICENSE
└── .gitignore
