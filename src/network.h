// #ifndef Network_h
// #define Network_h
#include <XBee.h>
#include <Arduino.h>

class Network {
 public:
  
//     /**
// 	 * Default constructor
// 	 */
    Network( XBee xbeeNet,HardwareSerial* serial );
    void  writeToSerial(uint8_t* str);
 	void writeXbee(uint16_t dest,uint8_t TypeNumber, uint8_t* data, int dataSize);
    XBeeResponse* reciveXbee (int timeout);
    

private:
    XBee xbeeNet;
    HardwareSerial* serial;

// #endif //Network_h
}; //you must end the class definition with a semicolon.