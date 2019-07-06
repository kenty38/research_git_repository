
#include "function.h"

void check_degree(struct Node n3[ONE_SIDE][ONE_SIDE]);

void set_edge_BA(struct Node nn[ONE_SIDE][ONE_SIDE],struct Edge e[ADD_EDGE*(ONE_SIDE*ONE_SIDE-ADD_EDGE)+(ADD_EDGE*(ADD_EDGE-1))/2]){
	int i,j,ve,found,done[ADD_EDGE];
	int M=0;
	int count;
	//int ave_degree=0;

	//Eには始点と終点がひとつずつ入るようになっているため、eには二つ情報を入れる
	int E[2*(ADD_EDGE*(ONE_SIDE*ONE_SIDE-ADD_EDGE)+(ADD_EDGE*(ADD_EDGE-1))/2)];

	//初期条件は頂点m0つの完全グラフ
	for(i=0;i<FIRST_PERFECT_GRAPH_NODE;i++){
		nn[i/ONE_SIDE][i%ONE_SIDE].degree=FIRST_PERFECT_GRAPH_NODE-1;
		for(j=0;j<i;j++){
			E[2*M]=i; E[2*M+1]=j;
			M++;
		}
	}

	//i+1番目の頂点を追加
	for(i=FIRST_PERFECT_GRAPH_NODE;i<ONE_SIDE*ONE_SIDE;i++){
		nn[i/ONE_SIDE][i%ONE_SIDE].degree=0;
		//追加する点がm本の枝を付け替えるまで繰り返す
		while(nn[i/ONE_SIDE][i%ONE_SIDE].degree<ADD_EDGE){

			//printf("nn[%d][%d].degree=%d,m=%d\n",i/n,i%n,nn[i/n][i%n].degree,m);
			fflush(0);

			//優先的選択を行う
			do{
				ve=E[(int)(Uniform()*2*M)];
			}while(ve==i);

			found=0;

			for(j=0;j<nn[i/ONE_SIDE][i%ONE_SIDE].degree;j++)
				//doneはiとつながっている点を格納する配列
				if(done[j]==ve)found=1;

			if(found==0){
				done[nn[i/ONE_SIDE][i%ONE_SIDE].degree]=ve;
				E[2*M]=i; 		nn[i/ONE_SIDE][i%ONE_SIDE].degree++;
				E[2*M+1]=ve;	nn[ve/ONE_SIDE][ve%ONE_SIDE].degree++;
				M++;
			}

		}

	}

	//for(i=0;i<n*n;i++)
		//ave_degree+=nn[i/n][i%n].degree;
	//printf("ave_degree=%d\n",ave_degree/(n*n));


	//edgeに始点と終点の情報を格納
	for(i=0;i<ADD_EDGE*(ONE_SIDE*ONE_SIDE-ADD_EDGE)+(ADD_EDGE*(ADD_EDGE-1))/2;i++){
		if(E[2*i]<E[2*i+1]){
			e[i].start=E[2*i];
			e[i].finish=E[2*i+1];
		}
		else{
			e[i].start=E[2*i+1];
			e[i].finish=E[2*i];

			printf("e[%d]: %d - %d\n",i,e[i].start,e[i].finish);
		}
	}
	
	//set_edge.cで記述済み
	init_status(e);
	input_status(nn,e);
	
	//check_degree(nn);
}



void check_degree(struct Node n3[ONE_SIDE][ONE_SIDE]){
	int i=0;
	
	while(i<ONE_SIDE*ONE_SIDE){
		printf("Node[%d][%d].degree=%d\n",i/ONE_SIDE,i%ONE_SIDE,n3[i/ONE_SIDE][i%ONE_SIDE].degree);
		i++;
	}
}

