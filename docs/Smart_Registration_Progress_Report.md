# Project Progress: Smart Registration & Finisher QR System

## 1. Project Overview & Target
---
Our sub-group is responsible for managing the entry and exit digital tracking for the campus 4km Run event. The system focuses on two core stages:
1. **Registration Gate (RFID Check-In):** An ESP32 microcontroller with an RC522 RFID reader is placed at the starting line to scan runners' cards, instantly sending pendaftaran data to our local Flask server.
2. **Finisher Line (QR Certificate Form):** At the end of the 4km run, finishers will scan a physical QR code that redirects them to a Google Form to log their Name and Matric Number for fast E-Certificate processing.

## 2. What We Have Done So Far
---
- [x] **RFID Hardware Setup:** Wired up the RC522 module to the ESP32 via SPI and tested tag UID detection successfully.
- [x] ** Flask Backend Server:** Built the core script for our Python Flask server (`server.py`) to listen for incoming check-in requests.
- [x] **Race Condition Guard:** Applied an OS-level lock (`threading.Lock()`) in Python to make sure the local `runners.csv` file doesn't corrupt when hundreds of runners scan their RFID tags at the exact same time during morning registration.
- [x] **Finisher QR Integration:** Created and generated the final QR code that links directly to our official Google Form data collector.

## 3. Current System Status
---
* **Hardware Connection:** The ESP32 successfully connects to the local network hotspot and pushes JSON payload data to the server IP (`http://10.70.27.228:5000/checkin`).
* **Database Logs:** The server correctly uses `os.path.exists()` to verify file status, open file streams, and update the runner's check-in status.
* **Finisher Form Readiness:** The Google Form endpoint is verified and ready to accept live inputs from runners on the event day.

## 4. Challenges & Solutions
---
* **Challenge: Data collision during peak registration**
  * *Solution:* When too many threads try to open and append data to `runners.csv` at the same time, it causes an OS race condition. We resolved this by wrapping the write-to-file logic inside a `with csv_lock:` critical section.
* **Challenge: Connection timeout between ESP32 and Server**
  * *Solution:* Extracted the exact live IPv4 address of the host laptop using `ipconfig` and updated the endpoint string inside the Arduino IDE config header.

## 5. Upcoming Tasks
---
- [ ] **Data Cross-Matching:** Prepare a quick script utility to match the local RFID check-in log with the Google Form spreadsheet rows to confirm valid participants before certificate distribution.
- [ ] **Hardware Enclosure Box:** Assemble a small protective box to house the ESP32 board and power bank neatly at the registration counter.

## 6. Project Visuals
---
Example of the check-in data packet processed by our OS backend server:

```json
{
  "uid": "537AB21C",
  "status": "Checked-In"
}
