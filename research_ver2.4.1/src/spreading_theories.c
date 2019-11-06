
#include"function.h"

void agree_SIR(struct Node nn[ONE_SIDE][ONE_SIDE] , int edgedot, int launch_x, int launch_y, int *infected);

void spreading_theories_SIR(struct Node nn[ONE_SIDE][ONE_SIDE], struct Edge e[EDGE_NUMBER]){

	int i=0,j;				//作業用変数
	struct Cell *temp;		//headの位置を一時的に覚えておくためのセルポインタ
	double pro_remedy;		//情報に飽きたかどうか判定するために使用する確率用変数
	int temp_ad=0;			//tempの隣人を格納
	int temp_ad_j=0;		//tempの隣人を格納(lifetime判定用)
	int judge;


	sir_time=0;

	//感染者がいなくなるまで続ける
	while(1){

		temp=head;
		
		//tempがNULLになるまで回す
		do{

			i=0;
			
			//printf("temp=%d\n",nn[temp->x][temp->y].node_number);
			
			//S,Rは飛ばす
			if( nn[temp->x][temp->y].statement=='S' || nn[temp->x][temp->y].statement=='R'){
				temp=temp->next;
				//printf("temp:%d\n",nn[temp->x][temp->y].node_number);
				continue;
			}
			
			//隣人に情報を広げる
			while(i<nn[temp->x][temp->y].degree){

				temp_ad=nn[temp->x][temp->y].ad_list[i];
				
				judge=strcmp(nn[temp_ad/ONE_SIDE][temp_ad%ONE_SIDE].name,"SEA");
				if(judge==0){
					i++;
					continue;
				}
				
				//情報を共有するかどうか判断する
				agree_SIR(nn,nn[temp->x][temp->y].ad_list[i],temp->x,temp->y,&infected_count);
				i++;

				//情報を流す度に、一定の確率でI→Rにする(非共有者がI,Rの時のみ)
				pro_remedy=Uniform();
				if(pro_remedy>REMEDY_PROBABIRITY){
					if(nn[temp_ad/ONE_SIDE][temp_ad%ONE_SIDE].statement=='I'){
						nn[temp->x][temp->y].statement='R';
						infected_count--;
						break;
					}
				}
			}
			
			if(nn[temp->x][temp->y].lifetime==5){
				nn[temp->x][temp->y].statement='R';
				infected_count--;
			}
			
			nn[temp->x][temp->y].lifetime++;
			
			temp=temp->next;

		}while(temp!=NULL);

		sir_time++;
		if(infected_count<=0 || sir_time==30){
			break;
		}
	}
}



void agree_SIR(struct Node nn[ONE_SIDE][ONE_SIDE] , int edgedot, int launch_x, int launch_y,int *infected){

//	printf("edgedot=%d,launch_x=%d,launch_y=%d\ONE_SIDE",edgedot,launch_x,launch_y);
		float inf_pro;
		
		inf_pro=Uniform();
		
		if(nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].statement=='S'){
			if(inf_pro<=INFECTED_PROBABIRITY){
				(*infected)++;
				nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].statement='I';
				Insert(edgedot/ONE_SIDE,edgedot%ONE_SIDE,&tail);
				nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].height=nn[launch_x][launch_y].height+1;
			}
		}

}




