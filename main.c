/*****************************/
/*   Brainfuck Interpreter   */
/*   Made by: Kevin Modding  */
/*****************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEBUG 0   //set to 1 to print "Hello World!" as a test

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

byte Cells[MAX_NUMBER_CELLS]; //We will have to null them

int main(int argc, char** argv){

	char src[MAX_CODE_SIZE];
	int curCell = 0; //Current Cell
	int flen = 0;    //File Length


	/*ZeroMemory*/
	memset(src, 0, MAX_CODE_SIZE);
	memset(Cells, 0, MAX_NUMBER_CELLS);

	if (!DEBUG){ //This variable is set manually at the beginning of the code
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

	}
	else{
		/*This debug string will print "Hello World!" */
		strcpy(src, "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.");
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


		/*Gotta test*/
		case START_LOOP:
			/*incase we start a loop with 0 as a value*/
			if (Cells[curCell] == 0){
				int occurences = 0;  //number of loops after it
				for (int a = i+1; a > srcLen; a++){
					if (src[a] == START_LOOP){
						occurences++; //we found another loop, we will have to skip his 'START_LOOP'
					}
					else if (src[a] == END_LOOP){
						if (occurences > 0){ occurences--; } //we have skipped a loop
						else{ break; } //gotta take a break
					}

				}
			}
			break;


		case END_LOOP:
			if (Cells[curCell] != 0){
				int occurences = 0;  //number of loops before it
				for (int a = i-1; a > 0; a--){
					if (src[a] == START_LOOP){
						if (occurences > 0){ occurences--; }
						else{ i = a - 1; break; }
					}
					else if (src[a] == END_LOOP){
						occurences++;
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
