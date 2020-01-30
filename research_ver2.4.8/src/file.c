
#include "function.h"

void file_value(struct Node nn[ONE_SIDE][ONE_SIDE],struct Edge e[ONE_SIDE],int number){
	int i;
	int source_cnt=number+1;
	float people=0;
	int max=0;
	char tmp[256]={""};
		//感染源1の感染者リスト
	char tmp_2nd[256]={""};
//感染源2の感染者リスト
	int list_count=0;
	
	struct Cell *temp;
	struct Cell *which_temp;
	//tmpかtmp_2ndのどちらのリストに入れるか決めるセル

	//共有者の情報
	if((fp=fopen(filename,"a"))==NULL){
		printf("ファイルをオープンできません\n");
		exit(1);
	}


	temp=head;
	
	while(temp != NULL){
		list_count++;
		temp=temp->next;
	}
	
	temp=head;
		
	//総感染人口の算出
	do{

		people+=(nn[temp->x][temp->y].population * INF_PEOPLE_RATE);

#ifdef	DETECT_SOURCE		
		if(nn[temp->x][temp->y].height == 1	){
			if(nn[temp->x][temp->y].kind_of_source == SOURCE_1){
				strcat(tmp,"*");
			}
			else{
				strcat(tmp_2nd,"*");
			}
			source_cnt--;
		}
#endif

		which_temp = head;
	  while(which_temp != NULL){
			
		//TraverseList(head);
		//printf("te.fv=%d, wh_te.nu=%d\n",nn[temp->x][temp->y].from_virus, nn[which_temp->x][which_temp->y].node_number); 
		//printf("kind_source=%d\n",nn[which_temp->x][which_temp->y].kind_of_source);
			if( nn[temp->x][temp->y].from_virus == nn[which_temp->x][which_temp->y].node_number	){ 
				if( nn[temp->x][temp->y].kind_of_source == SOURCE_1){
					strcat(tmp,nn[temp->x][temp->y].name);	
					if(temp->next!=NULL)
						strcat(tmp," ");
				}
				else{
					strcat(tmp_2nd,nn[temp->x][temp->y].name);	
					if(temp->next!=NULL)
						strcat(tmp_2nd," ");
				}
				break;
			}	
		which_temp = which_temp->next;
		}
		
		
		temp=temp->next;
	}while(temp!=NULL);
	
	temp=head;

	fprintf(fp,"%d ",list_count);
	fprintf(fp,"%4.2f ",people);//総人数
//	fprintf(fp,"%s\n",nn[temp->x][temp->y].name);
	fprintf(fp,"%s\n",tmp);	
//	fprintf(fp,"%s\n",tmp_2nd);	
		
	fclose(fp);
}
