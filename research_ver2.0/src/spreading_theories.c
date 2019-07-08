
#include"function.h"

extern void agree_SIR(struct Node nn[][n] , int,int,int,int *);

/**********************************************************
 *														  *
 * void spreading_theories_SIR(struct Node,struct Edge)	  *
 * -情報共有者が情報を広げるための関数。					  *
 * -infected_countが0になるまで情報伝播を繰り返す			  *
 * -関数agree_SIRに判定、リスト挿入を行わせる。	          *
 **********************************************************/

void spreading_theories_SIR(struct Node nn[n][n], struct Edge e[N]){

	int i=0,j;				//作業用変数
	struct Cell *temp;		//headの位置を一時的に覚えておくためのセルポインタ
	double pro_remedy;		//情報に飽きたかどうか判定するために使用する確率用変数
	int temp_ad=0;			//tempの隣人を格納
	int temp_ad_j=0;		//tempの隣人を格納(lifetime判定用)
	int lifetime_sum=0;		//隣人のlifetimeの合計

	t=0;

	//感染者がいなくなるまで続ける
	while(1){

		temp=head;

		//tempがNULLになるまで回す
		do{

			i=0;
			lifetime_sum=0;

			//S,Rは飛ばす
			if( nn[temp->x][temp->y].statement=='S' || nn[temp->x][temp->y].statement=='R'){
				temp=temp->next;
				//printf("飽きているので飛ばします\n");
				continue;
			}

			//隣接リストの個数分だけ情報を広げる
			while(i<nn[temp->x][temp->y].degree){

				temp_ad=nn[temp->x][temp->y].ad_list[i];

				//情報を共有するかどうか判断する
				agree_SIR(nn,nn[temp->x][temp->y].ad_list[i],
						temp->x,temp->y,&infected_count);
				i++;
				pro_remedy=Uniform();

				//情報を流す度に、一定の確率でI→Rにする(非共有者がI,Rの時のみ)
				if(pro_remedy<large_gamma){
					if(nn[temp_ad/n][temp_ad%n].statement=='I' ||
						nn[temp_ad/n][temp_ad%n].statement=='R'){

						//printf("途中で終わりました(%d/%d)\n",i,nn[temp->x][temp->y].degree);
						nn[temp->x][temp->y].statement='R';
						infected_count--;
						break;
					}
				}
			}
#ifdef DEBUG
			//隣人のlifetimeの合計を計算
			for(j=0;j<nn[temp->x][temp->y].degree;j++){
				temp_ad_j=nn[temp->x][temp->y].ad_list[j];
				lifetime_sum+=nn[temp_ad_j/n][temp_ad_j%n].lifetime;
			}

			//隣人のタイムラインから消えてなくなった場合
			if(lifetime_sum==0 && nn[temp->x][temp->y].statement=='I'){
				nn[temp->x][temp->y].statement='R';
				infected_count--;
			}
#endif
			temp=temp->next;

		}while(temp!=NULL);

		t++;

		if(infected_count==0){
			//printf("感染者はいません\n");
			break;
		}

	}
}
