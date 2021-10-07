#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Return true (non-zero) if c is a whitespace characer

   ('\t' or ' ').

   Zero terminators are not printable (therefore false) */

bool delim_character(char c, const char s){

	if(c == s){
		return true;
	}

	return false;

}

/* Return true (non-zero) if c is a non-whitespace

   character (not tab or space).

   Zero terminators are not printable (therefore false) */



bool non_delim_character(char c, const char s){

	if(!delim_character(c, s)){
		return true;
	}

	return false;
}
/* Returns a pointer to the first character of the next

   space-separated word*/



char *word_start(char* str, const char s){	
	while(*str != '\0' && non_delim_character(*str, s)){ //checks for end or separator
		str++;
	}

	if(*str != '\0'){
		str++;
	}

	return str;



}
/* Returns a pointer to the first space character of the zero

terminated string*/



char *end_word(char* str, const char s){
	while(*str != '\0' && non_delim_character(*str, s)){
		str++;
	}

	return str;
}



// counts the number of words or tokens
int count_tokens(char* str, const char s){
	int counter = 0;
	if(*str == '\0')
		return 0;
	counter++;
	while(*str != '\0'){
		str++;
		if(delim_character(*str, s)){

			if(*str+1 != '\0'){
				counter++;
			}
		}	
				
	}

	return counter;



}
char *copy_str(char *inStr, short len){

	char* word = (char*) malloc(len * sizeof(char*));
	
	for(int i = 0; i < len; i++){
		
		word[i] = *inStr;
		inStr++;

	}
	//printf("Word: %s\n", word);
	word[len] = '\0';	

	return word;
}







char** tokenize(char* str, const char separator){	
	int len = count_tokens(str, separator);
	char** tokens = (char**) malloc(len * sizeof(char*));
	char* start = str;
	char* end = end_word(start, separator);
	for(int i = 0; i < len; i++){
		tokens[i] = copy_str(start, end-start);
			
		//printf("%s %d\n", tokens[i], end-start);
		
		start = word_start(end, separator);
		end = end_word(start, separator);
	}

	
	return tokens;

}
void print_all_tokens(char** tokens, int len){

	for(int i = 0; i < len; i++){

		printf("Token[%d] = %s\n", i, tokens[i]);

	}
}














