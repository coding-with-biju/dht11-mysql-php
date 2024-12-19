#include <ESP8266WiFi.h>
#include <DHT.h>

#define DHTPIN D4       // GPIO2 pin for DHT11
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Wi-Fi credentials
const char* ssid = "839";
const char* password = "8399009050";

// Server address
const char* server = "192.168.214.190";  // Replace with your Node.js server IP
const int port = 3000;

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected!");
    dht.begin();
}

void loop() {
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    if (isnan(temp) || isnan(hum)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }else{
        Serial.println(temp);
        Serial.println(hum);
    }

    // Prepare data
    String postData = "temperature=" + String(temp) + "&humidity=" + String(hum);
    Serial.println(postData);

    // Send data to server
    WiFiClient client;
    if (client.connect(server, port)) {
        client.println("POST /send-data HTTP/1.1");
        client.println("Host: " + String(server));
        client.println("Content-Type: application/x-www-form-urlencoded");
        client.print("Content-Length: ");
        client.println(postData.length());
        client.println();
        client.print(postData);
    }

    delay(5000);  // Send data every 5 seconds
}
