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

Status CreateBiTree(BiTree &T)//���õ���
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

Status PreOrderTraverse(BiTree T,Status(*Visit)(TElemType e))//�ݹ�����
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

Status InOrderTraverse(BiTree T,Status(*Visit)(TElemType e))//�ݹ�����
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

Status PostOrderTraverse(BiTree T,Status(*Visit)(TElemType e))//�ݹ����
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
	printf("�밴����˳����������Ԫ��\n");
	CreateBiTree(TT);

	printf("���õݹ�����Ľ����\n");
	PreOrderTraverse(TT,PrintElement);
	printf("\n");

	printf("���õݹ�����Ľ����\n");
	InOrderTraverse(TT,PrintElement);
	printf("\n");

	printf("���õݹ����Ľ����\n");
	PostOrderTraverse(TT,PrintElement);
	printf("\n");
	return 0;
}