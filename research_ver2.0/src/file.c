
#include "function.h"

void file_value(struct Node nn[n][n],struct Edge e[n]){
	int people=0;
	int max=0;
	int i=0,j=0;
	int *height_count;

	struct Cell *temp;

	temp=head;
	//共有者の情報
	if((fp=fopen(filename,"a"))==NULL)
		printf("ファイルをオープンできません\n");

	else{

#ifdef SIR
		do{
			people++;
			if(max<nn[temp->x][temp->y].height){
				max=nn[temp->x][temp->y].height;
			}
			temp=temp->next;
		}while(temp!=NULL);

		temp=head;

		height_count=malloc(sizeof (int)*max);
		for(i=0;i<max;i++)height_count[i]=0;//初期化

		do{
			height_count[nn[temp->x][temp->y].height-1]++;
			temp=temp->next;

		}while(temp!=NULL);

#endif

#ifndef DEBUG
//深さが20以上の時、ヒストグラム生成

		if(max>20){

				puts("最高の深さが20を超えました.");

//				for(i=0;i<max;i++)
//					printf("height_count[%2d]=%2d\n",i+1,height_count[i]);


				for(i=0;i<max;i++){

					printf("%2d :",i+1);

					for(j=0;j<height_count[i];j++)printf("*");
						;
					puts("");

				}

		}
#endif

		//printf("合計共有者人数=%d\n",people);
		//printf("max=%d\n",max);
		//printf("深さ=%d\n",max);

	}

		fprintf(fp,"%d ",people);//総人数
		fprintf(fp,"%d ",max);	  //最大の深さ
		fprintf(fp,"%.2f\n",theta);


		free(height_count);
		fclose(fp);
}
