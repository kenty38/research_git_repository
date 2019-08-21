
#include<stdio.h>
#include<stdlib.h>
#define N 256
#define MAX_LINE 110000

int main(int argc,char *argv[]){
  int current_line=1;               //1~MAX_LINEまでコピーさせるために必要な変数
  int first_share=0;                //ファイル分割のために用いる整数
  char readline[N];                 //コピー元のデータを一行ずつ読み込ませるために使う文字列
  char filename[N];
  
  FILE *ori_fp,*copy_fp;            //コピー元のファイルとコピー先のファイルのポインタ
  
  sprintf(filename,"%s/value_first=0.txt",argv[2]);
  
  //---ファイルの読み込みとエラー検出---
  ori_fp  = fopen(argv[1],"r");
  copy_fp = fopen(filename,"a");
  
  if(ori_fp==NULL){
    puts("コピー元、ファイルオープン失敗");
    return -1;
  }
  else if(copy_fp==NULL){
    puts("コピー先、ファイルオープン失敗");
    return -1;
  }
  
  
  //コピー元のファイルを最終行まで読み込む  
  while(fgets(readline,N,ori_fp)!=NULL){
    //printf("%s",readline);
    fputs(readline,copy_fp);
        
    if(current_line==MAX_LINE){                //最後のファイルの時はfcloseのみにするように手直し
      current_line=1;
      fclose(copy_fp);

      if(first_share==19)
        exit(1);

      first_share++;
      sprintf(filename,"%s/value_first=%d.txt",argv[2],first_share);
      copy_fp=fopen(filename,"a");
      if(copy_fp==NULL){
        puts("コピー先、ファイルオープン失敗");
        return -1;
      }
    }
  else
    current_line++;
  } 
  
  fclose(ori_fp);
  fclose(copy_fp);
}

