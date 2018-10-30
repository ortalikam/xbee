#include "network.h"
#include "Constants.h"

Network::Network(XBee xbeeNet, HardwareSerial* serial) {
    this->xbeeNet=xbeeNet;
    this->serial=serial;
}


void  Network::writeToSerial(uint8_t* str){
    (*serial).println((char*)str);
}


XBeeResponse* Network::reciveXbee (int timeout){
     if (xbeeNet.readPacket(timeout)){  // got a response!
       return &xbeeNet.getResponse();
    }
    return NULL;
}

void Network::writeXbee(uint16_t dest, uint8_t TypeNumber, uint8_t* data, int dataSize){
     Tx16Request tx;
     int k=7;
    switch (TypeNumber)
	{       
	    case 1:                      //get-request
		    uint8_t header[HEADER_SIZR] = { 1,0,0,0};
		    uint8_t payload[GET_REQ_SIZE] = { header[0],header[1],header[2],header[3],TypeNumber,data[0],data[1],data[2],data[3] };
            tx = Tx16Request(dest, payload, HEADER_SIZR+GET_REQ_SIZE);
        break;
	    case 2:                      //set-request
		    uint8_t header[HEADER_SIZR] = { 1,0,0,0};
		    uint8_t payload[SET_REQ_SIZE] = { header[0],header[1],header[2],header[3],TypeNumber};
		    for (int i = 0; i < dataSize; i++,k++){
			    payload[k] = data[i];
		    }
		     tx = Tx16Request(dest, payload, k-1);
		    break;
	    case 3:                      //get-response
		    uint8_t header[HEADER_SIZR] = { 0,0,0,0};
		    uint8_t payload[SET_REQ_SIZE] = { header[0],header[1],header[2],header[3],TypeNumber };
		    for (int i = 0; i < dataSize; i++, k++){
			    payload[k] = data[i];
		    }
		    tx = Tx16Request(dest, payload, k-1);
		    break;
        case 4:                      //trap
            uint8_t header[HEADER_SIZR] = { 0,0,0,0};
            uint8_t payload[TRAP_SIZE] = { header[0],header[1],header[2],header[3],TypeNumber};
            for (int i = 0; i < dataSize; i++, k++){
                payload[k] = data[i];
            }
            tx = Tx16Request(dest, payload, k-1);
            break;
        case 5:
            uint8_t header[HEADER_SIZR] = { 0,0,0,0};
            uint8_t payload[NETWORK_SIZE] = { header[0],header[1],header[2],header[3],TypeNumber };
            for (int i = 0; i < dataSize; i++, k++){
                payload[k] = data[i];
            }
            tx = Tx16Request(dest, payload, k-1);
            break;
        default:
            break;
        }
    xbeeNet.send(tx);
}

