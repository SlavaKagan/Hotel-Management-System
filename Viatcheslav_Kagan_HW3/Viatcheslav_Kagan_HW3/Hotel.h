#ifndef __HOTEL_H
#define __HOTEL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "Room.h"
#include "Bits.h"

typedef struct
{
	int numOfFloors;
	int numOfRooms;
	room_t** matrix;
}hotel_t;

void initHotel(hotel_t* hotel);
void printHotel(const hotel_t* hotel);
void chooseAttribute(const hotel_t* hotel);
void checkAttribute(int attribute, ...);
void encrypHotelRooms(hotel_t* hotel, FILE* txt, FILE* binary);
void decrypHotelRooms(hotel_t* hotel, FILE* txt, FILE* binary);
void freeTheHotel(hotel_t* hotel);

#endif // __HOTEL_H
