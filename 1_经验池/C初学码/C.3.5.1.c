#include <stdio.h>
int main()
{
    float x;
    printf("请输入成绩：\n");
    scanf("%f",&x);
    if(x>=100.0||x<=0){
        printf("这不是成绩"); 
	}
	else if(x>=90){
		printf("优秀");
	}
	else if(x>=80){
		printf("良好");
	}
	else if(x>=70){
		printf("中等");
	}
	else if(x>=60){
		printf("及格");
	}
	else if(x>=0){
		printf("不合格");
	}
	return 0;
 } 
