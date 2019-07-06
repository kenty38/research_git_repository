/*
 * file.c
 *
 *  Created on: 2017/10/31
 *      Author: f0416028-2
 */

#include "function.h"

void file_value(struct Node nn[ONE_SIDE][ONE_SIDE],struct Edge e[ONE_SIDE]){
	int i;
	int people=0;
	int max=0;
	int *height_count;

	struct Cell *temp;

	temp=head;
	//共有者の情報
	if((fp=fopen(filename,"a"))==NULL)
		printf("ファイルをオープンできません\n");

	else{
		//tailが必ず最大深さになる
		max=nn[tail->x][tail->y].height;

		height_count=malloc(sizeof (int)*max);
		for(i=0;i<max;i++)height_count[i]=0;//初期化

		do{
			people++;
			height_count[nn[temp->x][temp->y].height-1]++;
			temp=temp->next;

		}while(temp!=NULL);

	}

		fprintf(fp,"%d ",people);//総人数
		fprintf(fp,"%d ",max);	  //最大の深さ
		fprintf(fp,"%.2f\n",theta);


		free(height_count);
		fclose(fp);
}
