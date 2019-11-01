
/************************************************
 *												*
 * void set_firstInf(struct Node)				*
 * -初期共有者の分布を決め、初期情報共有者に		*
 * -選ばれたノードの情報を書き換える。				*
 * -リスト構造を用いて情報共有者をまとめている		*
 * 												*
 ************************************************/

#include "function.h"

void check_statement(struct Node n3[ONE_SIDE][ONE_SIDE]);

void set_firstInf(struct Node nn[ONE_SIDE][ONE_SIDE],int number){
	int i;			//作業用変数
	int f_shared;	//初期情報共有者のノード番号をランダムに決める


	//初期共有者の値をinfected_countへ代入(初期共有者固定の場合)
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

			i++;

		}
	}while(i < infected_count);

	fclose(fp);

};


/************************************************
 *												*
 * void set_firstInf_SIR(struct Node)			*
 * -set_firstInfのSIRモデル版。					*
 * -SIRモデルで使われるstatementの情報を更新する。	*
 * 												*
 ************************************************/

void set_firstInf_SIR(struct Node nn[ONE_SIDE][ONE_SIDE],int number){
	int i;			//作業用変数
	int f_shared;	//初期情報共有者のノード番号をランダムに決める
	int judge;

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

	//infected_count=4;

	//printf("共有者：%d\n",infected_count);

	//初期情報共有者のデータを入力
	do{
		f_shared=rand()%(ONE_SIDE*ONE_SIDE);

		if(nn[f_shared/ONE_SIDE][f_shared%ONE_SIDE].statement=='S'){
			
			judge=strcmp(nn[f_shared/ONE_SIDE][f_shared%ONE_SIDE].name,"SEA");
			//printf("judge=%d,name=%s\n",judge,nn[f_shared/ONE_SIDE][f_shared%ONE_SIDE].name);
			if(judge==0)
				continue;
			
			//printf("%s\n",nn[f_shared/ONE_SIDE][f_shared%ONE_SIDE].name);
			nn[f_shared/ONE_SIDE][f_shared%ONE_SIDE].height=1;
			nn[f_shared/ONE_SIDE][f_shared%ONE_SIDE].statement='I';
			nn[f_shared/ONE_SIDE][f_shared%ONE_SIDE].lifetime=1;

			if(i==0){
				HeadInsert(nn[f_shared/ONE_SIDE][f_shared%ONE_SIDE].x,nn[f_shared/ONE_SIDE][f_shared%ONE_SIDE].y,&head,&tail);
			}
			else{
				Insert(nn[f_shared/ONE_SIDE][f_shared%ONE_SIDE].x,nn[f_shared/ONE_SIDE][f_shared%ONE_SIDE].y,&tail);
			}
			
			i++;
		}
	}while(i<infected_count);
	
	
	//check_statement(nn);
	fclose(fp);

}


void check_statement(struct Node n3[ONE_SIDE][ONE_SIDE]){
	int i,j;
	
	for(i=0;i<ONE_SIDE;i++)
		for(j=0;j<ONE_SIDE;j++)
			printf("%d.statement=[%c]\n",n3[i][j].node_number,n3[i][j].statement);	
}


