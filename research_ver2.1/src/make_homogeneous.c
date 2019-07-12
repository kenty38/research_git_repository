/*
 * omega_renew.c
 *
 *  Created on: 2017/11/06
 *      Author: ipad
 */

#include "function.h"

#define NOISE 0.01

/**********************************************************
 *														  *
 * void make_homogeneous(struct Node,struct Edge)			  *
 * -均質パスを形成して、自分と似たような意見の隣人と繋がる	  *
 * -ようにするための関数							  		  *
 * -論文の通り,均質パスは0.56の割合で形成するように設定      *
 **********************************************************/

void first_calculate_homogeneous(struct Edge e[EDGE_NUMBER] , double *count);
void calculate_homogeneous(struct Node nn[ONE_SIDE][ONE_SIDE] ,struct Edge e[EDGE_NUMBER] , double *count);
void option_close(float *start_omega ,float *finish_omega );
void confirm_status(double d_rand , int i_rand , double count);



void make_homogeneous(struct Node nn[ONE_SIDE][ONE_SIDE],struct Edge e[EDGE_NUMBER]){

	int i;								//作業用変数
	int random;							//確率用変数
	double d_random;
	double count_homogeneous = 0.0;	//均質パスの数
	double denominator_edge_number = 4.0 * ONE_SIDE * ONE_SIDE ;
	double homogeneous_probabirity=0.0 ;

	first_calculate_homogeneous(e,&count_homogeneous);

	homogeneous_probabirity = count_homogeneous / denominator_edge_number;
	fflush(0);


	//0.36以上になるまで繰り返す
	while(homogeneous_probabirity < CRITICAL_PATH_PROBABIRITY){

    for(i = 0 ; i < 1000 ; i++){
		  d_random = Uniform() * (EDGE_NUMBER - 1 );
		  random=d_random;
			
			option_close(&nn[e[random].start / ONE_SIDE][e[random].start % ONE_SIDE].omega ,
			             &nn[e[random].finish / ONE_SIDE][e[random].finish %ONE_SIDE].omega);			             
		}
		
		calculate_homogeneous(nn,e,&count_homogeneous);
		homogeneous_probabirity = count_homogeneous / denominator_edge_number;
	};

	fflush(0);
}


/*---------------------------------------<<function>>-------------------------------------------------------*/

void first_calculate_homogeneous(struct Edge e[EDGE_NUMBER] , double *count){
  int i;
  
  *count=0;
  
  for(i = 0 ; i < EDGE_NUMBER ; i++){			//均質パスのカウント
		if(e[i].status == HOMOGENEOUS)
			*count += 1;
	}
}


void calculate_homogeneous(struct Node nn[ONE_SIDE][ONE_SIDE] ,struct Edge e[EDGE_NUMBER] , double *count){
  int i;
  double option_error = 0;
  *count=0;
   
  for(i = 0 ; i < EDGE_NUMBER ; i++){			//均質パスのカウント
		option_error = fabs(nn[e[i].start / ONE_SIDE][e[i].start % ONE_SIDE].omega  - 
		        nn[e[i].finish / ONE_SIDE][e[i].finish % ONE_SIDE].omega);
		
		if(option_error < DELTA)
		  e[i].status = HOMOGENEOUS;        
		else 
		  e[i].status = NONHOMOGENEOUS;
		
		if(e[i].status == HOMOGENEOUS)
			*count += 1;
	}
	
	//printf("count=%f\n\n" , *count);
}


void confirm_status(double d_rand , int i_rand , double count){
  printf("d_random=%f\n" , d_rand);
  printf("random=%d\n" , i_rand);
	printf("count_homogeneous=%f\n\n" , count);
}


/*意見を近づける*/
void option_close(float *start_omega ,float *finish_omega ){

	double pro;
	pro = Uniform();

	if( pro > 0.50)
		*finish_omega = *start_omega + Uniform() * NOISE;
	else
		*start_omega = *finish_omega + Uniform() * NOISE;

}

