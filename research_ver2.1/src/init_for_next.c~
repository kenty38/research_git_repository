
#include "function.h"

/************************************************
 *												*
 * void init_until_1000(struct Node,int *)		*
 * -ある一つのネットワークでは情報を1000回流し、	*
 * -その都度Nodeの特定の値だけ初期化するため、		*
 * -それに必要な関数。							*
 * -情報共有者のリストも初期化する。				*
 ************************************************/

void init_for_next(struct Node nn[ONE_SIDE][ONE_SIDE],int *rep_p){

	int i;	//作業用変数

	//深さと状態を初期化
	for(i=0;i<ONE_SIDE*ONE_SIDE;i++){
		nn[i/ONE_SIDE][i%ONE_SIDE].height=0;
		nn[i/ONE_SIDE][i%ONE_SIDE].statement='S';
		nn[i/ONE_SIDE][i%ONE_SIDE].lifetime=LIFETIME_DAY*(8/nn[i/ONE_SIDE][i%ONE_SIDE].degree);
	}


	//情報共有者リストを初期化
	allDeleteList(head);
	head=NULL;
	tail=head;

	fflush(0);
	(*rep_p)++;//ポインタの中身の値を1増やす

}
