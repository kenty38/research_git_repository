
#include "function.h"

void file_value(struct Node nn[ONE_SIDE][ONE_SIDE],struct Edge e[ONE_SIDE],int number){
	int i;
	int people=0;
	int max=0;

	struct Cell *temp;

	temp=head;
	//共有者の情報
	if((fp=fopen(filename,"a"))==NULL){
		printf("ファイルをオープンできません\n");
		exit(1);
	}

		//tailが必ず最大深さになる
		max=nn[tail->x][tail->y].height;
		
		//fprintf(fp,"%d ",number+1);
		//fprintf(fp,"%d ",people);//総人数
		fprintf(fp,"%d ",max);	  //最大の深さ
		fprintf(fp,"%.2f\n",theta);

		fclose(fp);
}
