
#include"function.h"

void p_dens_station_ave(struct Node nn[ONE_SIDE][ONE_SIDE], int temp_x, int temp_y,double *d_ave, double *st_ave);

void agree_SIR(struct Node nn[ONE_SIDE][ONE_SIDE] , int edgedot, int launch_x, int launch_y, int *infected, double d_ave, double st_ave);


void spreading_theories_SIR(struct Node nn[ONE_SIDE][ONE_SIDE], struct Edge e[EDGE_NUMBER]){

	int i=0,j;				//作業用変数
	struct Cell *temp;		//headの位置を一時的に覚えておくためのセルポインタ
	struct Cell *height_temp;
	double pro_remedy;		//情報に飽きたかどうか判定するために使用する確率用変数
	int temp_ad=0;			//tempの隣人を格納
	int temp_ad_j=0;		//tempの隣人を格納(lifetime判定用)
	int judge;
	double dens_ave=0;
	double station_ave=0;
	char *sir_filename;
	int max_height = 0;

	sir_time=1;


	//感染者がいなくなるまで続ける
	while(1){

		height_temp = head;
		while(height_temp != NULL){
			if(nn[height_temp->x][height_temp->y].height > max_height)
				max_height = nn[height_temp->x][height_temp->y].height; 
			height_temp = height_temp->next;
		}
		temp=head;
		
		//tempがNULLになるまで回す
		do{

			i=0;
			
			//S,Rは飛ばす
			if( nn[temp->x][temp->y].statement=='S' || nn[temp->x][temp->y].statement=='R'){
				temp=temp->next;
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
				if(nn[temp->x][temp->y].height <= max_height)
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
		if(sir_time==SIMULATION_PERIOD){
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

		float inf_pro;
		double d_correction=0;
		double st_correction=0;
		struct Cell *which_temp;
		
		inf_pro=Uniform();
		
		if(nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].statement == 'S' && nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].height != 1){
		
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
				nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].from_virus=nn[launch_x][launch_y].node_number;
				nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].kind_of_source=nn[launch_x][launch_y].kind_of_source;
				//printf("%d, %d\n", nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].kind_of_source,nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].from_virus);
				Insert(edgedot/ONE_SIDE,edgedot%ONE_SIDE,&tail);
				nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].height=nn[launch_x][launch_y].height+1;
				nn[edgedot/ONE_SIDE][edgedot%ONE_SIDE].infected_time = sir_time;
				if( (launch_x == 0 && launch_y == 14) || (launch_x == 14 && launch_y == 0)){
          which_temp=head;
/*          while(which_temp != NULL){
            TraverseList(head);
            printf("[[which_temp->x=%d,which_temp->y=%d]]\n",which_temp->x,which_temp->y);
	  	      printf("which_temp.from_virus=%d\n",nn[which_temp->x][which_temp->y].from_virus); 
	  	      printf("which_temp_kind_source=%d\n",nn[which_temp->x][which_temp->y].kind_of_source);
	  	      printf("which_temp_statement=%c\n",nn[which_temp->x][which_temp->y].statement);
	  	      printf("which_temp_height=%d\n",nn[which_temp->x][which_temp->y].height);
	  	      which_temp = which_temp->next;
	  	    }
*/        }
			}
		}

}

