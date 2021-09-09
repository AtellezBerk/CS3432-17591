#include <stdio.h>

int main(){
	printf("Please enter string: ");
	char word[1000];
	scanf("%999[^\n]", &word);
	printf("\n%s\n", word);

	return 0;
}
