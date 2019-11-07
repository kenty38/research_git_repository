
#include "function.h"

void source_reset(struct Node nn[ONE_SIDE][ONE_SIDE]){
	
	int i;
	
	//情報共有者リストを初期化
	allDeleteList(head);
	head=NULL;
	tail=head;
	
	for(i=0;i<ONE_SIDE*ONE_SIDE;i++){
		if(nn[i/ONE_SIDE][i%ONE_SIDE].source_of_infection == TEMP_IMMEDIATELY)
			nn[i/ONE_SIDE][i%ONE_SIDE].source_of_infection = STILL;
	}
}
