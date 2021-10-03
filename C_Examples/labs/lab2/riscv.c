#include <stdio.h>

#include <stdbool.h>

#include <stdlib.h> // malloc & free

#include <stdint.h> // use guaranteed 64-bit integers

#include "tokenizer.h" // Create header file and reference that

#include "memory.h" // built-in functions to read and write to a specific file



int32_t* reg; // Array of 32 32-bit registers



void init_regs();

bool interpret(char* instr);

void write_read_demo();

bool compare(char* str1, char* str2);

int get_length(char* str);

char* get_new_string(char* str);



/**

 * Initialize register array for usage.

 * Malloc space for each 32-bit register then initializes each register to 0.

 * Do not alter this function!

 */

void init_regs(){

	int reg_amount = 32;

	reg = malloc(reg_amount * sizeof(int32_t)); // 32 * 4 bytes

	for(int i = 0; i < 32; i++)

		reg[i] = i;

}







/**

 * Fill out this function and use it to read interpret user input to execute RV64 instructions.

 * You may expect that a single, properly formatted RISC-V instruction string will be passed

 * as a parameter to this function.

 */

bool interpret(char* instr){

	char** tokens = tokenize(instr, ' ');
	int len = count_tokens(instr, ' ');
	//print_all_tokens(tokens, len);

	//char* mem_file = "mem.txt";
	//int token_length = 0;
	int i;
	//int j;
	char** paren_word;	
	char* ptr;	

	if(compare(tokens[0], "LW")){
		char word[10];
		//Traverse the tokens start from 2nd token
		for(i = 1; i < len; i++){
			if(*tokens[i] == 'X'){
				*word = get_new_string(tokens[i]); //Remove X from word
				printf("%s\n", word);
			}
			else{
				printf("%s\n", tokens[i]); //in case of 8(X22)
				paren_word = tokenize(tokens[i], '(');
				print_all_tokens(paren_word, 2);
			}
		}
		return true;
	}
	else if(compare(tokens[0], "SW")){
		
		return true;
	}
	else if(compare(tokens[0], "ADD")){
		return true;
	}
	else if(compare(tokens[0], "ADDI")){
		return true;
	}
	
	return false;

}

char* get_new_string(char* str){
	int len = get_length(str) - 1;
	char word[len];
	int i;
	int j = 1;
	for(i = 0; i < len; i++){
		word[i] = str[j];
		j++;
	} 
	return *word;

}

char* get_new_string_has_paren(char* str){
	int len = get_length(str) - 2;
	char word[len];
	int i;
	int j = 1;
	for(i = 0; i < len; i++){
		word[i] = str[j];
		j++;
	}
	return *word;
	
}

bool compare(char* str1, char* str2){
	int len1 = get_length(str1);
	int len2 = get_length(str2);
	

	if(len1 != len2){
		return false;
	}
	

	for (int i = 0; i < len1; i++){
		if (str1[i] != str2[i]){
			return false;
		}
	}
	
	return true;

}

int get_length(char* str){
	int i = 0;
	while(str[i] != '\0'){
		i++;
	}
	return i;
}


/**

 * Simple demo program to show the usage of read_address() and write_address() found in memory.c

 * Before and after running this program, look at mem.txt to see how the values change.

 * Feel free to change "data_to_write" and "address" variables to see how these affect mem.txt

 * Use 0x before an int in C to hardcode it as text, but you may enter base 10 as you see fit.

 */

void write_read_demo(){

	int32_t data_to_write = 0xFFF; // equal to 4095

	int32_t address = 0x98; // equal to 152

	char* mem_file = "mem.txt";



	// Write 4095 (or "0000000 00000FFF") in the 20th address (address 152 == 0x98)

	int32_t write = write_address(data_to_write, address, mem_file);

	//if(write == (int32_t) NULL)
	//	printf("ERROR: Unsucessful write to address %0X\n", 0x40);
	int32_t read = read_address(address, mem_file);



	//printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read); // %lu -> format as an long-unsigned

}



/**

 * Your code goes in the main

 *

 */

int main(){

	// Do not write any code between init_regs

	init_regs(); // DO NOT REMOVE THIS LINE



	// Below is a sample program to a write-read. Overwrite this with your own code.

	//write_read_demo();
	
	printf("Input text into input.txt and separate words by spaces\n");
	
	//char input[100];
	char* input = (char*) malloc(100 * sizeof(char));
	//fgets(input, 100, stdin)
	//scanf("%99[^\n]", input)
	while(fgets(input, 100, stdin) != NULL){
		if(interpret(input)){
			printf("Valid\n");
		}
	}

	
	printf("Print Something\n");


	return 0;

}







