#include<stdio.h>
void incre(); 
int x=3; 
int main() 
{ 
	int i; 
	for (i=1;i<x;i++)
	incre();
	return 0; 
} 
void incre() 
{ 
	static int x = 1; 
	x*=x+1; 
	printf("%d\n",x);  
}


