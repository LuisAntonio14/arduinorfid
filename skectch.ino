#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5   // Pin 5 para SS (SDA) del RC522
#define RST_PIN 22 // Pin 22 para Reset del RC522

const char* ssid = "WIFI UTC EdificioH";         // Reemplaza con el nombre de tu red WiFi
const char* password = "utcalvillo"; // Reemplaza con la contraseña de tu red
const char* serverUrl = "https://turistas.onrender.com/esp32/estado"; // URL base de tu API

MFRC522 mfrc522(SS_PIN, RST_PIN); // Creamos el objeto para el RC522

void setup() {
    Serial.begin(115200);
    SPI.begin();
    mfrc522.PCD_Init();
    
    Serial.println("Conectando a WiFi...");
    WiFi.begin(ssid, password);

    // Esperar conexión
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("\nConectado a WiFi");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());

    // Probar conexión con la API
    testAPIConnection();
}

void loop() {
    // Puedes agregar lógica para leer la tarjeta RFID aquí si quieres.
}

void testAPIConnection() {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(String(serverUrl) + "/"); // Intentamos conectar al servidor
        int httpCode = http.GET(); // Hacemos una petición GET

        if (httpCode > 0) {
            Serial.print("Respuesta del servidor: ");
            Serial.println(httpCode);
            String payload = http.getString();
            Serial.println("Respuesta:");
            Serial.println(payload);
        } else {
            Serial.print("Error en la conexión: ");
            Serial.println(http.errorToString(httpCode).c_str());
        }
        
        http.end();
    } else {
        Serial.println("No hay conexión a Internet");
    }
}
