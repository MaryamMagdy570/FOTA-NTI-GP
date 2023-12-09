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
bool file_downloaded = false;

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
     espSerial.begin(115200);    // SoftwareSerial for ESP-01
}
/*
 - 'A' : Blink  esp LED 
 - 'B' : Check if the network has access to the internet
 - 'C' : Check if there is new version or NOT
 - 'D' : Send hex File
 - 'E' : Send Size of hex file
 - 'F' : Check Wifi Connections 
 - else -> return 'E'
*/

void loop() {
  /* Check if there is a new version of not */
  Firebase.RTDB.getBool(&fbdo, "/info/new_version", &new_version);
  Firebase.RTDB.getBool(&fbdo, "/info/firmware_downloaded", &file_downloaded);
  if(new_version && (!file_downloaded)){
    espSerial.printf("Get int size... %s\n", Firebase.RTDB.getInt(&fbdo, "/info/size", &size)  ? "OK"  : fbdo.errorReason().c_str());
    if (Firebase.ready()) {
      /* Start Download the file in esp */
        espSerial.println("\nDownload file...\n");
        // The file systems for flash and SD/SDMMC can be changed in FirebaseFS.h.
        if (!Firebase.Storage.download(&fbdo, STORAGE_BUCKET_ID /* Firebase Storage bucket id */, "FOTA/firmware.hex" /* path of remote file stored in the bucket */, "/firmware.hex" /* path to local file */, mem_storage_type_flash /* memory storage type, mem_storage_type_flash and mem_storage_type_sd */, fcsDownloadCallback /* callback function */))
            espSerial.println(fbdo.errorReason());
        else{
          espSerial.println("File Downloaded Successfully");
          espSerial.print("File Size: "); Serial.println(size); Serial.print("Byte");
          /* Set firmware_downloaded in firebase to true  */
          espSerial.printf("Set firmware_downloaded to true... %s\n", Firebase.RTDB.setBool(&fbdo, "/info/firmware_downloaded", true) ? "ok" : fbdo.errorReason().c_str());
        }
    //  // Send pulse on GPIO 2 to tell the Nucleo u have new Update
    //   digitalWrite(GPIO2_PIN, HIGH);delay(50);   digitalWrite(GPIO2_PIN, LOW);delay(50);   
    //   digitalWrite(GPIO2_PIN, HIGH);delay(50);   digitalWrite(GPIO2_PIN, LOW);delay(50);     
    }else{ /* There is no new firmware Do Nothing */ }
  }
 
  // /* UART In and To Nucleo */
  // Serial for debugging
  //   if (Serial.available()) {
  //   char data = Serial.read();
  //   Serial.print("Received data from Nucleo: ");
  //   Serial.println(data);
  //   // Process the received data from Nucleo
  //   // Send response back to Nucleo
  //   Serial.write(data);
  //   Serial.write('d');
  // }
   // SoftwareSerial for ESP-01
    if (espSerial.available()) {
      char data = espSerial.read();
      espSerial.print("Received data from Nucleo: ");
      espSerial.println(data);
      // espSerial.write('y');
      // Process the received data from Nucleo
      if (data == 'A') {
      //  Blink  esp LED 
      digitalWrite(GPIO2_PIN, HIGH); delay(2000);  
      digitalWrite(GPIO2_PIN, LOW);  delay(2000);  
      espSerial.println("Blink  esp LED ");
    }else if (data == 'B') {
      // Check if the network has access to the internet
    if (WiFi.status() == WL_CONNECTED) {
      if (checkInternet()) {
        espSerial.write('Y');
        espSerial.println("  Internet access available  ");
      } else {
        espSerial.write('N');
        espSerial.println("No internet access");
      }
      } else {
        espSerial.write('N');
        espSerial.println("Not connected to Wi-Fi");
      }  
    }else if (data == 'C') {
      // Check if there is new version or NOT
      if(new_version){
        espSerial.write('Y');
      }else{
        espSerial.write('N');
      }
    } else if (data == 'D') {
      //  Open file and send it
      if (!LittleFS.begin()) {
          espSerial.println("Failed to mount LittleFS");
          espSerial.write('E');
          return;}
       File firmwareFile = LittleFS.open("/firmware.hex", "r");
      if (!firmwareFile) {
      espSerial.println("Failed to open firmware file");
      espSerial.write('E');
      return;
      }
      while (firmwareFile.available()) {
      uint8_t buffer[128];
      size_t bytesRead = firmwareFile.read(buffer, sizeof(buffer)); 
      espSerial.write(buffer, 128);
      }
      firmwareFile.close();
      /* Set firmware_flashed in firebase to true  */
      espSerial.printf("Set firmware_flashed to true... %s\n", Firebase.RTDB.setBool(&fbdo, "/info/firmware_flashed", true) ? "ok" : fbdo.errorReason().c_str());
      /* Set new_version in firebase to false  */     
      espSerial.printf("Set new_version to false... %s\n", Firebase.RTDB.setBool(&fbdo, "/info/new_version", false) ? "ok" : fbdo.errorReason().c_str());
      espSerial.println("firmware Send Successfully");
    
    } else if(data == 'E'){
      // Perform action E ->  Send Size of hex file  
       String numberString = String(size);
       espSerial.write(numberString.c_str());  
       espSerial.write("Hello");  
      //  espSerial.write(reinterpret_cast<const uint8_t*>(&size), sizeof(size)); 
      espSerial.println("Action E performed");
    } else if(data == 'F'){
      /* Check Internet Connections */
      espSerial.write('Y');
      espSerial.println(); 
      espSerial.print("WiFi status: ");
      espSerial.println(WiFi.status());

    }else {
      // Unknown command
      espSerial.write('E');
      espSerial.println("Unknown command received");
    }      
      // espSerial.write(sendData, 128);
    }
    // delay(10000); // Wait for 10 seconds before checking again
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