// ECU 1: Engine ECU
#include <SPI.h>
#include <mcp_can.h>

const int SPI_CS_PIN = 10;
MCP_CAN CAN(SPI_CS_PIN);
const int TEMP_PIN = A0;     // TMP36 sensor
const int RPM_PIN = A1;      // Potentiometer

void setup() {
  Serial.begin(115200);
  while (CAN_OK != CAN.begin(CAN_500KBPS)) {
    Serial.println("CAN BUS Init Failed");
    delay(100);
  }
  Serial.println("CAN BUS Ready");
}

void loop() {
  int analogTemp = analogRead(TEMP_PIN);      // TMP36 output (0.01 V/°C + 0.5V offset)
  float voltage = analogTemp * (5.0 / 1023.0);
  int tempC = (voltage - 0.5) * 100;

  int analogRpm = analogRead(RPM_PIN);        // 0–1023 → 0–8000 RPM scale
  int rpm = map(analogRpm, 0, 1023, 0, 8000);

  byte data[3];
  data[0] = (rpm >> 8) & 0xFF;
  data[1] = rpm & 0xFF;
  data[2] = tempC;

  CAN.sendMsgBuf(0x101, 0, 3, data);
  delay(1000);
}
