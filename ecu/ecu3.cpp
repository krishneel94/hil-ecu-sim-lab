
// ECU 3: Diagnostic ECU
#include <SPI.h>
#include <Ethernet.h>
#include <mcp_can.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);       // Static IP of this ECU
IPAddress server(192, 168, 1, 100);   // Your PC IP

EthernetClient client;
MCP_CAN CAN(10);

void setup() {
  Serial.begin(115200);
  Ethernet.begin(mac, ip);
  while (CAN_OK != CAN.begin(CAN_500KBPS)) {
    Serial.println("CAN BUS Init Failed");
    delay(100);
  }
  Serial.println("ECU 3 Ready");
}

void loop() {
  // TCP heartbeat
  if (client.connect(server, 5000)) {
    client.println("Diagnostic ECU 3: Online");
    client.stop();
  }

  // Log all CAN traffic
  byte len = 0;
  byte buf[8];
  if (CAN_MSGAVAIL == CAN.checkReceive()) {
    CAN.readMsgBuf(&len, buf);
    unsigned long canId = CAN.getCanId();

    Serial.print("CAN ID: 0x");
    Serial.print(canId, HEX);
    Serial.print(" Data: ");
    for (int i = 0; i < len; i++) {
      Serial.print(buf[i]);
      Serial.print(" ");
    }
    Serial.println();
  }

  delay(5000);  // send heartbeat every 5s
}
