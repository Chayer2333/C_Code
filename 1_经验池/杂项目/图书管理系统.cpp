#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_BOOKS 100
typedef struct
{
	int  id,ISBN;
	char title[50];
	char author[50];
	int year;
	float price;
	char pub[50];
}Book;
	 
	 Book books[MAX_BOOKS];
	 int bookCount=0;
	 
	 void addBook();
	 void displayBooks();
	 void searchBookByTitle();
	 void sortBookByYear ();
	 void updateBookInfo();
	 void deletBook ();
	 void saveBooksToFile();
	 void loadBooksFromFile();
	 void printMenu();


	 
	 void printMenu(){
	 	  printf("\n图书管理系统\n");
	 	  printf("1.图书信息录入\n");
	 	  printf("2.图书信息浏览\n");
	 	  printf("3.按书名查询\n");
	 	  printf("4.按出版年份排列图书\n");
	 	  printf("5.修改图书信息\n");
	 	  printf("6.删除图书\n");
	 	  printf("7.退出系统\n");
	 	  printf("请选择(1-7):");
	 } 
	void addBook(){
	    	if(bookCount>=MAX_BOOKS){
	    		printf("图书数量已达到上限:\n");
	    		return ;
			} 
			books[bookCount].id=bookCount+1;
			printf("请输入图书的书名:\n");
			scanf("%s",books[bookCount].title);
			printf("请输入图书的作者:\n");
			scanf("%s",books[bookCount].author);
			printf("请输入ISBN号:\n");
			scanf("%d",&books[bookCount].ISBN);
			printf("请输入图书出版社:\n");
			scanf("%s",books[bookCount].pub);
			printf("请输入出版年份:\n");
			scanf("%d",&books[bookCount].year);
			printf("请输入图书价格:\n");
			scanf("%f",&books[bookCount].price); 
			bookCount++;
		    printf("图书添加成功。\n");
		}
	void displayBooks(){
			if(bookCount==0){
				printf("没有图书信息。\n");
				return ;
			}
			for(int i=0;i<bookCount;i++){
				printf("图书ID:%d\n",books[i].id);
				printf("书名:%s\n",books[i].title);
				printf("作者:%s\n",books[i].author);
				printf("ISBN号:%d\n",books[i].ISBN);
				printf("出版社:%s\n",books[i].pub);
				printf("出版年份:%d\n",books[i].year);
				printf("价格:%f\n",books[i].price);
				printf("-----------\n");
			}
		}
	void searchBookByTitle(){
			char title[50];
			printf("请输入要搜素图书的书名: ");
			scanf("%s",title);
			int found=0;
			for(int i=0;i<bookCount;i++){
				if(strcmp(books[i].title,title)==0){
					found=1;
					printf("找到图书信息。\n");
					printf("图书ID:%d\n",books[i].id);
					printf("书名:%s\n",books[i].title);
				    printf("作者:%s\n",books[i].author);
				    printf("ISBN号:%d\n",books[i].ISBN);
					printf("出版社:%s\n",books[i].pub);
					printf("出版年份:%d\n",books[i].year);
					printf("价格:%f\n",books[i].price);
					break;
				}
			}
		 	if(!found){
		 		printf("未找到图书。\n",title);
			 }
	 	}
	void sortBookByYear(){
		for(int i=0;i<bookCount-1;i++){
			for(int j=i+1;j<bookCount;j++){
				if(books[i].year>books[j].year){
					Book temp=books[i];
					books[i]=books[j];
					books[j]=temp;
				}
			}
		} 
		printf("图书以按年份排列。\n");
		displayBooks();
	} 	
	void updateBookInfo(){
		int id;
		printf("请输入要修改图书的ID:");
		scanf("%d",&id);
		for(int i=0;i<bookCount;i++){
			if(books[i].id==id){
				printf("请输入图书的书名:\n");
			scanf("%s",books[i].title);
			printf("请输入图书的作者:\n");
			scanf("%s",books[i].author);
			printf("请输入ISBN号:\n");
			scanf("%d",&books[i].ISBN);
			printf("请输入图书出版社:\n");
			scanf("%s",books[i].pub);
			printf("请输入出版年份:\n");
			scanf("%d",&books[i].year);
			printf("请输入图书价格:\n");
			scanf("%f",&books[i].price); 
			saveBooksToFile();
			printf("图书信息修改成功。\n");
			return ;
			}
		}
		printf("未找到图书。\n",id);
	}
	void deleteBook(){
		int id;
		printf("请输入要删除的图书ID:");
		scanf("%d",&id);
		int found=0;
		for(int i=0;i<bookCount;i++){
		if(books[i].id==id){
			found=1;
			for(int j=i;j<bookCount-1;j++){
				books[j]=books[j+1];
				books[j].id=j+1;
			}
			bookCount--;
			saveBooksToFile();
			printf("图书删除成功。\n");
			break;
		}
		}
		if(!found){
		printf("未找到图书。\n",id);
		}		
	}
	void saveBooksToFile() {
    FILE *file = fopen("books.dat", "wb");
    if (file == NULL) {
        printf("无法打开文件！\n");
        return;
    }
    fwrite(&bookCount, sizeof(int), 1, file);
    fwrite(books, sizeof(Book), bookCount, file);
    fclose(file);
}

void loadBooksFromFile() {
    FILE *file = fopen("books.dat", "rb");
    if (file == NULL) {
        printf("无法打开文件,将使用空数据库...\n");
        return;
    }
    fread(&bookCount, sizeof(int), 1, file);
    fread(books, sizeof(Book), bookCount, file);
    fclose(file);
}
    
    int main() {
    loadBooksFromFile();
    int choice;
    do {
        printMenu();
        scanf("%d", &choice);
        while (getchar() != '\n'); 
        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBookByTitle(); break;
            case 4: sortBookByYear(); break;
            case 5: updateBookInfo(); break;
            case 6: deleteBook(); break;
            case 7:  printf("退出系统。\n"); break;
            default: printf("无效的选择，请重新选择。\n");
        }
    } while (choice != 7);
    return 0;
}
	 
	 
	  
