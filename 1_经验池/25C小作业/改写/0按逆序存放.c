#include <stdio.h>
#define SIZE 8
int main() {
    int data[SIZE];
    int pos,k;
    printf("ÇëÖð¸öÊäÈëÔªËØ£º\n");
    for(k=SIZE-1; k>=0; k--) 
	{
        scanf("%d", &data[k]);
    }
    pos=0;
    while (pos < SIZE) {
        printf("%4d", data[pos]);
        pos++;
    }
    return 0;
}

