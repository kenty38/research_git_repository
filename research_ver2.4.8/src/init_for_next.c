
#include "function.h"

/************************************************
 *												*
 * void init_until_1000(struct Node,int *)		*
 * -ある一つのネットワークでは情報を1000回流し、	*
 * -その都度Nodeの特定の値だけ初期化するため、		*
 * -それに必要な関数。							*
 * -情報共有者のリストも初期化する。				*
 ************************************************/

void init_for_next(struct Node nn[ONE_SIDE][ONE_SIDE],int number){

	int i;	//作業用変数
	struct Cell *temp;

	temp=head;

	//深さと状態を初期化
	for(i=0;i<ONE_SIDE*ONE_SIDE;i++){
		nn[i/ONE_SIDE][i%ONE_SIDE].height=0;
		nn[i/ONE_SIDE][i%ONE_SIDE].statement='S';
		nn[i/ONE_SIDE][i%ONE_SIDE].lifetime=0;			
		nn[i/ONE_SIDE][i%ONE_SIDE].kind_of_source=NOT_SOURCE;
		nn[i/ONE_SIDE][i%ONE_SIDE].from_virus=0;
	}

	//情報共有者リストを初期化
	allDeleteList(head);
	head=NULL;
	tail=head;
	
	//都道府県を固定(深さを1にいしておくことに注意)
	HeadInsert(nn[temp->x][temp->y].x,nn[temp->x][temp->y].y,&head,&tail);
	nn[temp->x][temp->y].height=1;	
	nn[i/ONE_SIDE][i%ONE_SIDE].lifetime=1;
	nn[i/ONE_SIDE][i%ONE_SIDE].kind_of_source = SOURCE_1; 
	fflush(0);
}
