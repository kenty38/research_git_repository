
#include "function.h"

struct Cell *head=NULL;

void display(struct Node[][n]);
void display_h(struct Node[][n]);

//main関数
int main(){

	int i,j;	//作業用変数
	int rep=0;	//繰り返し回数をカウントする変数
	int first_shared;
	int k;
	int rep_news=1100;	//ニュースを投げる回数

	//点の定義、辺の定義,情報共有者の定義
	struct Node node[n][n];
	struct Edge edge[m*(n*n-m)+(m*(m-1))/2];	//BAモデル時

	//シード値入力
	srand((unsigned)time(NULL));

	clock_t start_t,end_t;
	start_t = clock();

//ここにファイル名変更手順を入力
	//gammaは2~20
	
#ifdef SIR
	gamma_denominator=1.5;
	while(gamma_denominator<3.1){
		large_gamma=1.0/gamma_denominator;
		printf("gamma_denominator=%.01f\n",gamma_denominator);
		printf("large_gamma=%f\n",large_gamma);
		fflush(0);
		//lifetimeは1~100
		for(lifetime_hour=9;lifetime_hour<10;lifetime_hour++){
			printf("lifetime_hour=%d\n",lifetime_hour);
			rep=0;

			sprintf(filename,"./data/result_SIR/SIR_deno=%.01f_life=%d.txt"
					,gamma_denominator,lifetime_hour);
			printf("ファイル名:%s\n",filename);
#endif

	  for(first_shared=0;first_shared<20;first_shared++){
#ifdef DEBUG
			for(i=0;i<100;i++){
#endif
				theta=0.0;
				//sprintf(filename,"./data/value_first=%d.txt",first_shared);
				sprintf(filename,"./data/value.txt");

				//格子の要素, x座標, y座標を入れる
				set_value(node);

				//初期情報共有者を分布に従って入れる
				set_firstInf_SIR(node);
				
				//辺の情報を格納
				set_edge_BA(node,edge);
				
				//隣接リスト生成
				make_ad_list(node,edge);

				//(BAでは)隣接リストも生成
				//clustering_BA(node,edge);


//------------ほぼ共通の挙動---------------
#ifdef DEBUG

		//0.56の割合で均質パスを形成させる
#ifdef HOMO_PATH
				omega_renew(node,edge);
#endif
				//for(theta=0.0;theta<1.1;theta+=0.1){
					for(j=0;j<rep_news;j++){
						//ニュース(m=1000)
						if(j>99 && j%100==0)
							theta+=0.1;
							//theta=(float)rand()/RAND_MAX;

						//情報拡散(SIRのときのみ変化)
#ifdef SIR
					spreading_theories_SIR(node,edge);
#endif

						//ファイル出力
						file_value(node,edge);

						//puts("oimo");
						//初期化
//lifetime確認用のループ
#ifndef DEBUG
					for(k=0;k<n*n;k++)
									printf("node[%d][%d].lifetime=%d\n",k/n,k%n,node[k/n][k%n].lifetime);
#endif
						init_until_1000(node,&rep);
						if(j!=rep_news-1)
#ifdef SIR
						set_firstInf_SIR(node);
#endif

					}
				//}
				//それぞれの隣接リスト(動的配列)の解放
				//改良の余地あり
				for(j=0;j<n*n;j++)
					free(node[j/n][j%n].ad_list);

			}

#endif
	}//ループの最後
		}
		gamma_denominator=gamma_denominator+0.1;
	}


	end_t = clock();
	printf("%.2f秒かかりました\n",(double)(end_t-start_t)/CLOCKS_PER_SEC);

	return 0;
}



//---------------<<表示するための簡易な関数>>----------------------------------------

void display(struct Node nn[n][n]){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			printf("node[%d][%d].statement=%c\n",i,j,nn[i][j].statement);
	}

}

void display_h(struct Node nn[n][n]){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			printf("node[%d][%d].height=%d\n",i,j,nn[i][j].height);
	}

}
