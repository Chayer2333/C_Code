#include <stdio.h> 
#include <string.h> 
int main() 
{
	int i; 
	char s[20], str[3][20]; 
	for ( i = 0; i < 3; i++) 
	gets (str[i]); 
	strcpy (s,str[1]); 
	if( strcmp (s, str[2]) > 0) 
	strcpy (s, str[2]); 
	printf ("The min string is %s\n",s); 
	return 0;
} 
