
#include "function.h"

void ad_list_check(struct Node n3[ONE_SIDE][ONE_SIDE]);

/**********************************************************
 *														  *
 * void make_ad_list(struct Node,struct Edge)			  *
 * -Node分だけ接続リストを生成する						  *
 * -SIR時のみlifetimeを追加する							  *
 * -lifetimeの初期化はinit_until_1000で行う		          *
 * -SIRモデルでは辺生成時に次数を数えてしまうため、ここでは除外
 **********************************************************/

void make_ad_list(struct Node nn[ONE_SIDE][ONE_SIDE],struct Edge e[]){

	int i=0,j=0;			//作業用変数
	int count;				//隣接リストに辺の数だけ追加するときに使う作業用変数

	i=0;

	//各ノードの隣接リストを作る
	while(i<ONE_SIDE*ONE_SIDE){
		//次数分の配列を生成
		//nn[i/ONE_SIDE][i%ONE_SIDE].ad_list=(int*)malloc(nn[i/ONE_SIDE][i%ONE_SIDE].degree*sizeof(int));
		nn[i/ONE_SIDE][i%ONE_SIDE].ad_list=malloc(sizeof (int)*nn[i/ONE_SIDE][i%ONE_SIDE].degree);
		
		//lifetime設定
		//nn[i/ONE_SIDE][i%ONE_SIDE].lifetime=LIFETIME_DAY;//*(8/nn[i/ONE_SIDE][i%ONE_SIDE].degree);

		count=0;

		//辺の数だけ隣接リストに始点と終点と格納
		for(j=0;j<EDGE_NUMBER;j++){
			if(e[j].start==nn[i/ONE_SIDE][i%ONE_SIDE].node_number){
				nn[i/ONE_SIDE][i%ONE_SIDE].ad_list[count]=e[j].finish;
				count++;
			}
			else if(e[j].finish==nn[i/ONE_SIDE][i%ONE_SIDE].node_number){
				nn[i/ONE_SIDE][i%ONE_SIDE].ad_list[count]=e[j].start;
				count++;
			}

			if(count==nn[i/ONE_SIDE][i%ONE_SIDE].degree)
				break;
		}

		//配列を小さい順にソートする(list.c)
			Qsort(nn[i/ONE_SIDE][i%ONE_SIDE].ad_list,0,nn[i/ONE_SIDE][i%ONE_SIDE].degree-1);
		i++;
	}
		ad_list_check(nn);
}



//-------------------------------------------------------------------------------------------------------

void ad_list_check(struct Node n3[ONE_SIDE][ONE_SIDE]){

	int i=0,j=0;
	
	puts("");
	
	while(j<ONE_SIDE*ONE_SIDE){

		printf("Node[%d][%d].ad_list=\n",j/ONE_SIDE,j%ONE_SIDE);

		for(i=0;i<n3[j/ONE_SIDE][j%ONE_SIDE].degree;i++)
				printf("%d ",n3[j/ONE_SIDE][j%ONE_SIDE].ad_list[i]);
		puts("\n");
		j++;
	}
}

