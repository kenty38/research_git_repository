/*
 * make_ad_list.c
 *
 *  Created on: 2017/12/07
 *      Author: tktk
 */
#include "function.h"

/**********************************************************
 *														  *
 * void make_ad_list(struct Node,struct Edge)			  *
 * -Node分だけ接続リストを生成する						  *
 * -SIR時のみlifetimeを追加する							  *
 * -lifetimeの初期化はinit_until_1000で行う		          *
 **********************************************************/

void make_ad_list(struct Node nn[n][n],struct Edge e[]){

	int i=0,j=0;			//作業用変数
	int count;				//隣接リストに辺の数だけ追加するときに使う作業用変数

	//各ノードの次数を入れる
	while(i<N){
		nn[e[i].s/n][e[i].s%n].degree+=1;
		nn[e[i].f/n][e[i].f%n].degree+=1;
		i++;
	}

	i=0;

	//各ノードの隣接リストを作る
	while(i<n*n){
		//次数分の配列を生成
		//nn[i/n][i%n].ad_list=(int*)malloc(nn[i/n][i%n].degree*sizeof(int));
		nn[i/n][i%n].ad_list=malloc(sizeof (int)*nn[i/n][i%n].degree);

#ifdef SIR
		//SIR時のみ、情報の寿命を追加
		nn[i/n][i%n].lifetime=lifetime_hour*(8/nn[i/n][i%n].degree);

		//printf("nn[%d][%d].lifetime=%d\n",i/n,i%n,nn[i/n][i%n].lifetime);
#endif

		count=0;

		//辺の数だけ隣接リストに始点と終点と格納
		for(j=0;j<N;j++){
			if(e[j].s==nn[i/n][i%n].node_number){
				nn[i/n][i%n].ad_list[count]=e[j].f;
				count++;
			}
			else if(e[j].f==nn[i/n][i%n].node_number){
				nn[i/n][i%n].ad_list[count]=e[j].s;
				count++;
			}

			if(count==nn[i/n][i%n].degree)
				break;
		}

		//配列を小さい順にソートする(list.c)
			Qsort(nn[i/n][i%n].ad_list,0,nn[i/n][i%n].degree-1);
		i++;
	}
}
