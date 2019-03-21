#define _CRT_SECURE_NO_WARNINGS
#include "Room.h"

/** Initialize a room */
void inputRoom(room_t* theRoom)
{
	printf("Please enter the number of beds in the room: ");
	scanf("%d", &theRoom->numOfBed);
	const char *strings[SIZE_OF_STRINGS] = { "POOL_VIEW","BALCONY_VIEW","TEA_POT","WIFI","SOFA","TV","OCCUPATION" };

	int i, temp;
	for (i = 0; i < SIZE_OF_STRINGS; i++)
	{
		printf("Please enter if there is %s in the room by pressing (0-no, 1-yes): ", strings[i]);
		scanf("%d", &temp);
		while (temp < ZERO || temp > ONE)
		{
			printf("Invalid Number.\nPlease enter if there is %s in the room by pressing (0-no, 1-yes): ", strings[i]);
			scanf("%d", &temp);
		}
		theRoom->checkByte = theRoom->checkByte | temp << i;
	}
}

/** get specific attribute */
int getRoomAttribute(const room_t* theRoom, int index)
{
	return getBit(theRoom->checkByte, index);
}

/** print room function */
void printRoom(const room_t* theRoom)
{
	printf("\nThe number of beds in the room: %d", theRoom->numOfBed);
	printf("\nThe attributes of the room:\n");
	if (getRoomAttribute(theRoom, ROOM_POOL_VIEW) == 1)
		printf(" Pool_V |");
	
	if (getRoomAttribute(theRoom, ROOM_BALCONY_VIEW) == 1)
		printf(" Balcony_V |");

	if (getRoomAttribute(theRoom, ROOM_TEA_POT) == 1)
		printf(" Tea_Pot |");

	if (getRoomAttribute(theRoom, ROOM_WIFI) == 1)
		printf(" Wifi |");

	if (getRoomAttribute(theRoom, ROOM_SOFA) == 1)
		printf(" Sofa |");

	if (getRoomAttribute(theRoom, ROOM_TV) == 1)
		printf(" TV |");

	if (getRoomAttribute(theRoom, ROOM_OCCUPIED_ROOM) == 1)
		printf(" Room occupied |");
	printf("\n");
}