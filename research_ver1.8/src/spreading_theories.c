
#include"function.h"

void agree(struct Node nn[][ONE_SIDE] , int,int,int,double);

double modify_topic(struct Node nn[][ONE_SIDE],int edgedot);

/**********************************************************
 *														  *
 * void spreading_theories(struct Node,struct Edge)		  *
 * -情報共有者が情報を広げるための関数。				  *
 * -リスト構造内の共有者がtailになるまでこれを繰り返す。  *
 * -関数agreeに判定、リスト挿入を行わせる。		          *
 **********************************************************/

void spreading_theories(struct Node nn[ONE_SIDE][ONE_SIDE], struct Edge e[EDGE_NUMBER]){
	int i=0;				//作業用変数
	double modify_threthold=0;  //境界補正値
	struct Cell *temp;		//headの位置を一時的に覚えておくためのセルポインタ

	temp=head;
	//TraverseList(head);
  
	do{
		//printf("spreading_theories : temp=[%d][%d]\ONE_SIDE",temp->x,temp->y);

		i=0;
    modify_threthold=0;
    
		while(i<nn[temp->x][temp->y].degree){
		  if(nn[nn[temp->x][temp->y].ad_list[i]/ONE_SIDE][nn[temp->x][temp->y].ad_list[i]%ONE_SIDE].height==0){
      
        nn[nn[temp->x][temp->y].ad_list[i]/ONE_SIDE][nn[temp->x][temp->y].ad_list[i]%ONE_SIDE].height+1;
      
#ifdef TOPIC			  
			  modify_threthold=modify_topic(nn,nn[temp->x][temp->y].ad_list[i]);
#endif

			  agree(nn,nn[temp->x][temp->y].ad_list[i],temp->x,temp->y,modify_threthold);
			}
			i++;
		}

		temp=temp->next;

	}while(temp!=NULL);
}



double modify_topic(struct Node nn[][ONE_SIDE],int edgedot){
  
  switch(abs(nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].favorite_topic-theta_topic)){
    case 0:
      return 0.2;
      break;
    case 1:
      return 0.1;
      break;
    case 2:
      return -0.1;
      break;
    case 3:
      return -0.2;
      break;
    case 4:
      return -0.1;
      break;
    case 5:
      return 0.1;
      break;
  }
 
}



void agree(struct Node nn[ONE_SIDE][ONE_SIDE] , int edgedot, int launch_x, int launch_y,double mod  ){

//	printf("edgedot=%d,launch_x=%d,launch_y=%d\ONE_SIDE",edgedot,launch_x,launch_y);

	//omega-theta<deltaの時、情報を共有する

//node_thetaを用いて情報を広げるかどうか
#ifdef NODE_THETA
		//if(fabs(nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].omega-theta)<nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].deltaex){
		if(fabs(nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].omega-theta)<nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].deltaex){
			Insert(edgedot/ONE_SIDE,edgedot%ONE_SIDE,&tail);
			//nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].node_theta=nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].omega+(2*Uniform()-1)*delta;
		}
#endif
#ifndef NODE_THETA
		if(fabs(nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].omega-theta)<DELTA*(1+mod)){
			Insert(edgedot/ONE_SIDE,edgedot%ONE_SIDE,&tail);
			nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].height=nn[launch_x][launch_y].height+1;
		}
#endif
}


