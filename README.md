# Proyecto LoRa: Transmisor y Receptor con RYLR998 y ESP32

## Descripción
Este proyecto permite la comunicación inalámbrica utilizando los módulos LoRa RYLR998, configurados en un sistema de transmisión y recepción con ESP32. El sistema usa comandos AT para configurar los módulos LoRa y permite la transmisión de mensajes entre dispositivos a través de radiofrecuencia.

## Requisitos

- **Hardware:**
  - 2 x ESP32 (uno como transmisor y otro como receptor)
  - 2 x Módulo LoRa RYLR998
  - Cables y fuentes de alimentación adecuadas

- **Software:**
  - [Arduino IDE](https://www.arduino.cc/en/software) o [PlatformIO](https://platformio.org/)
  - Librerías necesarias para ESP32 (si es necesario)
  
## Configuración

1. **Configuración del transmisor:**
   - Conecta el módulo LoRa RYLR998 al ESP32 usando los pines TX (17) y RX (16).
   - Asegúrate de que la velocidad de transmisión del puerto serie esté configurada a **9600 baudios**.
   - Sube el código del transmisor (`transmisor.ino`).
   - El código configura el LoRa para enviar mensajes periódicos con un contador.
  
2. **Configuración del receptor:**
   - Conecta el módulo LoRa RYLR998 al otro ESP32 usando los pines TX (17) y RX (16).
   - Sube el código del receptor (`receptor.ino`).
   - El receptor está esperando mensajes y los muestra por el puerto serie al recibirlos.

## Estructura del proyecto

- **`transmisor.ino`**: Código para el dispositivo transmisor.
- **`receptor.ino`**: Código para el dispositivo receptor.
  
## Comandos AT utilizados

Durante la configuración del transmisor y receptor, se utilizan los siguientes comandos AT para configurar el módulo LoRa:

- **`AT+MODE=0`**: Configura el modo de operación (modo normal).
- **`AT+IPR=9600`**: Configura la tasa de baudios del módulo LoRa a 9600.
- **`AT+ADDRESS=2`**: Configura la dirección del transmisor.
- **`AT+NETWORKID=5`**: Configura la red del LoRa.
- **`AT+BAND=868500000`**: Establece la frecuencia de operación (868 MHz).
- **`AT+PARAMETER=10,7,1,7`**: Ajusta los parámetros del LoRa.
- **`AT+CRFOP=15`**: Ajusta la potencia de transmisión del LoRa.

## Instrucciones para compilar y cargar

1. **Instalar el ESP32 en Arduino IDE o PlatformIO:**
   - Si estás utilizando **Arduino IDE**, ve a "Archivo" > "Preferencias" y añade el siguiente enlace en "Gestor de URLs de tarjetas adicionales":
     ```
     https://dl.espressif.com/dl/package_esp32_index.json
     ```
   - En **PlatformIO**, selecciona la plataforma ESP32.

2. **Subir el código:**
   - Conecta tu ESP32 al puerto USB.
   - Selecciona la tarjeta ESP32 adecuada y el puerto en tu IDE.
   - Sube el código correspondiente al transmisor y al receptor.

## Contribución

Si deseas contribuir, por favor haz un fork de este repositorio y abre un pull request con tus cambios.

## Licencia

Este proyecto está bajo la [MIT License](LICENSE).
