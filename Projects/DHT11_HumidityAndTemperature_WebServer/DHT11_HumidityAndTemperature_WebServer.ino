/*
 * January 2023
 * DTU course: 34338 Telecommunication programming projects with Arduino
 * Author(s): All group members
 *
 * The async webserver is inspired by this tutorial:
 * https://randomnerdtutorials.com/esp8266-dht11dht22-temperature-and-humidity-web-server-with-arduino-ide/
 */

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DHT.h>

#define RELAY_PIN 5
#define BUTTON_PIN 16
#define DHTPIN 12
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
AsyncWebServer server(80);

const char* ssid = "your_ssid";
const char* password = "your_password";

float temperature = 0.0;
int humidity = 0;

/*
VentilationState has 3 states: 
  0 = turn ventilation off for 5 seconds
  1 = turn ventilation on for 5 seconds
  2 = turn on/off automatically (default)
*/
int ventilationState = 2;

const char html_index[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>

  <head>
    <title> Smart Ventilation System </title>
    <meta name="viewport" content="width=device-width, initial-scale=1" charset="utf-8">
    <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  </head>

  <body>
    <h1> Bathroom temperature and humidity </h1>
    <div id="content-wrapper">
      <div class="measurement-container">
        <span> Temperature </span>
        <span><span id="temperature">%TEMPERATURE%</span>&degC <i id="thermometer-icon" class="fas fa-thermometer-half" style="color:#059e8a;"></i></span>
      </div>
      <div class="measurement-container">
        <span> Humidity </span>
        <span> <span id="humidity">%HUMIDITY%</span>% <i id="humidity-icon" class="fas fa-tint" style="color:#00add6;"></i></span>
      </div>
      <span id="button-container"> 
        <button id="on-button" onclick="updateVentilation(true)"> Turn on ventilation </button>
        <button id="off-button" onclick="updateVentilation(false)"> Turn off ventilation </button>
      </span>        
    </div>
  </body>
  <script>
    function updateVentilation(state) {
      var xhttp = new XMLHttpRequest();
      if (state) {
        xhttp.open("GET", "/ventilationState?state=1", true);
      }
      else {
        xhttp.open("GET", "/ventilationState?state=0", true);
      }
      xhttp.send();
    }
    
    setInterval(function ( ) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("temperature").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "/temperature", true);
      xhttp.send();
    }, 1000 );

    setInterval(function ( ) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("humidity").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "/humidity", true);
      xhttp.send();
    }, 1000 );      
  </script>
  <style>
    body {
      background-color: #112233;
    }
    html {
      font-family: Arial;
      font-size: 40px;
      color: #aaaacc; 
    }
    h1 {
      text-align: center;
      font-size: 50px;
      font-family: Verdana;
    }
    button {
      width: 140px;
      height: 100px;
      border-radius: 10px;
      transition-duration: 0.2s;
      font-size: 25px;
      background-color: #aaaacc;
      cursor: pointer;
    }
    #on-button:hover {
      background-color: green;
    }
    #off-button:hover {
      background-color: #c62222;
    }
    #on-button:active {
      background-color: #3e8e41;
      box-shadow: 0 1px #000;
      transform: translateY(2px);
    }
    #off-button:active {
      background-color: #c64242;
      box-shadow: 0 1px #000;
      transform: translateY(2px);
    }
    #button-container {
      width: 300px;
      display: flex;
      justify-content: space-between;
    }
    .measurement-container {
      display: flex;
      flex-direction: column;
      align-items: center;
      border-style: solid;
      height: 100px;
      width: 300px;
      border-radius: 10px;
    }
    #content-wrapper {
      display: flex;
      flex-direction: column;
      align-items: center;
      width: 100%;
      gap: 60px;
      margin-top: 80px; 
    }
  </style>
</html>
)rawliteral";


String processor(const String& var){  // Replaces placeholder values in the index HTML with the actual values
  if(var == "TEMPERATURE"){
    return String(temperature);
  }
  else if(var == "HUMIDITY"){
    return String(humidity);
  }
  return String();
}

void setup(){
  Serial.begin(115200);
  dht.begin();

  pinMode(BUTTON_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  
  // Connect to wifi
  WiFi.begin(ssid, password);  
  Serial.print("\nConnecting ...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected to ");
  Serial.println(WiFi.SSID());
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


  // Handlers for HTTP requests on webserver
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {  // Loads the default webpage
    request->send_P(200, "text/html", html_index, processor);
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request) {  // Sends the current temperature to the webserver when a GET request is made
    request->send_P(200, "text/plain", String(temperature).c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request) {  // Sends the current humidity to the webserver when a GET request is made
    request->send_P(200, "text/plain", String(humidity).c_str());
  });
  server.on("/ventilationState", HTTP_GET, [](AsyncWebServerRequest *request) {  // Updates the ventilationState when one of the buttons on the webpage sends a GET request with the new value as an argument
    if (request->hasParam("state")) { 
      ventilationState = request->getParam("state")->value().toInt();
    }
  });
    
  // Start the server
  server.begin();
  Serial.println("Server started"); 
}
 
void loop(){
  // DHT11 has a 1Hz sampling rate (collects data at most once every second)
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  delay(2000);  

  float tmp_humidity = dht.readHumidity();
  float tmp_temperature = dht.readTemperature();
  
  // If no numbers are read from the sensor, the loop restarts to get new sensor readings
  if (isnan(tmp_humidity) || isnan(tmp_temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  else {
    temperature = tmp_temperature;
    humidity = (int) tmp_humidity;
  }
  
  if (humidity >= 50) { 
    // Turn ventilation on when humidity >= 50 except if ventilationState = 0 (off)
    if (ventilationState == 0) {
      digitalWrite(RELAY_PIN, LOW);
      delay(5000);
      ventilationState = 2;
      return;      
    } else {
      digitalWrite(RELAY_PIN, HIGH);
    }
  }
  else {
    // Turn ventilation off when humidity < 50 except if ventilationState = 1 (on)
    if (ventilationState == 1) {
      digitalWrite(RELAY_PIN, HIGH);
      delay(5000);
      ventilationState = 2;
      return;
    }
    else {
      digitalWrite(RELAY_PIN, LOW);  
    }
  }
}
