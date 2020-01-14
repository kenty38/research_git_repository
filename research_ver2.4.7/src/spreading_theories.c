
#include"function.h"

void p_dens_station_ave(struct Node nn[ONE_SIDE][ONE_SIDE], int temp_x, int temp_y,double *d_ave, double *st_ave);

void agree_SIR(struct Node nn[ONE_SIDE][ONE_SIDE] , int edgedot, int launch_x, int launch_y, int *infected, double d_ave, double st_ave);



void spreading_theories_SIR(struct Node nn[ONE_SIDE][ONE_SIDE], struct Edge e[EDGE_NUMBER]){

	int i=0,j;				//作業用変数
	struct Cell *temp;		//headの位置を一時的に覚えておくためのセルポインタ
	double pro_remedy;		//情報に飽きたかどうか判定するために使用する確率用変数
	int temp_ad=0;			//tempの隣人を格納
	int temp_ad_j=0;		//tempの隣人を格納(lifetime判定用)
	int judge;
	double dens_ave=0;
	double station_ave=0;

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
			
			dens_ave = 0;
			station_ave = 0;

			//隣人に情報を広げる
			while(i<nn[temp->x][temp->y].degree){
				
				p_dens_station_ave(nn,temp->x,temp->y,&dens_ave,&station_ave);
				
				temp_ad=nn[temp->x][temp->y].ad_list[i];
				
				judge=strcmp(nn[temp_ad/ONE_SIDE][temp_ad%ONE_SIDE].name,"SEA");
				if(judge==0){
					i++;
					continue;
				}
				
				//情報を共有するかどうか判断する
				agree_SIR(nn,nn[temp->x][temp->y].ad_list[i],temp->x,temp->y,&infected_count,dens_ave,station_ave);
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
			
			if(nn[temp->x][temp->y].lifetime==7){
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



void p_dens_station_ave(struct Node nn[ONE_SIDE][ONE_SIDE], int temp_x, int temp_y, double *d_ave, double *st_ave){
	int i;
	int count=0;
	int ad_x;
	int ad_y;
	
	for(i=0 ; i<nn[temp_x][temp_y].degree ; i++){
		ad_x = nn[temp_x][temp_y].ad_list[i]/ONE_SIDE;
		ad_y = nn[temp_x][temp_y].ad_list[i]%ONE_SIDE;

		*d_ave  = *d_ave  + nn[ad_x][ad_y].popu_dens;
		*st_ave = *st_ave + nn[ad_x][ad_y].station_number;
		
		if(nn[ad_x][ad_y].popu_dens > 1 || nn[ad_x][ad_y].station_number > 1)
			count++;
	}
}


void agree_SIR(struct Node nn[ONE_SIDE][ONE_SIDE] , int edgedot, int launch_x, int launch_y, int *infected, double d_ave, double st_ave){

//	printf("edgedot=%d,launch_x=%d,launch_y=%d\ONE_SIDE",edgedot,launch_x,launch_y);
		float inf_pro;
		double d_correction=0;
		double st_correction=0;
		
		inf_pro=Uniform();
		
		if(nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].statement=='S' && nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].height != 1){
		
			if(nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].popu_dens < d_ave)
				d_correction=NEGATIVE_CORRECTION;
			else if(nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].popu_dens > d_ave)
				d_correction=POSSITIVE_CORRECTION;
		
			if(nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].station_number < st_ave)
				st_correction=NEGATIVE_CORRECTION;
			else if(nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].station_number > st_ave)
				st_correction=POSSITIVE_CORRECTION;

			switch(mode){
				case ORIGINAL:
					d_correction = 0;
					st_correction = 0;
					break;
				case DENSITY:
					st_correction = 0;
					break;
				case STATION:
					d_correction = 0;
					break;
			}

			if(inf_pro + d_correction + st_correction <= INFECTED_PROBABIRITY){
				(*infected)++;
				nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].statement='I';
				Insert(edgedot/ONE_SIDE,edgedot%ONE_SIDE,&tail);
				nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].height=nn[launch_x][launch_y].height+1;
			}
		}

}

