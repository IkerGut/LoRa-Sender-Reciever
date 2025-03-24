#include <Arduino.h>
#include <HardwareSerial.h>

#define LORA_TX 17
#define LORA_RX 16
#define LED_PIN 2

int messageCount = 0;

void sendCmd(String cmd) {
    Serial.print(">> Sending: ");
    Serial.println(cmd);
    
    Serial2.println(cmd);
    delay(500);
    
    String response = "";
    unsigned long startTime = millis();
    
    while (millis() - startTime < 1000) {
        if (Serial2.available()) {
            char c = Serial2.read();
            if (c != '\0') {
                response += c;
            }
            if (c == '\n') break;
        }
    }
    
    response.trim();
    if (response.length() > 0) {
        Serial.print("<< Response: ");
        Serial.println(response);
        if (response.indexOf("+OK") != -1) {
            digitalWrite(LED_PIN, HIGH);
            delay(200);
            digitalWrite(LED_PIN, LOW);
        }
    } else {
        Serial.println("<< No response!");
    }
}

void setup() {
    Serial.begin(115200);
    Serial2.begin(9600, SERIAL_8N1, LORA_RX, LORA_TX);
    pinMode(LED_PIN, OUTPUT);
    
    delay(2000);
    Serial.println("\n=== RYLR998 Transmitter Starting ===\n");
    
    sendCmd("AT");
    delay(500);
    sendCmd("AT+MODE=0");
    delay(500);
    sendCmd("AT+IPR=9600");
    delay(500);
    sendCmd("AT+ADDRESS=2");
    delay(500);
    sendCmd("AT+NETWORKID=5");
    delay(500);
    sendCmd("AT+BAND=868500000");
    delay(500);
    sendCmd("AT+PARAMETER=10,7,1,7");
    delay(500);
    sendCmd("AT+CRFOP=15");
    
    Serial.println("\n=== Configuration Complete ===\n");
}

void loop() {
    messageCount++;
    String message = "Test" + String(messageCount);
    String cmd = "AT+SEND=1," + String(message.length()) + "," + message;
    
    Serial.println("------------------------");
    Serial.println("Sending message: " + message);
    Serial.println("Command: " + cmd);
    Serial.println("------------------------");
    
    sendCmd(cmd);
    delay(2000);
}