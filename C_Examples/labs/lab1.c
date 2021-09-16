#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

/* Return true (non-zero) if c is a whitespace characer

   ('\t' or ' ').

   Zero terminators are not printable (therefore false) */

bool delim_character(char c){
	if(c == ' ' || c == '\t'){
		return true;
	}
	return false;

}



/* Return true (non-zero) if c is a non-whitespace

   character (not tab or space).

   Zero terminators are not printable (therefore false) */

bool non_delim_character(char c){
	if(!delim_character(c)){
		return true;
	}
	return false;

}



/* Returns a pointer to the first character of the next

   space-separated word*/

char *word_start(char* str){
	
	if(*str == ' '){ //make sure that the character the string is on isn't a space
		*str++;
	}
	while(*str != '\0' && *str != ' '){ //checks for end or space
		*str++;
	}
	if(*str != '\0'){
		*str++;
	}
	return str;

}



/* Returns a pointer to the first space character of the zero

terminated string*/

char *end_word(char* str){
	while(*str != '\0' && *str != ' '){
		*str++;
	}
	return str;


}

// counts the number of words or tokens

int count_tokens(char* str){
	int counter = 0;
	if(*str == '\0')
		return 0;
	counter++;
	for(*str; *str != '\0'; *str++){
		if(*str == ' ' || *str == '\t'){
			if(*str+1 != '\0'){
				counter++;
			}
		}			

	}
	return counter;

}

/* Returns a freshly allocated zero-terminated vector of freshly allocated

   space-separated tokens from zero-terminated str.

   For example, tokenize("hello world string") would result in:

     tokens[0] = "hello"

     tokens[1] = "world"

     tokens[2] = "string"

     tokens[3] = 0

*/

char *copy_str(char *inStr, short len){
	char* word = (char*) malloc(len * sizeof(char));
	for(int i = 0; i < len; i++){
		word[i] = *inStr;
		*inStr++;
	}
	
	return word;
}



char** tokenize(char* str){	
	int len = count_tokens(str);
	char** tokens = (char**) malloc(len * sizeof(char));
	char* start = str;
	//printf("Hello, &c\n", &start);
	char* end = end_word(start);

	for(int i = 0; i < len; i++){
		printf("End - start: %d\n", end - start);
		tokens[i] = copy_str(start, end-start);
		start = word_start(end);
		end = end_word(start);
		
	}
	

	return tokens;
}





void print_all_tokens(char** tokens, int len){
	for(int i = 0; i < len; i++){
		printf("Token[%d] = %s\n", i, tokens[i]);
	}

}

int main(){
	printf("Please enter string: ");
	
	int str_size = 100;
	char* new_string = (char*) malloc(str_size * sizeof(char)); 		

	scanf("%99[^\n]", new_string);
	//printf("\n%s\n", new_string);
	
	char** tokens = tokenize(new_string);
	int len = count_tokens(new_string);
	print_all_tokens(tokens, len);
	
	//char* end = end_word(new_string);
	//printf("start: %d, end: %d, subtract: %d", new_string, end, end - new_string);

	return 0;	
}
















