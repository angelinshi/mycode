#include<stdio.h>
#define MAX_VERTRX_NUM 20
#define ERROR -2
typedef int AdjMartix[MAX_VERTRX_NUM][MAX_VERTRX_NUM];
typedef struct{
	char vexs[MAX_VERTRX_NUM];
	int arcs[20][20];
	int vexnum;
	int arcnum;//顶点数，弧数
}MGraph;
AdjMartix A;

int LocateVex(MGraph G,char v)
{
	int i;
	for(i=0;i<G.arcnum;i++)
	{	
		if(v==G.vexs[i])
		{	return i;
			break;
		}
	}
}

void CreatrUDN(MGraph &G)
{
	int i,j,k,v1,v2,w;
	printf("现在开始构造无向网，请输入“顶点数 弧数”\n");
	scanf("%d%d",&G.vexnum,&G.arcnum);
	for(i=0;i<G.arcnum;i++)
	{
		getchar();
		printf("请输入第%d个顶点名称\n",i+1);
		scanf("%c",&G.vexs[i]);
	}
	for(i=0;i<G.arcnum;i++)
	{
		for(j=0;j<G.arcnum;j++)
		{
			G.arcs[i][j]=1000;
		}
	}
	for(k=0;k<G.arcnum;k++)
	{
		printf("请输入第%d条弧的两个顶点以及权值“v1,v2,w”\n",k+1);
		getchar(); 
		scanf("%c,%c,%d",&v1,&v2,&w);
		i=LocateVex(G,v1);
		j=LocateVex(G,v2);
		G.arcs[i][j]=w;
		G.arcs[j][i]=G.arcs[i][j];	
	}
}
void floyd(MGraph G)
{
	
	int i,j,k;
	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
			A[i][j]=G.arcs[i][j];
	}
	for(i=0;i<G.vexnum;i++)
		A[i][i]=0;
	for(k=0;k<G.vexnum;k++)
	{
		for(i=0;i<G.vexnum;i++)
			for(j=0;j<G.vexnum;j++)
				if((A[i][k]+A[k][j])<A[i][j])
					A[i][j]=A[i][k]+A[k][j];
	}
}






int main()
{
	int i,j;
	MGraph G;
	CreatrUDN(G);
	printf("邻接矩阵为：\n");
	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
			printf("%5d ",G.arcs[i][j]);
		printf("%\n");
	}
	floyd(G);
	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
		{
			if(i==j)
				continue;
			else
			{
				printf("从%c到%c的最短路径值为%d\n",G.vexs[i],G.vexs[j],A[i][j]);
			}
		}
			
		printf("%\n");
	}


	return 0;
}