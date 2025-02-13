#include <stdio.h>
#define MAXLINE 1000    /* maximum input line size */

int getaline(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
int main()
{
    int len;              /* current line length */
    int max;              /* maximum length seen so far */
    char line[MAXLINE];   /* current input line */
    char longest[MAXLINE]; /* longest line saved here */

    max = 0;
    while ((len = getaline(line, MAXLINE)) > 0) 
	//pintf("Length is %i\n", len); //code goes on forver so I had to figure out why that is
        if (len > max) {
	    max = len;
	    copy(longest, line);
	}
    if (max > 0) {    /* there was a line */
        printf("%d\n", max);
	printf("%s", longest);
    }
    return 0;
}

/* getaline:  read a line into s, return length */
int getaline(char s[], int lim)
{
    int c, i;

    for (i = 0; (c=getchar())!=EOF && c!='\n'; ++i)
	if(i< lim-1){//Small edit to get the number of characters and to print only first 999
		s[i] = c;
	}
    if (c == '\n') {
	s[i] = c;
	++i;
    }
    s[i] = '\0';
    return i;
}

/* copy:  copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
