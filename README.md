# Secure OTA Firmware Update Framework for STM32 Using ESP32

### Design and Development of a Secure Internet-Based OTA Firmware Update Framework for STM32 Embedded Systems

![STM32](https://img.shields.io/badge/STM32-Blue-blue)
![ESP32](https://img.shields.io/badge/ESP32-WiFi-green)
![Python](https://img.shields.io/badge/Python-Flask-yellow)
![PlatformIO](https://img.shields.io/badge/PlatformIO-ESP32-orange)
![License](https://img.shields.io/badge/License-MIT-red)

---

# 📑 Table of Contents

1. 📸 Web Dashboard
2. 📖 Project Overview
3. ❓ Why This Project?
4. ✨ Key Features
5. 🏗️ System Architecture
6. 🔄 OTA Workflow
7. 📂 Project Architecture
8. 🛠️ Hardware Requirements
9. 💻 Software Requirements
10. 📊 Dashboard Features
11. 🔒 Security Features
12. 🌍 Remote OTA Firmware Updates
13. 📜 Event Logging
14. 💻 Technologies Used
15. 🚀 Future Improvements
16. 📈 Results
17. 🎥 Project Demonstration
18. ⚙️ Installation Guide
19. 📂 Folder Structure
20. 🏷️ GitHub Topics
21. 📄 License
22. 👨‍💻 Author
23. ⭐ Support

---

# 1. 📸 Web Dashboard

...
The Secure OTA Firmware Update Framework includes a modern web-based dashboard that provides real-time monitoring and management of the entire firmware update process. The dashboard enables users to monitor device status, firmware versions, update progress, security verification, and event logs from any location with Internet access.

## Dashboard Overview

| Dashboard | Device & Firmware |
|-----------|-------------------|
| ![](Web_1.png) | ![](Web_2.png) |

## OTA Update Status

| OTA Success | Device Status |
|-------------|---------------|
| ![](OTA_Img_1.png) | ![](OTA_Img_2.png) |

## Event Logs & Monitoring

| Event Logs | STM32 Monitoring |
|------------|------------------|
| ![](Web_3.png) | ![](OTA_Img_3.png) |

---

## Dashboard Features

The dashboard provides comprehensive monitoring of the OTA update system, including:

- 📡 Real-time STM32 device monitoring
- 🌐 ESP32 Wi-Fi connection status
- 📦 Current firmware version
- ⬆️ Latest available firmware version
- 🔄 Live OTA update progress
- 📜 Real-time event logging
- 📍 Device location tracking
- 🕒 Current date and time synchronization
- 🔐 Authentication token verification status
- ✅ CRC32 integrity verification result
- 🔒 SHA-256 firmware hash verification
- 📊 Firmware size and metadata information
- 📶 Network connectivity status
- ⚡ Firmware update completion status
- 🚨 Error and warning notifications

---

## Dashboard Highlights

- **Live Device Monitoring:** Monitor the STM32 device status in real time.
- **Firmware Management:** View installed firmware version and available updates.
- **OTA Progress Tracking:** Observe firmware download, transfer, verification, and installation progress.
- **Security Verification:** Display CRC32, SHA-256, and authentication verification results.
- **Event Logging:** Record every significant system event for debugging and analysis.
- **Cloud Connectivity:** Monitor communication between the ESP32 gateway and the cloud-hosted Flask server.
- **Device Information:** Display firmware details, network status, and update history in one interface.

The dashboard acts as the central monitoring interface for the Secure OTA Firmware Update Framework, providing complete visibility into firmware deployment, device health, and system security.

---

# 2. 📖 Project Overview

## Overview

The **Secure OTA Firmware Update Framework for STM32 Using ESP32** is a complete embedded firmware management solution designed to perform **secure Internet-based Over-the-Air (OTA) firmware updates** for STM32 microcontrollers. The framework eliminates the need for physical access to embedded devices after deployment, enabling firmware upgrades from anywhere in the world through a cloud-connected infrastructure.

The system integrates a **custom STM32 UART bootloader**, an **ESP32 Wi-Fi gateway**, a **Flask REST API server**, and a **real-time web dashboard** to create a reliable, scalable, and secure OTA ecosystem suitable for modern IoT and embedded applications.

Unlike traditional firmware update methods that require a USB connection, ST-Link programmer, or on-site maintenance, this framework allows firmware images to be uploaded to a cloud server and securely delivered to remote embedded devices over the Internet.

---

## Project Objectives

The primary objectives of this project are:

- Design and develop a custom UART bootloader for STM32 microcontrollers.
- Enable secure Internet-based firmware updates using an ESP32 Wi-Fi gateway.
- Implement firmware integrity verification using CRC32 and SHA-256.
- Prevent unauthorized firmware installation using authentication tokens.
- Manage firmware versions to avoid accidental downgrades.
- Provide a real-time monitoring dashboard for OTA operations.
- Create a cloud-based firmware distribution server using Flask and Render.
- Develop a scalable architecture suitable for IoT deployments.

---

## System Overview

The framework consists of four major components that work together to perform secure OTA firmware updates.

### 1. STM32 Secure Bootloader

The STM32 bootloader is responsible for:

- Receiving firmware packets from the ESP32 over UART.
- Erasing application flash memory.
- Programming the new firmware into internal flash.
- Verifying firmware integrity.
- Authenticating firmware before installation.
- Jumping safely to the application after a successful update.

The bootloader is completely custom-developed and serves as the foundation of the OTA update process.

---

### 2. ESP32 Wi-Fi Gateway

The ESP32 acts as the communication bridge between the cloud server and the STM32.

Its responsibilities include:

- Connecting to available Wi-Fi networks.
- Communicating with the Flask server through HTTP requests.
- Checking the latest firmware version.
- Downloading firmware files from the cloud.
- Sending firmware packets to the STM32 using UART.
- Monitoring update progress.
- Reporting update status back to the dashboard.

Because the ESP32 communicates through the Internet, firmware updates can be performed even when the embedded device is located in a completely different city or country.

---

### 3. Flask Cloud Server

The Flask server functions as the firmware management backend.

Its responsibilities include:

- Hosting firmware binaries.
- Managing firmware versions.
- Providing REST APIs.
- Delivering firmware metadata.
- Serving firmware download requests.
- Logging update activities.

The server is deployed on **Render Cloud**, making it accessible over the Internet without requiring local hosting.

---

### 4. Web Dashboard

A responsive web dashboard provides real-time visualization of the OTA update process.

The dashboard displays:

- Device Status
- Firmware Version
- OTA Progress
- Download Status
- Verification Results
- Device Location
- Event Logs
- Current Date & Time
- Authentication Status
- Firmware Information

The dashboard enables users to monitor every stage of the firmware update process from a web browser.

---

## Firmware Update Process

The complete OTA workflow consists of the following stages:

1. Developer uploads a new firmware binary to the Flask server.
2. The firmware version and metadata are stored.
3. ESP32 periodically checks the server for new firmware.
4. The server compares installed and available firmware versions.
5. If an update is available, the ESP32 downloads the firmware.
6. The firmware is transferred to the STM32 bootloader through UART.
7. The bootloader erases the application flash memory.
8. The new firmware is programmed into flash.
9. CRC32 verification is performed.
10. SHA-256 verification is completed.
11. Authentication token is validated.
12. The firmware version is updated.
13. The STM32 boots into the new application.
14. The dashboard displays a successful OTA update.

---

## Security Mechanisms

Security is one of the major objectives of this framework.

The project implements multiple layers of protection including:

- CRC32 firmware verification
- SHA-256 hash verification
- Authentication token validation
- Firmware version management
- Device identification
- Flash memory verification
- Bootloader integrity checks

These mechanisms ensure that corrupted, unauthorized, or outdated firmware cannot be installed on the device.

---

## Key Advantages

Compared with traditional firmware update methods, this framework offers several advantages.

### Remote Firmware Updates

Firmware can be updated securely over the Internet without requiring physical access to the device.

### Cloud-Based Deployment

Firmware is hosted on a cloud server, allowing devices to receive updates from anywhere.

### Enhanced Security

Multiple verification mechanisms protect against corrupted or unauthorized firmware.

### Version Management

The system prevents firmware downgrade and ensures only valid firmware versions are installed.

### Real-Time Monitoring

A modern dashboard provides complete visibility into the firmware update process.

### Scalability

The architecture can support multiple embedded devices connected through different Wi-Fi networks, making it suitable for IoT deployments.

---

## Applications

This framework can be applied to various embedded and IoT systems, including:

- Industrial Automation
- Smart Home Devices
- Remote Sensor Networks
- Agriculture Monitoring Systems
- Medical Devices
- Energy Management Systems
- Automotive Electronics
- Environmental Monitoring
- Smart City Infrastructure
- Consumer IoT Products

---

## Summary

The Secure OTA Firmware Update Framework demonstrates a complete end-to-end solution for remote firmware management in embedded systems.

By integrating STM32, ESP32, Flask, Render Cloud, and a real-time web dashboard, the project provides a secure, reliable, and scalable OTA ecosystem capable of supporting modern embedded and IoT applications.

The framework not only simplifies firmware deployment but also enhances security, maintainability, and operational efficiency, making it suitable for both academic research and real-world industrial applications.

...

---

# 3. ❓ Why This Project?

## Background

Modern embedded systems and Internet of Things (IoT) devices are deployed in a wide range of applications such as industrial automation, healthcare, smart homes, agriculture, transportation, and environmental monitoring. These devices often require firmware updates to introduce new features, improve performance, fix software bugs, or address security vulnerabilities.

Traditionally, updating firmware on embedded devices requires physical access to the hardware. This process usually involves connecting the device to a computer using a USB cable or programming interface such as ST-Link, manually flashing the firmware, and restarting the device. While this approach is manageable for development, it becomes highly inefficient and expensive when hundreds or thousands of devices are deployed across different geographical locations.

As IoT deployments continue to grow, there is an increasing demand for secure, scalable, and remotely manageable firmware update systems. This project was developed to address these challenges by providing a secure Internet-based OTA firmware update framework for STM32 microcontrollers using an ESP32 Wi-Fi gateway.

---

## Problem Statement

Traditional firmware update methods present several limitations that make large-scale device management difficult.

### Conventional Firmware Update Process

```text
Developer

      │

Compile Firmware

      │

USB Cable / ST-Link

      │

Connect to Device

      │

Flash Firmware

      │

Restart Device

      │

Repeat for Every Device
```

For a single embedded system, this process is straightforward. However, when hundreds or thousands of devices are deployed, firmware maintenance becomes time-consuming, expensive, and impractical.

---

## Challenges with Traditional Firmware Updates

### 🔌 Physical Access Required

Most embedded systems require direct physical access for firmware updates. Devices installed in remote or inaccessible locations cannot be updated conveniently.

---

### 🔧 Dependence on External Programmers

Firmware flashing typically requires hardware programmers such as:

- ST-Link
- J-Link
- USB-UART adapters

This increases maintenance complexity and operational costs.

---

### ⏱️ Time-Consuming Maintenance

Every firmware update requires manual intervention, including:

- Connecting programming hardware
- Flashing firmware
- Verifying installation
- Restarting the device

Repeating this process across multiple devices significantly increases maintenance time.

---

### 🌍 Remote Devices Cannot Be Updated Easily

Devices deployed in different cities or countries often require technicians to travel to the installation site simply to update firmware.

This results in:

- Increased travel costs
- Longer maintenance windows
- Device downtime
- Reduced operational efficiency

---

### 📈 Poor Scalability

Traditional firmware update methods do not scale well for large IoT deployments.

For example:

- 10 devices → manageable
- 100 devices → difficult
- 1,000 devices → impractical
- 10,000 devices → impossible without automation

---

### 🔒 Limited Security

Many conventional firmware update systems lack robust security mechanisms such as:

- Firmware integrity verification
- Authentication
- Version validation
- Protection against corrupted firmware
- Downgrade prevention

This increases the risk of installing damaged or unauthorized firmware.

---

## Proposed Solution

This project introduces a secure Internet-based OTA firmware update framework capable of remotely updating STM32 microcontrollers through an ESP32 gateway.

Instead of requiring physical access, firmware is uploaded once to a cloud-hosted Flask server. The ESP32 periodically checks for new firmware, downloads the latest version over the Internet, and securely transfers it to the STM32 bootloader using UART communication.

The STM32 bootloader verifies the firmware using multiple security checks before programming it into flash memory.

---

## Proposed OTA Architecture

```text
Developer

      │

Upload Firmware

      │

Render Cloud Server

      │

Internet

      │

ESP32 Wi-Fi Gateway

      │

UART Communication

      │

STM32 Bootloader

      │

Flash Programming

      │

Firmware Verification

      │

STM32 Application
```

---

## Why ESP32?

The ESP32 was selected because it provides:

- Built-in Wi-Fi connectivity
- Low cost
- High processing capability
- HTTP client support
- UART communication
- Excellent compatibility with STM32
- Wide community support

The ESP32 acts as an Internet gateway between the cloud server and the STM32 microcontroller.

---

## Why a Custom STM32 Bootloader?

A custom bootloader provides complete control over the firmware update process.

Its responsibilities include:

- Receiving firmware packets
- Flash memory programming
- Firmware validation
- CRC32 verification
- SHA-256 verification
- Authentication token validation
- Firmware version management
- Safe application startup

Unlike vendor-provided bootloaders, a custom bootloader allows security features and update logic to be fully customized for the application.

---

## Why Render Cloud?

Render was chosen because it offers:

- Free cloud hosting
- Easy deployment
- Public HTTPS endpoints
- Automatic deployment
- High availability
- Simple Flask integration

Hosting the firmware server on Render allows devices connected to different Wi-Fi networks to access updates from anywhere with an Internet connection.

---

## Why Security Matters

Firmware updates are one of the most critical operations in embedded systems. Installing corrupted or unauthorized firmware can render a device unusable or introduce security vulnerabilities.

To address these concerns, this project incorporates multiple layers of protection:

- CRC32 verification
- SHA-256 hash verification
- Authentication token validation
- Firmware version management
- Device identification
- Flash integrity verification

These mechanisms ensure that only authentic and verified firmware is installed on the STM32 device.

---

## Key Benefits

This OTA framework provides several significant advantages over traditional firmware update methods.

### 🌍 Internet-Based Firmware Updates

Firmware can be updated remotely without requiring the developer to be physically present.

---

### ⚡ Faster Deployment

A single firmware upload can be distributed to multiple devices without manual intervention.

---

### 🔒 Enhanced Security

Multiple verification mechanisms ensure firmware authenticity and integrity before installation.

---

### 📊 Real-Time Monitoring

A web dashboard provides live monitoring of:

- Device status
- Firmware version
- OTA progress
- Event logs
- Security verification
- Device location

---

### 💰 Reduced Maintenance Cost

Remote firmware updates eliminate the need for repeated site visits, reducing maintenance costs and improving operational efficiency.

---

### 📈 Scalable Architecture

The framework is designed to support multiple embedded devices distributed across different geographical locations, making it suitable for IoT and industrial deployments.

---

## Target Applications

The Secure OTA Firmware Update Framework can be used in various real-world applications, including:

- Smart Home Automation
- Industrial IoT
- Agricultural Monitoring Systems
- Medical Devices
- Environmental Monitoring
- Smart Energy Management
- Automotive Embedded Systems
- Remote Sensor Networks
- Consumer Electronics
- Smart City Infrastructure

---

## Conclusion

The Secure OTA Firmware Update Framework addresses the limitations of traditional firmware update methods by enabling secure, reliable, and Internet-based firmware deployment for STM32 embedded systems.

By combining a custom STM32 bootloader, ESP32 Wi-Fi gateway, Flask cloud server, and real-time monitoring dashboard, the framework provides a complete end-to-end OTA solution that improves maintainability, enhances security, reduces operational costs, and supports scalable deployment across geographically distributed embedded devices.

...

---

# 4. ✨ Key Features

The **Secure OTA Firmware Update Framework** integrates embedded firmware management, cloud communication, security mechanisms, and a real-time monitoring dashboard into a single solution. The framework has been designed to provide reliable, scalable, and secure firmware updates for STM32-based embedded systems over the Internet.

The project is divided into several functional modules, each responsible for a specific part of the OTA update process.

---

## 4.1 Secure OTA Firmware Update

The core functionality of the project is the ability to perform secure firmware updates remotely without requiring physical access to the embedded device.

### Features

- Internet-based OTA firmware updates
- Remote firmware updates from anywhere
- Automatic firmware version checking
- Manual firmware update trigger
- Firmware download over Wi-Fi
- Secure firmware transfer using UART
- Real-time OTA progress monitoring
- Automatic application restart after successful update

### Benefits

- Eliminates USB-based firmware flashing
- No ST-Link required after deployment
- Supports geographically distributed devices
- Faster maintenance and deployment
- Reduced operational cost

---

## 4.2 Custom STM32 UART Bootloader

A custom bootloader has been developed specifically for the STM32F103C8T6 microcontroller.

The bootloader is responsible for safely receiving, validating, and installing new firmware into the application memory.

### Bootloader Features

- Custom UART Bootloader
- Firmware Packet Reception
- Flash Memory Erase
- Flash Programming
- Flash Verification
- Vector Table Relocation
- Application Jump
- Recovery Mode
- Boot Decision Logic

### Bootloader Workflow

```text
Power ON
     │
     ▼
Bootloader Starts
     │
     ▼
Check Update Request
     │
 ┌───┴────┐
 │        │
 │Yes     │No
 │        │
 ▼        ▼
Receive   Jump to
Firmware  Application
 │
 ▼
Erase Flash
 │
 ▼
Program Flash
 │
 ▼
Verify Firmware
 │
 ▼
Jump to Application
```

---

## 4.3 ESP32 Wi-Fi Gateway

The ESP32 acts as the communication bridge between the Internet and the STM32 microcontroller.

It periodically checks the cloud server for new firmware versions and downloads firmware whenever an update is available.

### ESP32 Features

- Wi-Fi Connectivity
- HTTP Client
- Firmware Download
- UART Communication
- OTA Manager
- Version Comparison
- Progress Reporting
- Dashboard Communication
- Automatic Reconnection
- Error Handling

### ESP32 Responsibilities

- Connect to Wi-Fi
- Connect to Flask Server
- Check Firmware Version
- Download Firmware
- Transfer Firmware to STM32
- Monitor OTA Progress
- Update Dashboard

---

## 4.4 Cloud-Based Firmware Server

The project uses a Flask REST API deployed on **Render Cloud** for firmware hosting and version management.

### Server Features

- REST API
- Firmware Upload
- Firmware Storage
- Firmware Version Management
- JSON Responses
- HTTP Download Service
- Cloud Deployment
- Device Communication

### Server APIs

| API | Description |
|------|-------------|
| `/api/version` | Returns latest firmware version |
| `/api/download` | Downloads firmware binary |
| `/api/upload` | Upload new firmware |
| `/api/device` | Device status |
| `/api/logs` | OTA event logs |

---

## 4.5 Firmware Version Management

The framework maintains firmware version information to ensure devices always receive the correct firmware update.

### Version Management Features

- Installed Firmware Version
- Latest Server Version
- Automatic Version Comparison
- Downgrade Prevention
- Version Validation
- Firmware Metadata Storage

### Example

```text
Installed Version : 2

Latest Version : 3

Result

↓

New Firmware Available

↓

Download Firmware

↓

Install Firmware
```

---

## 4.6 Firmware Verification

Before installing any firmware, the bootloader performs multiple verification steps to ensure data integrity.

### Verification Steps

- Firmware Header Validation
- Firmware Size Verification
- CRC32 Verification
- SHA-256 Verification
- Flash Verification
- Authentication Token Validation

These checks prevent corrupted or modified firmware from being installed.

---

## 4.7 Security Features

Security is one of the primary objectives of this project.

Multiple protection mechanisms have been implemented to ensure secure firmware deployment.

### Security Mechanisms

- CRC32 Integrity Verification
- SHA-256 Hash Verification
- Authentication Token Validation
- Device Identification
- Firmware Version Validation
- Secure Boot Decision
- Flash Integrity Check

### Security Workflow

```text
Firmware Received
        │
        ▼
Header Verification
        │
        ▼
CRC32 Verification
        │
        ▼
SHA-256 Verification
        │
        ▼
Authentication Token
        │
        ▼
Version Check
        │
        ▼
Install Firmware
```

---

## 4.8 Real-Time Web Dashboard

A responsive dashboard has been developed to visualize the OTA process.

The dashboard provides complete monitoring of the embedded device.

### Dashboard Features

- Live Device Status
- Firmware Version
- Latest Firmware
- OTA Progress
- Event Logs
- Device Location
- Date & Time
- Security Status
- Firmware Information
- Network Status
- Authentication Status

### Dashboard Screens

| Dashboard | Device Information |
|-----------|--------------------|
| ![](Web_1.png) | ![](Web_2.png) |

| OTA Success | Monitoring |
|-------------|------------|
| ![](OTA_Img_1.png) | ![](OTA_Img_2.png) |

| Event Logs | STM32 Status |
|------------|--------------|
| ![](Web_3.png) | ![](OTA_Img_3.png) |

---

## 4.9 Event Logging System

The framework records every important event occurring during the OTA process.

### Logged Events

- System Boot
- Wi-Fi Connected
- STM32 Connected
- Server Connected
- Firmware Version Check
- Firmware Download Started
- Firmware Download Completed
- Flash Programming
- CRC Verification
- SHA-256 Verification
- Authentication Passed
- OTA Successful
- Device Restart

The event logs are displayed on the dashboard for monitoring and debugging.

---

## 4.10 Remote Firmware Deployment

Unlike conventional OTA systems that only work within the same local network, this framework supports firmware deployment across different Internet-connected networks.

### Remote Deployment Architecture

```text
Developer

      │

Upload Firmware

      │

Render Cloud

      │

Internet

      │

ESP32 Gateway

      │

UART

      │

STM32 Bootloader

      │

STM32 Application
```

This enables firmware updates regardless of the geographical location of the embedded device.

---

## 4.11 Advantages of the Framework

- Internet-based OTA firmware updates
- Custom STM32 bootloader
- ESP32 Wi-Fi gateway
- Cloud-hosted firmware server
- Secure firmware verification
- Automatic version management
- Authentication token validation
- Real-time dashboard monitoring
- Remote firmware deployment
- Device location monitoring
- Event logging
- Scalable IoT architecture
- Easy firmware maintenance
- Reduced deployment cost
- Industrial-ready design

---

## Feature Summary

| Module | Capability |
|---------|------------|
| STM32 Bootloader | Flash Programming & Boot Management |
| ESP32 Gateway | Wi-Fi & Internet Communication |
| Flask Server | Firmware Hosting & REST APIs |
| Render Cloud | Global Firmware Distribution |
| Dashboard | Real-Time Monitoring |
| Security | CRC32, SHA-256 & Authentication |
| Firmware Manager | Version Control |
| OTA Engine | Remote Firmware Updates |
| Event Logger | Live System Logs |
| Device Monitor | Status, Location & Time |

...

---

# 5. 🏗️ System Architecture

The Secure OTA Firmware Update Framework is designed using a modular architecture that separates the embedded system, communication gateway, cloud backend, and monitoring dashboard into independent components. This modular approach improves scalability, maintainability, and reliability while enabling secure Internet-based firmware updates.

The complete architecture consists of five major layers:

1. Developer Layer
2. Cloud Layer
3. Communication Layer
4. Embedded Layer
5. Monitoring Layer

Together, these layers provide an end-to-end firmware management solution capable of securely updating STM32 microcontrollers from any location with Internet connectivity.

---

## 5.1 Overall System Architecture

```text
                               Developer
                                   │
                                   │ Upload Firmware (.bin)
                                   ▼
                   ┌─────────────────────────────────┐
                   │      Flask REST API Server       │
                   │        (Render Cloud)            │
                   └─────────────────────────────────┘
                                   │
                          HTTP / JSON Communication
                                   │
                                   ▼
                     Firmware Storage & Metadata
                                   │
                                   ▼
                        ESP32 Wi-Fi Gateway
                 (OTA Manager + HTTP Client + UART)
                                   │
                          UART Communication
                                   │
                                   ▼
                 STM32 Secure UART Bootloader
                                   │
                     Flash Memory Programming
                                   │
                    Firmware Verification
         (CRC32 + SHA-256 + Authentication)
                                   │
                                   ▼
                    STM32 Application Firmware
                                   │
                                   ▼
                  Web Dashboard & Event Logs
```

---

# 5.2 Architecture Components

The OTA framework consists of several interconnected modules, each responsible for a specific function during the firmware update process.

---

## 1. Developer Layer

The developer is responsible for creating, compiling, and publishing new firmware versions.

### Responsibilities

- Develop application firmware
- Build binary (.bin) file
- Upload firmware to the server
- Assign firmware version
- Monitor deployment progress

### Development Tools

- STM32CubeIDE
- PlatformIO
- VS Code
- Git
- GitHub

---

## 2. Cloud Layer

The cloud layer hosts firmware images and manages communication between remote devices and the firmware repository.

The Flask REST API is deployed on Render Cloud, making it accessible over the Internet.

### Responsibilities

- Firmware Upload
- Firmware Storage
- Firmware Version Management
- REST APIs
- JSON Responses
- Firmware Download Service
- Device Communication

### Cloud Components

```text
Flask Server

│

├── Firmware Repository

├── Version Database

├── REST APIs

├── Event Logs

└── JSON Services
```

---

## 3. Communication Layer

The communication layer enables secure data transfer between the cloud server and the STM32 microcontroller.

The ESP32 serves as a communication gateway by connecting to Wi-Fi, downloading firmware from the cloud, and transferring it to the STM32 over UART.

### Responsibilities

- Connect to Wi-Fi
- Connect to Flask Server
- HTTP Communication
- Firmware Download
- UART Communication
- OTA Progress Monitoring
- Error Handling

### Communication Flow

```text
Render Cloud

↓

HTTP Request

↓

ESP32

↓

UART

↓

STM32
```

---

## 4. Embedded Layer

The embedded layer consists of two software components:

- STM32 Bootloader
- STM32 Application

---

### STM32 Bootloader

The bootloader is responsible for receiving firmware updates and safely programming them into internal flash memory.

### Bootloader Responsibilities

- Receive firmware packets
- Validate firmware header
- Erase application memory
- Program flash memory
- Verify firmware integrity
- Authenticate firmware
- Jump to application

---

### STM32 Application

The application contains the primary embedded software executed after a successful firmware update.

Responsibilities include:

- Normal application execution
- Device functionality
- Sensor processing
- Peripheral management
- Communication services

---

## 5. Monitoring Layer

The monitoring layer provides complete visibility into the OTA update process through a responsive web dashboard.

The dashboard continuously displays:

- Device Status
- Firmware Version
- Latest Firmware
- OTA Progress
- Event Logs
- Device Location
- Current Date & Time
- Verification Results
- Update History

---

# 5.3 Component Interaction

The following sequence illustrates how different modules interact during a firmware update.

```text
Developer
     │
Upload Firmware
     │
     ▼
Flask Server
     │
Store Firmware
     │
     ▼
ESP32
     │
Check Version
     │
Download Firmware
     │
     ▼
STM32 Bootloader
     │
Program Flash
     │
Verify Firmware
     │
Jump to Application
     │
     ▼
Dashboard Updated
```

---

# 5.4 Data Flow

The OTA framework follows a structured data flow to ensure reliable firmware delivery.

```text
Firmware Binary

↓

Cloud Storage

↓

HTTP Download

↓

ESP32 Gateway

↓

UART Packets

↓

STM32 Bootloader

↓

Flash Memory

↓

Verification

↓

Application Execution
```

---

# 5.5 Security Architecture

The project incorporates multiple layers of security to protect the firmware update process.

```text
Firmware Received

        │

        ▼

Header Verification

        │

        ▼

Firmware Version Check

        │

        ▼

Authentication Token

        │

        ▼

CRC32 Verification

        │

        ▼

SHA-256 Verification

        │

        ▼

Flash Programming

        │

        ▼

Application Launch
```

Each verification stage must pass before the firmware is accepted and executed.

---

# 5.6 Communication Protocol

The communication between the ESP32 gateway and the STM32 bootloader is based on UART.

### Protocol Features

- Command-based communication
- Packetized firmware transfer
- ACK/NACK response mechanism
- Error detection
- Timeout handling
- Retry mechanism
- Firmware metadata transfer

Typical commands include:

- Firmware Update Request
- Firmware Header Transfer
- Firmware Packet Transfer
- Version Request
- CRC Verification
- Authentication Request
- Boot Command

---

# 5.7 System Advantages

The modular architecture offers several benefits over traditional firmware update methods.

### Reliability

- Robust firmware transfer
- Error detection
- Retry mechanisms
- Flash verification

### Security

- CRC32 integrity verification
- SHA-256 hash validation
- Authentication token verification
- Firmware version validation

### Scalability

- Supports multiple devices
- Cloud-based firmware hosting
- Internet connectivity
- Remote management

### Maintainability

- Modular software architecture
- Independent components
- Easy upgrades
- Simplified debugging

### Performance

- Fast firmware download
- Efficient UART communication
- Minimal memory usage
- Reliable flash programming

---

# 5.8 Architecture Summary

The Secure OTA Firmware Update Framework combines embedded firmware management, cloud computing, and secure communication into a unified architecture.

The interaction between the **STM32 Secure Bootloader**, **ESP32 Wi-Fi Gateway**, **Flask REST Server**, **Render Cloud**, and **Web Dashboard** provides a complete end-to-end OTA solution capable of securely deploying firmware updates to remote embedded devices over the Internet.

This modular design improves system scalability, simplifies maintenance, enhances firmware security, and provides real-time visibility into every stage of the firmware update lifecycle.

...

---

# 6. 🔄 OTA Workflow

The **Over-the-Air (OTA) Firmware Update Workflow** describes the complete process of securely delivering and installing a new firmware image on the STM32 microcontroller through the ESP32 Wi-Fi gateway. The workflow begins when the developer uploads a new firmware version to the cloud server and ends when the STM32 successfully boots into the updated application.

The OTA process has been designed to ensure **firmware integrity, authentication, version management, reliability, and fault tolerance** at every stage.

---

# 6.1 Complete OTA Workflow

```text
                    Developer
                        │
                        │
        Build New Firmware (.bin)
                        │
                        ▼
          Upload Firmware to Flask Server
                        │
                        ▼
         Firmware Stored on Render Cloud
                        │
                        ▼
      ESP32 Connects to Wi-Fi Network
                        │
                        ▼
     ESP32 Requests Latest Firmware Version
                        │
                        ▼
     Compare Installed & Server Versions
                        │
          ┌─────────────┴─────────────┐
          │                           │
     Same Version              New Version Available
          │                           │
          ▼                           ▼
     Continue Monitoring      Download Firmware
                                      │
                                      ▼
                         Verify Download Success
                                      │
                                      ▼
                    Transfer Firmware via UART
                                      │
                                      ▼
                     STM32 Bootloader Receives Data
                                      │
                                      ▼
                      Validate Firmware Header
                                      │
                                      ▼
                      Erase Application Flash
                                      │
                                      ▼
                      Program Flash Memory
                                      │
                                      ▼
                      Perform CRC32 Verification
                                      │
                                      ▼
                     Perform SHA-256 Verification
                                      │
                                      ▼
                  Validate Authentication Token
                                      │
                                      ▼
                    Update Firmware Information
                                      │
                                      ▼
                     Jump to Application Firmware
                                      │
                                      ▼
                 Dashboard Shows OTA Success
```

---

# 6.2 Step 1 – Firmware Development

The OTA process begins with firmware development.

The developer creates or modifies the STM32 application using **STM32CubeIDE**, compiles the project, and generates the application binary file (`.bin`).

### Activities

- Develop application
- Build firmware
- Generate binary
- Test firmware locally
- Prepare release version

---

# 6.3 Step 2 – Firmware Upload

After successful testing, the firmware is uploaded to the Flask server.

Along with the firmware file, metadata is also stored.

### Firmware Metadata

- Firmware Version
- Firmware Size
- CRC32
- SHA-256 Hash
- Upload Date
- Device ID
- Authentication Token

Example:

```text
Firmware Version : 3

Firmware Size : 83 KB

CRC32 : 0x6A48B3F1

SHA256 :
F3D8A5E8C4A8D1...

Upload Time :
2026-08-06
```

---

# 6.4 Step 3 – Cloud Storage

Once uploaded, the firmware is stored on the Flask server hosted on Render Cloud.

The cloud server maintains:

- Firmware Repository
- Latest Firmware Version
- Firmware Metadata
- Download Endpoint
- Device Logs

This enables remote devices to access firmware from anywhere using an Internet connection.

---

# 6.5 Step 4 – ESP32 Connects to Wi-Fi

When powered on, the ESP32 performs the following tasks:

- Initialize peripherals
- Connect to Wi-Fi
- Obtain IP Address
- Check Internet availability
- Connect to Flask Server

Example Console Output

```text
Wi-Fi Connected

IP Address:
192.168.1.105

Connecting to Server...

Server Connected
```

---

# 6.6 Step 5 – Firmware Version Check

The ESP32 periodically requests the latest firmware version from the cloud server.

Example REST API

```text
GET /api/version
```

Example Response

```json
{
  "version": 5,
  "file": "application.bin",
  "size": 84560
}
```

The ESP32 compares:

- Installed Version
- Latest Version

Decision Logic

```text
Installed Version = 4

Latest Version = 5

↓

New Firmware Available

↓

Start Download
```

If both versions are identical:

```text
Installed Version = 5

Latest Version = 5

↓

Firmware Already Up-to-Date
```

---

# 6.7 Step 6 – Firmware Download

The ESP32 downloads the firmware using HTTP.

Download Process

```text
HTTP GET Request

↓

Receive Binary Data

↓

Store into Buffer

↓

Verify Download

↓

Ready for UART Transfer
```

During download, the dashboard displays:

- Download Progress
- File Size
- Download Status
- Connection Status

---

# 6.8 Step 7 – UART Firmware Transfer

After downloading the firmware, the ESP32 transfers it to the STM32 bootloader.

Firmware is divided into multiple packets.

Example

```text
Packet 1

↓

Packet 2

↓

Packet 3

↓

...

↓

Last Packet
```

Each packet includes:

- Command
- Packet Number
- Data Length
- Firmware Data
- Checksum

The STM32 acknowledges every successfully received packet.

```text
ESP32

↓

Packet

↓

STM32

↓

ACK

↓

Next Packet
```

This ensures reliable communication.

---

# 6.9 Step 8 – Bootloader Processing

The STM32 bootloader performs the following operations:

- Receive Header
- Validate Header
- Verify Firmware Size
- Erase Flash
- Write Flash
- Verify Flash
- Store Firmware Information

The application area is erased before programming begins.

---

# 6.10 Step 9 – Firmware Verification

After programming, the bootloader verifies the firmware using multiple security checks.

### Verification Sequence

```text
Firmware Header

↓

Firmware Size

↓

CRC32 Verification

↓

SHA-256 Verification

↓

Authentication Token

↓

Version Validation

↓

Flash Verification
```

If every verification succeeds:

```text
Firmware Valid

↓

Boot Application
```

Otherwise:

```text
Firmware Invalid

↓

Abort Installation

↓

Remain in Bootloader
```

---

# 6.11 Step 10 – Firmware Information Update

After successful verification, firmware information is updated.

Stored Information

- Installed Version
- Firmware Size
- CRC32
- SHA-256
- Update Date
- Device ID

This information is used for future OTA updates.

---

# 6.12 Step 11 – Application Startup

Once verification is complete:

- Interrupts are disabled
- Vector Table is relocated
- Main Stack Pointer is updated
- Bootloader jumps to application

Execution then continues from the new firmware.

---

# 6.13 Step 12 – Dashboard Update

The dashboard immediately displays the update result.

Displayed Information

- Firmware Version
- Update Status
- Download Status
- Verification Status
- Device Status
- Event Logs
- Update Time
- Device Location

Example

```text
OTA Update Successful

Firmware Version : 5

CRC32 : PASS

SHA-256 : PASS

Authentication : PASS

Status : Online
```

---

# 6.14 Error Handling

The OTA framework includes comprehensive error handling.

Possible Errors

| Error | Action |
|--------|--------|
| Wi-Fi Disconnected | Reconnect Automatically |
| Server Offline | Retry Connection |
| Download Failed | Retry Download |
| UART Timeout | Resend Packet |
| CRC Failure | Abort Update |
| SHA-256 Failure | Reject Firmware |
| Authentication Failed | Reject Firmware |
| Flash Error | Remain in Bootloader |
| Version Mismatch | Cancel Update |

---

# 6.15 OTA Workflow Advantages

The implemented OTA workflow offers several advantages over conventional firmware update methods.

### Reliability

- Packet acknowledgment
- Retry mechanism
- Flash verification
- Error recovery

### Security

- Authentication Token
- CRC32 Verification
- SHA-256 Verification
- Version Validation

### Scalability

- Cloud-hosted firmware
- Internet-based updates
- Multiple device support

### Ease of Maintenance

- No USB connection required
- No ST-Link required after deployment
- Remote firmware deployment
- Automated update process

---

# 6.16 OTA Workflow Summary

The Secure OTA Firmware Update Framework follows a structured and secure workflow that ensures reliable firmware deployment from the developer to the target STM32 device.

By integrating **STM32**, **ESP32**, **Flask**, **Render Cloud**, and a **real-time web dashboard**, the framework enables secure Internet-based firmware updates with end-to-end verification, authentication, and monitoring.

This workflow significantly reduces maintenance effort, improves deployment efficiency, and provides a scalable solution for modern embedded and IoT applications.

...

---


# 8. 🛠️ Hardware Requirements

The Secure OTA Firmware Update Framework is built using widely available embedded development hardware. The hardware architecture consists of an **STM32F103C8T6 microcontroller** as the target device, an **ESP32 DevKit** acting as the Internet gateway, and supporting peripherals for programming, debugging, communication, and status indication.

The hardware components have been selected to provide a low-cost, scalable, and reliable platform suitable for embedded systems, IoT applications, and firmware update research.

---

# 8.1 Hardware Architecture

```text
                    +----------------------+
                    |      Developer PC    |
                    +----------+-----------+
                               |
                        USB / ST-Link
                               |
                               ▼
                    +----------------------+
                    | STM32F103C8T6 Board  |
                    |  (Target Device)     |
                    +----------+-----------+
                               ▲
                               │ UART
                               ▼
                    +----------------------+
                    |     ESP32 DevKit     |
                    |  (Wi-Fi Gateway)     |
                    +----------+-----------+
                               │
                         Wi-Fi / Internet
                               │
                               ▼
                    +----------------------+
                    |   Flask REST Server  |
                    |   (Render Cloud)     |
                    +----------------------+
```

---

# 8.2 Hardware Components

| Component | Model | Purpose |
|-----------|-------|---------|
| STM32 Development Board | STM32F103C8T6 (Blue Pill) | Target Microcontroller |
| Wi-Fi Module | ESP32 DevKit V1 | Internet Gateway |
| Programmer | ST-Link V2 | Programming & Debugging STM32 |
| USB-to-UART Converter | FT232RL | UART Communication & Debugging |
| LEDs | On-board / External LEDs | Status Indication |
| Push Buttons | Reset & Boot Button | Bootloader Recovery |
| USB Cable | Micro USB | Power & Programming |
| Breadboard | Standard | Hardware Prototyping |
| Jumper Wires | Male-Male / Male-Female | Hardware Connections |
| OLED Display *(Optional)* | SSD1306 OLED | Display Device Information |

---

# 8.3 STM32F103C8T6

The STM32F103C8T6 serves as the primary embedded controller responsible for executing the application firmware.

The custom UART bootloader resides in the lower flash memory, while the user application is stored in a separate flash region.

### Key Specifications

| Feature | Description |
|----------|-------------|
| Core | ARM Cortex-M3 |
| Maximum Clock | 72 MHz |
| Flash Memory | 64 KB (Blue Pill) |
| SRAM | 20 KB |
| Operating Voltage | 3.3 V |
| UART | USART1 |
| Flash Programming | Supported |
| Bootloader | Custom UART Bootloader |

### Responsibilities

- Execute application firmware
- Receive firmware packets
- Flash memory programming
- Firmware verification
- Boot management
- Version management

---

# 8.4 ESP32 DevKit

The ESP32 acts as the communication gateway between the cloud server and the STM32 microcontroller.

It connects to Wi-Fi, communicates with the Flask server over HTTP, downloads firmware updates, and transfers firmware to the STM32 through UART.

### Key Specifications

| Feature | Description |
|----------|-------------|
| MCU | ESP32 Dual-Core Xtensa |
| Clock Frequency | Up to 240 MHz |
| Flash Memory | 4 MB |
| SRAM | 520 KB |
| Wi-Fi | IEEE 802.11 b/g/n |
| Bluetooth | BLE + Classic |
| UART | Multiple UART Interfaces |
| Operating Voltage | 3.3 V |

### Responsibilities

- Wi-Fi connectivity
- HTTP communication
- Firmware download
- UART communication
- OTA management
- Dashboard communication
- Version checking

---

# 8.5 ST-Link V2

The ST-Link V2 programmer is used during development for programming and debugging the STM32.

After deployment, firmware updates are performed remotely, eliminating the need for the ST-Link.

### Uses

- Flash Bootloader
- Flash Initial Application
- Debug Firmware
- Memory Inspection

---

# 8.6 FT232 USB-to-UART Converter

The FT232 module provides UART communication between the computer and STM32 during debugging and development.

### Uses

- Serial Communication
- Bootloader Debugging
- Log Monitoring
- Firmware Testing

---

# 8.7 LEDs

LEDs provide visual indication of system status.

### Example Status Indicators

| LED Status | Meaning |
|------------|---------|
| Blinking | System Running |
| Fast Blink | OTA Update in Progress |
| Solid ON | OTA Success |
| OFF | System Idle |
| Alternate Blink | Error Condition |

---

# 8.8 Push Buttons

Push buttons are used for system control and recovery.

### Functions

- System Reset
- Bootloader Recovery
- Manual OTA Trigger *(Optional)*
- Factory Reset *(Future Enhancement)*

---

# 8.9 OLED Display (Optional)

An optional OLED display can be connected to provide real-time system information.

Displayed Information may include:

- Firmware Version
- Wi-Fi Status
- Device IP Address
- OTA Progress
- Update Status
- Error Messages
- Date & Time

---

# 8.10 Hardware Connections

## ESP32 ↔ STM32 UART Connection

| ESP32 Pin | STM32 Pin | Purpose |
|------------|-----------|---------|
| TX | RX (PA10) | Firmware Data Transfer |
| RX | TX (PA9) | Responses & Commands |
| GND | GND | Common Ground |

---

## Programming Connection

| Programmer | STM32 |
|-------------|-------|
| SWDIO | SWDIO |
| SWCLK | SWCLK |
| NRST | NRST |
| GND | GND |
| 3.3V | 3.3V |

---

# 8.11 Power Supply

The hardware operates from a regulated **3.3V power supply**.

Power sources may include:

- USB Power
- ST-Link
- External Adapter
- Battery Pack *(Optional)*

---

# 8.12 Hardware Operation

The complete hardware operation follows this sequence:

```text
Power ON

↓

ESP32 Connects to Wi-Fi

↓

STM32 Bootloader Starts

↓

ESP32 Checks Server

↓

Firmware Download

↓

UART Transfer

↓

STM32 Flash Programming

↓

Firmware Verification

↓

Application Starts

↓

Dashboard Updated
```

---

# 8.13 Hardware Advantages

The selected hardware platform offers several benefits:

- Low Cost Development Platform
- Easy Availability
- Wi-Fi Connectivity
- Reliable UART Communication
- Industrial-Grade STM32 MCU
- Cloud-Based OTA Support
- Easy Debugging
- Scalable Architecture
- Suitable for IoT Applications
- Supports Future Feature Expansion

---

# 8.14 Hardware Summary

| Hardware | Purpose |
|-----------|---------|
| **STM32F103C8T6** | Target Microcontroller |
| **ESP32 DevKit V1** | Wi-Fi Gateway for OTA Updates |
| **ST-Link V2** | Programming & Debugging |
| **FT232RL** | UART Communication |
| **LEDs** | System Status Indication |
| **Push Buttons** | Reset & Recovery |
| **OLED Display (Optional)** | Real-Time Device Information |
| **USB Cable** | Power & Programming |
| **Breadboard & Jumper Wires** | Hardware Interconnections |

---

The chosen hardware architecture provides a compact, cost-effective, and scalable platform for implementing secure Internet-based OTA firmware updates. The combination of the **STM32F103C8T6**, **ESP32 DevKit**, and cloud-hosted backend enables reliable remote firmware deployment while maintaining high security through firmware verification and authentication mechanisms.

...

---

# 9. 💻 Software Requirements

The **Secure OTA Firmware Update Framework** integrates multiple software technologies across embedded development, IoT communication, cloud computing, web development, and version control. Each software component plays a critical role in enabling secure Internet-based firmware updates, device communication, firmware verification, and real-time monitoring.

The software architecture is divided into five major layers:

1. Embedded Software
2. ESP32 Gateway Software
3. Backend Server Software
4. Frontend Dashboard
5. Development & Version Control Tools

Together, these components create a complete end-to-end OTA firmware update ecosystem.

---

# 9.1 Software Architecture

```text
                 Developer

                     │

        STM32CubeIDE / VS Code

                     │

                     ▼

            STM32 Application

                     │

                     ▼

        STM32 Secure Bootloader

                     ▲

                UART Protocol

                     ▼

          ESP32 Gateway Firmware

                     │

             HTTP / JSON APIs

                     ▼

        Flask REST API Server

                     │

                Render Cloud

                     │

                     ▼

            Web Dashboard
```

---

# 9.2 Embedded Software

The STM32 firmware is developed using **STM32CubeIDE** with the STM32 Hardware Abstraction Layer (HAL). The embedded software consists of two independent applications:

- STM32 Bootloader
- STM32 Application Firmware

---

## STM32 Bootloader

The bootloader is responsible for firmware updates and secure boot management.

### Features

- UART Communication
- Flash Memory Programming
- Flash Erase
- Firmware Header Parsing
- CRC32 Verification
- SHA-256 Verification
- Authentication Token Validation
- Version Management
- Boot Decision Logic
- Application Jump

### Responsibilities

- Receive firmware packets
- Validate firmware
- Program flash memory
- Verify firmware integrity
- Launch application

---

## STM32 Application

The application firmware contains the primary functionality of the embedded device.

### Responsibilities

- Execute user application
- Initialize peripherals
- Process sensors
- Handle communication
- Execute business logic

---

## Programming Language

```text
Embedded C
```

---

## Development Environment

```text
STM32CubeIDE
```

---

## Libraries

- STM32 HAL Drivers
- CMSIS
- UART Driver
- Flash Driver
- CRC Library
- SHA-256 Library

---

# 9.3 ESP32 Gateway Software

The ESP32 firmware is responsible for Internet communication and OTA management.

The firmware is developed using **PlatformIO** with the **Arduino Framework**.

---

## ESP32 Features

- Wi-Fi Connectivity
- HTTP Client
- JSON Parsing
- Firmware Download
- UART Communication
- OTA Manager
- Progress Reporting
- Dashboard Communication
- Automatic Reconnection

---

## ESP32 Modules

```text
main.cpp

↓

Wi-Fi Manager

↓

HTTP Client

↓

OTA Manager

↓

UART Protocol

↓

Logger

↓

Dashboard Communication
```

---

## Libraries Used

- WiFi.h
- HTTPClient.h
- ArduinoJson
- HardwareSerial
- SPIFFS *(Optional)*
- Preferences *(Optional)*

---

## Development Environment

```text
PlatformIO
```

---

## Programming Language

```text
C++
```

---

# 9.4 Backend Software

The backend is implemented using **Python Flask**.

It hosts firmware files, provides REST APIs, manages firmware versions, and communicates with remote ESP32 devices.

---

## Backend Features

- Firmware Upload
- Firmware Storage
- Firmware Version Management
- REST APIs
- JSON Responses
- Download Service
- Device Status
- Event Logs

---

## Flask Modules

```text
app.py

↓

Firmware Upload API

↓

Firmware Download API

↓

Version API

↓

Device API

↓

Logs API
```

---

## REST APIs

| API Endpoint | Purpose |
|--------------|---------|
| `/api/version` | Latest Firmware Version |
| `/api/download` | Download Firmware |
| `/api/upload` | Upload Firmware |
| `/api/device` | Device Status |
| `/api/logs` | Event Logs |

---

## Programming Language

```text
Python
```

---

## Framework

```text
Flask
```

---

## Libraries

- Flask
- Requests
- JSON
- OS
- Hashlib
- Datetime

---

# 9.5 Frontend Dashboard

The dashboard provides a graphical interface for monitoring the OTA firmware update process.

It displays real-time device information and update progress.

---

## Dashboard Features

- Device Status
- Firmware Version
- Latest Firmware
- OTA Progress
- Device Location
- Date & Time
- Event Logs
- Authentication Status
- CRC32 Status
- SHA-256 Status
- Network Status
- Update History

---

## Technologies

- HTML5
- CSS3
- JavaScript

---

## Screenshots

| Dashboard | Device Information |
|-----------|--------------------|
| ![](Web_1.png) | ![](Web_2.png) |

| OTA Status | Monitoring |
|------------|------------|
| ![](OTA_Img_1.png) | ![](OTA_Img_2.png) |

| Event Logs | Device Status |
|------------|---------------|
| ![](Web_3.png) | ![](OTA_Img_3.png) |

---

# 9.6 Cloud Platform

The firmware server is deployed using **Render Cloud**.

Render provides Internet accessibility for firmware distribution.

---

## Cloud Features

- Free Hosting
- Global Access
- REST API Support
- Automatic Deployment
- HTTPS Support
- High Availability

---

## Responsibilities

- Host firmware
- Serve firmware downloads
- Respond to ESP32 requests
- Store firmware metadata

---

# 9.7 Communication Technologies

The OTA framework uses multiple communication protocols.

| Technology | Purpose |
|------------|---------|
| UART | ESP32 ↔ STM32 Communication |
| HTTP | Firmware Download |
| JSON | API Communication |
| Wi-Fi | Internet Connectivity |

---

## Communication Flow

```text
Developer

↓

Flask Server

↓

HTTP

↓

ESP32

↓

UART

↓

STM32
```

---

# 9.8 Security Libraries

Security is implemented using multiple verification algorithms.

### CRC32

Purpose

- Detect transmission errors
- Verify firmware integrity

---

### SHA-256

Purpose

- Verify firmware authenticity
- Detect modification

---

### Authentication Token

Purpose

- Prevent unauthorized firmware installation

---

# 9.9 Development Tools

The project uses professional embedded development tools.

| Tool | Purpose |
|------|---------|
| STM32CubeIDE | STM32 Development |
| PlatformIO | ESP32 Development |
| VS Code | Code Editing |
| Git | Version Control |
| GitHub | Repository Hosting |
| STM32CubeProgrammer | Flash Programming |
| Postman | API Testing |
| Serial Monitor | Debugging |

---

# 9.10 Programming Languages

| Language | Usage |
|----------|-------|
| Embedded C | STM32 Firmware |
| C++ | ESP32 Gateway |
| Python | Flask Backend |
| HTML | Dashboard Structure |
| CSS | Dashboard Styling |
| JavaScript | Dashboard Logic |

---

# 9.11 Software Workflow

```text
Write Code

↓

Compile

↓

Generate Firmware

↓

Upload to Server

↓

ESP32 Downloads Firmware

↓

UART Transfer

↓

STM32 Flash Programming

↓

Verification

↓

Application Execution

↓

Dashboard Updated
```

---

# 9.12 Software Dependencies

### STM32

- STM32CubeIDE
- STM32 HAL
- CMSIS

### ESP32

- PlatformIO
- Arduino Framework
- WiFi Library
- HTTPClient
- ArduinoJson

### Backend

- Python 3.x
- Flask
- Requests

### Dashboard

- HTML5
- CSS3
- JavaScript

---

# 9.13 Software Advantages

The selected software stack offers several advantages:

- Cross-platform development
- Open-source technologies
- Cloud accessibility
- Easy maintenance
- High scalability
- Secure firmware management
- Modular architecture
- Fast deployment
- Easy debugging
- Real-time monitoring

---

# 9.14 Software Summary

| Category | Software |
|----------|----------|
| Embedded IDE | STM32CubeIDE |
| ESP32 IDE | PlatformIO |
| Code Editor | Visual Studio Code |
| Programming Languages | Embedded C, C++, Python, HTML, CSS, JavaScript |
| Backend Framework | Flask |
| Cloud Platform | Render |
| Communication | UART, HTTP, JSON |
| Version Control | Git & GitHub |
| Debugging | STM32CubeProgrammer, Serial Monitor |


...

---

# 10. 📊 Dashboard Features

The **Secure OTA Firmware Update Framework** includes a modern web-based dashboard that provides a centralized interface for monitoring, managing, and controlling the entire firmware update process. The dashboard enables developers and system administrators to visualize device information, firmware status, OTA progress, security verification results, and event logs in real time.

Unlike traditional embedded systems that rely solely on serial terminals for debugging, this dashboard offers an intuitive web interface accessible from any device connected to the Internet.

The dashboard communicates with the **Flask REST Server** to retrieve firmware information, update status, device details, and event logs, providing complete visibility into the OTA ecosystem.

---

# 10.1 Dashboard Overview

The dashboard serves as the central monitoring interface of the Secure OTA Firmware Update Framework.

It allows users to:

- Monitor connected devices
- View installed firmware version
- Check latest firmware availability
- Monitor OTA update progress
- View firmware verification results
- Display device location
- Display current date & time
- View event logs
- Monitor device connectivity
- Observe update history

---

# 10.2 Dashboard Architecture

```text
                    STM32 Device
                         │
                    UART Communication
                         │
                         ▼
                    ESP32 Gateway
                         │
                     HTTP Requests
                         │
                         ▼
                Flask REST API Server
                         │
                   JSON Responses
                         │
                         ▼
                  Web Dashboard
```

The dashboard continuously retrieves information from the Flask server and presents it through a responsive graphical interface.

---

# 10.3 Dashboard Screenshots

## Dashboard Home

| Home Dashboard | Device Information |
|---------------|--------------------|
| ![](Web_1.png) | ![](Web_2.png) |

---

## OTA Update Status

| OTA Success | Device Monitoring |
|-------------|-------------------|
| ![](OTA_Img_1.png) | ![](OTA_Img_2.png) |

---

## Event Logs

| Event Logs | STM32 Monitoring |
|------------|------------------|
| ![](Web_3.png) | ![](OTA_Img_3.png) |

---

# 10.4 Device Information Panel

The Device Information section displays the current status of the embedded device.

Displayed Information

- Device Name
- Device ID
- Device Status
- Online/Offline Status
- Wi-Fi Connection Status
- IP Address
- ESP32 Status
- STM32 Status

Example

```text
Device Name : STM32 Gateway

Device ID : STM32_001

Status : Online

ESP32 : Connected

STM32 : Connected

IP Address : 192.168.1.105
```

---

# 10.5 Firmware Information Panel

The Firmware Information section provides detailed information about the installed firmware.

Displayed Information

- Installed Firmware Version
- Latest Available Version
- Firmware Size
- Build Date
- Firmware File Name
- Firmware Status

Example

```text
Installed Version : 4

Latest Version : 5

Firmware File :
application.bin

Firmware Size :
84 KB
```

---

# 10.6 OTA Update Progress

During firmware updates, the dashboard displays the progress in real time.

Progress Stages

```text
Checking Server

↓

Checking Version

↓

Downloading Firmware

↓

Transferring Firmware

↓

Writing Flash

↓

Verifying Firmware

↓

Restarting Device

↓

OTA Successful
```

Displayed Information

- Download Percentage
- Packet Transfer Status
- Flash Programming Status
- Verification Status
- Completion Percentage

---

# 10.7 Security Status Panel

The dashboard visualizes firmware verification results.

Security Checks

- Firmware Header Verification
- CRC32 Verification
- SHA-256 Verification
- Authentication Token Validation
- Firmware Version Validation

Example

```text
CRC32

PASS

SHA-256

PASS

Authentication

PASS

Firmware

Verified
```

---

# 10.8 Event Logging Panel

Every important event generated by the OTA framework is recorded and displayed.

Typical Events

```text
System Started

Wi-Fi Connected

Checking Server

Checking STM32

Downloading Firmware

Firmware Download Complete

Writing Flash

CRC32 Verification

SHA-256 Verification

Authentication Passed

Jumping to Application

OTA Successful
```

Event logging greatly simplifies debugging and troubleshooting.

---

# 10.9 Device Location

The dashboard can display the geographical location of the deployed device.

Displayed Information

- City
- State
- Country
- Latitude
- Longitude

Example

```text
Location

New Delhi

India

Latitude :
28.6139

Longitude :
77.2090
```

This feature is especially useful when multiple devices are deployed in different geographical locations.

---

# 10.10 Date & Time

The dashboard continuously displays the current date and time.

Displayed Information

- Current Date
- Current Time
- Last Update Time
- Last OTA Update

Example

```text
Date

06 August 2026

Time

14:35:24

Last OTA

14:32:18
```

---

# 10.11 Device Connectivity Status

The dashboard continuously monitors communication between all components.

Connectivity Status

| Component | Status |
|-----------|--------|
| STM32 | Connected |
| ESP32 | Connected |
| Flask Server | Online |
| Render Cloud | Active |
| Internet | Available |

If communication is interrupted, the dashboard immediately notifies the user.

---

# 10.12 OTA Update History

The dashboard maintains a history of firmware updates.

Example

| Version | Status | Date |
|----------|--------|------|
| Version 1 | Installed | 01-Aug-2026 |
| Version 2 | Updated | 03-Aug-2026 |
| Version 3 | Updated | 05-Aug-2026 |
| Version 4 | Updated | 06-Aug-2026 |

---

# 10.13 Dashboard Technologies

The dashboard is developed using modern web technologies.

| Technology | Purpose |
|------------|---------|
| HTML5 | Page Structure |
| CSS3 | Styling |
| JavaScript | Dynamic Content |
| Flask | Backend Integration |
| JSON | Data Exchange |
| HTTP | Communication |

---

# 10.14 Dashboard Advantages

The dashboard provides several operational benefits:

- Real-time system monitoring
- Remote firmware management
- Easy device supervision
- Live OTA progress tracking
- Simplified debugging
- Security verification visualization
- Centralized event logging
- Cloud-based accessibility
- User-friendly interface
- Supports multiple devices

---

# 10.15 Dashboard Workflow

```text
STM32

↓

ESP32

↓

Flask Server

↓

JSON Response

↓

Dashboard

↓

Display

• Device Status

• Firmware Version

• OTA Progress

• Logs

• Security Status

• Device Location

• Date & Time
```

---

# 10.16 Dashboard Summary

The **Web Dashboard** is one of the key components of the Secure OTA Firmware Update Framework. It transforms complex embedded system operations into an intuitive graphical interface, allowing developers to monitor firmware deployment, device connectivity, security verification, and OTA progress in real time.


...

---

# 11. 🔒 Security Features

Security is one of the most critical aspects of any Over-the-Air (OTA) firmware update system. Since firmware is transferred over communication networks and directly controls the operation of embedded devices, protecting the firmware against corruption, unauthorized modification, replay attacks, and invalid installations is essential.

The **Secure OTA Firmware Update Framework** implements multiple layers of security to ensure that only authentic, verified, and authorized firmware images are installed on the STM32 microcontroller.

The security architecture combines **firmware integrity verification**, **authentication**, **version management**, and **bootloader validation** to provide a reliable and secure firmware update mechanism.

---

# 11.1 Security Architecture

The security process begins immediately after the ESP32 downloads the firmware from the cloud server.

Every firmware image must successfully pass multiple verification stages before it is programmed into the STM32 flash memory.

```text
Firmware Download

        │

        ▼

Firmware Header Verification

        │

        ▼

Firmware Size Verification

        │

        ▼

Authentication Token Verification

        │

        ▼

Firmware Version Validation

        │

        ▼

CRC32 Verification

        │

        ▼

SHA-256 Verification

        │

        ▼

Flash Programming

        │

        ▼

Flash Validation

        │

        ▼

Jump to Application
```

If any verification step fails, the firmware update is immediately terminated to prevent installation of an invalid firmware image.

---

# 11.2 Security Objectives

The implemented security mechanisms aim to achieve the following objectives:

- Ensure firmware integrity
- Verify firmware authenticity
- Prevent unauthorized firmware installation
- Prevent firmware corruption
- Prevent firmware downgrade attacks
- Protect flash memory
- Ensure successful firmware execution
- Improve OTA reliability

---

# 11.3 Firmware Header Verification

Before programming begins, the bootloader validates the firmware header.

The firmware header contains essential metadata used throughout the OTA process.

### Header Information

- Firmware Version
- Firmware Size
- Device ID
- Authentication Token
- CRC32 Value
- SHA-256 Hash

Example

```text
Firmware Header

----------------------------

Version : 5

Size : 84560 Bytes

Device ID : STM32_001

CRC32 : 0x6A48B3F1

SHA-256 :
5FA82A....

Authentication Token :
**************
```

If the header is invalid or corrupted, the firmware update is rejected.

---

# 11.4 Firmware Size Verification

The bootloader verifies the firmware size before programming.

This prevents:

- Buffer overflow
- Flash memory overflow
- Invalid firmware images

Example

```text
Received Size

↓

84560 Bytes

↓

Allowed Flash Size

↓

96000 Bytes

↓

Verification Passed
```

---

# 11.5 CRC32 Verification

CRC32 (Cyclic Redundancy Check) is used to detect accidental data corruption during firmware transmission.

After the firmware is written to flash memory, the STM32 recalculates the CRC32 checksum and compares it with the value stored in the firmware header.

### Workflow

```text
Firmware Received

↓

Calculate CRC32

↓

Compare with Header CRC32

↓

PASS

↓

Continue Installation
```

If the calculated CRC32 value does not match the expected value, the firmware update is aborted.

### Benefits

- Detects transmission errors
- Detects flash write corruption
- Improves firmware reliability
- Fast verification

Example

```text
Expected CRC32

0x6A48B3F1

Calculated CRC32

0x6A48B3F1

Result

PASS
```

---

# 11.6 SHA-256 Verification

SHA-256 is used to verify firmware integrity using a cryptographic hash.

Unlike CRC32, SHA-256 provides strong protection against intentional modification of the firmware.

After programming the firmware, the bootloader computes the SHA-256 hash of the flash contents and compares it with the hash stored in the firmware header.

### Verification Process

```text
Firmware Written

↓

Calculate SHA-256

↓

Compare Hash

↓

PASS

↓

Firmware Authentic
```

Example

```text
Expected SHA-256

5FA82D9A...

Calculated SHA-256

5FA82D9A...

Verification

PASS
```

### Advantages

- Detects firmware modification
- Cryptographic integrity verification
- Prevents tampered firmware installation
- Strong security

---

# 11.7 Authentication Token Validation

To prevent unauthorized firmware installation, the framework validates an authentication token before accepting the firmware.

The authentication token is included in the firmware header and verified by the bootloader.

### Authentication Process

```text
Receive Firmware

↓

Read Authentication Token

↓

Compare Stored Token

↓

Match

↓

Continue Update
```

If the authentication token does not match the expected value:

```text
Authentication Failed

↓

Reject Firmware

↓

Remain in Bootloader
```

### Benefits

- Prevents unauthorized firmware updates
- Restricts firmware installation
- Improves deployment security

---

# 11.8 Device Identification

The firmware header also contains a unique Device ID.

During the OTA process, the bootloader verifies that the firmware is intended for the target device.

Example

```text
Firmware Device ID

STM32_001

↓

Target Device

STM32_001

↓

PASS
```

This prevents accidental installation of firmware intended for another device.

---

# 11.9 Firmware Version Management

The bootloader compares the installed firmware version with the incoming firmware version before programming.

### Version Comparison

```text
Installed Version

4

↓

Incoming Version

5

↓

Update Allowed
```

If the incoming firmware version is older than the installed version:

```text
Installed Version

5

↓

Incoming Version

4

↓

Reject Firmware
```

### Benefits

- Prevents firmware downgrade
- Ensures latest firmware remains installed
- Avoids accidental rollback

---

# 11.10 Flash Memory Validation

After writing the firmware, the bootloader verifies the programmed flash memory.

Validation includes:

- Flash Write Verification
- Address Validation
- Memory Boundary Check
- Firmware Size Validation

This ensures that the firmware has been correctly programmed before execution.

---

# 11.11 Secure Boot Decision

The bootloader determines whether the application should be executed.

Only firmware that passes every verification stage is allowed to boot.

Decision Logic

```text
Firmware Verified

↓

CRC32 PASS

↓

SHA-256 PASS

↓

Authentication PASS

↓

Version PASS

↓

Jump to Application
```

Otherwise:

```text
Verification Failed

↓

Remain in Bootloader

↓

Wait for New Firmware
```

---

# 11.12 Security Workflow

The complete security process can be summarized as follows:

```text
Firmware Download

↓

Header Verification

↓

Size Verification

↓

Authentication Token

↓

Device ID Validation

↓

Version Comparison

↓

Flash Programming

↓

CRC32 Verification

↓

SHA-256 Verification

↓

Flash Validation

↓

Boot Application
```

---

# 11.13 Security Features Summary

| Security Feature | Purpose |
|------------------|---------|
| Firmware Header Verification | Validates firmware metadata |
| Firmware Size Verification | Prevents invalid memory writes |
| CRC32 Verification | Detects transmission errors |
| SHA-256 Verification | Ensures firmware integrity |
| Authentication Token | Prevents unauthorized updates |
| Device ID Validation | Ensures firmware matches the target device |
| Firmware Version Management | Prevents firmware downgrade |
| Flash Validation | Confirms successful programming |
| Secure Boot Decision | Executes only verified firmware |

---

# 11.14 Security Advantages

The implemented security mechanisms provide several important benefits:

- Multi-layer firmware protection
- Reliable firmware integrity verification
- Unauthorized firmware prevention
- Protection against corrupted firmware
- Firmware downgrade prevention
- Secure boot process
- Improved system reliability
- Enhanced OTA security
- Safe remote firmware deployment
- Scalable security architecture

---

# 11.15 Future Security Enhancements

The framework can be extended with additional enterprise-grade security mechanisms.

Planned improvements include:

- HTTPS-based firmware downloads
- AES-256 firmware encryption
- RSA/ECDSA digital signature verification
- Secure Boot with hardware root of trust
- Certificate-based authentication
- MQTT over TLS
- Hardware security module (HSM) integration
- TPM support
- Anti-rollback protection
- Encrypted firmware storage

---


...

---

# 12. 🌍 Remote OTA Firmware Updates

One of the most significant features of the **Secure OTA Firmware Update Framework** is its ability to perform **Internet-based remote firmware updates**. Unlike traditional firmware update methods that require physical access or a shared local network, this framework enables firmware deployment to STM32 devices located anywhere in the world.

The system uses an **ESP32 Wi-Fi Gateway** to connect the STM32 microcontroller to the Internet. Firmware images are hosted on a **Flask REST Server** deployed on **Render Cloud**, allowing the ESP32 to securely download the latest firmware and transfer it to the STM32 bootloader via UART.

This architecture eliminates the need for USB cables, ST-Link programmers, or on-site maintenance after the initial deployment.

---

# 12.1 Why Remote OTA?

Traditional embedded firmware updates often require engineers to be physically present at the device location.

Typical update methods include:

- USB Cable
- ST-Link Programmer
- UART Flashing
- Manual Firmware Installation
- SD Card Updates

These methods are practical during development but become inefficient when devices are deployed in remote or large-scale environments.

### Challenges of Traditional Updates

- Physical access required
- High maintenance costs
- Increased downtime
- Slow firmware deployment
- Difficult to manage multiple devices
- Not suitable for IoT applications

The Remote OTA framework addresses these challenges by enabling firmware updates over the Internet.

---

# 12.2 Remote OTA Architecture

The framework follows a cloud-connected architecture where firmware is delivered from the developer to the target STM32 device through the ESP32 gateway.

```text
                    Developer
                        │
                        │
          Upload Firmware (.bin)
                        │
                        ▼
             Flask REST API Server
                 (Render Cloud)
                        │
                 HTTP / Internet
                        │
                        ▼
               ESP32 Wi-Fi Gateway
                        │
                 UART Communication
                        │
                        ▼
          STM32 Secure UART Bootloader
                        │
                  Flash Programming
                        │
                        ▼
             STM32 Application Firmware
```

---

# 12.3 Remote Update Workflow

The OTA update process follows a structured sequence from firmware creation to installation.

```text
Developer

↓

Compile Firmware

↓

Generate Binary (.bin)

↓

Upload Firmware

↓

Render Cloud Server

↓

ESP32 Checks Server

↓

Version Comparison

↓

Download Firmware

↓

UART Transfer

↓

STM32 Bootloader

↓

Firmware Verification

↓

Flash Programming

↓

Application Starts

↓

Dashboard Updated
```

---

# 12.4 Firmware Upload Process

The developer builds the application firmware and uploads it to the Flask server.

The uploaded firmware contains important metadata, including:

- Firmware Version
- Firmware Size
- CRC32 Checksum
- SHA-256 Hash
- Device ID
- Authentication Token

The server stores both the firmware file and its metadata for future OTA requests.

---

# 12.5 Internet-Based Firmware Distribution

The firmware server is deployed on **Render Cloud**, making it accessible over the Internet.

Unlike local servers, cloud hosting enables globally distributed devices to download firmware without requiring the developer and device to be on the same network.

### Cloud Responsibilities

- Host firmware binaries
- Manage firmware versions
- Serve REST API requests
- Store firmware metadata
- Provide firmware download endpoints

---

# 12.6 ESP32 Remote Update Manager

The ESP32 continuously monitors the server for new firmware releases.

Its responsibilities include:

- Connect to Wi-Fi
- Verify Internet connectivity
- Contact Flask server
- Check latest firmware version
- Download firmware
- Transfer firmware via UART
- Report OTA status
- Update dashboard

Example Console Output

```text
Connecting to Wi-Fi...

Wi-Fi Connected

Checking Server...

Server Connected

Checking Firmware Version...

New Firmware Available

Downloading Firmware...

Download Complete
```

---

# 12.7 Version Comparison

Before downloading firmware, the ESP32 compares the installed firmware version with the latest version available on the server.

Example

```text
Installed Version : 4

Latest Version : 5

↓

Update Available

↓

Start Download
```

If the versions match:

```text
Installed Version : 5

Latest Version : 5

↓

Firmware Already Up-to-Date
```

This prevents unnecessary firmware downloads.

---

# 12.8 Firmware Download

When a newer firmware version is detected, the ESP32 downloads the binary file using an HTTP request.

Download Process

```text
HTTP GET Request

↓

Receive Firmware

↓

Store Data

↓

Verify Download

↓

Ready for UART Transfer
```

The firmware is downloaded directly from the cloud server without requiring user intervention.

---

# 12.9 UART Transfer to STM32

After downloading the firmware, the ESP32 transfers it to the STM32 bootloader over UART.

The firmware is divided into packets for reliable communication.

```text
Firmware

↓

Packet 1

↓

Packet 2

↓

Packet 3

↓

...

↓

Last Packet
```

Each packet is acknowledged by the STM32 before the next packet is transmitted.

---

# 12.10 Secure Firmware Installation

The STM32 bootloader performs several security checks before accepting the firmware.

Verification Steps

```text
Firmware Header

↓

Firmware Size

↓

Authentication Token

↓

Version Check

↓

CRC32 Verification

↓

SHA-256 Verification

↓

Flash Programming

↓

Flash Validation

↓

Application Launch
```

If any verification fails, the update is aborted and the existing firmware remains protected.

---

# 12.11 Dashboard Monitoring

The web dashboard provides complete visibility into the remote OTA process.

Displayed Information

- Device Status
- Wi-Fi Status
- Server Status
- Installed Firmware Version
- Latest Firmware Version
- OTA Progress
- Download Status
- Verification Status
- Event Logs
- Device Location
- Date & Time

Dashboard Screenshots

| Dashboard | Device Information |
|-----------|--------------------|
| ![](Web_1.png) | ![](Web_2.png) |

| OTA Success | Device Status |
|-------------|---------------|
| ![](OTA_Img_1.png) | ![](OTA_Img_2.png) |

| Event Logs | STM32 Monitoring |
|------------|------------------|
| ![](Web_3.png) | ![](OTA_Img_3.png) |

---

# 12.12 Remote Deployment Example

The following example demonstrates a real-world deployment scenario.

```text
Developer Location

Bengaluru, India

↓

Upload Firmware

↓

Render Cloud Server

↓

Internet

↓

ESP32 Gateway

New Delhi, India

↓

STM32 Device

↓

Firmware Updated Successfully
```

The developer and embedded device can be located in different cities, states, or even countries.

---

# 12.13 Applications

The Remote OTA Framework is suitable for a wide range of embedded and IoT applications.

Example Applications

- Industrial Automation
- Smart Home Systems
- Smart Agriculture
- Healthcare Devices
- Environmental Monitoring
- Smart Energy Meters
- Vehicle Monitoring Systems
- Smart Street Lighting
- Building Automation
- Remote Sensor Networks
- Educational Research
- Embedded Product Development

---

# 12.14 Advantages of Remote OTA

Compared to conventional firmware update methods, the proposed framework provides several advantages.

### Operational Benefits

- No USB connection required
- No ST-Link required after deployment
- Supports remote maintenance
- Reduces maintenance cost
- Faster firmware deployment
- Easy firmware management
- Suitable for large-scale deployments

### Technical Benefits

- Internet-based communication
- Automatic version checking
- Secure firmware verification
- Cloud-hosted firmware repository
- Real-time dashboard monitoring
- Event logging
- Scalable architecture

---

# 12.15 Future Enhancements

The Remote OTA Framework can be further improved by integrating additional technologies.

Future enhancements include:

- HTTPS-based firmware downloads
- MQTT-based OTA updates
- End-to-end encryption
- AES-256 encrypted firmware
- Digital signature verification
- OTA scheduling
- Automatic rollback mechanism
- Fleet device management
- Multi-device firmware deployment
- Push notifications
- Device grouping
- Load-balanced cloud servers

---

...

---

# 13. 📜 Event Logging

The **Event Logging System** is an essential component of the **Secure OTA Firmware Update Framework**, providing real-time visibility into every stage of the firmware update process. It records all significant events generated by the STM32 bootloader, ESP32 Wi-Fi gateway, Flask server, and OTA update engine.

The primary objective of the logging system is to assist developers in monitoring system behavior, diagnosing communication issues, verifying firmware updates, and simplifying debugging during both development and deployment.

Unlike traditional embedded systems that rely solely on serial console messages, this framework integrates event logging with the **Web Dashboard**, allowing users to monitor OTA activities remotely in real time.

---

# 13.1 Objectives of Event Logging

The event logging system has been designed to achieve the following objectives:

- Monitor the complete OTA update lifecycle
- Track device connectivity
- Display firmware update progress
- Assist in debugging communication failures
- Verify firmware installation
- Record security verification results
- Monitor cloud communication
- Maintain update history
- Improve system reliability

---

# 13.2 Logging Architecture

The logging system collects information from different software modules and forwards it to the dashboard.

```text
                STM32 Bootloader
                       │
                 Boot Events
                       │
                       ▼
                 ESP32 Gateway
                       │
               OTA Manager Logs
                       │
                       ▼
               Flask REST Server
                       │
                Store & Process
                       │
                       ▼
               Web Dashboard
                       │
                 Display Logs
```

Every important system activity is recorded and displayed through the dashboard.

---

# 13.3 Event Sources

Logs are generated from multiple components within the framework.

### STM32 Bootloader

- Bootloader Started
- Firmware Header Received
- Flash Erase Started
- Flash Programming
- CRC32 Verification
- SHA-256 Verification
- Authentication Result
- Application Jump

---

### ESP32 Gateway

- System Startup
- Wi-Fi Connected
- Server Connected
- Version Check
- Firmware Download
- UART Packet Transfer
- OTA Progress
- Update Complete

---

### Flask Server

- Firmware Upload
- Firmware Download Request
- API Access
- Version Request
- Device Registration
- Dashboard Request

---

### Dashboard

- Device Connected
- Device Online
- OTA Status Updated
- Firmware Information Updated
- Event History Updated

---

# 13.4 Complete OTA Logging Flow

The following sequence illustrates the typical log messages generated during a successful OTA firmware update.

```text
System Boot

↓

Initializing Hardware

↓

Connecting to Wi-Fi

↓

Wi-Fi Connected

↓

Checking Internet

↓

Connecting to Flask Server

↓

Server Connected

↓

Checking Latest Firmware Version

↓

New Firmware Available

↓

Downloading Firmware

↓

Download Complete

↓

Sending Firmware Header

↓

STM32 Bootloader Started

↓

Header Verified

↓

Erasing Flash Memory

↓

Writing Flash

↓

Flash Programming Complete

↓

CRC32 Verification

↓

SHA-256 Verification

↓

Authentication Passed

↓

Version Updated

↓

Jumping to Application

↓

STM32 Application Started

↓

Device Online

↓

OTA Update Successful
```

---

# 13.5 Event Categories

The event logging system categorizes logs based on their purpose.

| Category | Description |
|----------|-------------|
| INFO | General system information |
| SUCCESS | Successful operations |
| WARNING | Non-critical issues |
| ERROR | Operation failures |
| OTA | Firmware update events |
| SECURITY | Verification and authentication |
| NETWORK | Wi-Fi and Internet communication |
| SYSTEM | Device startup and initialization |

---

# 13.6 Example Console Output

A typical OTA update generates log messages similar to the following:

```text
====================================
 Secure OTA Firmware System
====================================

[INFO] Bootloader Started

[INFO] Initializing UART

[INFO] Connecting to Wi-Fi...

[INFO] Wi-Fi Connected

[INFO] IP Address:
192.168.1.105

[INFO] Connecting to Server...

[SUCCESS] Server Connected

[INFO] Checking Firmware Version...

[INFO] Installed Version : 4

[INFO] Latest Version : 5

[SUCCESS] New Firmware Available

[INFO] Downloading Firmware...

[INFO] Download Complete

[INFO] Sending Firmware Header

[INFO] Programming Flash

[SUCCESS] Flash Programming Complete

[INFO] CRC32 Verification

[SUCCESS] CRC32 PASS

[INFO] SHA-256 Verification

[SUCCESS] SHA-256 PASS

[INFO] Authentication Successful

[SUCCESS] Firmware Updated Successfully

[INFO] Restarting Device...

[SUCCESS] Application Started
```

---

# 13.7 Dashboard Event Logs

The dashboard displays the latest OTA events in chronological order.

### Displayed Information

- Timestamp
- Event Type
- Description
- Status
- Device Name

Example

| Time | Event | Status |
|------|-------|--------|
| 10:15:03 | System Boot | Success |
| 10:15:05 | Wi-Fi Connected | Success |
| 10:15:08 | Server Connected | Success |
| 10:15:12 | Firmware Check | Success |
| 10:15:20 | Download Started | Success |
| 10:15:35 | Flash Programming | Success |
| 10:15:42 | CRC32 PASS | Success |
| 10:15:44 | SHA-256 PASS | Success |
| 10:15:46 | OTA Completed | Success |

---

# 13.8 Security Event Logs

The framework records security-related operations separately.

Typical security logs include:

```text
Firmware Header Verified

Device ID Validated

Authentication Token Verified

Firmware Version Valid

CRC32 Verification Passed

SHA-256 Verification Passed

Flash Validation Passed

Secure Boot Successful
```

These logs help verify that only authenticated firmware is installed.

---

# 13.9 Error Logging

If an error occurs during the OTA process, the system immediately records the failure.

Examples of logged errors include:

```text
[ERROR] Wi-Fi Connection Failed

[ERROR] Server Not Reachable

[ERROR] Firmware Download Failed

[ERROR] UART Timeout

[ERROR] Packet Loss Detected

[ERROR] Flash Programming Failed

[ERROR] CRC32 Verification Failed

[ERROR] SHA-256 Verification Failed

[ERROR] Authentication Failed

[ERROR] Version Validation Failed
```

These logs simplify troubleshooting and reduce debugging time.

---

# 13.10 Warning Logs

Warning messages indicate non-critical issues that do not immediately stop system operation.

Examples

```text
[WARNING] Weak Wi-Fi Signal

[WARNING] Retry Download

[WARNING] Packet Retransmission

[WARNING] Server Response Delayed

[WARNING] OTA Retry Initiated
```

---

# 13.11 Log Storage

The framework can maintain logs in different locations depending on the implementation.

Possible storage methods include:

- RAM Buffer
- ESP32 Flash Memory
- Flask Server Database
- Dashboard History
- External SD Card *(Future Enhancement)*

---

# 13.12 Benefits of Event Logging

The event logging system provides numerous operational benefits.

### Monitoring

- Live OTA progress
- Device connectivity
- Firmware status
- Cloud communication

### Debugging

- Simplifies troubleshooting
- Identifies communication failures
- Detects firmware issues
- Monitors bootloader execution

### Security

- Tracks authentication
- Records verification results
- Detects invalid firmware
- Monitors update integrity

### Maintenance

- Historical update records
- Easy issue diagnosis
- Reduced maintenance effort
- Improved system reliability

---

# 13.13 Future Enhancements

The logging system can be further improved with advanced monitoring capabilities.

Planned enhancements include:

- Log filtering
- Search functionality
- Export logs (CSV/PDF)
- Remote notifications
- Email alerts
- Cloud database integration
- Log analytics
- Device-specific log history
- Real-time log streaming
- Automatic error reporting

---

...

---

# 14. 💻 Technologies Used

The **Secure OTA Firmware Update Framework** integrates a diverse set of technologies spanning embedded systems, wireless communication, cloud computing, web development, cybersecurity, and version control. Each technology has been carefully selected to build a secure, scalable, and reliable Internet-based OTA firmware update ecosystem.

The project combines **STM32 embedded firmware**, **ESP32 IoT connectivity**, **Python Flask backend**, **Render cloud deployment**, and a **modern web dashboard** into a unified architecture capable of securely updating embedded devices from anywhere in the world.

---

# 14.1 Technology Stack Overview

```text
                 Secure OTA Firmware Update Framework

                        Embedded Systems
                               │
                 STM32 • HAL • Embedded C
                               │
                               ▼
                      UART Communication
                               │
                               ▼
                    ESP32 Wi-Fi Gateway
                               │
                    HTTP / JSON Protocol
                               │
                               ▼
                  Flask REST API (Python)
                               │
                     Render Cloud Hosting
                               │
                               ▼
                HTML • CSS • JavaScript Dashboard
```

---

# 14.2 Embedded Technologies

The embedded portion of the project consists of the STM32 bootloader and application firmware.

## STM32F103C8T6

The STM32F103C8T6 serves as the primary target microcontroller.

### Responsibilities

- Execute Application Firmware
- Flash Programming
- Bootloader Execution
- Firmware Verification
- UART Communication
- Firmware Version Management

### Key Features

- ARM Cortex-M3
- 72 MHz CPU
- Flash Memory Programming
- UART Peripheral
- Low Power Operation

---

## Embedded C

Embedded C is used to develop both the STM32 Bootloader and the Application Firmware.

### Used For

- Peripheral Drivers
- Bootloader Logic
- Flash Programming
- Firmware Verification
- UART Communication
- Memory Management

### Advantages

- High Performance
- Low Memory Usage
- Hardware-Level Control
- Fast Execution

---

## STM32 HAL

The STM32 Hardware Abstraction Layer (HAL) simplifies peripheral configuration.

Used Modules

- UART
- GPIO
- FLASH
- RCC
- NVIC
- SysTick

Benefits

- Easy peripheral initialization
- Hardware abstraction
- Better code portability
- Reduced development time

---

# 14.3 ESP32 Technologies

The ESP32 acts as the Internet gateway for the STM32.

It connects to Wi-Fi, downloads firmware from the cloud, and communicates with the STM32 via UART.

---

## ESP32 DevKit

Responsibilities

- Wi-Fi Connectivity
- HTTP Client
- Firmware Download
- OTA Manager
- UART Communication
- Dashboard Updates

---

## PlatformIO

PlatformIO is used for ESP32 firmware development.

Features

- Library Management
- Multiple Board Support
- Integrated Build System
- Serial Monitor
- Upload Support

Advantages

- Faster development
- Easy dependency management
- Cross-platform compatibility

---

## Arduino Framework

The Arduino Framework provides libraries for ESP32 development.

Libraries Used

- WiFi
- HTTPClient
- ArduinoJson
- HardwareSerial

---

# 14.4 Communication Technologies

Reliable communication is essential for OTA updates.

The project uses multiple communication protocols.

---

## UART

UART provides communication between the ESP32 and STM32.

Applications

- Firmware Packet Transfer
- Bootloader Commands
- Version Requests
- Event Logging

Advantages

- Simple
- Reliable
- Low Overhead
- Widely Supported

---

## Wi-Fi

ESP32 connects to the Internet using Wi-Fi.

Functions

- Connect to Router
- Download Firmware
- Communicate with Cloud
- Update Dashboard

---

## HTTP

Firmware files are downloaded using the HTTP protocol.

Functions

- Firmware Download
- Version Requests
- Device Communication

Typical API Calls

```text
GET /api/version

GET /api/download

POST /api/upload
```

---

## JSON

JSON is used for exchanging structured data between the ESP32 and Flask server.

Example

```json
{
  "version": 5,
  "file": "application.bin",
  "size": 84560
}
```

Advantages

- Lightweight
- Human Readable
- Easy Parsing
- Platform Independent

---

# 14.5 Backend Technologies

The backend manages firmware storage and communication.

---

## Python

Python is used for backend development.

Responsibilities

- REST APIs
- Firmware Upload
- Firmware Download
- Version Management
- Device Management

Advantages

- Simple Syntax
- Fast Development
- Large Ecosystem
- Excellent Flask Support

---

## Flask

Flask provides the REST API used by the OTA framework.

API Services

- Firmware Upload
- Firmware Download
- Firmware Version
- Device Status
- Event Logs

Advantages

- Lightweight
- Easy Deployment
- Flexible
- REST API Friendly

---

# 14.6 Cloud Platform

## Render Cloud

Render hosts the Flask application on the Internet.

Responsibilities

- Host Flask Server
- Store Firmware
- Provide Public API
- Handle Device Requests

Advantages

- Cloud Access
- Automatic Deployment
- Public URL
- High Availability
- Easy Maintenance

---

# 14.7 Frontend Technologies

The project includes a responsive web dashboard.

---

## HTML5

Used to create the dashboard structure.

Functions

- Dashboard Layout
- Device Information
- Firmware Details
- Event Logs

---

## CSS3

CSS is used for dashboard styling.

Provides

- Responsive Layout
- Colors
- Tables
- Cards
- Navigation
- Animations

---

## JavaScript

JavaScript provides dynamic dashboard functionality.

Responsibilities

- API Requests
- Auto Refresh
- OTA Progress Updates
- Device Status Updates
- Live Monitoring

---

# 14.8 Security Technologies

Several security mechanisms protect the firmware update process.

---

## CRC32

Purpose

- Detect firmware corruption
- Verify flash programming

Benefits

- Fast
- Lightweight
- Reliable

---

## SHA-256

Purpose

- Verify firmware integrity
- Detect tampering

Benefits

- Strong cryptographic hashing
- High reliability
- Secure verification

---

## Authentication Token

Purpose

- Authorize firmware installation
- Prevent unauthorized updates

Benefits

- Secure deployment
- Device authentication

---

# 14.9 Development Tools

The following development tools were used throughout the project.

| Tool | Purpose |
|------|---------|
| STM32CubeIDE | STM32 Firmware Development |
| PlatformIO | ESP32 Development |
| Visual Studio Code | Code Editor |
| STM32CubeProgrammer | Flash Programming |
| Git | Version Control |
| GitHub | Source Code Hosting |
| Serial Monitor | UART Debugging |
| Postman | REST API Testing |

---

# 14.10 Programming Languages

| Language | Application |
|----------|-------------|
| Embedded C | STM32 Bootloader & Application |
| C++ | ESP32 Gateway |
| Python | Flask Backend |
| HTML5 | Dashboard Structure |
| CSS3 | Dashboard Design |
| JavaScript | Dashboard Logic |

---

# 14.11 Technology Integration

The following diagram illustrates how all technologies work together.

```text
Developer

↓

STM32CubeIDE

↓

Embedded C

↓

STM32 Bootloader

↓

UART

↓

ESP32

↓

Wi-Fi

↓

HTTP

↓

Flask Server

↓

Render Cloud

↓

JSON

↓

Dashboard

↓

HTML + CSS + JavaScript
```

---

# 14.12 Technology Advantages

The selected technologies provide several advantages:

### Embedded

- Low resource usage
- Reliable performance
- Real-time operation

### Communication

- Internet-based firmware delivery
- Reliable UART communication
- Lightweight JSON messaging

### Cloud

- Global accessibility
- Easy deployment
- Scalable architecture

### Web

- Responsive dashboard
- Real-time monitoring
- User-friendly interface

### Security

- Firmware integrity verification
- Authentication
- Version validation
- Secure firmware deployment

---

# 14.13 Technology Summary

| Category | Technologies |
|----------|--------------|
| Microcontroller | STM32F103C8T6 |
| Gateway | ESP32 DevKit |
| Programming Languages | Embedded C, C++, Python, HTML5, CSS3, JavaScript |
| Embedded Framework | STM32 HAL |
| ESP32 Framework | Arduino Framework |
| ESP32 IDE | PlatformIO |
| STM32 IDE | STM32CubeIDE |
| Backend | Python Flask |
| Cloud Platform | Render |
| Communication | UART, Wi-Fi, HTTP, JSON |
| Security | CRC32, SHA-256, Authentication Token |
| Dashboard | HTML5, CSS3, JavaScript |
| Version Control | Git & GitHub |

---



# 15. 🚀 Future Improvements

The current implementation of the **Secure OTA Firmware Update Framework** provides a complete Internet-based firmware update solution for STM32 embedded systems. However, as embedded and IoT technologies continue to evolve, the framework can be further enhanced with advanced security mechanisms, communication protocols, cloud services, and fleet management capabilities.

The following improvements are proposed to transform the framework into an enterprise-grade OTA firmware management platform suitable for large-scale industrial and commercial deployments.

---

# 15.1 Secure HTTPS Communication

Currently, firmware is downloaded using HTTP. A future enhancement is to migrate the communication channel to HTTPS using SSL/TLS encryption.

### Objectives

- Encrypt communication
- Prevent Man-in-the-Middle (MITM) attacks
- Protect firmware downloads
- Improve communication security

### Benefits

- Secure data transmission
- Improved authentication
- Better cloud security
- Industry-standard communication

---

# 15.2 MQTT-Based OTA Updates

Instead of periodically polling the server for updates, the ESP32 can subscribe to an MQTT broker and receive firmware update notifications instantly.

### Workflow

```text
Developer

↓

Upload Firmware

↓

MQTT Broker

↓

ESP32 Notification

↓

Download Firmware

↓

STM32 Update
```

### Advantages

- Lower bandwidth usage
- Faster update notifications
- Real-time communication
- Better scalability
- Ideal for IoT deployments

---

# 15.3 AES-256 Firmware Encryption

Although the framework verifies firmware integrity using SHA-256, the firmware image itself can also be encrypted before transmission.

### Encryption Workflow

```text
Firmware

↓

AES-256 Encryption

↓

Upload to Server

↓

Download by ESP32

↓

AES-256 Decryption

↓

STM32 Bootloader
```

### Benefits

- Prevents firmware theft
- Protects intellectual property
- Secure firmware transmission
- Prevents unauthorized firmware analysis

---

# 15.4 Digital Signature Verification

Digital signatures provide proof that the firmware originates from a trusted developer.

Future versions can implement RSA or ECDSA digital signature verification before firmware installation.

### Verification Process

```text
Firmware

↓

Generate Digital Signature

↓

Upload

↓

Verify Signature

↓

Install Firmware
```

### Advantages

- Firmware authenticity
- Prevents malicious firmware
- Strong cryptographic protection
- Trusted firmware deployment

---

# 15.5 Secure Boot

A Secure Boot mechanism can be implemented to verify the firmware every time the STM32 starts.

Only firmware with a valid signature or hash will be executed.

### Boot Process

```text
Power ON

↓

Bootloader

↓

Verify Firmware

↓

Valid

↓

Start Application
```

### Benefits

- Prevents unauthorized firmware execution
- Protects against flash modification
- Enhances system security

---

# 15.6 Automatic Rollback

If a firmware update fails or the new firmware becomes unstable, the system can automatically restore the previous working firmware.

### Rollback Workflow

```text
Install New Firmware

↓

Boot Test

↓

Failure Detected

↓

Restore Previous Firmware

↓

Restart Device
```

### Benefits

- Improved reliability
- Reduced downtime
- Automatic recovery
- Safer firmware deployment

---

# 15.7 Differential OTA Updates

Instead of downloading the complete firmware image, only the modified portions of the firmware can be transmitted.

### Workflow

```text
Old Firmware

↓

Calculate Differences

↓

Generate Patch

↓

Download Patch

↓

Reconstruct Firmware
```

### Benefits

- Smaller downloads
- Faster updates
- Reduced Internet usage
- Lower power consumption

---

# 15.8 Fleet Device Management

Future versions can support simultaneous management of hundreds or thousands of embedded devices.

### Fleet Features

- Device Registration
- Device Groups
- Firmware Assignment
- Device Health
- Online Status
- Remote Diagnostics

Example

```text
Organization

↓

Building A

↓

50 Devices

↓

Building B

↓

100 Devices

↓

Building C

↓

75 Devices
```

---

# 15.9 Multi-Device Dashboard

The existing dashboard monitors a single device.

A future enhancement is to support multiple embedded devices from a single interface.

### Dashboard Features

- Device List
- Device Groups
- Firmware Version
- Online Status
- Update Progress
- Error Reports
- Live Monitoring

---

# 15.10 Device Health Monitoring

The dashboard can monitor hardware health parameters in addition to OTA status.

Possible Parameters

- CPU Usage
- RAM Usage
- Flash Usage
- Temperature
- Voltage
- Battery Level
- Wi-Fi Signal Strength
- Device Uptime

---

# 15.11 Push Notifications

Real-time notifications can be sent whenever important events occur.

Examples

- Firmware Uploaded
- OTA Started
- OTA Completed
- Firmware Failed
- Device Offline
- Authentication Failed

Notification Methods

- Email
- Mobile Push Notifications
- Telegram Bot
- Slack
- Microsoft Teams

---

# 15.12 Scheduled OTA Updates

Instead of updating immediately, administrators can schedule firmware deployment.

Example

```text
Upload Firmware

↓

Schedule

↓

02:00 AM

↓

Automatic OTA Update
```

### Benefits

- Reduced downtime
- Off-peak maintenance
- Better operational planning

---

# 15.13 Database Integration

Currently, firmware information can be managed using files or simple storage.

Future versions can integrate a database.

Possible Databases

- SQLite
- MySQL
- PostgreSQL
- MongoDB

Stored Information

- Firmware Versions
- Device Information
- OTA History
- Event Logs
- Authentication Data

---

# 15.14 Docker Deployment

The Flask server can be containerized using Docker for simplified deployment.

### Benefits

- Easy installation
- Platform independence
- Scalable deployment
- Simplified maintenance

Deployment Flow

```text
Flask Server

↓

Docker Container

↓

Cloud Deployment

↓

OTA Service
```

---

# 15.15 FreeRTOS Integration

The ESP32 firmware can be migrated to FreeRTOS for better task scheduling and multitasking.

Possible Tasks

- Wi-Fi Task
- OTA Task
- UART Task
- Dashboard Task
- Logging Task
- Watchdog Task

### Benefits

- Better responsiveness
- Improved performance
- Modular design
- Real-time task scheduling

---

# 15.16 Enhanced Security

Additional security features can be incorporated into future releases.

Possible Improvements

- Certificate-Based Authentication
- TPM Integration
- Hardware Security Modules (HSM)
- Secure Key Storage
- Anti-Rollback Protection
- Encrypted Flash Storage
- Secure Firmware Keys

---

# 15.17 AI-Based Predictive Maintenance

Machine learning algorithms can be integrated to analyze device behavior.

Possible Features

- Failure Prediction
- Battery Health Analysis
- Network Quality Prediction
- Firmware Stability Analysis
- Device Performance Analytics

---

# 15.18 Mobile Application

A mobile application can be developed for remote monitoring and OTA management.

Features

- Live Device Status
- OTA Notifications
- Firmware Updates
- Event Logs
- Device Location
- Dashboard Access

Supported Platforms

- Android
- iOS

---

# 15.19 CI/CD Integration

The firmware development process can be automated using Continuous Integration and Continuous Deployment (CI/CD).

### Workflow

```text
Developer Pushes Code

↓

GitHub Actions

↓

Build Firmware

↓

Run Tests

↓

Generate Binary

↓

Upload to Server

↓

OTA Deployment
```

### Benefits

- Automated firmware builds
- Faster deployment
- Reduced manual effort
- Improved software quality

---

# 15.20 Future Roadmap

| Enhancement | Purpose |
|-------------|---------|
| HTTPS Communication | Secure data transmission |
| MQTT OTA | Real-time firmware notifications |
| AES-256 Encryption | Firmware confidentiality |
| Digital Signature | Firmware authenticity |
| Secure Boot | Trusted firmware execution |
| Automatic Rollback | Recovery from failed updates |
| Differential OTA | Smaller firmware downloads |
| Fleet Management | Large-scale device administration |
| Multi-Device Dashboard | Monitor multiple devices |
| Device Health Monitoring | System diagnostics |
| Push Notifications | Real-time alerts |
| Scheduled OTA | Planned firmware deployment |
| Database Integration | Persistent data management |
| Docker Deployment | Simplified cloud deployment |
| FreeRTOS Integration | Real-time multitasking |
| Enhanced Security | Advanced protection mechanisms |
| AI Predictive Maintenance | Intelligent monitoring |
| Mobile Application | Remote device management |
| CI/CD Integration | Automated firmware deployment |

---

# 15.21 Vision for the Framework

The long-term vision of this project is to evolve from a secure academic prototype into a **fully featured enterprise-grade OTA firmware management platform** capable of supporting thousands of Internet-connected embedded devices.

Future versions will emphasize:

- Enterprise-level security
- Large-scale IoT deployments
- Intelligent device monitoring
- High availability and reliability

...

---

# 16. 📈 Results

The **Secure OTA Firmware Update Framework** was successfully designed, implemented, and tested on a real embedded hardware platform consisting of an **STM32F103C8T6 microcontroller**, an **ESP32 Wi-Fi Gateway**, and a **cloud-hosted Flask REST Server** deployed on **Render**.

The experimental results demonstrate that the proposed framework can securely perform Internet-based firmware updates while ensuring firmware integrity, authenticity, and reliable deployment. The framework also provides a real-time web dashboard for monitoring the complete OTA process.

The successful implementation validates the effectiveness of combining embedded systems, cloud computing, wireless communication, and cybersecurity techniques into a single OTA firmware management solution.

---

# 16.1 Experimental Setup

The complete framework was tested using the following hardware and software components.

| Component | Description |
|------------|-------------|
| Target MCU | STM32F103C8T6 |
| Gateway | ESP32 DevKit |
| Communication | UART |
| Cloud Server | Flask REST API |
| Cloud Platform | Render |
| Dashboard | HTML, CSS, JavaScript |
| Development IDE | STM32CubeIDE |
| ESP32 IDE | PlatformIO |
| Programming Language | Embedded C, C++, Python |

---

# 16.2 Test Scenario

The framework was evaluated under real operating conditions.

### Test Procedure

1. Develop new STM32 application firmware.
2. Compile and generate the binary (`.bin`) file.
3. Upload the firmware to the Flask server.
4. Deploy the server on Render Cloud.
5. Connect the ESP32 gateway to the Internet.
6. Check the latest firmware version.
7. Download the firmware from the cloud.
8. Transfer the firmware to the STM32 through UART.
9. Verify firmware using CRC32 and SHA-256.
10. Boot the updated application.
11. Display the update status on the web dashboard.

The OTA update process completed successfully without requiring physical access to the embedded device.

---

# 16.3 Functional Verification

Each subsystem was tested individually before validating the complete OTA workflow.

| Module | Status |
|---------|--------|
| STM32 Bootloader | ✅ Passed |
| Flash Programming | ✅ Passed |
| UART Communication | ✅ Passed |
| ESP32 Wi-Fi Connection | ✅ Passed |
| HTTP Communication | ✅ Passed |
| Flask REST API | ✅ Passed |
| Render Deployment | ✅ Passed |
| Firmware Download | ✅ Passed |
| Dashboard Monitoring | ✅ Passed |
| Event Logging | ✅ Passed |

---

# 16.4 OTA Update Verification

The OTA firmware update process was tested multiple times using different firmware versions.

### Successful OTA Workflow

```text
Compile Firmware

↓

Upload Firmware

↓

Render Cloud

↓

ESP32 Connects

↓

Version Check

↓

Firmware Download

↓

UART Transfer

↓

Flash Programming

↓

CRC32 Verification

↓

SHA-256 Verification

↓

Application Starts

↓

Dashboard Updated
```

Every stage of the firmware update process completed successfully.

---

# 16.5 Security Verification Results

The implemented security mechanisms were validated during firmware installation.

| Security Feature | Result |
|------------------|--------|
| Firmware Header Verification | ✅ Passed |
| Firmware Size Verification | ✅ Passed |
| Authentication Token Validation | ✅ Passed |
| Device Identification | ✅ Passed |
| Firmware Version Management | ✅ Passed |
| CRC32 Verification | ✅ Passed |
| SHA-256 Verification | ✅ Passed |
| Flash Validation | ✅ Passed |
| Secure Boot | ✅ Passed |

These results confirm that only verified firmware is accepted and executed.

---

# 16.6 Dashboard Validation

The web dashboard successfully displayed real-time information throughout the OTA process.

### Dashboard Features Tested

- Device Status
- Firmware Version
- OTA Progress
- Event Logs
- Device Location
- Date & Time
- Security Verification
- Update Status

Dashboard Screenshots

| Dashboard | Device Information |
|-----------|--------------------|
| ![](Web_1.png) | ![](Web_2.png) |

| OTA Success | Device Status |
|-------------|---------------|
| ![](OTA_Img_1.png) | ![](OTA_Img_2.png) |

| Event Logs | STM32 Monitoring |
|------------|------------------|
| ![](Web_3.png) | ![](OTA_Img_3.png) |

---

# 16.7 Remote OTA Validation

The OTA framework successfully demonstrated firmware updates over the Internet.

### Validation Steps

```text
Developer

↓

Upload Firmware

↓

Render Cloud

↓

ESP32 Downloads Firmware

↓

STM32 Updated

↓

Dashboard Updated
```

The developer and embedded device were able to operate from different network environments, confirming successful remote OTA functionality.

---

# 16.8 Performance Evaluation

The framework was evaluated based on several performance metrics.

| Parameter | Observation |
|------------|-------------|
| Firmware Download | Successful |
| Flash Programming | Successful |
| UART Communication | Stable |
| Internet Connectivity | Stable |
| Cloud Communication | Reliable |
| Firmware Verification | Successful |
| Dashboard Monitoring | Real-Time |
| OTA Completion | Successful |

---

# 16.9 Reliability Assessment

Multiple OTA update cycles were performed to evaluate system reliability.

### Observations

- Stable UART communication between ESP32 and STM32
- Reliable Wi-Fi connectivity
- Successful cloud communication
- No firmware corruption observed
- Consistent firmware verification
- Successful application execution after update
- Continuous dashboard monitoring
- Accurate event logging

The framework remained stable throughout repeated testing.

---

# 16.10 Advantages Achieved

The implemented framework provides several practical advantages over traditional firmware update methods.

### Operational Advantages

- Internet-based firmware updates
- No USB cable required
- No ST-Link programmer required after deployment
- Remote device maintenance
- Reduced maintenance costs
- Faster firmware deployment

### Technical Advantages

- Secure bootloader implementation
- Firmware integrity verification
- Authentication token validation
- Firmware version management
- Real-time monitoring
- Cloud-based deployment
- Event logging
- Device tracking

---

# 16.11 Comparison with Traditional Firmware Updates

| Feature | Traditional Method | Proposed Framework |
|----------|-------------------|--------------------|
| Physical Access Required | Yes | No |
| USB Connection | Required | Not Required |
| ST-Link Programmer | Required | Only Initial Programming |
| Internet-Based Updates | No | Yes |
| Cloud Deployment | No | Yes |
| Remote Firmware Update | No | Yes |
| Real-Time Dashboard | No | Yes |
| OTA Progress Monitoring | No | Yes |
| Security Verification | Limited | CRC32 + SHA-256 + Authentication |
| Device Monitoring | No | Yes |

---

# 16.12 Key Achievements

The project successfully accomplished the following objectives:

- ✅ Custom STM32 UART Bootloader
- ✅ ESP32 Wi-Fi Gateway
- ✅ Internet-Based OTA Firmware Updates
- ✅ Remote Firmware Updates Across Different Networks
- ✅ Flask REST API Server
- ✅ Render Cloud Deployment
- ✅ Real-Time Web Dashboard
- ✅ Firmware Version Management
- ✅ CRC32 Verification
- ✅ SHA-256 Integrity Verification
- ✅ Authentication Token Validation
- ✅ Event Logging
- ✅ Device Location Monitoring
- ✅ Real-Time Date & Time Display
- ✅ OTA Progress Monitoring

---

# 16.13 Educational Outcomes

This project provided practical experience in several domains of embedded systems and IoT development, including:

- Embedded Firmware Development
- Bootloader Design
- Flash Memory Management
- UART Communication
- Wi-Fi Networking
- REST API Development
- Cloud Deployment
- Web Dashboard Development
- Embedded Cybersecurity
- Firmware Verification
- Version Control using Git & GitHub

---

# 16.14 Project Outcome

The implemented framework demonstrates that secure firmware updates can be performed over the Internet without requiring physical access to the target device.

The integration of a **custom STM32 bootloader**, **ESP32 Wi-Fi gateway**, **Flask REST API**, **Render Cloud**, and **real-time dashboard** creates a reliable, scalable, and secure OTA firmware management system suitable for embedded systems and IoT applications.

The project successfully meets its primary objectives of enabling secure remote firmware deployment, ensuring firmware integrity through **CRC32** and **SHA-256 verification**, managing firmware versions, and providing comprehensive real-time monitoring through a web-based dashboard.

---

---

# 17. 🎥 Project Demonstration

The **Secure OTA Firmware Update Framework** demonstrates a complete Internet-based firmware update solution for STM32 embedded systems. The project integrates a **custom STM32 UART bootloader**, an **ESP32 Wi-Fi Gateway**, a **Flask REST API server**, **Render Cloud deployment**, and a **real-time web dashboard** into a single embedded firmware management ecosystem.

This section highlights the various demonstrations and resources that showcase the implementation, working principles, and capabilities of the framework.

---

# 17.1 Demonstration Overview

The project demonstration includes the following components:

- Hardware Demonstration
- OTA Firmware Update Demonstration
- Web Dashboard Demonstration
- Cloud Server Demonstration
- Security Verification
- Event Logging
- Firmware Version Management
- Remote OTA Update
- Complete System Workflow

These demonstrations collectively validate the successful implementation of the proposed framework.

---

# 17.2 Complete System Demonstration

The following diagram illustrates the overall working principle of the project.

```text
                 Developer

                     │

        Build Application Firmware

                     │

                     ▼

        Upload Firmware to Server

                     │

                     ▼

        Flask REST API (Render Cloud)

                     │

             HTTP Communication

                     │

                     ▼

            ESP32 Wi-Fi Gateway

                     │

            UART Communication

                     │

                     ▼

       STM32 Secure UART Bootloader

                     │

        Firmware Verification

                     │

        Flash Programming

                     │

                     ▼

         STM32 Application Starts

                     │

                     ▼

        Dashboard Updated
```

This workflow demonstrates the complete Internet-based OTA firmware update process.

---

# 17.3 Hardware Demonstration

The hardware demonstration validates the embedded implementation of the framework.

### Hardware Components

| Hardware | Purpose |
|-----------|---------|
| STM32F103C8T6 | Target Microcontroller |
| ESP32 DevKit | Wi-Fi Gateway |
| ST-Link V2 | Initial Programming |
| FT232 | UART Communication |
| LEDs | Status Indicators |
| Push Buttons | Recovery / Reset |
| OLED (Optional) | Device Information |

### Demonstrated Functions

- STM32 Bootloader
- ESP32 Gateway
- UART Communication
- Firmware Programming
- Status LEDs
- Recovery Mode

---

# 17.4 OTA Firmware Update Demonstration

The OTA demonstration verifies the successful firmware update process.

### Demonstration Steps

1. Compile STM32 Application.
2. Generate Binary Firmware.
3. Upload Firmware to Flask Server.
4. Deploy Server on Render.
5. ESP32 Connects to Internet.
6. ESP32 Checks Latest Version.
7. Firmware Download Begins.
8. Firmware Sent to STM32.
9. Flash Programming.
10. Firmware Verification.
11. Device Restart.
12. Updated Application Executes.

Workflow

```text
Compile Firmware

↓

Upload Firmware

↓

Render Cloud

↓

ESP32 Downloads Firmware

↓

STM32 Bootloader

↓

Flash Programming

↓

Verification

↓

Application Starts
```

---

# 17.5 Dashboard Demonstration

The project includes a modern web dashboard that displays the complete OTA update process in real time.

### Dashboard Screenshots

#### Dashboard Overview

| Dashboard | Device Information |
|-----------|--------------------|
| ![](Web_1.png) | ![](Web_2.png) |

---

#### OTA Update Status

| OTA Success | Device Status |
|-------------|---------------|
| ![](OTA_Img_1.png) | ![](OTA_Img_2.png) |

---

#### Event Logs

| Event Logs | STM32 Monitoring |
|------------|------------------|
| ![](Web_3.png) | ![](OTA_Img_3.png) |

---

### Dashboard Features

- Device Status
- Firmware Version
- Latest Firmware
- OTA Progress
- Event Logs
- Device Location
- Date & Time
- Authentication Status
- CRC32 Result
- SHA-256 Result

---

# 17.6 Cloud Server Demonstration

The backend server is deployed on **Render Cloud**, making firmware available over the Internet.

### Server Functions

- Firmware Upload
- Firmware Download
- Firmware Version API
- Device Information
- Event Logging
- Dashboard Data

Server Workflow

```text
Developer

↓

Upload Firmware

↓

Render Cloud

↓

REST API

↓

ESP32 Gateway
```

---

# 17.7 Security Demonstration

The project demonstrates multiple security mechanisms before installing firmware.

### Security Verification

```text
Firmware Header

↓

Firmware Size

↓

Authentication Token

↓

Version Check

↓

CRC32

↓

SHA-256

↓

Flash Validation

↓

Application Start
```

### Demonstrated Security Features

- Firmware Header Verification
- Firmware Size Verification
- Authentication Token Validation
- Firmware Version Management
- CRC32 Verification
- SHA-256 Verification
- Flash Validation

---

# 17.8 Event Logging Demonstration

Every stage of the OTA update process is logged.

Example Event Log

```text
System Started

↓

Wi-Fi Connected

↓

Checking Server

↓

Checking Firmware Version

↓

Downloading Firmware

↓

Programming Flash

↓

CRC32 PASS

↓

SHA-256 PASS

↓

Firmware Updated

↓

Application Started
```

These logs are available through both the serial terminal and the web dashboard.

---

# 17.9 Remote OTA Demonstration

One of the major achievements of this framework is the ability to update firmware remotely over the Internet.

Unlike conventional OTA systems that require devices to be connected to the same Wi-Fi network, this framework allows firmware updates from geographically different locations.

Example

```text
Developer

Bengaluru

↓

Render Cloud

↓

Internet

↓

ESP32 Gateway

New Delhi

↓

STM32 Device

↓

Firmware Updated Successfully
```

This demonstrates true Internet-based OTA capability.

---

# 17.10 Firmware Version Management Demonstration

The system automatically compares the installed firmware version with the latest version available on the server.

Example

```text
Installed Version

4

↓

Latest Version

5

↓

Update Available

↓

Download Firmware
```

If both versions are identical:

```text
Installed Version

5

↓

Latest Version

5

↓

Firmware Already Up-to-Date
```

This prevents unnecessary firmware downloads.

---

# 17.11 Performance Demonstration

The implemented framework successfully demonstrates:

| Feature | Status |
|----------|--------|
| UART Communication | ✅ Successful |
| Internet Connectivity | ✅ Successful |
| Cloud Deployment | ✅ Successful |
| Firmware Download | ✅ Successful |
| Flash Programming | ✅ Successful |
| CRC32 Verification | ✅ Successful |
| SHA-256 Verification | ✅ Successful |
| Authentication | ✅ Successful |
| Dashboard Monitoring | ✅ Successful |
| Event Logging | ✅ Successful |
| Remote OTA Updates | ✅ Successful |

---

# 17.12 Demonstration Resources

The following resources can be added to the repository for users to explore the project.

| Resource | Description |
|-----------|-------------|
| 🎥 Demo Video | Complete OTA firmware update demonstration |
| 🌐 Live Dashboard | Real-time monitoring dashboard |
| 📄 Project Report | Detailed technical documentation |
| 📊 System Architecture | Framework architecture diagram |
| 🔌 Circuit Diagram | Hardware connections |
| 📷 Hardware Images | STM32 and ESP32 setup |
| 📸 Dashboard Screenshots | User interface overview |
| 📚 Documentation | Setup and usage guides |

---

# 17.13 Repository Links

Replace the placeholders below with your project resources.

### GitHub Repository

```text
https://github.com/ankushsaroj530/secure-ota-firmware-update-stm32-esp32
```

### Live Dashboard

```text
https://your-dashboard-url.onrender.com
```

### Flask REST API

```text
https://your-api-url.onrender.com
```

### YouTube Demonstration

```text
https://youtu.be/your-video-link
```

---


# 18. 🏷️ GitHub Topics

```text
stm32
esp32
embedded-systems
bootloader
ota
firmware
firmware-update
embedded-c
platformio
python
flask
render
iot
stm32f103
uart
http
json
cybersecurity
device-management
```

---

# 21. 📄 License

This project is licensed under the **MIT License**.

---

# 19. 👨‍💻 Author

**Ankush Saroj**

**B.Tech Electronics and Communication Engineering**

**Central University of Karnataka**

### Connect with Me

- GitHub: https://github.com/ankushsaroj530
- LinkedIn: *(Add your LinkedIn profile here)*

---

# 20. ⭐ Support

If you found this project helpful, please consider giving it a **⭐ Star** on GitHub.

If you have suggestions, improvements, or discover any issues, feel free to open an **Issue** or submit a **Pull Request**.
