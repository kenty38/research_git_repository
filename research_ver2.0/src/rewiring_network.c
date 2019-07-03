/*
 * rewiring_network.c
 *
 *  Created on: 2017/10/24
 *      Author: f0416028-2
 */

#include"function.h"

/**********************************************************
 *														  *
 * void rewiring_network(struct Node,struct Edge)		  *
 * -総人数x再接続確率(r)分だけ辺を切り離してつなげる関数	  *
 * -これによりスモールワールドが再現できる			  		  *
 * 												          *
 **********************************************************/

void rewiring_network(struct Node nn[n][n],struct Edge e[N]){
	int i,j;	//作業用変数
	int x;		//乱数用変数
	int con;	//con=0の時は繋ぎ変えをやり直し,con=1の時は繋ぎ変え
	int temp;	//始点>終点のときに数値を入れ替えるための変数

	//xはランダムに選んで繋げ変えられる辺
	x=rand()%N;

	//printf("original_edge[%d]:%d - %d, n=%f\n",x,e[x].s,e[x].f,e[x].vec);

	//r回つなぎかえ
	for(i=0;i<r;i++){
		con=1;
		e[x].s=rand()%(n*n);
		e[x].f=rand()%(n*n);

		//始点>終点の時
		if(e[x].s>e[x].f){
			temp=e[x].f;
			e[x].f=e[x].s;
			e[x].s=temp;
		}
		//printf("rewiring; edge[%d]:%d - %d\n",x,e[x].s,e[x].f);

		j=0;

		//if文に引っかからなければ、数値を変更
		while(j<N){
			//printf("edge[%d].s=%d,edge[%d].f=%d\n",j,edge[j].s,j,edge[j].f);

			//x番目の辺を変えているため、x番目の時は何もしない
			if(j==x){
				j++;
				continue;
			}
			//始点と終点が同じだった場合、やり直し
			else if(e[x].s==e[x].f){
				//puts("やり直します");
					i--;
					con=0;
					break;
			}
			//既に存在している辺だった場合
			else if(e[x].s==e[j].s  ||  e[x].s==e[j].f ){
				if(e[x].f==e[j].s || e[x].f==e[j].f ){
					//puts("やり直します");
					i--;
					con=0;
					break;
				}
			}

			j++;

		}

		//con=1:何も問題がなかったとき。r-1以外は新たなxを決める。
		if(con==1){
			if(i==r-1)break;
			else{
				//辺の並べ替えを行う
				e[x].vec=(2*nn[e[x].s/n][e[x].s%n].omega-1)*(2*nn[e[x].f/n][e[x].f%n].omega-1);
				//printf("rewiring_edge[%d]:%d - %d, n=%f\n",x,e[x].s,e[x].f,e[x].vec);
				x=rand()%N;
				//printf("original_edge[%d]:%d - %d, n=%f\n",x,e[x].s,e[x].f,e[x].vec);
			}
		}

	}
	//printf("rewiring_edge[%d]:%d - %d, n=%f\n",x,e[x].s,e[x].f,e[x].vec);
	puts("");
}
