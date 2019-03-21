#ifndef __BITS_H
#define __BITS_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBER 7
#define MIN_NUMBER 0
#define BYTE 8
#define MASK_1 255 //11111111

int getBit(unsigned char ch, int index);
char setBitFromRight(unsigned char ch, int index, int value);
void encrypt(void* data, int elementSize, FILE* fileName);
void decrypt(void* data, int elementSize, FILE* fileName);

#endif // __BITS_H