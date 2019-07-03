/*
 * init_until_1000.c
 *
 *  Created on: 2017/12/11
 *      Author: titi
 */

#include "function.h"

/************************************************
 *												*
 * void init_until_1000(struct Node,int *)		*
 * -ある一つのネットワークでは情報を1000回流し、	*
 * -その都度Nodeの特定の値だけ初期化するため、		*
 * -それに必要な関数。							*
 * -情報共有者のリストも初期化する。				*
 ************************************************/

void init_until_1000(struct Node nn[n][n],int *rep_p){

	int i;	//作業用変数

	//深さと状態を初期化
	for(i=0;i<n*n;i++){
		nn[i/n][i%n].height=0;
		nn[i/n][i%n].statement='S';
		nn[i/n][i%n].lifetime=lifetime_hour*(8/nn[i/n][i%n].degree);
	}

	//情報共有者の人数を初期化
	infected_count=0;

	//情報共有者リストを初期化
	allDeleteList(head);
	head=NULL;
	tail=head;

	//repが100で割り切れる時,何回目か表示する
	if(((*rep_p)+1)%10000==0)printf("%d回目\n",(*rep_p)+1);
		fflush(0);
		(*rep_p)++;//ポインタの中身の値を1増やす

}
