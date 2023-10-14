/* 
 
 Created by:- Rishi Tiwari
 Website:- TrickSumo.com
 Video Tutorial:- https://youtu.be/nLzC0-VaqDs
 
 Libraries used:- 

https://github.com/mobizt/Firebase-ESP8266/

*/

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <DHT.h>   
               
#define FIREBASE_HOST "fir-iot-90bb8-default-rtdb.firebaseio.com"                     //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "0YqlS2Tc9lplQZzKjpnw4N0eQLyxGcQrytjmpnFa" //Your Firebase Database Secret goes here

#define WIFI_SSID "Abhishek"                                               //WiFi SSID to which you want NodeMCU to connect
#define WIFI_PASSWORD "Abhi#2171"                                      //Password of your wifi network 
 
#define DHTPIN 10                                            // Digital pin connected to DHT11
#define DHTTYPE DHT11                                        // Initialize dht type as DHT 11
DHT dht(DHTPIN, DHTTYPE);                                                  

// Declare the Firebase Data object in the global scope
FirebaseData firebaseData;

// Declare global variable to store value
int val=0;

void setup() {

  Serial.begin(115200);                                   // Select the same baud rate if you want to see the datas on Serial Monitor
  dht.begin(); 
  Serial.println("Serial communication started\n\n");  
           
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);


  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   // connect to firebase

  Firebase.reconnectWiFi(true);
  delay(1000);
}

void loop() { 
 float h = dht.readHumidity();                                 // Read Humidity
 float t = dht.readTemperature();                              // Read temperature
  if (isnan(h) || isnan(t))                                     // Checking sensor working
  {                                   
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  } 

// Firebase Error Handling And Writing Data At Specifed Path************************************************


if (Firebase.setInt(firebaseData, "/Humidity", h)) {    // On successful Write operation, function returns 1  
               Serial.println("Value Uploaded Successfully");
               Serial.print("Humidity = ");
               Serial.println(h);
               Serial.println("\n");
               val++;
               delay(1000);

     }
if (Firebase.setInt(firebaseData, "/Temperture", t)) {    // On successful Write operation, function returns 1  
               Serial.println("Value Uploaded Successfully");
                Serial.print("%  Temperature: ");  
                Serial.print(t);  
                Serial.println("°C ");
               Serial.println("\n");
               delay(1000);

     }
else {        
    Serial.println(firebaseData.errorReason());
  }

}
