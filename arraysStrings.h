//other includes are necessary
//SUPER ERROR DO NOT INCLUDE vectors.c OR YOU WILL NUKE THE WORLD!!!!!!!
#include "vectors.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//fill in the parameters and return type
//Can these be pointers?
char * joinrev(char* x, char* y);
//Since any two arrays do I use voids?
void* joinrev_generic(void* a1, void* a2, int typeSize, int nElementsX, int nElementsY);
int readTextAddBinary(char *vectorsTxt, char *binaryFile);
int readBinaryNormText(char * binaryFile, char * normalFile);
//readNormTextWriteNormBinary();
//wc();
