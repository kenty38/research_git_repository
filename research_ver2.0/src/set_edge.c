/*
 * set_edge.c
 *
 *  Created on: 2017/10/24
 *      Author: f0416028-2
 */

/************************************************
 *												*
 * void set_edge(struct Node)					*
 * -辺の情報を格納する							*
 * -隣接リストが生成されていないことに注意			*
 * 												*
 ************************************************/

#include"function.h"

void set_edge(struct Node nn[n][n],struct Edge e[N]){

	int i,j,ii,jj;	//作業用変数
	int value=0;	//0~Nまで辺の値を格納するために使われる作業用変数
	int count;		//0~7までの値を取り、隣人の情報を得るために使われる
	int ne[8];  	//隣人の情報を格納

	for(i=0;i<n;i++){
			for(j=0;j<n;j++){

				//ムーア近傍の判定
				count=0;

				for(ii=-1;ii<=1;ii++){	//x軸固定
					for(jj=-1;jj<=1;jj++){

						//同じ点の時はスルー
						if((nn[i][j].x+ii)==nn[i][j].x&&(nn[i][j].y+jj)==nn[i][j].y){
							//printf("<%d> ",node[node[i][j].x][node[i][j].y].node_number);
							continue;
						}

						//x,y共に負の時の周期境界による点の指定
						if((nn[i][j].x+ii)<0 && (nn[i][j].y+jj)<0){
							ne[count]=nn[n-1][n-1].node_number;
						}
						//xのみ負の時の点の指定
						else if(nn[i][j].x+ii<0){
							ne[count]=nn[n-1][(nn[i][j].y+jj)%n].node_number;
						}
						//yのみ負の時の点の指定
						else if((nn[i][j].y+jj)<0){
							ne[count]=nn[(nn[i][j].x+ii)%n][n-1].node_number;
						}
						//特別な条件がない時
						else{
							ne[count]=nn[(nn[i][j].x+ii)%n][(nn[i][j].y+jj)%n].node_number;
						}

						//(e[].s < e[].f)の時だけedgeに値を入れるようにする
						if(nn[i][j].node_number<ne[count]){
							e[value].s=nn[i][j].node_number;
							e[value].f=ne[count];
							e[value].vec=(2*nn[e[value].s/n][e[value].s%n].omega-1)*(2*nn[e[value].f/n][e[value].f%n].omega-1);
							value++;
						}

						count++;
						//for(l=0;l<8;l++)printf("%d:ne[%d]=%d\n",nn[i][j].node_number,l,ne[l]);
					}
				}

			}
	}
}
