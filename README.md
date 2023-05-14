# HMI System for Corrosion Monitoring Product WEL-iPEC

This repository contains the development files for a Human Machine Interface (HMI) system designed for use with a corrosion monitoring product (iPEC-Probe). The HMI system includes a user interface with buttons connected to a microcontroller. Due to the unavailability of direct connection with the iPEC Probe, various sensors have been used to simulate data that will be displayed on the LCD screen.

## Files

The repository consists of the following files:

- **Packaging Enclosure CAD**: This folder contains CAD files for the packaging enclosure of the HMI system.

- **Board Files**: This folder contains the PCB design files for the microcontroller board.

- **HMI Code**: This folder contains the complex code that runs the HMI system.

- **Project Report**: This file is a comprehensive documented report of the entire project. It provides detailed information about the development process, implementation, and results. [Download Project Report](https://github.com/jaideepk3/EDL-HMI-System/blob/main/TUES-25_final_report.pdf)

## Project Description

### Aim
The aim of this project is to develop an HMI system that interfaces with the iPEC-Probe corrosion monitoring product. The HMI system will provide a user interface with buttons connected to a microcontroller. To simulate real-time data, sensors have been utilized instead of the actual iPEC Probe.

### Description
The project utilizes a Raspberry Pi Pico microcontroller board as the central controller for the HMI system. The microcontroller board interfaces with various buttons and an LCD screen. The buttons enable user interaction with the LCD screen, while the microcontroller controls the display based on the button inputs.

The HMI system displays real-time measurements obtained from various sensors, including the distance traveled from the scanning start point, rebar depth, rebar size, and other parameters. This provides users with an overview of the concrete structure's condition, enabling informed decision-making. The simulated values from the sensors facilitate comprehensive testing of the HMI system.

## Getting Started

To get started with the HMI system development, follow these steps:

1. Clone this repository to your local machine.
2. Navigate to the respective folders to access the CAD files, board design files, and HMI code.
3. Refer to the documentation provided in the report for further instructions.

## Additional Resources

- **Demo Video**: Watch a breadboard circuit demonstration of the HMI system in action. [Watch Demo Video](https://drive.google.com/file/d/1d6G7GhgJb7exQOc0swpD6kvzHQxaDGIW/view?usp=drivesdk)

- **Final Presentation**: Access the final presentation video for a detailed overview of the project. [View Final Presentation](https://drive.google.com/file/d/1m0dKYORe6IZ8-cWrcGXbmrLrGEMQUf9Z/view?usp=share_link)
