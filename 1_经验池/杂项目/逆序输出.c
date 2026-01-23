#include <stdio.h>
int main()
{
	int a, b = 0, i;
	printf("请输入一个不大于五位数的数\n");
	do
	{
		if (scanf("%d", &a) != 1)
		{
			while (getchar() != '\n')
				; /* 清除错误输入 */
			printf("输入无效，请重新输入：\n");
			continue;
		}
		if (a < 0 || a > 99999)
		{
			printf("超过五位，请重新输入：\n");
			continue;
		}
		break;
	} while (1);
	for (i = 0; i < 5; i++)
	{
		b += a % 10;
		a /= 10;
		if (a <= 0)
			break;
		b *= 10;
	}
	printf("%d", b);
	return 0;
}
