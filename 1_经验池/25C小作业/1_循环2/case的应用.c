#include<stdio.h>
int main()
{
	char c;
	printf("这是一个饮料机 ,输入0时停止运行 :\n");
	for(;(c=getchar())!='0';)
	{
		if(c=='1'||'2'||'3'||'4'||'5')
		switch(c)
		{
			case '1':printf("经常用脑，多喝六个核桃\n");break;
			case '2':printf("农夫山泉有点甜\n");break;
			case '3':printf("喝汇源果汁，走健康之路\n");break;
			case '4':printf("你能品味的历史——国窖1573\n");break;
			case '5':printf("我是你的什么？你是我的优乐美啊\n");break; 
			//default :printf("输入错误请重新输入 :\n");
		}
		else printf("输入错误请重新输入 :\n");
	}
	printf("已关机"); 
	return 0;
} 
