
#include<stdio.h>
#include<stdlib.h>

typedef int Status;
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef char TElemType;
typedef enum PointerTag{Link,Thread};


typedef struct BiThrNode{
	TElemType data;
	struct BiThrNode *lchild,*rchild;
	PointerTag LTag,RTag;
}BiThrNode,*BiThrTree;

BiThrTree pre;

Status CreateBiTree(BiThrTree &T)//引用调用
{
	char ch;
	scanf("%c",&ch);
	if(ch==' ')
		T=NULL;
	else
	{
		if(!(T=(BiThrNode*)malloc(sizeof(BiThrNode))))
			exit(OVERFLOW);
		T->data=ch;
		T->LTag=Link;
		T->RTag=Link;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return OK;	
}

Status PrintElement(TElemType e)
{
	printf("%c ",e);
	return OK;
}

Status InOrderTraverse_Thr(BiThrTree T,Status(*Visit)(TElemType e))
{
	BiThrTree p;
	p=T->lchild;
	while(p!=T)
	{
		while(p->LTag==Link)
			p=p->lchild;
		if(!Visit(p->data))
			return ERROR;
		while(p->RTag==Thread&&p->rchild!=T)
		{
			p=p->rchild;
			Visit(p->data);
		}
		p=p->rchild;
		
	}
	return OK;
}


void InThreading(BiThrTree p)
{
	if(p)
	{
		InThreading(p->lchild);
		if(!p->lchild)
		{
			p->LTag=Thread;
			p->lchild=pre;
		}
		if(!pre->rchild)
			{
				pre->RTag=Thread;
				pre->rchild=p;
			}
		pre=p;
		InThreading(p->rchild);	
	}
}


Status InOrderThreading(BiThrTree &Thrt,BiThrTree T)
{
	if(!(Thrt=(BiThrTree)malloc(sizeof(BiThrNode))))
		exit(OVERFLOW);
	Thrt->LTag=Link;
	Thrt->RTag=Thread;
	Thrt->rchild=Thrt;
	if(!T)	
		Thrt->lchild=Thrt;
	else
	{
		Thrt->lchild=T;
		pre=Thrt;
		InThreading(T);
		pre->rchild=Thrt;
		pre->RTag=Thread;
		Thrt->rchild=pre;
	}
	return OK;
}


int main()
{
	BiThrTree TT,thrt;
	printf("请按先序顺序输入树的元素\n");
	CreateBiTree(TT);
	InOrderThreading(thrt,TT);
	printf("线索化结果：\n");
	InOrderTraverse_Thr(thrt,PrintElement);
	printf("\n");
	return 0;
}