#define _CRT_SECURE_NO_WARNINGS
#include "Bits.h"

/** get value of the specific bit */
int getBit(unsigned char ch, int index)
{
	unsigned char mask = 1; // 00000001
	mask = mask << index;

	if ((ch & mask) == 0)
		return 0;
	else
		return 1;
}

/** set specific bit */
char setBitFromRight(unsigned char ch, int index, int value)
{
	unsigned char mask = 1; // 00000001
	unsigned char result;
	mask <<= index;

	if (value == 1)
		result = ch | mask;
	else
	{
		mask = ~mask;
		result = ch & mask;
	}
	return result;
}

/** encription function */
void encrypt(void* data, int elementSize, FILE* fileName)
{
	int x = rand() % (MAX_NUMBER + 1 - MIN_NUMBER) + MIN_NUMBER;
	int i, value, value_next;
	fprintf(fileName, "%d", x);
	unsigned char* current = (unsigned char*)data;

	for (i = 0; i < elementSize; i++)
	{
		value = getBit(current[i], x);
		if (x != 7)
		{
			value_next = getBit(current[i], x + 1);
			current[i] = setBitFromRight(current[i], x, value_next);
			current[i] = setBitFromRight(current[i], x + 1, value);
		}
		else
		{
			value_next = getBit(current[i], 0);
			current[i] = setBitFromRight(current[i], x, value_next);
			current[i] = setBitFromRight(current[i], 0, value);
		}

		unsigned char mask = MASK_1; // 11111111
		current[i] = current[i] ^ mask; //xor with 1

		unsigned char temp1 = current[i] >> x;
		unsigned char temp2 = current[i] << (BYTE - x);
		current[i] = temp1 | temp2;
	}
}

/** decryption function */
void decrypt(void* data, int elementSize, FILE* fileName)
{
	int i, x, value, value_last;
	fscanf(fileName, "%1d", &x);
	unsigned char* current = (unsigned char*)data;
	for (i = 0; i < elementSize; i++)
	{
		unsigned char temp1 = current[i] << x;
		unsigned char temp2 = current[i] >> (BYTE - x);
		current[i] = temp1 | temp2;

		unsigned char mask = MASK_1; // 11111111
		current[i] = current[i] ^ mask; //xor with 1

		value = getBit(current[i], x);

		if (x != 7)
		{
			value_last = getBit(current[i], x + 1);
			current[i] = setBitFromRight(current[i], x, value_last);
			current[i] = setBitFromRight(current[i], x + 1, value);
		}
		else
		{
			value_last = getBit(current[i], 0);
			current[i] = setBitFromRight(current[i], x, value_last);
			current[i] = setBitFromRight(current[i], 0, value);
		}
	}
}