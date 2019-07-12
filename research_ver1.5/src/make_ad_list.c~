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

void make_ad_list(struct Node nn[ONE_SIDE][ONE_SIDE],struct Edge e[]){

	int i=0,j=0;			//作業用変数
	int count;				//隣接リストに辺の数だけ追加するときに使う作業用変数

	//各ノードの次数を入れる
	while(i<EDGE_NUMBER){
		nn[e[i].start/ONE_SIDE][e[i].start%ONE_SIDE].degree+=1;
		nn[e[i].finish/ONE_SIDE][e[i].finish%ONE_SIDE].degree+=1;
		i++;
	}

	i=0;

	//各ノードの隣接リストを作る
	while(i<ONE_SIDE*ONE_SIDE){
		//次数分の配列を生成
		//nn[i/ONE_SIDE][i%ONE_SIDE].ad_list=(int*)malloc(nn[i/ONE_SIDE][i%ONE_SIDE].degree*sizeof(int));
		nn[i/ONE_SIDE][i%ONE_SIDE].ad_list=malloc(sizeof (int)*nn[i/ONE_SIDE][i%ONE_SIDE].degree);

		count=0;

		//辺の数だけ隣接リストに始点と終点と格納
		for(j=0;j<EDGE_NUMBER;j++){
			if(e[j].start==nn[i/ONE_SIDE][i%ONE_SIDE].node_number){
				nn[i/ONE_SIDE][i%ONE_SIDE].ad_list[count]=e[j].finish;
				count++;
			}
			else if(e[j].finish==nn[i/ONE_SIDE][i%ONE_SIDE].node_number){
				nn[i/ONE_SIDE][i%ONE_SIDE].ad_list[count]=e[j].start;
				count++;
			}

			if(count==nn[i/ONE_SIDE][i%ONE_SIDE].degree)
				break;
		}

		//配列を小さい順にソートする(list.c)
			Qsort(nn[i/ONE_SIDE][i%ONE_SIDE].ad_list,0,nn[i/ONE_SIDE][i%ONE_SIDE].degree-1);
		i++;
	}
}
