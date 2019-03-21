//Viatcheslav Kagan 311763213
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Hotel.h"
#define FILE_TXT "hotel.txt"
#define FILE_BINARY "hotel.bin"

void main(int argc, char* argv[])
{
	srand((unsigned int)time(NULL));
	hotel_t theHotel;
	int fcontinue = 1, numOfRooms, option;
	FILE* f1 = NULL;
	FILE* f2 = NULL;

	if (argc == 2)
	{
		f1 = fopen(FILE_TXT, "r");
		f2 = fopen(FILE_BINARY, "rb");
		if (f1 == NULL || f2 == NULL)
		{
			printf("Failed opening the file. Exiting!\n");
			return;
		}

		decrypHotelRooms(&theHotel, f1, f2);
		printf("Load successfully!\n");
		fclose(f1);
		fclose(f2);
	}
	else
		initHotel(&theHotel);

	numOfRooms = theHotel.numOfRooms;
	if (numOfRooms >= N_ROOMS)
		checkAttribute(ROOM_BALCONY_VIEW, &(theHotel.matrix[0][0]), &(theHotel.matrix[0][1]), &(theHotel.matrix[0][2]), NULL);
	else
		printf("There is no 3 rooms in floor number 1, so let's go to the menu\n");

	do
	{
		printf("\nWelcome to the hotel! Now choose one of the following options:\n");
		printf("==============================================================\n");
		printf("\n\t1. Show all the room details in the hotel");
		printf("\n\t2. Show all the available rooms with the specific attribute");
		printf("\n\t0- Exit.\n\n");

		printf("Please enter your choice--> ");
		scanf("%d", &option);
		printf("\n");

		switch (option)
		{
			/*Show all the room details in the hotel*/
		case 1:
		{
			printHotel(&theHotel);
			break;
		}

		/*Show all the available rooms with the specific attribute*/
		case 2:
		{
			chooseAttribute(&theHotel);
			break;
		}

		/* Option to exit from the program*/
		case 0:
		{
			f1 = fopen(FILE_TXT, "w");
			f2 = fopen(FILE_BINARY, "wb");
			encrypHotelRooms(&theHotel, f1, f2);
			fclose(f1);
			fclose(f2);
			freeTheHotel(&theHotel);
			fcontinue = 0;
			break;
		}

		default:
			printf("Invalid option. Please try again \n\n");
			break;
		}
	} while (fcontinue == 1);
	printf("Thank you and Goodbye!");
}