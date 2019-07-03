
#include "function.h"

void clustering_BA(struct Node nn[n][n],struct Edge e[]){

	int i=0,j=0,k=0,l=0;	//作業用変数
	float C=0;				//注目点が形成する三角形の個数
	float ave_C;			//全体のクラスター係数の平均
	int k_value=0;			//２つめの隣接点が複雑なため、k_valueと置く

	i=0;

	//三角形があるかどうか調べる
	while(i<n*n){

		C=0;
		//printf("<<");
		//printf("%d回目",i);
		//printf(">>\n");

		//一つ目の隣接点jを決める
		for(j=0;j<nn[i/n][i%n].degree-1;j++){

			//二つ目の隣接点kを決める
			for(k=j+1;k<nn[i/n][i%n].degree;k++){

				//二つ目の隣接点の値をk_valueとする
				k_value=nn[i/n][i%n].ad_list[k];

				//kの隣接リストにjがいるか
				for(l=0;l<nn[k_value/n][k_value%n].degree;l++){
					if(nn[k_value/n][k_value%n].ad_list[l]==nn[i/n][i%n].ad_list[j]){
						//printf("%d - %d\n",nn[i/n][i%n].ad_list[j],nn[i/n][i%n].ad_list[k]);
						C+=1;
						break;
					}
				}

			}
		}

		//printf("\nC[%d]=%f\n",i,C);

		//クラスター係数の計算
		nn[i/n][i%n].cluster=C/(nn[i/n][i%n].degree*(nn[i/n][i%n].degree-1)/2);
		ave_C+=nn[i/n][i%n].cluster;
		//printf("nn[%d][%d].cluster=%f\n",i/n,i%n,C/(nn[i/n][i%n].degree*(nn[i/n][i%n].degree-1)/2));

		i++;
	}


	printf("平均クラスター係数が%fです\n",ave_C/(n*n));
}
