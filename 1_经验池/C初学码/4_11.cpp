/*
判断一个整数能否被3或5整除。
*/
#include"stdio.h"
int main()
{
	int num;
	printf("Input num:\n");
	scanf("%d",&num);
	switch(num%3==0)
	{
	   case 0:
          switch(num%5==0)
		  {
		  case 0:
			  printf("%d不能被3或5整除！\n",num);
			  break;
		  case 1:
			  printf("%d只能被5整除！\n",num);
			  break;
		  }
		  break;
		case 1:
            switch(num%5==0)
			{
			case 0:
				printf("%d只能被3整除！\n",num);
			    break;
			case 1:
                printf("%d能被3或5整除！\n",num);
			    break;
			}
		break;
	}
	return 0;
}
