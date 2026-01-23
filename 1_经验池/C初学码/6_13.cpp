/*
定义一个4×4的二维数组array，数组元素的值由表达式array[i][j]=i+j得到，按矩阵形式输出array。
0 1 2 3
1 2 3 4
2 3 4 5
3 4 5 6
行标i：0           1          2          3           (0~3)
列标j: 0,1,2,3     0,1,2,3    0,1,2,3    0,1,2,3     (0~3)
*/
#include"stdio.h"
int main()
{
    int array[4][4];
    int i,j;
    for(i=0;i<4;i++){ //i=0 1 2 3 4  //按表达式对二维数组元素赋值
   	    for(j=0;j<4;j++){//j=0 1 2 3 4
   	    //array[0][0]=0 array[0][1]=1 array[0][2]=2 array[0][3]=3
   	    //array[1][0]=1 array[1][1]=2 array[1][2]=3 array[1][3]=4
   	    //array[2][0]=2 array[2][1]=3 array[2][2]=4 array[2][3]=5
   	    //array[3][0]=3 array[3][1]=4 array[3][2]=5 array[3][3]=6 
   	   		array[i][j]=i+j;
		}   
	}
    for(i=0;i<4;i++)   //按矩阵形式输出二维数组元素
    {
   	    for(j=0;j<4;j++){
		    printf("%d ",array[i][j]);
		}
	    printf("\n");
    }
    return 0;
}


//int a[][3]={{1,2},{},{4,5}};
//a[0][0]=1 a[0][1]=2 a[0][2]=0
//a[1][0]=0 a[1][1]=0 a[1][2]=0 
//a[2][0]=4 a[2][1]=5 a[2][2]=0
