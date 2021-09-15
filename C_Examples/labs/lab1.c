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
	while(str != NULL && *str != ' '){
		str++;
	}
	str++;
	return str;

}



/* Returns a pointer to the first space character of the zero

terminated string*/

char *end_word(char* str){
	while(str != NULL && *str != ' '){
		str++;
	}
	return str;


}

// counts the number of words or tokens

int count_tokens(char* str){
	int counter = 0;
	if(str == NULL)
		return 0;
	counter++;
	for(str; str != NULL; str++){
		if(*str == ' ' || *str == '\t'){
			if(str+1 != NULL){
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
		i++;
		*inStr++;
	}
	
	return word;
}



char** tokenize(char* str){	
	int i = 0;
	int len = 0;
	char** result;
	char** temp = result;
	char* word = str;
	while(str[i] != '\0'){
		if(delim_character(str[i])){
			&temp = *copy_str(word, len);
			temp++;
			i++;
			word = str[i];
			len = 0;	
		}
		len++;
		i++;
	}	
	return result;
}





void print_all_tokens(char** tokens){
	int i = 0;
	while (tokens != NULL){
		printf("Token[%d] = %s", i, tokens);
		i++;
		tokens++;
	}

}

int main(){
	printf("Please enter string: ");
	//char word[1000];
	
	int str_size = 100;
	char* new_string = (char*) malloc(str_size * sizeof(char)); 		

	scanf("%99[^\n]", new_string);
	printf("\n%s\n", new_string);
	
	tokenize(new_string);


		

	return 0;	
}
















