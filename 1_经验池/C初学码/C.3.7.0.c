#include <stdio.h>
int main()
{
	float x;
	printf("请输入成绩：\n");
	scanf("%f",&x);
	if(x>=0&&x<=100){
		switch((int)(x/10)){
			case 10:
			case 9: printf(" 优秀 ");break;
			case 8: printf(" 良好 ");break;
			case 7: printf(" 中等 ");break;
			case 6: printf(" 及格 ");break;
			default:printf("不合格");
		}
	}
	else{
		printf("这不是成绩");
	}
	return 0;
}
