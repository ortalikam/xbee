#include <XBee.h>
#include <network.h>
#include <Constants.h>
XBeeResponse response = XBeeResponse();
XBee xbee = XBee();
// create reusable response objects for responses we expect to handle 
Rx16Response rx16 = Rx16Response();

Network network(xbee,&Serial);
 
//Buffer for receiving Serial data
uint8_t serialData[100] ;

///uint8_t* data  ;

struct dataStruct { 
  uint32_t sons[SON_SIZE]; // array of suns
  int sons_size=0; //how much sons exists

  uint32_t fathers[FATHERS_SIZE]; // array of fathers
  int father_size=0; //how much fathers exists

  //parameters    
  int time_to_rebuild_network; //define-1 , in microsecond
  int Number_attempts_send_message; //define-2 
  int Time_to_get_ack; //define-3 ,in microsecond 

  // מערך ציקלי של הודעות 
}myData;



void setup() {
  
  // start serial
  Serial1.begin(9600);
  Serial.begin(9600);
  xbee.setSerial(Serial1);
 network=Network(xbee,&Serial);
}

// continuously reads packets, looking for RX16 or RX64
void loop() {
    
    //serial
    if (Serial.available()) {
      Serial.readBytes(serialData, sizeof(serialData));

    if (serialData[0]==BUILD_NETWORK)  find_Neighbors();

    else if (serialData[0]=SET_REQUEST)  set_request();

    else if (serialData[0]=GET_RESPONSE)  get_request();
   }

  //xbee
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
          uint8_t option = rx16.getOption();
          Serial.print("option");
          Serial.println(option);

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
bool find_Neighbors() {
  String ids[SONSIZE];
  int idsNum = 0;

  if (!writeToWireless(addressTx, message[0])) { //sending "discover Neighbors" message
    //writeToSerial("error in sending find_Neighbors");
    return false;
  }
   
  radio.startListening();
  delay(100);
  while (radio.available(addressRx)) {
    //delay(100);
    char text[50] = "";
    radio.read(&text, sizeof(text));
    String newText(text);
    //writeToSerial(newText);
    String msg = newText.substring(0, strlen(message[1]));
    if (msg == message[1]) //id_
    {
      String idNumber = newText.substring(strlen(message[1]), strlen(text));
      ids[idsNum++] = idNumber;
      //writeToSerial(idNumber);
      
    }
    delay(1000);
  }
  for (int i=0;i<idsNum;i++)
    if (!handShake(ids[i])) {
      writeToSerial("error in handShake");
      return false;
    }
  return true;

}
