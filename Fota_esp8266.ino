#include <FS.h>
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <Firebase_ESP_Client.h>  

bool checkInternet();
void fcsDownloadCallback(FCS_DownloadStatusInfo info);
void downloadProgressCallback(size_t current, size_t total);

#define RX_PIN 3  // GPIO3 (RX) on ESP-01
#define TX_PIN 1  // GPIO1 (TX) on ESP-01
#define GPIO0_PIN 0  // GPIO0 on ESP-01
#define GPIO2_PIN 2  // GPIO2  on ESP-01
#define DATABASE_URL "https://fota-3324f-default-rtdb.firebaseio.com/" 
const char* ssid = "data"; 
const char* password = "xyzxyzxyz"; 
#define API_KEY "AIzaSyAoLcGR14GDer8bzOEIv7ZBqGdFC4y7nWw"
#define USER_EMAIL "ahmedesam1369@gmail.com"
#define USER_PASSWORD "01021271369"
#define STORAGE_BUCKET_ID "fota-3324f.appspot.com"

/* For UART */
SoftwareSerial espSerial(RX_PIN, TX_PIN);


// Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

bool start_send = true;
bool print_file = false;
bool taskCompleted = false;
fs::File file;
String uid;
bool new_version = false;
int size = 0;
bool signupOK = false;

void setup() {
  /* Connect to WIFI */
    Serial.begin(115200);
    Serial.println(); Serial.println("Hello");
    WiFi.begin(ssid, password);
    Serial.println("Connecting to Wi-Fi");
    unsigned long ms = millis();
    while (WiFi.status() != WL_CONNECTED) {
      delay(2000); 
      Serial.print(" . ");
      Serial.println(WiFi.status());
    }
    Serial.println("WiFi connected");
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.print(WiFi.status());

   /* GPIO Pins Setup  */
    pinMode(GPIO2_PIN, OUTPUT);
    pinMode(GPIO0_PIN, INPUT);

    /* Connecting to Firebase  */
    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;
    /* Sign up */
    if (Firebase.signUp(&config, &auth, "", "")){
      Serial.println("ok");
      signupOK = true;
    }else{
      Serial.printf("%s\n", config.signer.signupError.message.c_str());
    }
    Firebase.reconnectWiFi(true);
    fbdo.setResponseSize(4096);
    Firebase.reconnectNetwork(true);
    fbdo.setBSSLBufferSize(2048 /* Rx buffer size in bytes from 512 - 16384 */, 512 /* Tx buffer size in bytes from 512 - 16384 */);

   config.max_token_generation_retry = 5;
    Firebase.begin(&config, &auth);
    // if use SD card, mount it.
    // SD_Card_Mounting(); // See src/addons/SDHelper.h
    Serial.println("Getting User UID");
    while ((auth.token.uid) == "") {
      Serial.print('.');
      delay(1000);
    }
    uid = auth.token.uid.c_str();
    Serial.print("User UID: ");
    Serial.println(uid);

    /* UART */
    // // uart.begin(115200);
    //  espSerial.begin(115200);    // SoftwareSerial for ESP-01
}

void loop() {
  /* Check Internet Connections */
  Serial.println(); Serial.print("WiFi status: ");Serial.println(WiFi.status());
  // Check if the network has access to the internet
  if (WiFi.status() == WL_CONNECTED) {
    if (checkInternet()) {
      Serial.println("Internet access available");
    } else {
      Serial.println("No internet access");
    }
  } else {
    Serial.println("Not connected to Wi-Fi");
  }  
  /* Check if there is a new version of not */
  Serial.printf("Get bool new_version... %s\n", Firebase.RTDB.getBool(&fbdo, "/info/new_version", &new_version)  ? "OK" : fbdo.errorReason().c_str());
  if(new_version){
    Serial.printf("Get int size... %s\n", Firebase.RTDB.getInt(&fbdo, "/info/size", &size)  ? "OK"  : fbdo.errorReason().c_str());
    if (Firebase.ready()) {
      /* Start Download the file in esp */
        Serial.println("\nDownload file...\n");
        // The file systems for flash and SD/SDMMC can be changed in FirebaseFS.h.
        if (!Firebase.Storage.download(&fbdo, STORAGE_BUCKET_ID /* Firebase Storage bucket id */, "FOTA/firmware.hex" /* path of remote file stored in the bucket */, "/firmware.hex" /* path to local file */, mem_storage_type_flash /* memory storage type, mem_storage_type_flash and mem_storage_type_sd */, fcsDownloadCallback /* callback function */))
            Serial.println(fbdo.errorReason());
        else{
          Serial.println("File Downloaded Successfully");
          Serial.print("File Size: "); Serial.println(size); Serial.print("Byte");
          /* Set firmware_downloaded in firebase to true  */
          Serial.printf("Set firmware_downloaded to true... %s\n", Firebase.RTDB.setBool(&fbdo, "/info/firmware_downloaded", true) ? "ok" : fbdo.errorReason().c_str());
        }
     // Send pulse on GPIO 2 to tell the Nucleo u have new Update
      digitalWrite(GPIO2_PIN, HIGH);delay(50);   digitalWrite(GPIO2_PIN, LOW);delay(50);   
      digitalWrite(GPIO2_PIN, HIGH);delay(50);   digitalWrite(GPIO2_PIN, LOW);delay(50);     
      /* Set new_version in firebase to false  */     
      Serial.printf("Set new_version to false... %s\n", Firebase.RTDB.setBool(&fbdo, "/info/new_version", false) ? "ok" : fbdo.errorReason().c_str());
    }else{ /* There is no new firmware Do Nothing */ }

  }

  /* UART In and To Nucleo */
  // Serial for debugging
    if (Serial.available()) {
    char data = Serial.read();
    Serial.print("Received data from Nucleo: ");
    Serial.println(data);
    // Process the received data from ESP-01
    if (data == 'A') {
      // Perform action A ->  Blink  
    digitalWrite(GPIO2_PIN, HIGH); delay(2000);  
    digitalWrite(GPIO2_PIN, LOW);  delay(2000);  
    Serial.println("Action A performed");
    } else if (data == 'B') {
      // Perform action B -> Open file and send it
      if (!LittleFS.begin()) {
          Serial.println("Failed to mount LittleFS");
          return;}
     File firmwareFile = LittleFS.open("/firmware.hex", "r");
      if (!firmwareFile) {
      Serial.println("Failed to open firmware file");
      return;
      }
      while (firmwareFile.available()) {
      uint8_t buffer;
      size_t bytesRead = firmwareFile.read(&buffer, sizeof(buffer)); 
      // Send it via UART Send Byte by Byte 
      Serial.write(buffer);
      }
      start_send = false;
      firmwareFile.close();
      Serial.println("Action B performed");
    } else {
      // Unknown command
      Serial.println("Unknown command received");
    }
  }
  
  // SoftwareSerial for ESP-01
    if (espSerial.available()) {
      char data = espSerial.read();
      Serial.print("Received data from Nucleo: ");
      Serial.println(data);
      // Process the received data from Nucleo
      // Send response back to Nucleo
      espSerial.write(data);
    }


  /* GPIO 1 is Input When receive high on it */
  /* print file only for debugging */
  Serial.printf("Get bool print_file... %s\n", Firebase.RTDB.getBool(&fbdo, "/info/print_file", &print_file)  ? "OK" : fbdo.errorReason().c_str());
  start_send = digitalRead(GPIO0_PIN);
  if(start_send || print_file){
      /* Open the firmware and Send the firmware to Nucleo through UART */
    if (!LittleFS.begin()) {
          Serial.println("Failed to mount LittleFS");
          return;}
     File firmwareFile = LittleFS.open("/firmware.hex", "r");
      if (!firmwareFile) {
      Serial.println("Failed to open firmware file");
      return;
      }
      int counter = 0;
      while (firmwareFile.available()) {
      uint8_t buffer[128];
      size_t bytesRead = firmwareFile.read(buffer, sizeof(buffer)); 
      // Send it via UART
      // uart.write(buffer, bytesRead);
      
      // Print Data
      counter++;
      Serial.println();
      Serial.print(counter);
      Serial.print(" -> ");
      Serial.print(bytesRead);
      Serial.print("  ");
      Serial.printf("%s", buffer);
      Serial.println();
      }
      start_send = false;
      firmwareFile.close();
      Serial.println("Firmware file sent");
      /* Set firmware_flashed in firebase to true  */
      Serial.printf("Set firmware_flashed to true... %s\n", Firebase.RTDB.setBool(&fbdo, "/info/firmware_flashed", true) ? "ok" : fbdo.errorReason().c_str());
      Serial.printf("Set print_file to false... %s\n", Firebase.RTDB.setBool(&fbdo, "/info/print_file", false) ? "ok" : fbdo.errorReason().c_str());
    }else{ /* Do Nothing */ }

    delay(10000); // Wait for 10 seconds before checking again
}


bool checkInternet() {
  WiFiClient client;
  HTTPClient http;
  // Send a GET request to a well-known website
  http.begin(client, "http://www.google.com");
  int httpCode = http.GET();
  // Check the HTTP response code
  if (httpCode > 0) {
    http.end();
    return true;
  } else {
    http.end();
    return false;
  }
}

void downloadProgressCallback(size_t current, size_t total) {
  Serial.print("Download Progress: ");
  Serial.print(current);
  Serial.print(" / ");
  Serial.println(total);
}

// The Firebase Storage download callback function
void fcsDownloadCallback(FCS_DownloadStatusInfo info)
{
    if (info.status == firebase_fcs_download_status_init)
    {
        Serial.printf("Downloading file %s (%d) to %s\n", info.remoteFileName.c_str(), info.fileSize, info.localFileName.c_str());
    }
    else if (info.status == firebase_fcs_download_status_download)
    {
        Serial.printf("Downloaded %d%s, Elapsed time %d ms\n", (int)info.progress, "%", info.elapsedTime);
    }
    else if (info.status == firebase_fcs_download_status_complete)
    {
        Serial.println("Download completed\n");
    }
    else if (info.status == firebase_fcs_download_status_error)
    {
        Serial.printf("Download failed, %s\n", info.errorMsg.c_str());
    }
}