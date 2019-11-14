
#include "function.h"

struct Cell *head=NULL;

void confirm(void);
void note(void);
void display(struct Node[][ONE_SIDE]);
void display_h(struct Node[][ONE_SIDE]);
void statement_check(struct Node nn[ONE_SIDE][ONE_SIDE]);

//-------------------------------------------<<main関数>>---------------------------------------------------------
int main(){

	int i;						//作業用変数
	int temp_pref;
	int free_count;		//メモリ解放時に用いる作業用変数
	int simulation_day;//シミュレーションの日数
	int init_timer=0;	//特定回数数えたときに初期化するために必要なカウント
	int first_shared;	//初期共有者の現在の数
	int rep;

	struct Node node[ONE_SIDE][ONE_SIDE];		//点の定義、辺の定義,情報共有者の定義
	struct Edge edge[EDGE_NUMBER];				//辺の定義、BAの時とそれ以外で異なる

	//シード値入力
	srand((unsigned)time(NULL));

	clock_t start,end;
	start = clock();
	
	confirm();
	
	for(first_shared = 0 ; first_shared < MAX_FIRST_SHARE ; first_shared++){

		printf("first_shared=%d\n",first_shared+1);
		
		//ファイル名記入
		sprintf(filename,"../data/result/value_first=%d.txt",first_shared+1);
		
		//平均するためにREPEAT_AVERAGE繰り返す
		for(rep=0;rep<REPEAT_AVERAGE;rep++){
		
		//格子の要素, x座標, y座標を入れる
		set_value(node);
			
		//TraverseList(head);
			
		//辺の情報を格納
		set_edge(node,edge);
			
		//再接続
		rewiring_network(node,edge);
			
		//隣接リスト生成
		make_ad_list(node,edge);
		
		
		
			//各都道府県を選ぶ
			for(i=0;i<PREFECTURE_NUMBER;i++){
		
				for(temp_pref=0;temp_pref<PREFECTURE_NUMBER-i;temp_pref++){
		
					if(first_shared > 0 && temp_pref == PREFECTURE_NUMBER-(i+1))
						break;
					
					//初期情報共有者を分布に従って入れる
					set_firstInf_SIR(node,first_shared,temp_pref);
				
					//感染シミュレーション
					for(simulation_day = 0 ; simulation_day < SIMULATION_PERIOD ; simulation_day++)
						spreading_theories_SIR(node,edge);
				
					//ファイル出力
					file_value(node,edge,first_shared);

					//次の拡散のための初期化
					init_for_next(node);
					
					if(first_shared==0)
						break;
				}
				
					//TEMP_IMMEDIATELYをSTILLに戻す
					if(i != PREFECTURE_NUMBER-1)
						source_reset(node);
			}
		//
				
		//それぞれの隣接リスト(動的配列)の解放
		for(free_count=0 ; free_count<ONE_SIDE*ONE_SIDE ; free_count++)
			free(node[free_count/ONE_SIDE][free_count%ONE_SIDE].ad_list);
		
		}
	}//ループの最後

	end = clock();
	printf("%.2f秒かかりました\n",(double)(end-start)/CLOCKS_PER_SEC);

	return 0;
}







//-------------------------------------------------<<表示するための簡易な関数>>--------------------------------------------------------

void confirm(void){
	int i;
	int x[5]={
						remove("../data/result/value_first=1.txt"),
						remove("../data/result/value_first=2.txt"),
						remove("../data/result/value_first=3.txt"),
						remove("../data/result/value_first=4.txt"),
						remove("../data/result/value_first=5.txt")};
						
	for(i=0;i<MAX_FIRST_SHARE;i++)
		printf("%d ",x[i]);
	
	puts("");
}


void display(struct Node nn[ONE_SIDE][ONE_SIDE]){
	int i,j;
	for(i=0;i<ONE_SIDE;i++){
		for(j=0;j<ONE_SIDE;j++)
			printf("node[%d][%d].degree=%d\n",i,j,nn[i][j].degree);
	}

}

void display_h(struct Node nn[ONE_SIDE][ONE_SIDE]){
	int i,j;
	for(i=0;i<ONE_SIDE;i++){
		for(j=0;j<ONE_SIDE;j++)
			printf("node[%d][%d].height=%d\n",i,j,nn[i][j].height);
	}

}



void statement_check(struct Node nn[ONE_SIDE][ONE_SIDE]){
	int i;
	
	for(i=0;i<ONE_SIDE*ONE_SIDE;i++)
					printf("%d.statement=[%c]\n",nn[i/ONE_SIDE][i%ONE_SIDE].node_number,nn[i/ONE_SIDE][i%ONE_SIDE].statement);
}


