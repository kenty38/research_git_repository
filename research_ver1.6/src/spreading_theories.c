
#include"function.h"

void agree(struct Node nn[][ONE_SIDE] , int,int,int);
void agree_SIR(struct Node nn[ONE_SIDE][ONE_SIDE] , int edgedot, int launch_x, int launch_y,int *p);

void spreading_theories_SIR(struct Node nn[ONE_SIDE][ONE_SIDE], struct Edge e[EDGE_NUMBER_BA]){

	int i=0,j;				//作業用変数
	struct Cell *temp;		//headの位置を一時的に覚えておくためのセルポインタ
	double pro_remedy;		//情報に飽きたかどうか判定するために使用する確率用変数
	int temp_ad=0;			//tempの隣人を格納
	int temp_ad_j=0;		//tempの隣人を格納(lifetime判定用)
	int lifetime_sum=0;		//隣人のlifetimeの合計

	sir_time=0;

	//感染者がいなくなるまで続ける
	while(1){

		temp=head;

		//tempがNULLになるまで回す
		do{

			i=0;
			lifetime_sum=0;

			//S,Rは飛ばす
			if( nn[temp->x][temp->y].statement=='S' || nn[temp->x][temp->y].statement=='R'){
				temp=temp->next;
				//printf("飽きているので飛ばします\n");
				continue;
			}

			//隣接リストの個数分だけ情報を広げる
			while(i<nn[temp->x][temp->y].degree){

				temp_ad=nn[temp->x][temp->y].ad_list[i];

				//情報を共有するかどうか判断する
				agree_SIR(nn,nn[temp->x][temp->y].ad_list[i],
						temp->x,temp->y,&infected_count);
				i++;
				pro_remedy=Uniform();

				//情報を流す度に、一定の確率でI→Rにする(非共有者がI,Rの時のみ)
				if(pro_remedy<large_gamma){
					if(nn[temp_ad/ONE_SIDE][temp_ad%ONE_SIDE].statement=='I' ||
						nn[temp_ad/ONE_SIDE][temp_ad%ONE_SIDE].statement=='R'){

						//printf("途中で終わりました(%d/%d)\n",i,nn[temp->x][temp->y].degree);
						nn[temp->x][temp->y].statement='R';
						infected_count--;
						break;
					}
				}
			}
#ifdef DEBUG
			//隣人のlifetimeの合計を計算
			for(j=0;j<nn[temp->x][temp->y].degree;j++){
				temp_ad_j=nn[temp->x][temp->y].ad_list[j];
				lifetime_sum+=nn[temp_ad_j/ONE_SIDE][temp_ad_j%ONE_SIDE].lifetime;
			}

			//隣人のタイムラインから消えてなくなった場合
			if(lifetime_sum==0 && nn[temp->x][temp->y].statement=='I'){
				nn[temp->x][temp->y].statement='R';
				infected_count--;
			}
#endif
			temp=temp->next;

		}while(temp!=NULL);

		sir_time++;

		if(infected_count==0){
			//printf("感染者はいません\n");
			break;
		}

	}
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


/**************************************************************
 *														  	  *
 * void spreading_theories(struct Node,struct Edge,int,int)	  *
 * -情報を共有するかどうかの関数。							  	  *
 * -lauch_x,launch_yは情報共有者の座標を表す。				  *
 * -感染率betaの確率で情報を共有するようにする。				  *
 * -*pはinfected_countであり、情報を共有するたび1増やす。    	  *
 **************************************************************/

void agree_SIR(struct Node nn[ONE_SIDE][ONE_SIDE] , int edgedot, int launch_x, int launch_y,int *p){
	float pro_infected;	//確率、beta以下で情報を共有
	//printf("edgedot=%d,launch_x=%d,launch_y=%d\n",edgedot,launch_x,launch_y);

	//Iの相手がSの時だけ噂を広げる
	if(nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].statement=='S'){

		if(nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].lifetime==0){

			return;
		}

		pro_infected=Uniform();

		if(pro_infected<INFECTED_PROBABIRITY){
			Insert(edgedot/ONE_SIDE,edgedot%ONE_SIDE,&tail);
			nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].height=nn[launch_x][launch_y].height+1;
			nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].statement='I';
			*p=*p+1;
		}

		nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].lifetime--;

	}
}



