
#include "function.h"

void set_edge_BA(struct Node nn[n][n],struct Edge e[m*(n*n-m)+(m*(m-1))/2]){
	int i,j,ve,found,done[m];
	int M=0;
	int count;
	//int ave_degree=0;

	//Eには始点と終点がひとつずつ入るようになっているため、eには二つ情報を入れる
	int E[2*(m*(n*n-m)+(m*(m-1))/2)];

	//初期条件は頂点m0つの完全グラフ
	for(i=0;i<m0;i++){
		nn[i/n][i%n].degree=m0-1;
		for(j=0;j<i;j++){
			E[2*M]=i; E[2*M+1]=j;
			M++;
		}
	}

	//i+1番目の頂点を追加
	for(i=m0;i<n*n;i++){
		nn[i/n][i%n].degree=0;
		//追加する点がm本の枝を付け替えるまで繰り返す
		while(nn[i/n][i%n].degree<m){

			//printf("nn[%d][%d].degree=%d,m=%d\n",i/n,i%n,nn[i/n][i%n].degree,m);
			fflush(0);

			//優先的選択を行う
			do{
				ve=E[(int)(Uniform()*2*M)];
			}while(ve==i);

			found=0;

			for(j=0;j<nn[i/n][i%n].degree;j++)
				//doneはiとつながっている点を格納する配列
				if(done[j]==ve)found=1;

			if(found==0){
				done[nn[i/n][i%n].degree]=ve;
				E[2*M]=i; 		nn[i/n][i%n].degree++;
				E[2*M+1]=ve;	nn[ve/n][ve%n].degree++;
				M++;
			}

		}

	}

	//for(i=0;i<n*n;i++)
		//ave_degree+=nn[i/n][i%n].degree;
	//printf("ave_degree=%d\n",ave_degree/(n*n));



	//edgeに始点と終点の情報を格納
	for(i=0;i<m*(n*n-m)+(m*(m-1))/2;i++){
		if(E[2*i]<E[2*i+1]){
			e[i].s=E[2*i];
			e[i].f=E[2*i+1];
		}
		else{
			e[i].s=E[2*i+1];
			e[i].f=E[2*i];

			//printf("e[%d]: %d - %d\n",i,e[i].s,e[i].f);
		}
	}

	i=0;

	//各ノードの隣接リストを作る
	while(i<n*n){
		//次数分の配列を生成
		nn[i/n][i%n].ad_list=(int*)malloc(nn[i/n][i%n].degree*sizeof(int));

		count=0;
		for(j=0;j<N;j++){
			if(e[j].s==nn[i/n][i%n].node_number){
				nn[i/n][i%n].ad_list[count]=e[j].f;
				count++;
			}
			else if(e[j].f==nn[i/n][i%n].node_number){
				nn[i/n][i%n].ad_list[count]=e[j].s;
				count++;
			}

			if(count==nn[i/n][i%n].degree)break;
		}

		//配列を小さい順にソートする
			Qsort(nn[i/n][i%n].ad_list,0,nn[i/n][i%n].degree-1);
		i++;
	}

/*
	j=0;
	while(j<n*n){

		printf("Node[%d][%d].degree=%d\n",j/n,j%n,nn[j/n][j%n].degree);

		j++;
	}

	puts("");
	j=0;
	while(j<n*n){

		printf("Node[%d][%d].ad_list=\n",j/n,j%n);

		for(i=0;i<nn[j/n][j%n].degree;i++)
				printf("%d ",nn[j/n][j%n].ad_list[i]);
		puts("\n");
		j++;
	}
*/
}