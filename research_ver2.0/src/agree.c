
#include"function.h"

/**************************************************************
 *														  	  *
 * void spreading_theories(struct Node,struct Edge,int,int)	  *
 * -情報を共有するかどうかの関数。							  	  *
 * -lauch_x,launch_yは情報共有者の座標を表す。				  *
 * -感染率betaの確率で情報を共有するようにする。				  *
 * -*pはinfected_countであり、情報を共有するたび1増やす。    	  *
 **************************************************************/

void agree_SIR(struct Node nn[n][n] , int edgedot, int launch_x, int launch_y,int *p){

	float pro_infected;	//確率、beta以下で情報を共有
	//printf("edgedot=%d,launch_x=%d,launch_y=%d\n",edgedot,launch_x,launch_y);

	//Iの相手がSの時だけ噂を広げる
	if(nn[edgedot/n][edgedot%n].statement=='S'){

		if(nn[edgedot/n][edgedot%n].lifetime==0){

			return;
		}

		pro_infected=Uniform();

		if(pro_infected<beta){
			Insert(edgedot/n,edgedot%n,&tail);
			nn[edgedot/n][edgedot%n].height=nn[launch_x][launch_y].height+1;
			nn[edgedot/n][edgedot%n].statement='I';
			*p=*p+1;
		}

		nn[edgedot/n][edgedot%n].lifetime--;

	}
}