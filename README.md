## STM32L476 Peripheral Driver
A lightweight, portable, and educational peripheral driver library for STM32L476-based microcontrollers, written in C from the ground up.

This repository is intended to help you understand how STM32 peripherals work at the register level, how drivers are layered from low-level access to higher-level abstractions, and how to build clean, reusable firmware for embedded systems.

## Overview
The STM32L476 series is a power-efficient MCU family from STMicroelectronics, commonly used in IoT, sensor, battery-powered, and industrial applications. This repository focuses on building custom peripheral drivers for the STM32L476 using direct register access and structured C APIs.



## Project Goals
``
This repository aims to demonstrate a gradual build-up from:
``

Bare-metal register definitions
Low-level peripheral configuration
Driver abstraction layers
Controlled application-level APIs
Example firmware using the drivers
In other words, it is not just a collection of functions; it is a practical reference for how drivers are structured in embedded C.

## Supported MCU
The project targets STM32L476xx family devices, especially:
