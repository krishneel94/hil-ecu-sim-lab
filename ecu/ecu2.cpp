
// ECU 2: Climate ECU
#include <SPI.h>
#include <mcp_can.h>

const int SPI_CS_PIN = 10;
MCP_CAN CAN(SPI_CS_PIN);
const int FAN_PIN = 3;  // Connect LED here

void setup() {
  pinMode(FAN_PIN, OUTPUT);
  Serial.begin(115200);
  while (CAN_OK != CAN.begin(CAN_500KBPS)) {
    Serial.println("CAN BUS Init Failed");
    delay(100);
  }
  CAN.init_Mask(0, 0, 0x7FF);         // Accept all
  CAN.init_Filt(0, 0, 0x101);         // Filter to only 0x101 from Engine ECU
  Serial.println("CAN BUS Ready");
}

void loop() {
  byte len = 0;
  byte buf[8];

  if (CAN_MSGAVAIL == CAN.checkReceive()) {
    CAN.readMsgBuf(&len, buf);
    if (CAN.getCanId() == 0x101) {
      int tempC = buf[2];

      if (tempC > 90) {
        digitalWrite(FAN_PIN, HIGH); // Fan ON
      } else {
        digitalWrite(FAN_PIN, LOW);  // Fan OFF
      }

      // Optionally send fan status
      byte status = tempC > 90 ? 1 : 0;
      CAN.sendMsgBuf(0x220, 0, 1, &status);
    }
  }
}
