#pragma once

//msg
#define BUILD_NETWORK 1
#define GET_REQUEST 2
#define SET_REQUEST 3
#define GET_RESPONSE 4
#define TRAP 5
#define NETWORK 6

//parameters
//parameters
#define TIME_TO_REBUILD_NETWORK 60000 // every 2 minthe minutes 
#define NUMBER_ATTEMPTS_SEND_MESSAGE 2
#define TIME_TO_GET_ACK 5000 // wait up to 5 seconds for response

#define PARAM_TIME_TO_REBUILD_NETWORK 1
#define PARAM_NUMBER_ATTEMPTS_SEND_MESSAGE 2
#define PARAM_TIME_TO_GET_ACK 3


#define REQUEST_ID_SIZE 2
#define KEY_SIZE 2
#define PARAM_DATA_SIZE 50 
#define HEADER_SIZR 4
#define GET_REQ_SIZE 11 //6+1+4
#define SET_REQ_SIZE 72 //6+2+max 32 param * 2 bytes
#define GET_RES_SIZE 76 //6+1+5+max 32 param * 2 bytes
#define TRAP_SIZE 11 //6+1+5+max 32 param * 2 bytes
#define NETWORK_SIZE 76 //6+1+2+1+2++max 32 param * 2 bytes
#define MAX_SIZE 76 
#define SON_SIZE 10
#define FATHERS_SIZE 10