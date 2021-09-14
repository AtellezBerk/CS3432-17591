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
	


}



char** tokenize(char* str){
		

}





void print_all_tokens(char** tokens){

}

int main(){
	printf("Please enter string: ");
	char word[1000];
	
	//Testing first two functions
	/*char blank = '\t';
	char blank2 = ' ';
	printf("%i\n", non_delim_character(blank));//1 true 0 false
	printf("%i\n", non_delim_character(blank2));
	*/
	
	scanf("%999[^\n]", &word);
	printf("\n%s\n", word);
	
	//*word_start test
	/*char* start = word;
	char place = *word_start(start);	
	printf("%c\n", place);
	*/
	char* end = word;
	char place = *end_word(end);
	//char* place1 = place+1;
	
	printf("%p Space\n", place);
	
	return 0;	
}
















