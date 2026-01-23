#include <stdio.h>

int main()
{
	
	printf("1234567\tX\n"); // 光标会移动到第9个位置打印X
	printf("12345678\tX\n"); // 光标会移动到第17个位置打印X
	
	printf("\n\n"); 
	
	printf("%-8s\t%-8s\t%-8s\n", "Name", "Score", "Grade");
	printf("%-8s\t%-8d\t%-8s\n", "Alice", 90, "A");
	printf("%-8s\t%-8d\t%-8s\n", "Bob", 85, "B");
	
	printf("\n\n"); 
	
	printf("垂直制表符：\\v\n\n");
	printf("1234\v56789\n"); // 56789将从下一行的第5列开始打印
	
	printf("\n\n"); 
	
	//直接认为C语言中制表符\t表示8个空格符是不准确的，实际上制表符的作用是使光标定位到一个新的位置，
	//新位置之前的输出占用的列数为8的倍数，即将光标移动至最接近8倍的地方，使之后的输出从光标处开始进行。
	//1、当\t之前的字符所占输出列数在0~7时，将光标定位至第9列。
	//2、当\t之前的字符所占输出列数在8~15时，将光标定位至第17列......
	
	printf("123456781234567812345678\n");//line1
	printf("\ta\n");                     //line2
	printf("1234\ta\n");                 //line3
	printf("1234567\ta\n");              //line4
	printf("12345678\ta\n");             //line5
	printf("1234567812345\ta\n");        //line6
	printf("123456781234567\ta\n");      //line7
	printf("1234567812345678\ta\n");     //line8
	
	return 0;
}
