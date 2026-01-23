#include <stdio.h>
int main() 
{
    int year,year_0,month,day,totalday=0,i,sum=0;
    printf("Input 2005-7-28 after 2025-3-28:");
    scanf("%d-%d-%d",&year,&month,&day);
    while(year<2005 )
    {
		printf("the year is error,please input again:");
    	scanf("%d-%d-%d",&year,&month,&day);
    }
    for(year_0=2005;year_0<=year;year++)
	{    
		for(i=1;i<month;i++);
	    { 
			switch(i)
	    	{
	       		case 1:case 3:case 5:case 7:case 8:case 10:case 12:totalday=31;break;
	        	case 4:case 6:case 9:case 11:totalday=30;break;
	        	case 2:
	            	if(year%4==0&&year%100!=0||year%400==0)
	            		totalday=29;
	            	else
	            		totalday=28;break;
	    	}
			sum=sum+totalday;
		}
	    sum=sum+day;
	}
    printf("µÚ%dÌì\n",sum);
    return 0;
}
