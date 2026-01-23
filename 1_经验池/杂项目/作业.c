#include <stdio.h> 
int main() 
{ 
	int y = 10; 
	do 
	{ 
		y--;
	} 
	while( --y ); 
	printf ("%d\n", y--); 
	return 0; 
}
