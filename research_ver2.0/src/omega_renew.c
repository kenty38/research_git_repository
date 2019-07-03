/*
 * omega_renew.c
 *
 *  Created on: 2017/11/06
 *      Author: ipad
 */

#include "function.h"

/**********************************************************
 *														  *
 * void omega_renew(struct Node,struct Edge)			  *
 * -均質パスを形成して、自分と似たような意見の隣人と繋がる	  *
 * -ようにするための関数							  		  *
 * -論文の通り,均質パスは0.56の割合で形成するように設定      *
 **********************************************************/

void omega_renew(struct Node nn[n][n],struct Edge e[N]){

	int i;				//作業用変数
	float a_omega;		//
	double pro;			//確率用変数

	pro=Uniform();
	//56%の確率で均質パスを形成する
	//つまり隣人と-delta~deltaの差ができる程度の違いしか生まれない
	for(i=0;i<N;i++){
		if(pro<0.56){
			a_omega=(nn[e[i].s/n][e[i].s%n].omega+nn[e[i].f/n][e[i].f%n].omega)/2.0;
			nn[e[i].s/n][e[i].s%n].omega=a_omega;
			nn[e[i].f/n][e[i].f%n].omega=a_omega;
		}
	}


}
