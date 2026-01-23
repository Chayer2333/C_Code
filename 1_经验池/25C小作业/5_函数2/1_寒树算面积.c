#include<stdio.h>
#define Pi 3.1415926535
void area(int);

int main()
{
	int k;
	printf("可计算的图形形状: \n");
	printf(" 1.长方形\n 2.三角形\n 3.圆形\n 4.退出\n");
	printf("——————————————————");
	do{
		printf("\n\n请输入待计算的图形形状: ");
		scanf("%d",&k);
		if(k>=1&&k<=3)
            area(k);
        else if(k!=4)
            printf("无效输入，请重新选择！\n");
	}while(k!=4);
	printf("\n程序已退出。\n");
	return 0;
}



void area(int choice)
{
	float a,b,r;
   	switch(choice)
	   	{
       	case 1: 
		   {
			printf("\n请输入长,宽: ");
			scanf("%f,%f",&a,&b);
			printf("面积为：%.3f",a*b);
			break;
		   } 
       	case 2:
		   {
       		printf("\n请输入底,高: ");
			scanf("%f,%f",&a,&b);
			printf("面积为：%.3f",a*b/2);
			break;
		   }
       	case 3:
		   {
		   	printf("\n请输入半径: ");
			scanf("%f",&r);
			printf("面积为：%.3f",Pi*r*r);
			break;
		   }
		default:
    		break;
		}
}
