
/************************************************
 *												*
 * void set_value(struct Node)					*
 * -Nodeのメンバの初期化、または必要な数値を入力	*
 * 												*
 ************************************************/

#include "function.h"

void set_value(struct Node nn[ONE_SIDE][ONE_SIDE]){
	int i=0;
	
	FILE *fp2;
	char fname[]="japan_2.csv";
	char line[STRING_MAX];
	
	fp2=fopen(fname,"r");
	if(fp2 == NULL){
		printf("%s file not open!\n",fname);
		exit(1);
	}
	
	while(fgets(line,STRING_MAX,fp2) !=NULL){
	
		sscanf(line,"%[^,],%d,%d,%d,%d,%f,%d,%f",
				nn[i/ONE_SIDE][i%ONE_SIDE].name,&nn[i/ONE_SIDE][i%ONE_SIDE].x,&nn[i/ONE_SIDE][i%ONE_SIDE].y,
				&nn[i/ONE_SIDE][i%ONE_SIDE].population,&nn[i/ONE_SIDE][i%ONE_SIDE].space,
				&nn[i/ONE_SIDE][i%ONE_SIDE].popu_dens,&nn[i/ONE_SIDE][i%ONE_SIDE].station_number,
				&nn[i/ONE_SIDE][i%ONE_SIDE].activity);
				
				nn[i/ONE_SIDE][i%ONE_SIDE].node_number = i;
				nn[i/ONE_SIDE][i%ONE_SIDE].x = i/ONE_SIDE;
				nn[i/ONE_SIDE][i%ONE_SIDE].y = i%ONE_SIDE;
				nn[i/ONE_SIDE][i%ONE_SIDE].height = 0;
				nn[i/ONE_SIDE][i%ONE_SIDE].degree = 0;
				nn[i/ONE_SIDE][i%ONE_SIDE].statement = 'S';
				nn[i/ONE_SIDE][i%ONE_SIDE].lifetime=INFECTION_PERIOD;
				nn[i/ONE_SIDE][i%ONE_SIDE].source_of_infection=STILL;	
			  nn[i/ONE_SIDE][i%ONE_SIDE].from_virus=0;
			  nn[i/ONE_SIDE][i%ONE_SIDE].kind_of_source = NOT_SOURCE;	
				nn[i/ONE_SIDE][i%ONE_SIDE].infected_time = 0;
				//population,name,space
				
				//printf("%s %d %d %d %d %.1f\n",nn[i/ONE_SIDE][i%ONE_SIDE].name,nn[i/ONE_SIDE][i%ONE_SIDE].x,nn[i/ONE_SIDE][i%ONE_SIDE].y,nn[i/ONE_SIDE][i%ONE_SIDE].population,nn[i/ONE_SIDE][i%ONE_SIDE].space,nn[i/ONE_SIDE][i%ONE_SIDE].popu_dens);
				
				i++;
				
				if(i==ONE_SIDE*ONE_SIDE){
					break;
				}
		}
		
		fclose(fp2);
}