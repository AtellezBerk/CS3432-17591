#include <stdio.h>

float convert(float fahr){//funcion that converts from fahr to cel
	float cel;
	
	cel = (5.0 / 9.0) * (fahr - 32);	

	return cel;
}

int main(){
	int fahr;

	for (fahr = 0; fahr <= 300; fahr = fahr + 20)
		printf("%3d %6.1f\n", fahr, convert(fahr));
	return 0;
}
