Project documentation
Team A : Smart Registration & Check In (Using RFID sensor)
Team Members : 1.MARSHEILLYN NATASHA ANAK NAGA (CN230318), 2.MUHAMMAD AFIQ BIN KHAIRIL ASHRAF (AN230040), 3.ABDUL AZIZ BIN MARSULI (AN230136), 4.AINA SYAFIQAH BINTI MOHAMMAD ARNIE (CN230328), 5.MUHAMMAD QAID HAKIM BIN MOHD AZAHARI (CN250179), 6.MUHAMMAD IMRAN SYAFI BIN MOHD ISMAIL (CN230387), 7.MUHAMMAD HADI HANAFI BIN AHMAD (230017), 8.MUHAMMAD IKHMAL BIN ANUAR (CN230408), 9.AMEERUL HAMIZAN KHAN BIN AMEER ALI KHAN (AN230087)
Quick Start Guide : # Smart Registration & Check-In System Using RFID
## Overview
This project uses an ESP32 and RC522 RFID reader to perform student registration and attendance check-in. When an RFID card is scanned, the system reads the card UID and records the attendance data.

## Hardware Required
- ESP32 Development Board
- RC522 RFID Reader
- RFID Card / RFID Tag
- Jumper Wires
- USB Cable

## Software Required
- Arduino IDE
- ESP32 Board Package
- MFRC522 Library
- Wi-Fi Connection
- GitHub Repository

## Wiring Connection

| RC522 | ESP32 |
|---------|---------|
| SDA (SS) | GPIO 5 |
| SCK | GPIO 18 |
| MOSI | GPIO 23 |
| MISO | GPIO 19 |
| RST | GPIO 22 |
| 3.3V | 3.3V |
| GND | GND |

## Installation

### Step 1: Install Arduino IDE
Download and install Arduino IDE.

### Step 2: Install ESP32 Board
Arduino IDE → Preferences

Additional Boards Manager URLs:

https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

Tools → Board Manager

Search:
ESP32

Install the ESP32 package.

### Step 3: Install MFRC522 Library
Sketch → Include Library → Manage Libraries

Search:
MFRC522

Install the library.

### Step 4: Upload the Program
1. Connect ESP32 to PC.
2. Open the RFID source code.
3. Select the correct COM Port.
4. Click Upload.

### Step 5: Run the System
1. Open Serial Monitor.
2. Set baud rate to 115200.
3. Scan RFID card.
4. The UID will be displayed.

## Folder Structure

docs/
├── flowchart.png
├── architecture.png
└── documentation.pdf

src_iot/
└── esp32_rfid.ino

src_os/
└── server.py

media/
├── setup.jpg
├── testing.jpg
└── demo.mp4

README.md

## Expected Output

Scan Card...
UID: 53 7A B2 1C

Attendance Recorded

## Team Module

Module:
Registration and Check-In Using RFID

Hardware:
ESP32 + RC522 RFID Reader

Function:
Read RFID card UID and record user attendance.
