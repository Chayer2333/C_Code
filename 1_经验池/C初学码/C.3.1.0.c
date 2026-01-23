#include <stdio.h>
int main()
{
	float x,y;
	printf("ÇëÊäÈëxµÄÖ»£º\n");
	scanf("%f",&x);
	if(x>=0)
	{
		y=5*x+4;
	}
	else
	{
		y=2*x+3;
	}
	printf("y=%.3f\n",y);
	return 0;
}
