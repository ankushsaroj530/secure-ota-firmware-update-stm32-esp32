# Secure OTA Firmware Update Framework for STM32 Using ESP32

### Design and Development of a Secure Internet-Based OTA Firmware Update Framework for STM32 Embedded Systems

![STM32](https://img.shields.io/badge/STM32-Blue-blue)
![ESP32](https://img.shields.io/badge/ESP32-WiFi-green)
![PlatformIO](https://img.shields.io/badge/PlatformIO-ESP32-orange)
![Python](https://img.shields.io/badge/Python-Flask-yellow)
![Render](https://img.shields.io/badge/Cloud-Render-purple)
![License](https://img.shields.io/badge/License-MIT-red)

---

# Project Overview

This project presents a **Secure Embedded Firmware Management and Internet-Based Over-the-Air (OTA) Update Framework** for STM32 microcontrollers using an ESP32 Wi-Fi Gateway.

The framework enables firmware updates remotely over the Internet without requiring physical access to embedded devices or programming tools such as ST-Link after deployment.

The system integrates a **custom STM32 UART bootloader**, an **ESP32 Wi-Fi gateway**, a **Flask-based cloud server deployed on Render**, and a **real-time web dashboard** for monitoring OTA operations, firmware versions, update progress, security verification, and device status.

Unlike conventional OTA systems that operate only within a local network, this implementation supports firmware updates across **different Wi-Fi networks**, allowing firmware to be updated securely from anywhere with Internet connectivity.

---

# Motivation

Firmware updates are essential throughout the lifecycle of embedded systems.

Traditional firmware update methods require:

- USB Connection
- ST-Link Programmer
- Manual Installation
- Physical Access to the Device

These approaches become inefficient and costly when managing large-scale IoT deployments.

This project solves these limitations by implementing a secure cloud-based OTA firmware update system.

---

# Key Features

## OTA Firmware Management

- Internet-Based OTA Updates
- Remote Firmware Updates
- Automatic Version Checking
- Manual Update Trigger
- OTA Progress Monitoring
- Cloud-Based Firmware Repository

## Bootloader

- Custom STM32 UART Bootloader
- Flash Memory Programming
- Memory Mapping
- Application Jump
- Firmware Header Parsing
- Recovery Support

## Security

- CRC32 Firmware Verification
- SHA-256 Integrity Verification
- Authentication Token Validation
- Firmware Version Validation

## Dashboard

- Real-Time OTA Status
- Device Information
- Firmware Information
- Event Logging
- Device Location
- Real-Time Date & Time
- Firmware Integrity Information
- OTA Progress Monitoring

## Cloud

- Flask REST API
- Render Cloud Deployment
- Remote Firmware Repository
- Internet-Based Communication

---

# Dashboard Overview

| Dashboard | Device & Firmware |
|-----------|-------------------|
| ![Dashboard](Web_1.png) | ![Device & Firmware](Web_2.png) |

### OTA Status

| OTA Success | Device Status |
|-------------|---------------|
| ![OTA Success](OTA_Img_1.png) | ![Device Status](OTA_Img_2.png) |

### Monitoring & Logs

| Event Log | STM32 Monitoring |
|-----------|------------------|
| ![Event Log](Web_3.png) | ![STM32 Monitoring](OTA_Img_3.png) |

---

# System Architecture

```text
                           Developer
                                │
                                │ Upload Firmware
                                ▼
                  Flask Server (Hosted on Render)
                                │
                                ▼
                    Firmware Repository
                                │
                       HTTP / HTTPS
                                │
                                ▼
                     ESP32 Wi-Fi Gateway
                                │
                     UART Communication
                                │
                                ▼
                  STM32 Secure Bootloader
                                │
                    Flash Programming
                                │
                CRC32 & SHA-256 Verification
                                │
                                ▼
                  STM32 Application Starts
                                │
                                ▼
                Dashboard Status Updated
```

---

# OTA Workflow

```text
Firmware Upload
        │
        ▼
Flask Server
        │
        ▼
Render Cloud
        │
        ▼
ESP32 Gateway
        │
        ▼
Version Check
        │
        ▼
Download Firmware
        │
        ▼
UART Transfer
        │
        ▼
STM32 Bootloader
        │
        ▼
Flash Programming
        │
        ▼
CRC32 Verification
        │
        ▼
Application Starts
        │
        ▼
Dashboard Updated
```

---

# Hardware Used

| Hardware | Purpose |
|-----------|----------|
| STM32F103C8T6 | Target MCU |
| ESP32 DevKit V1 | Wi-Fi Gateway |
| ST-Link V2 | Initial Programming |
| FT232 USB-UART | UART Communication |
| LEDs | Status Indicators |
| Push Buttons | Recovery Mode |
| Laptop/PC | Flask Server Development |

---

# Software Stack

## Embedded

- STM32CubeIDE
- Embedded C
- STM32 HAL
- UART Bootloader
- Flash Driver

## ESP32

- PlatformIO
- Arduino Framework
- Wi-Fi
- HTTP Client
- UART Communication

## Backend

- Python
- Flask
- REST API
- JSON

## Frontend

- HTML5
- CSS3
- JavaScript

## Cloud

- Render Cloud Platform

---

# Dashboard Features

The web dashboard provides real-time monitoring and management of the OTA process.

- Device Status
- Firmware Version
- Available Firmware
- OTA Progress
- Firmware Information
- Device Location
- Current Date & Time
- Authentication Token
- CRC32 Verification
- SHA-256 Verification
- Event Logs

---

# Security Features

The OTA framework implements multiple verification mechanisms to ensure firmware authenticity and integrity.

- CRC32 Verification
- SHA-256 Integrity Verification
- Authentication Token Validation
- Firmware Version Validation
- Header Verification

---

# Remote OTA Capability

One of the key highlights of this project is its ability to perform firmware updates over the Internet.

Unlike traditional implementations that require the server and device to be connected to the same local network, this framework allows firmware updates across different Wi-Fi networks.

As long as the ESP32 has Internet connectivity, firmware can be securely downloaded from the Render-hosted Flask server.

---

# Event Logging

The dashboard maintains real-time event logs during every OTA operation.

Typical events include:

- Checking Server
- Checking STM32
- Firmware Available
- Download Started
- Download Completed
- Flash Programming
- CRC Verification
- OTA Success
- OTA Failed

---

# Technologies Used

- STM32
- ESP32
- Embedded C
- Python
- Flask
- HTML
- CSS
- JavaScript
- UART
- HTTP
- JSON
- PlatformIO
- STM32CubeIDE
- Render
- Git
- GitHub

---

# Results

The proposed framework successfully demonstrates:

- Secure Internet-Based OTA Updates
- Remote Firmware Updates Across Different Wi-Fi Networks
- Automatic Firmware Version Management
- Reliable UART Firmware Transfer
- Flash Programming using Custom Bootloader
- CRC32 and SHA-256 Firmware Verification
- Real-Time Dashboard Monitoring
- Cloud-Based Firmware Repository
- Successful Firmware Deployment Without Physical Access

---

# Future Enhancements

- Digital Signature Verification
- Raspberry Pi Edge Server
- Secure Device Provisioning
- Certificate-Based Authentication
- Cloud Database Integration
- Mobile Application
- Batch Device Update Scheduling
- OTA Analytics Dashboard

---

# Installation

## Clone Repository

```bash
git clone https://github.com/your-username/secure-ota-firmware-update-stm32-esp32.git
```

## STM32

- Import Bootloader Project
- Build
- Flash using ST-Link

## ESP32

- Open PlatformIO
- Configure Wi-Fi Credentials
- Build
- Upload Firmware

## Flask Server

```bash
cd Flask_Server
pip install -r requirements.txt
python app.py
```

Or deploy using **Render**.

---

# Project Structure

```text
Secure_OTA_Firmware_System
│
├── STM32_Bootloader
├── STM32_Application
├── ESP32_Gateway
├── Flask_Server
├── Dashboard
├── Firmware
├── Documentation
├── Images
├── README.md
└── LICENSE
```

---

# Author

**Ankush Saroj**

B.Tech – Electronics and Communication Engineering

Embedded Systems | IoT | Firmware Development

GitHub: https://github.com/your-username

LinkedIn: https://linkedin.com/in/your-profile

---

# License

This project is licensed under the MIT License.

See the LICENSE file for more details.
