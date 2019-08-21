

/************************************************
 *												*
 * void set_value(struct Node)					*
 * -Nodeのメンバの初期化、または必要な数値を入力	*
 * 												*
 ************************************************/

int decide_topics(void);

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
				nn[i][j].favorite_topic=decide_topics();
				value++;
				}
		}
}


//----------------------------------------------------------------------------------
int decide_topics(void){
  float topics_number;
  
  topics_number=Uniform();
  
  if(topics_number>=0 && topics_number<0.3)
    return POLITICS;
  else if(topics_number>=0.3 && topics_number<0.55)
    return RELIGION;
  else if(topics_number>=0.55 && topics_number<0.70)
    return URBAN_LEGEND;
  else if(topics_number>=0.70 && topics_number<0.85)
    return COMMERCE;
  else if(topics_number>=0.85 && topics_number<0.95)
    return ENTERTAINMENT;
  else
    return SCIENCE_TECHNOLOGY;
}
