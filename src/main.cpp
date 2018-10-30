#include <XBee.h>
#include "network.h"

XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
// create reusable response objects for responses we expect to handle 
Rx16Response rx16 = Rx16Response();
Rx64Response rx64 = Rx64Response();
 
Network network;


uint8_t option = 0;
uint8_t* data  ;

void setup() {
  
  // start serial
  Serial1.begin(9600);
  Serial.begin(9600);
  xbee.setSerial(Serial1);
  
  network=Network(xbee,Serial);

}

// continuously reads packets, looking for RX16 or RX64
void loop() {
    Serial.println("waiting..");

    
    xbee.readPacket();
    if (xbee.getResponse().isAvailable()) {
      // got something
      if (xbee.getResponse().getApiId() == RX_16_RESPONSE) {
        // got a rx packet
        if (xbee.getResponse().getApiId() == RX_16_RESPONSE) {
                xbee.getResponse().getRx16Response(rx16);
                if (rx16.isAddressBroadcast ())
                  Serial.println("Broadcast");
                else
                 Serial.println("not Broadcast");
        	data = rx16.getData();
           for (int i = 0; i < rx16.getFrameDataLength(); i++) {
            Serial.print("FrameData [");
            Serial.print(i, DEC);
            Serial.print("] is ");
            Serial.print(rx16.getData()[i], HEX);
            Serial.println("-");
          }                                            

          for (int i = 0; i < rx16.getDataLength(); i++) {
            Serial.print("payload [");
           Serial.print(i, DEC);
            Serial.print("] is ");
            Serial.print(rx16.getData()[i], DEC);
           }

        } 

      } else {
      	// not something we were expecting
        Serial.println("error ");
      }
    } else if (xbee.getResponse().isError()) {
       Serial.print("Error reading packet.  Error code: ");
       Serial.println(xbee.getResponse().getErrorCode());
      // or flash error led
    } 
      delay(1000);
}
