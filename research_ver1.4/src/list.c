/*
 * list.c
 *
 *  Created on: 2017/10/26
 *      Author: f0416028-2
 */

#include"function.h"

/****************************************************************************/
/* 関数名: Insert(x,y,pt,t)                                                  */
/* 動作: x,yの値を格納し、現在のtailの位置を示すポインタtを用いて接続する    */
/* その後、ptによりtailの位置情報を更新する*/
/****************************************************************************/
 void Insert(int x, int y,struct Cell **pt) {

  struct Cell *newcell;
  newcell = (struct Cell *)malloc(sizeof(struct Cell));
  newcell->x = x;
  newcell->y = y;

  newcell->next=(*pt)->next;
  (*pt)->next=newcell;
  *pt=newcell;

  //free(newcell);
}

 /****************************************************************************/
 /* 関数名: HeadInsert(x,y,ph,pt)                                            */
 /* 動作:NULLの時headに値を入れる関数								         */
 /* headとtailのポインタph,ptに新たな位置情報を与える*/
 /****************************************************************************/

 void HeadInsert(int x, int y, struct Cell **ph,struct Cell **pt){

	 struct Cell *newcell;
	 newcell = (struct Cell *)malloc(sizeof(struct Cell));
	 newcell->x = x;
	 newcell->y = y;

	 newcell->next=*ph;
	 *ph=newcell;
	 *pt=*ph;

	//free(newcell);

 }

 /****************************************************************************/
 /*         関数名: TraverseList                                             */
 /*         動作: リストの中身を画面に出力する。                             */
 /****************************************************************************/
 void TraverseList(struct Cell *p) {
   struct Cell *temp=p;

   puts("情報共有者を表示します");
   printf("( ");

   while (temp != NULL) {
	 printf("[%d][%d]",temp->x,temp->y);
     temp = temp->next;
     if(temp !=NULL)
    	 printf(" , ");
   }
   printf(" )");
   putchar('\n');

   free(temp);
 }


 /****************************************************************************/
 /*         関数名: freeList	          	                                 */
 /*         動作: リストの中身を開放する		                             */
 /****************************************************************************/
 void freeList(struct Cell *p){
     struct Cell  *temp;

     while( p != NULL ) {
         temp = p->next; //次のデータの参照を取っておく
         free( p );
         p = temp;       //tempを次の処理対象に
     }
 }


 /****************************************************************************/
 /*         関数名: allDeleteList	       	                                 */
 /*         動作: 全リストを削除する			                             */
 /****************************************************************************/
void allDeleteList(struct Cell *p)
{
  struct Cell *tmp;
  while (p->next != NULL)
  {

    tmp = p->next;
    p->next = tmp->next;
    free(tmp);
  }
}

/****************************************************************************/
/*         関数名: deleteList		       	                                */
/*         動作: 削除したいセルを指しているポインタ			                */
/****************************************************************************/
void deleteList(struct Cell* p)
{
  struct Cell *tmp;

  tmp = p->next;
  p->next = tmp->next;
  free(tmp);

}

/* クイックソートを行う
 	 http://www1.cts.ne.jp/~clab/hsample/Sort/Sort9.html
*/
void Qsort(int x[ ], int left, int right)
{
  int i, j;
  int pivot;

  i = left;                      /* ソートする配列の一番小さい要素の添字 */
  j = right;                     /* ソートする配列の一番大きい要素の添字 */

  pivot = x[(left + right) / 2]; /* 基準値を配列の中央付近にとる */

  while (1) {                    /* 無限ループ */

      while (x[i] < pivot)       /* pivot より大きい値が */
          i++;                   /* 出るまで i を増加させる */

      while (pivot < x[j])       /* pivot より小さい値が */
          j--;                   /*  出るまで j を減少させる */
      if (i >= j)                /* i >= j なら */
          break;                 /* 無限ループから抜ける */

      Swap(x, i, j);             /* x[i] と x[j]を交換 */
      i++;                       /* 次のデータ */
      j--;
  }

  if (left < i - 1)              /* 基準値の左に 2 以上要素があれば */
      Qsort(x, left, i - 1);     /* 左の配列を Q ソートする */
  if (j + 1 <  right)            /* 基準値の右に 2 以上要素があれば */
      Qsort(x, j + 1, right);    /* 右の配列を Q ソートする */
}

/* 配列の要素を交換する */
void Swap(int x[ ], int i, int j)
{
  int temp;

  temp = x[i];
  x[i] = x[j];
  x[j] = temp;
}

