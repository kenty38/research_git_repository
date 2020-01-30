
#include "function.h"

void check_statement(struct Node n3[ONE_SIDE][ONE_SIDE]);


/************************************************
 *												*
 * void set_firstInf_SIR(struct Node)			*
 * -set_firstInfのSIRモデル版。					*
 * -SIRモデルで使われるstatementの情報を更新する。	*
 * 												*
 ************************************************/

void set_firstInf_SIR(struct Node nn[ONE_SIDE][ONE_SIDE],int number,int t_pref){
	int i,j;			//作業用変数
	int judge;

	infected_count=number+1;
	if(infected_count==0)infected_count=1;

	if((fp=fopen(filename,"a"))==NULL){
			printf("aファイルをオープンできません\n");
			exit(1);
	}
/*	else{
			fprintf(fp,"%d ",infected_count);
	}
*/
	i=0;
	j=0;

	//47都道府県を順番に感染源にしていく
	//感染源に指定されてない県ならば、感染源に指定する
	do{
	
			judge=strcmp(nn[i/ONE_SIDE][i%ONE_SIDE].name,"SEA");
			//printf("judge=%d,name=%s\n",judge,nn[i/ONE_SIDE][i%ONE_SIDE].name);

			if(judge!=SAME){
				if(nn[i/ONE_SIDE][i%ONE_SIDE].source_of_infection == STILL){
					//printf("%s:%d\n",nn[i/ONE_SIDE][i%ONE_SIDE].name,nn[i/ONE_SIDE][i%ONE_SIDE].source_of_infection);
					
					nn[i/ONE_SIDE][i%ONE_SIDE].height=1;
					nn[i/ONE_SIDE][i%ONE_SIDE].statement='I';
					nn[i/ONE_SIDE][i%ONE_SIDE].lifetime=1;
					nn[i/ONE_SIDE][i%ONE_SIDE].from_virus=nn[i/ONE_SIDE][i%ONE_SIDE].node_number;
          nn[i/ONE_SIDE][i%ONE_SIDE].kind_of_source = SOURCE_1; 
					nn[i/ONE_SIDE][i%ONE_SIDE].source_of_infection=IMMEDIATELY;

					if(j==0 && t_pref==0){     //感染源2つの時の一番最初の条件,これで固定する県を選ぶ
						HeadInsert(nn[i/ONE_SIDE][i%ONE_SIDE].x,nn[i/ONE_SIDE][i%ONE_SIDE].y,&head,&tail);
					}
					else{
						nn[i/ONE_SIDE][i%ONE_SIDE].source_of_infection=TEMP_IMMEDIATELY;
	//2つ目の感染源に設定し,IMMEDIATELYからTEMP_IMMEDIATELYに変更
            nn[i/ONE_SIDE][i%ONE_SIDE].kind_of_source = SOURCE_2; 
						Insert(nn[i/ONE_SIDE][i%ONE_SIDE].x,nn[i/ONE_SIDE][i%ONE_SIDE].y,&tail);
						
						//jをわざと大きくしてループから抜け出す
						j++;
					}
			
					j++;
				}
			}
		
		i++;
	}while(j<infected_count);
	
	
	//check_statement(nn);
	fclose(fp);

}


void check_statement(struct Node n3[ONE_SIDE][ONE_SIDE]){
	int i,j;
	
	for(i=0;i<ONE_SIDE;i++)
		for(j=0;j<ONE_SIDE;j++)
			printf("%d.statement=[%c]\n",n3[i][j].node_number,n3[i][j].statement);	
}


