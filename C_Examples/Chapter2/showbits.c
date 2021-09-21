#include <stdio.h>

    

void showbits( unsigned int x )

{

    int i=0;

    for (i = (sizeof(int) * 8) - 1; i >= 0; i--)

    {

       putchar(x & (1u << i) ? '1' : '0');

    }

    printf("\n");

}

unsigned int setbits(unsigned int x, int p, int n, unsigned int y){
	y = ~(~0 << n) & y; //get n right most bits of y only
	
	y = y << (p-n); //shift those n bits p-n to the left

	x = x & ~((~(~0 << n)) << (p-n)); //zero out n bits of x starting at p

	return x | y;
}

unsigned int invert(unsigned int x, int p int n){
	return setbits(x, p, n, ~x >> (p-n));

}

unsigned int rightrot(unsigned int x, int n){
	int i;
	for(i; i < n; i++){
		x = setbits(x >> 1, 16, 1, x); // assumes 16 bits

	}
	return x;

}


int main( void )

{

	int j = 5225;

   	printf("%d in binary \t\t ", j);

	/* assume we have a function that prints a binary string when given 

	a decimal integer 

    	*/

    	showbits(j);



    	/* the loop for right shift operation */

    	for (int m = 0; m <= 5; m++)

    	{

        	int n = j >> m;

        	printf("%d right shift %d gives ", j, m);

        	showbits(n);

    	}
	
	


    	return 0;

}

































