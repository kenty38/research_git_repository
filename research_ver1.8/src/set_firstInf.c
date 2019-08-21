
/************************************************
 *												*
 * void set_firstInf(struct Node)				*
 * -初期共有者の分布を決め、初期情報共有者に		*
 * -選ばれたノードの情報を書き換える。				*
 * -リスト構造を用いて情報共有者をまとめている		*
 * 												*
 ************************************************/

#include "function.h"

void set_firstInf(struct Node nn[ONE_SIDE][ONE_SIDE],int number){
	int i;			//作業用変数
	int f_shared;	//初期情報共有者のノード番号をランダムに決める


	//初期共有者の値をinfected_countへ代入
	infected_count=number+1;

	if(infected_count==0)infected_count=1;

	if((fp=fopen(filename,"a"))==NULL){
			printf("aファイルをオープンできません\n");
			exit(1);
	}
	else{
			fprintf(fp,"%d ",infected_count);
	}

	i=0;
#ifndef DEBUG
	infected_count=4;
#endif
	//printf("共有者：%d\n",infected_count);

	//初期情報共有者のデータを入力
	do{
		f_shared=rand()%(ONE_SIDE*ONE_SIDE);

		if(nn[f_shared/ONE_SIDE][f_shared%ONE_SIDE].height==0){
			nn[f_shared/ONE_SIDE][f_shared%ONE_SIDE].height=1;

			if(i==0){
				HeadInsert(nn[f_shared/ONE_SIDE][f_shared%ONE_SIDE].x,nn[f_shared/ONE_SIDE][f_shared%ONE_SIDE].y,&head,&tail);
			}
			else{
				Insert(nn[f_shared/ONE_SIDE][f_shared%ONE_SIDE].x,nn[f_shared/ONE_SIDE][f_shared%ONE_SIDE].y,&tail);
			}

			//値の変更
			//nn[f_shared/n][f_shared%n].omega=theta+delta;
      //TraverseList(head);
			nn[f_shared/ONE_SIDE][f_shared%ONE_SIDE].node_theta=nn[f_shared/ONE_SIDE][f_shared%ONE_SIDE].omega+(2*Uniform()-1)*0.015;
			//nn[f_shared/n][f_shared%n].deltaex=delta+Uniform()*2*delta;
			i++;

		}
	}while(i < infected_count);

	fclose(fp);

}
