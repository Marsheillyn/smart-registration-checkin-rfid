#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>

// ==================================================================
// 📌 CONFIGURATION (INFO HOTSPOT & LAPTOP KAU)
// ==================================================================
const char* ssid = "ROG";              // Nama Hotspot telefon kau
const char* password = "qwertyuiop123";  // Masukkan password hotspot kau (GANTI DI SINI)

// Alamat IPv4 laptop kau yang kita semak guna 'ipconfig' tadi
const char* serverURL = "http://10.70.27.228:5000/checkin";

// Definisikan Pin SPI tepat ikut kedudukan wayar fizikal ESP32-S kau
#define SS_PIN    5   // Pin SDA di sensor ➡️ Pin G5/P5 di ESP32-S
#define RST_PIN   22  // Pin RST di sensor ➡️ Pin G22/P22 di ESP32-S

MFRC522 mfrc522(SS_PIN, RST_PIN); 

void setup() {
  Serial.begin(115200);
  SPI.begin();           // Hidupkan Bas Perkakasan SPI
  mfrc522.PCD_Init();    // Hidupkan Sensor MFRC522

  Serial.println("\n========================================");
  Serial.println("ESP32-S Smart Registration System (Excel Lokal)");
  Serial.println("========================================");

  // Sambungkan ke WiFi Hotspot ROG
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // Tunggu sehingga WiFi berjaya disambung
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n[INFO] WiFi Connected!");
  Serial.print("[INFO] IP Address ESP32-S: ");
  Serial.println(WiFi.localIP());
  Serial.println("[INFO] Sedia untuk scan kad RFID...");
  Serial.println("----------------------------------------");
}

void loop() {
  // Semak jika ada kad baru diletakkan pada sensor
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Semak jika nombor UID kad berjaya dibaca
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Ambil dan tukar UID kad kepada format String (Tulisan)
  String uidString = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) {
      uidString += "0";
    }
    uidString += String(mfrc522.uid.uidByte[i], HEX);
  }
  
  uidString.toUpperCase(); // Tukar tulisan jadi Huruf Besar
  
  Serial.println("\n----------------------------------------");
  Serial.print("UID Kad Di-scan: ");
  Serial.println(uidString);

  // Semak sambungan WiFi sebelum hantar data ke server laptop
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    // Mulakan sambungan HTTP ke Server Python Laptop (Flask)
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");

    // Bina data dalam format JSON untuk dihantar ke server
    String jsonPayload = "{\"uid\":\"" + uidString + "\"}";

    // Hantar data menggunakan kaedah HTTP POST
    int httpResponseCode = http.POST(jsonPayload);

    // Paparkan maklum balas dari Server Python
    Serial.print("HTTP Code: ");
    Serial.println(httpResponseCode);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.print("Server Response: ");
      Serial.println(response);
    } else {
      Serial.print("Error semasa hantar POST: ");
      Serial.println(http.errorToString(httpResponseCode).c_str());
    }

    http.end(); // Tutup sambungan HTTP
  } else {
    Serial.println("[ERROR] WiFi Terputus! Gagal hantar data.");
  }

  // Hentikan pembacaan kad semasa dan beri ruang untuk kad seterusnya
  mfrc522.PICC_HaltA();
  delay(1500); // Delay 1.5 saat sebelum boleh scan kad seterusnya
}
