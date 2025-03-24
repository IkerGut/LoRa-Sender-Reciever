#include <Arduino.h>
#include <HardwareSerial.h>

#define LORA_TX 17
#define LORA_RX 16
#define LED_PIN 2

unsigned long lastCheck = 0;
const long checkInterval = 5000; // Status check every 5 seconds

void sendCmd(String cmd) {
    Serial.print(">> Sending: ");
    Serial.println(cmd);
    
    Serial2.flush(); // Clear any pending data
    Serial2.println(cmd);
    delay(500);
    
    String response = "";
    unsigned long startTime = millis();
    
    while (millis() - startTime < 1000) {
        if (Serial2.available()) {
            char c = Serial2.read();
            if (c != '\0' && c != '\r') { // Filter out null and CR
                response += c;
            }
        }
    }
    
    response.trim();
    if (response.length() > 0) {
        Serial.print("<< Response: ");
        Serial.println(response);
        if (response.indexOf("OK") != -1) {
            digitalWrite(LED_PIN, HIGH);
            delay(100);
            digitalWrite(LED_PIN, LOW);
        }
    } else {
        Serial.println("<< No response!");
    }
}

void setup() {
    Serial.begin(115200);     // Debug console
    Serial2.begin(9600, SERIAL_8N1, LORA_RX, LORA_TX);
    pinMode(LED_PIN, OUTPUT);
    
    delay(2000);
    Serial.println("\n=== RYLR998 Receptor Iniciando ===\n");
    
    // Reset configuration
    sendCmd("AT+RESET");
    delay(1000);
    
    // Basic configuration with verification
    sendCmd("AT");
    delay(500);
    sendCmd("AT+MODE=0");  // Normal mode
    delay(500);
    sendCmd("AT+IPR=9600");
    delay(500);
    sendCmd("AT+ADDRESS=1");  // Set receiver address
    delay(500);
    sendCmd("AT+NETWORKID=5"); // Must match transmitter
    delay(500);
    sendCmd("AT+BAND=868500000");
    delay(500);
    sendCmd("AT+PARAMETER=10,7,1,7");
    delay(500);
    sendCmd("AT+CRFOP=15"); // Set max power
    
    Serial.println("\n=== Configuración Completada ===");
    Serial.println("Esperando mensajes del transmisor...\n");
    
    // Visual confirmation of ready state
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
}

void loop() {
    unsigned long currentMillis = millis();
    
    if (currentMillis - lastCheck >= checkInterval) {
        lastCheck = currentMillis;
        Serial.println("Sistema activo - " + String(currentMillis/1000) + "s");
    }
    
    if (Serial2.available()) {  // Changed from while to if
        String mensaje = Serial2.readStringUntil('\n');
        mensaje.trim();
        
        // More detailed debug
        Serial.print("Raw data [" + String(mensaje.length()) + " bytes]: ");
        for(int i = 0; i < mensaje.length(); i++) {
            Serial.print((byte)mensaje[i], HEX);
            Serial.print(" ");
        }
        Serial.println();
        
        if (mensaje.startsWith("+RCV=")) {
            digitalWrite(LED_PIN, HIGH);
            
            int firstComma = mensaje.indexOf(',');
            int secondComma = mensaje.indexOf(',', firstComma + 1);
            
            if (firstComma != -1 && secondComma != -1) {
                String sender = mensaje.substring(5, firstComma);
                String data = mensaje.substring(secondComma + 1);
                
                Serial.println("------------------------");
                Serial.println("Mensaje de: " + sender);
                Serial.println("Datos: " + data);
                Serial.println("RSSI: " + String(Serial2.available()) + " dBm");
                Serial.println("------------------------");
            }
            
            delay(100);
            digitalWrite(LED_PIN, LOW);
        }
    }
}