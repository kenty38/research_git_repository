
#ifndef FUNCTION_H_

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define DETECT_SOURCE

//ONE_SIDE*nで総人数になる
#define ONE_SIDE 	       			    15

//グラフの辺の総本数*rでつなぎ直す辺の数
#define REWIRING_COUNT              	ONE_SIDE * ONE_SIDE * 0.01

//シミュレーションの期間
#define SIMULATION_PERIOD 				100

//初期共有者の最大人数
#define MAX_FIRST_SHARE 				2

//都道府県の数(修正する可能性あり)
#define PREFECTURE_NUMBER	47

//平均を取るためにリピートする回数
#define REPEAT_AVERAGE 100

//thetaの増加量
#define THETA_INCREASE 				0.1

//辺の数
#define EDGE_NUMBER				    4 * ONE_SIDE * ONE_SIDE						//WSの時

//lifetimeを設定するときに使う変数
#define LIFETIME_DAY					1

#define STRING_MAX 64

//#define INFECTED_PROBABIRITY 		23.84 / (ONE_SIDE * ONE_SIDE)		//感染率{情報共有者の平均を総人数で割ったもの(23.84/(ONE_SIDE*ONE_SIDE))}
#define INFECTED_PROBABIRITY		0.02
#define REMEDY_PROBABIRITY      1/5*8.0

#define INF_PEOPLE_RATE 0.10
#define INFECTION_PERIOD 7

#define POSSITIVE_CORRECTION 0.1
#define NEGATIVE_CORRECTION -0.1

//辺の状態を示すための列挙型
enum EDGE_STATUS{
	HOMOGENEOUS ,
	NONHOMOGENEOUS
};

enum SOURCE_OF_INFECTION{
	IMMEDIATELY,
	STILL,
	TEMP_IMMEDIATELY
};

enum SAME{
	SAME
};

enum MODE{
	ORIGINAL,
	DENSITY,
	STATION,
	BOTH
};

FILE *fp;							//ファイルへのポインタ
char filename[FILENAME_MAX];		//ファイル名

float theta;					//ニュースの値

int mode;

//SIRモデル時に使用
int 	sir_time;					//時間
int 	infected_count;				//感染者の人数
float 	gamma_denominator;			//gammaの分母
float 	large_gamma;				//回復率{(1/日数)で定義,大量にデータを確保する時はマクロではなくこちらを使用

//Edgeの構造体
struct Edge{
	int status;			//思考ベクトル
	int start;				//始点（s<f）
	int finish;				//終点
};

//Nodeの構造体
typedef struct Node{
		int 	node_number;
		char  name[STRING_MAX];
		int 	x;
		int 	y;
		int 	height;
		int 	degree;
		int *ad_list;
		char statement;
		int  population;
		int  space;
		float popu_dens;
		int station_number;
		float activity;
		int lifetime;
		int source_of_infection;
}t_Node;


struct Cell{
	int x;						 //x座標
	int y;						 //y座標
	struct Cell *next;			 //次のセルのポインタ
};


struct Cell *head;
struct Cell *tail;


//多重配列のプロトタイプ宣言は最後に数値を入れる
//main関数に使われる関数
extern void set_value(struct Node[][ONE_SIDE]);

extern void set_firstInf(struct Node[][ONE_SIDE],int number);

extern void set_firstInf_SIR(struct Node[][ONE_SIDE],int number,int t_pref);

extern void set_edge(struct Node[][ONE_SIDE],struct Edge[]);

extern void rewiring_network(struct Node[][ONE_SIDE],struct Edge[]);

extern void make_ad_list(struct Node[][ONE_SIDE],struct Edge[]);

extern void spreading_theories_SIR(struct Node[][ONE_SIDE],struct Edge[]);

extern void init_for_next(struct Node[][ONE_SIDE]);

extern void source_reset(struct Node[][ONE_SIDE]);


//乱数を用いて分布を表す関数
//0~1の一様乱数
extern double Uniform(void);

extern double rand_normal(double,double);

extern double rand_lnormal(double,double);

extern double rand_Igauss(double , double);

extern double poisson(double);


//上記の関数内で使われる関数
extern void TraverseList(struct Cell *);

extern void HeadInsert(int ,int ,struct Cell **,struct Cell **);

extern void Insert(int ,int ,struct Cell **);

extern void freeList(struct Cell *);

extern void allDeleteList(struct Cell *);

extern void deleteList(struct Cell *);

extern void Qsort(int x[],int left,int right);

extern void Swap(int x[],int i,int j);

//ファイルへ入力するための関数
extern void file_value(struct Node[][ONE_SIDE],struct Edge[],int number);

#define FUNCTION_H_
#endif /* FUNCTION_H_ */
