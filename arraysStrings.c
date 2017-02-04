#include "arraysStrings.h"

	//Part 1 - 2 points
	//write a function joinrev that takes 2 strings and returns a 3rd string that is the first string
    //followed by the 2nd string reversed
	char *joinrev(char* x, char* y) {
		//Made it into one string first like the instructions.
		char *result = malloc(strlen(x)+strlen(y)+1);//+1 for the zero-terminator
		strcpy(result, x);
		strcat(result, y);
		//Used the reverse method shown in class except reversed after first string.
		//Can't be done earlier because World is a string literal.
		int left=strlen(x), right=strlen(result)-1;
		char temp;
		while(left < right){
			temp=result[right];
			result[right]=result[left];
			result[left]=temp;
			left++;
			right--;
		}
		return result;
	}
	//Part 2 - 2 points
	//Write a function joinrev_generic that takes pointers to any two arrays, a typesize,
	//and the number of elements in each array and does the same
	//thing as joinrev except that it will return a void pointer and will work on any type of array.
	// HINT - copy the code from part 1 and change the code so that the pointer arithmetic is done explicitly
	//and the copies are done using memcpy and memmove as in the class example reverse3
	void *joinrev_generic(void* x, void* y, int typeSize, int nElementsX, int nElementsY) {
		//This creates the void pointer, and allocating the size for it.
		void* result = malloc(1 + typeSize*(nElementsX+nElementsY));
		//Starts at the end of the first array. This reverses the second part of the pointer.
		//Error: only the end (right) needs the -1 !
		char *left=(char*)x+(nElementsX)*typeSize, *right=(char*)y+(nElementsY-1)*typeSize;
		char temp[typeSize];
		while(left < right){
		  memcpy(temp,right,typeSize);
		  memmove(right,left,typeSize);
		  memcpy(left,temp,typeSize);
		  left+=typeSize;
		  right-=typeSize;
		 }
		//ERROR: Remember you have to have the pointer + the index or else it outputs allot of zeroes.
		//memcpy is faster but memmove is safer/reliable, this adds the arrays to the pointer.
		memcpy(result,x,(typeSize*nElementsX));
		memmove(result+(nElementsX*typeSize),y,(typeSize*nElementsY));
		return result;
	}

	//Part 3 - 2 points
	//Write a function readTextAddBinary that takes two strings (filenames)
    //and returns 0 if the function completes successfully.
    //The function reads from the first filename,  a set of vectors,
	//2 per line and add them together and writes out a binary file (the second filename) with the new vectors (just the vectors - no spaces or other delimiters)
    //A test file is given to you along with the expected output - you can use the Unix diff function to compare your output with the expected output in testFiles
	int readTextAddBinary(char *vectorsTxt, char *binaryFile){
		FILE *ifp=fopen(vectorsTxt,"r");
		FILE *ofp=fopen(binaryFile,"w");
		if(!ifp || !ofp) {
			return 1;
		}
		char line[1024];
		//fgets reads from a text file
		while (fgets(line,sizeof(line),ifp)){ //read in at most 1023 before truncating
			//Matching with the vectors.txt  1.x1,y1,z1 2.x2,y2,z2
			float x1, x2, y1, y2, z1, z2;
			sscanf(line, "%f %f %f %f %f %f \n", &x1, &y1, &z1, &x2, &y2, &z2);
			//creates the two vectors and then adds them.
			vector vector1 = vector_init(x1, y1, z1);
			vector vector2 = vector_init(x2,y2,z2);
			vector writtenVector = vector_add(vector1,vector2);
			//the function fwrite writes to bytes.
			fwrite(&writtenVector, sizeof(writtenVector), 1, ofp);
		}
		fclose(ifp);
		fclose(ofp);
		return 0;
	}
	//Part 4 - 2 points
	//Write a function readBinaryNormText that takes two strings as input (filenames)
   //and returns 0 if the function completes successfully.
   //The first argument is a binary file of type produced in part 3.
   //The function will read it in,  normalize a, and print out to the text file in argument 2,
   //the components, x,y,z, and length separated by tabs (all as one big line) ;
	int readBinaryNormText(char *binaryFile, char *normalFile){
		FILE *ifp=fopen(binaryFile,"r");
		FILE *ofp=fopen(normalFile,"w");
		if(!ifp || !ofp) {
			return 1;
		}
		// Since the binary file already contains the vectors I don't need to initialize it again...I think.
//		float x1, x2, y1, y2, z1, z2;
//		vector myVector = vector_init(x1 + x2, y1 + y2, z1 + z2);
		vector myVector;
		//We use fread rather than fgets in this case because it takes in raw data from the binary file.
		//reads the input
		while (fread(&myVector,sizeof(myVector), 1 ,ifp)){
			vector_normalize(&myVector);
			//we are just printing in this case. But we use fprintf because we are writing to a file.
			fprintf(ofp, "%f \t %f \t %f \t %f \t", myVector.x, myVector.y, myVector.z, myVector.length);
		}
		fclose(ifp);
		fclose(ofp);
		return 0;
	}
	//Part 5 - 2 points
	//Write a function readNormTextWriteNormBinary that takes two strings as input (filenames) and returns 0 if the function completes successfully..
    //The first argument is the text file of type produced in part 4.
	//Read in the line using fgets or fread. Either use realloc or check for the size of the file using fseek, ftell to allocate enough space to store the line.
	//Then use strtok to parse the file. Print the results out to a binary file in the same format as the binary file produced in part 3. Remember to free the memory.

	//	if(readNormTextWriteNormBinary("norm.txt","norm.bin")){
	//		fprintf(stderr,"A fatal error occurred for readNormTextWriteNormBinary\n");
	//		return 1;
	//	}
   

