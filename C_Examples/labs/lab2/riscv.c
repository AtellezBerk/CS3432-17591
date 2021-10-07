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

char* get_new_string_has_paren(char* str);



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
	//printf("%s\n", instr);
	char** tokens = tokenize(instr, ' ');
	
	int len = count_tokens(instr, ' ');
	
	
	//print_all_tokens(tokens, len);

	int i;
	char** paren_word;
	int temp;
	int temp_word[3] = {0, 0, 0};	

	int32_t data_to_write;
	int32_t address;
	char* mem_file = "mem.txt";
	int32_t write;
	int32_t read = 0;
	char* word = (char*) malloc(1000 * sizeof(char));
	
	if(compare(tokens[0], "LW") || compare(tokens[0], "SW")){

		if(len != 3){
			return false;
		}
				
		//Traverse the tokens to remove X, start from 2nd token
		for(i = 1; i < len; i++){
			if(*tokens[i] == 'X'){
				
				word = get_new_string(tokens[i]); //Remove X
				temp_word[i-1] = atoi(word);
				
			}
			else{
				////For cases like 8(X22) separate with parenthesis
				paren_word = tokenize(tokens[i], '(');
			

				//print_all_tokens(paren_word, 2); //debugger
				word = get_new_string_has_paren(paren_word[1]);
				temp_word[i-1] = atoi(paren_word[0]);
				
				temp = atoi(word); 
				
				//printf("%s\n", word);//debugger
				//printf("%d\n", temp);// debugger
			
				//Have to move value by 4
				temp *= 4;
				
				temp_word[i-1] += temp;
				//printf("%s %s\n", paren_word[0], word2);
			}
		}
		if(compare(tokens[0], "LW")){
			//LW rd, imm(rs1) | x5 = Memory[x6 + 0]	
			data_to_write = (int32_t)temp_word[1];
	
			//printf("%d\n", temp_word[0]); 
			read = read_address(data_to_write, mem_file);
			reg[temp_word[0]] = read;
		}
		else{
			//SW x5, 40(x6) | Memory[x6 + 40] = x5
			//printf("%d\n", temp_word[1]);
			data_to_write = (int32_t)temp_word[0];
			address = (int32_t)temp_word[1];
			write = write_address(data_to_write, address, mem_file);
			
			if(write == (int32_t) NULL)
				printf("Error: Unsuccessful write to address %0X\n", 0x40);
			
		}
		//printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read);
		
		return true;
	}
	else if(compare(tokens[0], "ADD") || compare(tokens[0], "ADDI")){
		
		if(len != 4){
			return false;
		}
		
		for(i = 1; i < len; i++){

			if(*tokens[i] == 'X'){
				word = get_new_string(tokens[i]);
				temp_word[i-1] = atoi(word);
				//printf("tokens[i]: %s word: %s temp_word[i-1]: %d \n",tokens[i], word, temp_word[i-1]);	
			}
			else{
				temp_word[i-1] = atoi(tokens[i]);
			}
		
		}
		
		if(compare(tokens[0], "ADD")){
			//printf("%d\n", reg[temp_word[0]]);
			reg[temp_word[0]] = reg[temp_word[1]] + reg[temp_word[2]];

		}
		else{
			reg[temp_word[0]] = reg[temp_word[1]] + temp_word[2];
			
		}
			

		return true;
	}
	else if(compare(tokens[0],"AND") || compare(tokens[0],"OR")||compare(tokens[0],"XOR")){
		if(len != 4){
			return 4;
		}

		for(i = 1; i < len; i++){
			if(*tokens[i] == 'X'){
				word = get_new_string(tokens[i]);
				temp_word[i-1] = atoi(word);
				

			}
			else{
				return false;
			}
		}
		if(compare(tokens[0], "AND")){
			
			reg[temp_word[0]] = reg[temp_word[1]] & reg[temp_word[2]];
		
		}
		else if(compare(tokens[0], "OR")){
			reg[temp_word[0]] = reg[temp_word[1]] | reg[temp_word[2]];
		}
		else if(compare(tokens[0], "XOR")){
			reg[temp_word[0]] = reg[temp_word[1]] ^ reg[temp_word[2]];
		
		}
		
		return true;
	}

	
	return false;

}

char* get_new_string(char* str){
	int len = get_length(str) - 1;
	char* word = (char*)malloc(len * sizeof(char));
	int i;
	int j = 1;
	for(i = 0; i < len; i++){
		word[i] = str[j];
		j++;
	}
	word[len] = '\0';
	return word;

}

//Example will receive X29) so I will remove X and )
char* get_new_string_has_paren(char* str){
	int len = get_length(str) - 2;
	char* word = (char*)malloc(len * sizeof(char));
	int i;
	int j = 1;
	for(i = 0; i < len; i++){
		word[i] = str[j];
		j++;
	}
	word[len] = '\0';
	return word;
	
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

	//int32_t data_to_write = 0xFFF; // equal to 4095

	//int32_t address = 5; // equal to 152

	//char* mem_file = "mem.txt";



	// Write 4095 (or "0000000 00000FFF") in the 20th address (address 152 == 0x98)

	//int32_t write = write_address(data_to_write, address, mem_file);

	//if(write == (int32_t) NULL)
	//	printf("ERROR: Unsucessful write to address %0X\n", 0x40);
	//int32_t read = read_address(address, mem_file);



	//printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read); // %lu -> format as an long-unsigned

}


/**
 * Your code goes in the main
 *
 */
void print_regs(){
	int col_size = 10;
	for(int i = 0; i < 8; i++){
		printf("X%02i:%.*lld", i, col_size, (long long int) reg[i]);
		printf(" X%02i:%.*lld", i+8, col_size, (long long int) reg[i+8]);
		printf(" X%02i:%.*lld", i+16, col_size, (long long int) reg[i+16]);
		printf(" X%02i:%.*lld\n", i+24, col_size, (long long int) reg[i+24]);

	}
}

int main(){

	// Do not write any code between init_regs
	init_regs(); // DO NOT REMOVE THIS LINE
	print_regs();
	// Below is a sample program to a write-read. Overwrite this with your own code.
	//write_read_demo();
	//print_regs();
	
	printf("RV32 Interpreter.\nType RV32 instructions. Use upper-case letters and space as a delimiter.\nEnter 'EOF' character to end program\n");
	printf("Input text into input.txt or run the program manually, and separate words by spaces and immediates in memory with parenthesis\n\n");
	printf("Sample: LW X5 40(X6) or ADDI X5 X6 20 (Immediates in base 10 and everything must be uppercase)\n\n");
	

	char* input = (char*)malloc(1000 * sizeof(char));
	
	//bool is_null = false;
	//is_null = fgets(input, 1000, stdin) == NULL;
	
	
	while(fgets(input, 1000, stdin)){
		if(interpret(input)){
			printf("\n");
			print_regs();
			printf("\n");		
		}
		else{
			printf("Invalid command\n");
		}
		
	}

	
	printf("Thank you\n");


	return 0;

}







