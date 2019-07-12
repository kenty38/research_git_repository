
/************************************************
 *												*
 * void set_value(struct Node)					*
 * -Nodeのメンバの初期化、または必要な数値を入力	*
 * 												*
 ************************************************/

#include "function.h"

void set_value(struct Node nn[ONE_SIDE][ONE_SIDE]){
	int i,j;
	int value=0;

	for(i=0;i<ONE_SIDE;i++){
			for(j=0;j<ONE_SIDE;j++){
				nn[i][j].omega = (float)rand() / RAND_MAX;		//0~1.0の間で意見を持つ
				nn[i][j].node_number = value;
				nn[i][j].node_theta = 0;
				nn[i][j].deltaex = DELTA + Uniform() * DELTA_EXPANSION * DELTA;
				nn[i][j].x = i;
				nn[i][j].y = j;
				nn[i][j].height = 0;
				nn[i][j].cluster = 0;
				nn[i][j].degree = 0;
				nn[i][j].statement = 'S';
				nn[i][j].lifetime=1;
				value++;
				}
		}
}
