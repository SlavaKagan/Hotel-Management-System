#ifndef __ROOM_H
#define __ROOM_H

#include <stdio.h>
#include "Bits.h"

#define ROOM_POOL_VIEW 0
#define ROOM_BALCONY_VIEW 1
#define ROOM_TEA_POT 2
#define ROOM_WIFI 3
#define ROOM_SOFA 4
#define ROOM_TV 5
#define ROOM_OCCUPIED_ROOM 6
#define ZERO 0
#define ONE 1
#define SIZE_OF_STRINGS 7
#define N_ROOMS 3

typedef struct
{
	int  numOfBed;
	char checkByte; // 0- pool, 1- balcony, 2- tea, 3- wifi, 4- sofa, 5- tv, 6- occupied
} room_t;

void inputRoom(room_t* theRoom);
int getRoomAttribute(const room_t* theRoom, int index);
void printRoom(const room_t* theRoom);

#endif // __ROOM_H