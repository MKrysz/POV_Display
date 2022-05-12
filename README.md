
# PERSISTANCE OF VISION DISPLAY

## PRINCIPLE

The working principle of persistance of vision display is that human eye cannot process more than 12 images per second. So by turning on and off moving LEDs it is possible to create an illusion of a stationary image.

## ELECTRONICS

As the main purpose of this display is to have a fancy wall clock, one of the main concerns in electronics design was power usage. That's why I decided to use STM32L051C8 as the main MCU, due to its low power usage, high computational capabilities and my familiarity with STM's HAL interface. For driving LEDs i choose a combination of classical 74HC595 8-bit SIPO registers and current limiting resistors. For a position sensor I used a low power Hall sensor **which I had problems with, described below**.

Using the KiCad software I came up with following schematic:
![Schematic](POV_display_readme\SCH_IMG.jpg)

And PCB design:
![PCB](POV_display_readme\PCB_IMG.jpg)

After everything was soldered in, I began writing software and I couldn't get reliable data from used Hall sensor, so I was forced to change it to a combination of phototransistor with schmitt inverter trigger on propellers side and IR diode on motors side.

## MECHANICS

TODO:KAROL

## SOFTWARE

### IMAGE COMPILER

Python script used for compiling png images to a C-style array, that could be programmed into the MCU.

### FIRMWARE

Written in C using STMs CubeMx with HAL library in VSCode using Makefile toolchain. It's based around 2 independent timers, one responsible for measuring period of full rotation, the other responsible for ensuring proper timing in changing LEDs colors.

## END RESULT

