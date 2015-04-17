#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 70
#define STACKINCREMENT 10
#define OK 1
#define ERROR 0
#define OVERFLOW -2
int chess[8][8]={0};
int Htryx[8]={-2,-1,1,2,2,1,-1,-2};
int Htryy[8]={1,2,2,1,-1,-2,-2,-1};
int num=0;
typedef int Status;
//以下是栈的实现

typedef struct
{
	int x;
	int y;
	int di;
}SElemType;



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

Status GetTop(SqStack S,SElemType &e)
{
	if(S.top==S.base)
		return ERROR;
	e=*(S.top-1);
	return OK;
}

//判断是否走满
int yes()
{
	int k;
	k=1;
	int i,j;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			if(chess[i][j]==0)
				k=0;		
		}	
	}
	return k;
}

//输出棋盘
void put()
{
	int i,j;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			printf("%d ",chess[i][j]);		
		}	
		printf("\n");
	}
}

//判断点是否在棋盘内
int IN(SElemType e)
{
	if(e.x>=0&&e.x<8&&e.y>=0&&e.y<8)
		return 1;
	else
		return 0;
}


int main()
{
	SqStack S;
	InitStack(S);
	SElemType e;
	printf("请输入起始坐标：");
	scanf("%d,%d",&e.x,&e.y);	
	while(yes()==0)
	{
		if(chess[e.x][e.y]==0)
		{	
			Push(S,e);
			num++;
			e.di=-1;
			chess[e.x][e.y]=num;

			if(yes()==1)
				break;
			else
			{
				while(e.di<8)
				{
					e.di++;
					e.x=e.x+Htryx[e.di];
					e.y=e.y+Htryy[e.di];
					if(IN(e)==1)
						break;
					else
					{
						e.x=e.x-Htryx[e.di];
						e.y=e.y-Htryy[e.di];
					}							
				}	
			}
		}
		else
		{
			if(e.di<8)
			{
				while(e.di<8)
				{
					e.di++;
					e.x=e.x+Htryx[e.di];
					e.y=e.y+Htryy[e.di];
					if(IN(e)==1)
						break;

					else
					{
						e.x=e.x-Htryx[e.di];
						e.y=e.y-Htryy[e.di];
					}
				
				}					
			}
			else if(e.di==8)
			{
		
				Pop(S,e);
				chess[e.x][e.y]=0;
				e.di=-1;
				num--;
				GetTop(S,e);			
			}
		}
	}
	put();	
	return 0;
}