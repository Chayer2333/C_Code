#include <stdio.h>
int main()
{
	char x;
	scanf("%c",&x);
	if(x>='0'&&x<='9'){
		printf("\n  数字");
	}
	else if(x>='a'&&x<='z'){
		printf("\n  小写字母");
	}
	else if(x>='A'&&x<='Z'){
		printf("\n  大写字母");
	}
	else {
		printf("\n  其他类型");
	}
	return 0;
}
