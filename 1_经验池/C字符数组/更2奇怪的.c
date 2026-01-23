#include <stdio.h> 
#include <string.h> 
int main() 
{
	char a[7] = "abcde";
	char b[4] = "ABC";
	strcpy (a, b); 
	printf ("%c", a[3]);
	return 0; 
} 
