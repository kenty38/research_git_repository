
#include "function.h"

void file_value(struct Node nn[ONE_SIDE][ONE_SIDE],struct Edge e[ONE_SIDE],int number){
	int i;
	int source_cnt=number+1;
	int people=0;
	int max=0;
	char tmp[256]={""};
	
	struct Cell *temp;

	//共有者の情報
	if((fp=fopen(filename,"a"))==NULL){
		printf("ファイルをオープンできません\n");
		exit(1);
	}


	temp=head;
		
	//総感染人口の算出
	do{

		people+=(nn[temp->x][temp->y].population * INF_PEOPLE_RATE);

#ifdef	DETECT_SOURCE		
		if(source_cnt != 0){
			strcat(tmp,"*");
			source_cnt--;
		}
#endif
			
		strcat(tmp,nn[temp->x][temp->y].name);	
		//printf("tmp=%s\n",tmp);
		
		if(temp->next!=NULL)
			strcat(tmp," ");
		
		temp=temp->next;
		
	}while(temp!=NULL);
	
	temp=head;

	//fprintf(fp,"%d ",number+1);
	fprintf(fp,"%4d ",people);//総人数
	//fprintf(fp,"%s\n",nn[temp->x][temp->y].name);
	fprintf(fp,"%s\n",tmp);	
		
	fclose(fp);
}
