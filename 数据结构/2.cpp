#include<stdio.h>
#include<stdlib.h>

typedef int Status;
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef char TElemType;

typedef struct BiTNode
{
	TElemType data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

Status CreateBiTree(BiTree &T)//引用调用
{
	char ch;
	scanf("%c",&ch);
	if(ch==' ')
		T=NULL;
	else
	{
		if(!(T=(BiTNode*)malloc(sizeof(BiTNode))))
			exit(OVERFLOW);
		T->data=ch;
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

Status PreOrderTraverse(BiTree T,Status(*Visit)(TElemType e))//递归先序
{
	if(T)
	{	
		if(Visit(T->data))
			if(PreOrderTraverse(T->lchild,Visit))
			{	
				if(PreOrderTraverse(T->rchild,Visit))
				return OK;
			}
		return ERROR;

	}else return OK;
}

Status InOrderTraverse(BiTree T,Status(*Visit)(TElemType e))//递归中序
{
	if(T)
	{	
		if(InOrderTraverse(T->lchild,Visit))
			if(Visit(T->data))
			{	
				if(InOrderTraverse(T->rchild,Visit))
				return OK;
			}
		return ERROR;

	}else return OK;	
}

Status PostOrderTraverse(BiTree T,Status(*Visit)(TElemType e))//递归后序
{
	if(T)
	{	
		if(PostOrderTraverse(T->lchild,Visit))
			if(PostOrderTraverse(T->rchild,Visit))
			{	
				if(Visit(T->data))
				return OK;
			}
		return ERROR;

	}else return OK;	
}




int main()
{
	BiTree TT;
	printf("请按先序顺序输入树的元素\n");
	CreateBiTree(TT);

	printf("利用递归先序的结果：\n");
	PreOrderTraverse(TT,PrintElement);
	printf("\n");

	printf("利用递归中序的结果：\n");
	InOrderTraverse(TT,PrintElement);
	printf("\n");

	printf("利用递归后序的结果：\n");
	PostOrderTraverse(TT,PrintElement);
	printf("\n");
	return 0;
}