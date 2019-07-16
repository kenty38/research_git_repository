
#include"function.h"

void agree(struct Node nn[][ONE_SIDE] , int,int,int);


/**********************************************************
 *														  *
 * void spreading_theories(struct Node,struct Edge)		  *
 * -情報共有者が情報を広げるための関数。				  *
 * -リスト構造内の共有者がtailになるまでこれを繰り返す。  *
 * -関数agreeに判定、リスト挿入を行わせる。		          *
 **********************************************************/

void spreading_theories(struct Node nn[ONE_SIDE][ONE_SIDE], struct Edge e[EDGE_NUMBER]){
	int i=0;				//作業用変数
	struct Cell *temp;		//headの位置を一時的に覚えておくためのセルポインタ

	temp=head;
	//TraverseList(head);

	do{
		//printf("spreading_theories : temp=[%d][%d]\ONE_SIDE",temp->x,temp->y);

		i=0;

		while(i<nn[temp->x][temp->y].degree){
			agree(nn,nn[temp->x][temp->y].ad_list[i],temp->x,temp->y);
			i++;
		}

		temp=temp->next;

	}while(temp!=NULL);
}







void agree(struct Node nn[ONE_SIDE][ONE_SIDE] , int edgedot, int launch_x, int launch_y){

//	printf("edgedot=%d,launch_x=%d,launch_y=%d\ONE_SIDE",edgedot,launch_x,launch_y);

	//omega-theta<deltaの時、情報を共有する
	if(nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].height==0){

//node_thetaを用いて情報を広げるかどうか
#ifdef BIAS
		//if(fabs(nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].omega-theta)<nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].deltaex){
		if(fabs(nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].omega-theta)<nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].deltaex){
			Insert(edgedot/ONE_SIDE,edgedot%ONE_SIDE,&tail);
			nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].height=nn[launch_x][launch_y].height+1;
			//nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].node_theta=nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].omega+(2*Uniform()-1)*delta;
		}
#endif
#ifndef BIAS
		if(fabs(nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].omega-theta)<DELTA){
			Insert(edgedot/ONE_SIDE,edgedot%ONE_SIDE,&tail);
			nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].height=nn[launch_x][launch_y].height+1;
		}
#endif

	}
}






