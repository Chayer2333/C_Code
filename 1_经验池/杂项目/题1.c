#include<stdio.h> 
#define M 3 
#define N 4
int main( ) 
{ 
	int x[M][N] = {1, 5, 7, 4, 2, 6, 4, 3, 8, 2, 3, 1}; 
	int i, j, p; 
	for ( i = 0; i < M; i++) 
	{ 
		p = 0; 
		for ( j = 1; j < N; j++ ) 
		{ 
			if (x[i][p] < x[i][j]) 
			p=j; 
			printf ("The max value in line %d is %d\n", i, x[i][p]); 
		} 
	} 
	return 0; 
}
