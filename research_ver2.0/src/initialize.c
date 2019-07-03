/*
 *
 * set_value.c
 *  Created on: 2017/10/24
 *      Author: f0416028-2
 */

/************************************************
 *												*
 * void initialize(struct Node)					*
 * -Nodeのメンバの初期化、または必要な数値を入力	*
 * 												*
 ************************************************/

#include "function.h"

void initialize(struct Node nn[n][n]){
	int i,j;
	int value=0;

	for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				nn[i][j].omega=(float)rand()/RAND_MAX;		//0~1.0の間で意見を持つ
				nn[i][j].node_number=value;
				nn[i][j].node_theta=0;
				nn[i][j].deltaex=delta+Uniform()*2*delta;;
				nn[i][j].x=i;
				nn[i][j].y=j;
				nn[i][j].height=0;
				nn[i][j].cluster=0;
				nn[i][j].degree=0;
				nn[i][j].statement='S';
				nn[i][j].lifetime=0;
				value++;
				}
		}
}
