#include <stdio.h> 
int main() 
{ 
	char c; 
	int v0=0, v1=0, v2=0; 
	do
	{ 
		switch (c=getchar()) 
		{ 
			case 'a': case 'A': 
			case 'e': case 'E': 
			case 'i': case 'I': 
			case 'o': case 'O': 
			case 'u': case 'U': v1+=1; 
			default : v0 += 1 ; v2+=1; 
		}
	} while (c!='\n'); 
	printf ("v0=%d,v1=%d,v2=%d\n",v0,v1,v2); 
	return 0; 
} 
