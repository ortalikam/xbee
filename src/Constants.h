#pragma once

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