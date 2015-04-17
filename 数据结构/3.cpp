#include<stdio.h>
#include<stdlib.h>

#define STACK_INIT_SIZE 70
#define STACKINCREMENT 10
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

typedef BiTree SElemType;

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

typedef struct
{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

Status InitStack(SqStack &S)
{
	S.base=(SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if(!S.base)
		exit(OVERFLOW);
	S.top=S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}

Status Push(SqStack &S,SElemType e)
{
	if(S.top-S.base>=S.stacksize)
	{	S.base=(SElemType*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!S.base)
			exit(OVERFLOW);
		S.top=S.base+S.stacksize;
		S.stacksize=S.stacksize+STACKINCREMENT;
	}
	*S.top++=e;
	return OK;
}

Status Pop(SqStack &S,SElemType &e)
{
	if(S.top==S.base)
		return ERROR;
	e=*--S.top;
	return OK;
}

Status StackEmpty(SqStack S)
{
	if(S.top==S.base)
		return OK;
	else
		return ERROR;
}

Status InOT(BiTree T,Status(*Visit)(TElemType e))
{
	SqStack S;
	InitStack(S);
	BiTree p;
	p=T;
	while(p||!StackEmpty(S))
	{
		if(p)
		{
			Push(S,p);
			p=p->lchild;
		}
		else
		{
			Pop(S,p);
			if(!Visit(p->data))
				return ERROR;
			p=p->rchild;		
		}	
	}
	return OK;
}

int main()
{
	BiTree TT;
	printf("�밴����˳����������Ԫ��\n");
	CreateBiTree(TT);

	printf("���÷ǵݹ�����Ľ����\n");
	InOT(TT,PrintElement);
	printf("\n");

	return 0;
}