#define _CRT_SECURE_NO_WARNINGS
#include "Hotel.h"

/** Initialize hotel */
void initHotel(hotel_t* hotel)
{
	int numOfFloors, numOfRooms, i, j;
	printf("How many floors are there in the hotel?: ");
	scanf("%d", &numOfFloors);

	printf("How many rooms are there in each floor?: ");
	scanf("%d", &numOfRooms);

	hotel->numOfFloors = numOfFloors;
	hotel->numOfRooms = numOfRooms;
	hotel->matrix = (room_t**)malloc(sizeof(room_t*)*numOfFloors);

	for (i = 0; i < hotel->numOfFloors; i++)
	{
		hotel->matrix[i] = (room_t*)calloc(numOfRooms, sizeof(room_t));
		for (j = 0; j < hotel->numOfRooms; j++)
		{
			printf("\n%s %d %s", "Room number -", (i + 1) * 100 + j, ":\n\n");
			inputRoom(&(hotel->matrix[i][j]));
		}
		printf("\n");
	}
}

/** Print Hotel */
void printHotel(const hotel_t* hotel)
{
	int i, j;
	for (i = 0; i < hotel->numOfFloors; i++)
	{
		for (j = 0; j < hotel->numOfRooms; j++)
		{
			printf("\n%s %d %s", "Room number -", (i + 1) * 100 + j, ":\n\n");
			printRoom(&(hotel->matrix[i][j]));
		}
		printf("\n");
	}
}

/** Show specific attribute in rooms */
void chooseAttribute(const hotel_t* hotel)
{
	const char *strings[] = { "POOL_VIEW","BALCONY_VIEW","TEA_POT","WIFI","SOFA","TV","OCCUPATION" };
	int i, j, option, flag = 0;
	printf("The attributes of one room are:\n");
	for (i = 0; i < SIZE_OF_STRINGS; i++)
		printf("%d - %s\n", i + 1, strings[i]);
	printf("\nPlease enter a number of specific attribute from the list: ");
	scanf("%d", &option);

	while (option < ONE || option > SIZE_OF_STRINGS)
	{
		printf("Invalid Number.\nPlease enter a number of specific attribute from the list: ");
		scanf("%d", &option);
	}

	for (i = 0; i < hotel->numOfFloors; i++)
	{
		for (j = 0; j < hotel->numOfRooms; j++)
		{
			if ((getRoomAttribute(&(hotel->matrix[i][j]), (option - 1)) == 1) && (getRoomAttribute(&(hotel->matrix[i][j]), 6) == 0))
			{
				flag = 1;
				printf("\nRoom number %d is available and have %s in the room\n", (i + 1) * 100 + j, strings[(option - 1)]);
				printRoom(&(hotel->matrix[i][j]));
			}
		}
	}

	if (flag == 0)
		printf("There is no such free rooms with this attribute\n");
}

/** Check balcony attribute in the room */
void checkAttribute(int attribute, ...)
{
	va_list pointersToRooms;
	room_t* thisRoom = 0;
	va_start(pointersToRooms, attribute);
	thisRoom = va_arg(pointersToRooms, room_t*);

	while (thisRoom != NULL)
	{
		if (getRoomAttribute(thisRoom, attribute) == 1)
		{
			printf("\nRoom have Balcony View in the room-\n");
			printRoom(thisRoom);
		}
		thisRoom = va_arg(pointersToRooms, room_t*);
	}
	va_end(pointersToRooms);
}

/** encryption hotel function */
void encrypHotelRooms(hotel_t* hotel, FILE* txt, FILE* binary)
{
	int i, numOfFloors, numOfRooms;
	numOfFloors = hotel->numOfFloors;
	numOfRooms = hotel->numOfRooms;

	encrypt(&hotel->numOfFloors, sizeof(int), txt);
	encrypt(&hotel->numOfRooms, sizeof(int), txt);

	for (i = 0; i < numOfFloors; i++)
		encrypt(hotel->matrix[i], sizeof(room_t)*numOfRooms, txt);


	fwrite(&hotel->numOfFloors, sizeof(int), 1, binary);
	fwrite(&hotel->numOfRooms, sizeof(int), 1, binary);
	for (i = 0; i < numOfFloors; i++)
		fwrite(hotel->matrix[i], sizeof(room_t), numOfRooms, binary);
}

/** decryption hotel function */
void decrypHotelRooms(hotel_t* hotel, FILE* txt, FILE* binary)
{
	int i;
	fread(&hotel->numOfFloors, sizeof(int), 1, binary);
	fread(&hotel->numOfRooms, sizeof(int), 1, binary);

	decrypt(&hotel->numOfFloors, sizeof(int), txt);
	decrypt(&hotel->numOfRooms, sizeof(int), txt);
	hotel->matrix = (room_t**)malloc(sizeof(room_t*)*hotel->numOfFloors);

	for (i = 0; i < hotel->numOfFloors; i++)
	{
		hotel->matrix[i] = (room_t*)calloc(hotel->numOfRooms, sizeof(room_t));
		fread(hotel->matrix[i], sizeof(room_t), hotel->numOfRooms, binary);
		decrypt(hotel->matrix[i], sizeof(room_t)*hotel->numOfRooms, txt);
	}
}

/** free the hotel */
void freeTheHotel(hotel_t* theHotel)
{
	int i, j;
	for (i = 0; i < theHotel->numOfFloors; i++)
	{
		for (j = 0; j < theHotel->numOfRooms; j++)
		{
			free((&theHotel->matrix[i][j]));
		}
	}
}