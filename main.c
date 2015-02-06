/*****************************/
/*   Brainfuck Interpreter   */
/*   Made by: Kevin Modding  */
/*****************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


typedef unsigned char byte;

/*Operators*/
#define INCREMENT_PTR '>'
#define	DECREMENT_PTR '<'
#define	INCREMENT_VAL '+'
#define	DECREMENT_VAL '-'
#define	OUTPUT_VAL    '.'
#define	INPUT_VAL     ','
#define	START_LOOP    '['
#define	END_LOOP      ']'



/*Globals variables related to the interpreter*/
#define MAX_NUMBER_CELLS 30000 //Each cells are a single byte
#define MAX_CODE_SIZE 100000 //Max size of the source code, that should be enough

byte Cells[MAX_NUMBER_CELLS]; //We will have to zero them

int main(int argc, char** argv){

	char src[MAX_CODE_SIZE];
	int curCell = 0; //Current Cell
	int flen = 0;    //File Length


	/*ZeroMemory*/
	memset(src, 0, MAX_CODE_SIZE);
	memset(Cells, 0, MAX_NUMBER_CELLS);

	if (argc < 2){
		printf("Usage:Brainfuck.exe \"Input file\"\nExample: Brainfuck.exe \"C:\\test.txt\"\n\n");
		getchar();
		return -1;
	}


	/*Get Source code*/
	FILE* in = fopen(argv[1], "r");
	if (in != NULL){
		fseek(in, 0, SEEK_END);
		flen = ftell(in);
		if (flen > MAX_CODE_SIZE){
			fclose(in);
			printf("File is too big! Max length: %i\n", MAX_CODE_SIZE);
			getchar();
			return -1;
		}
		fseek(in, 0, SEEK_SET);
		fread(src, flen, 1, in);
		fclose(in);
		
	}
	else{
		printf("File cannot be read! Try to move it to your desktop?\n");
		getchar();
		return -1;
	}

	int srcLen = strlen(src);

	/*Iterate through every char*/
	for (int i = 0; i < srcLen; i++){

		switch (src[i]){

		case INCREMENT_PTR:
			if (curCell == MAX_NUMBER_CELLS - 1) curCell = 0;
			else curCell++;
			break;

		case DECREMENT_PTR:
			if (curCell == 0) curCell = MAX_NUMBER_CELLS - 1;
			else curCell--;
			break;

		case INCREMENT_VAL:
			Cells[curCell]++;
			break;

		case DECREMENT_VAL:
			Cells[curCell]--;
			break;

		case OUTPUT_VAL:
			printf("%c", Cells[curCell]);
			break;

		case INPUT_VAL:
			printf("\nInput: ");
			Cells[curCell] = _getch();
			printf("\n");
			break;


			
		case START_LOOP:
			if (Cells[curCell] == 0){
				for (int a = i; a < srcLen; a++){
					if (src[a] == END_LOOP){
						i = a; break;
					}

					if (a == srcLen -1){ return -1; }
				}

			}
			break;


		case END_LOOP:
			if (Cells[curCell] != 0){
				for (int a = i; a > 0; a--){
					if (src[a] == START_LOOP){
						i = a - 1; break;
					}
					if (a == 1){ return -1; }
				}
			}
			break;


		}

	}

	printf("\n\n\n\n****----DONE----****");
	getchar(); getchar();
	return 0;
}
