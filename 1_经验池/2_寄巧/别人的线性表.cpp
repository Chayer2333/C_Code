#include <iostream>
using namespace std;
class listclass
{
    int *listptr;//指向线性表
    int nlen;
    int nelem;
    
	public:
	    listclass(int n=10)
	    {
	        nelem=0;
	        nlen=n;
	        if(n)
	            listptr=new int[n];
	        else
	            listptr=0;
	    }
	    
	    
	    ~listclass()
	    {
	        delete  listptr;
	    }
	    
	    
	    int elem(int n);
	    
	    int &elem(unsigned n)
	    {
	        return listptr[n];//返回线性表下标为n的元素的引用
	    }
	    
	    
	    int elem(void)
	    {
	        return nelem;
	    }
	    
	    
	    int len(void)
	    {
	        return nlen;
	    }
	    
	    
	    int getelem(int i)
	    {
	        if(i>=0 && i<nelem)
	            return listptr[i];//返回下标为i的元素的值
	        else
	        {
	            cout<<"下标越界"<<endl;
	            return -1;
	        }
	    }
	    void print(void);
};



int listclass::elem(int elem)//在线性表末尾添加一个元素
{
    if(nelem==nlen)//线性表已满
    {
        int *newptr;
        newptr=new int[nlen+10];
        for(int i=0;i<nelem;i++)
            newptr[i]=listptr[i];
        delete listptr;
        nlen+=10;
        listptr=newptr;//指向新线性表的空间
    }
    listptr[nelem++]=elem;
    return nelem;//返回新的元素数量
}



void listclass::print(void)
{
    for(int i=0;i<nelem;i++)
        cout<<listptr[i]<<'\t';
    cout<<endl;
}



int main()
{
    listclass list(6);//调用构造函数
    for(int i=0;i<5;i++)
        list.elem(i);
    cout<<"线性表的长度是："<<list.len()<<endl;
    cout<<"线性表的元素个数为:"<<list.elem()<<endl;
    cout<<"线性表的元素为:";
    list.print();
    list.elem(3u)=100;
    cout<<"线性表下标为3的元素的值为："<<list.elem(3u)<<endl;
    list.elem(20);
    list.elem(200);
    cout<<"现在的线性表的长度为："<<list.len()<<endl;
    cout<<"现在线性表中元素的个数为："<<list.elem()<<endl;
    //cout<<"12345678912345678912345678912345678123456789123456789\n";
    cout<<"现在线性表中的元素为：";
    list.print();
    cout<<"线性表中的最后一个元素为："<<list.getelem(list.elem()-1)<<endl;
    return 0;
}
