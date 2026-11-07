#include <WiFi.h>
#include "DHTesp.h"

#define DHTPIN 15     
#define LED_PIN 2     
#define BUZZER_PIN 4  

DHTesp dhtSensor;

// Wokwi හි ඇති නොමිලේ ලබාදෙන වර්චුවල් Wi-Fi විස්තර
const char* ssid = "Wokwi-GUEST";
const char* password = "";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println("Connecting to Wi-Fi...");

  dhtSensor.setup(DHTPIN, DHTesp::DHT22);
  
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // Wi-Fi වෙත සම්බන්ධ වීම
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  TempAndHumidity data = dhtSensor.getTempAndHumidity();

  if (dhtSensor.getStatus() != 0) {
    Serial.println(F("Failed to read from DHT sensor!"));
    delay(2000);
    return;
  }

  // උෂ්ණත්වය පාලනය කිරීම
  if (data.temperature > 30.0) {
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);
  } else {
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
  }

  // බ්‍රව්සරයෙන් කෙනෙක් කනෙක්ට් වුණොත් වෙබ් පේජය පෙන්වීම
  WiFiClient client = server.available();
  if (client) {
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {
          if (currentLine.length() == 0) {
            // HTTP Header එක යැවීම
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // HTML වෙබ් ඩෑෂ්බෝඩ් එක
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta http-equiv=\"refresh\" content=\"5\"></head>"); // තත්පර 5න් 5ට ඔටෝ රිෆ්‍රෙෂ් වීම
            client.println("<body><h1>Smart Cold Storage Monitor</h1>");
            client.println("<p><b>Temperature: </b>" + String(data.temperature) + " &deg;C</p>");
            client.println("<p><b>Humidity: </b>" + String(data.humidity) + " %</p>");
            if(data.temperature > 30.0) {
              client.println("<h3 style='color:red;'>⚠️ WARNING: High Temperature!</h3>");
            } else {
              client.println("<h3 style='color:green;'>System Normal</h3>");
            }
            client.println("</body></html>");
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
  }
  delay(2000);
}
