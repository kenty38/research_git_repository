
# ctr+shift+c(一括コメント)

#これにより深さと増加量のグラフをすべて生成

#initialize
total_height<-0
total_increase<-0
ave_height<-0
ave_increase<-0

#filename
before_workspace <- "/home/ax909424/git_laptop/research_git_repository/r_workspace_master"
after_workspace  <- "/simulation_result"
expand           <- c("/reproduction","/homo_path","/bias","/both","/topic")
date             <- c("/20181104","/20181105","/20181104","/20181106","/20190821")

#マクロもどき
FIRST_SHARE      <- 1
TOTAL_SHARE      <- 2
HEIGHT           <- 3
VALUE_THETA      <- 4

AVERAGE_INCREASE <- 1
AVERAGE_HEIGHT   <- 2

MAX_FIRST_SHARE  <- 20
SPLIT            <- 11

X_LABEL          <- 1
Y_LABEL          <- 2


for(kind_of_expand in 1 : 5 ){ 
#------create total data matrix( 10000 colums * 220 rows)-----------------
  for(i in 1 : MAX_FIRST_SHARE){
    #filenameにファイル名を入れて、valueにその値を格納
    filename <- paste(before_workspace , after_workspace , expand[kind_of_expand] , date[kind_of_expand] ,"/value_first=",i,".txt",sep="")
    
    #read_txt_table:初期共有者,情報共有者,深さ,ニュースの値を格納する行列(110000 * 4)
    read_txt_table = read.table(filename,header=FALSE,sep=" ")
    #cat(filename)
    
    for(j in 1 : SPLIT){
      #thetaの値ごとにソート:temp~~ <- read_txt_table[該当行 , 欲しい情報]
      temp_height <- read_txt_table[read_txt_table[ , VALUE_THETA] == (j-1) / 10.0 , HEIGHT]
      temp_increase <- read_txt_table[
        read_txt_table[ , VALUE_THETA] == (j-1) / 10.0 , TOTAL_SHARE] - read_txt_table[read_txt_table[ , VALUE_THETA] == (j-1) / 10.0
                      , FIRST_SHARE
                      ]
      
      #一番最初だけtotalに代入し、それ以外は結合
      if(i == 1 && j==1 && (j-1) / 10 == 0){
        total_height <- temp_height
        total_increase <- temp_increase
      }
      else{
        total_height <- cbind(total_height , temp_height)
        total_increase <- cbind(total_increase , temp_increase)
      }
      
    }
  }
  
  
  #-------calculate 1*220 average matrix , increase and height---------
  for(i in 1:220){
    ave_height[i] <- mean(total_height[,i])  
    ave_increase[i] <- mean(total_increase[,i])
  }
  #--------------------------------------------------------------------
  
  #Average[,1]:increase , Average[,2]:height
  Average<-cbind(ave_increase,ave_height)
  
  k_first<-c(1,11)
  k_end<-c(10,20)
  inc_hei<-c("increase","height")
  main_thema<-c("increase and news content","height and news content")
  cols<-c("purple","green","blue","red","black")
  
  lty_status <- c("longdash" , "dotdash" , "dotted" , "dashed" , "solid")
  #legend_range <- c(20,15,10,5,1)
  
  pch_style <- c(0,15,16,17,18)
  
  #create 4 images
  #i:information's kind , j:launch 1 or 11 , k:draw line
  
  
  for(i in 1:2){
      lty_count <- 5
      bmp(paste("/home/ax909424/r/image",expand[kind_of_expand],"/",inc_hei[i],".bmp",sep=""),width=800,height=600)
      par(mar=c(5.5,6.0,4.1,2))
      par(mgp=c(4,1.2,0))
      plot(0,0,type="n",xlim=range(0,10),ylim=range(0,20),xlab="news content",ylab=inc_hei[i],main=main_thema[i] , xaxt = "n" , yaxt = "n" ,cex.lab = 2.5 , cex.main = 2.5)
      
      #mar=c(5,0,4,2)+0.1
      #par(mgp=c(10,1,0))
      
      #par(oma = c(3,4,3,2))
      
      #横軸の目盛の値を変更
      axis(X_LABEL,0:10, seq(0, 1,by = 0.1))
      axis(Y_LABEL,0:20, seq(0,20,by = 1) , las = 1 , tck=1.0 ,lty = "dotted")
      
      k_range<-k_first[1]:k_end[2]
      
      for(k in k_range){
        head=11*(k-1)+1
        tail=11*k
        par(pch = "+")
       
        if((k%%5 ==0) || k==1 ){
          lines(0:10,Average[head:tail,i],col=cols[lty_count],lty=lty_status[lty_count] , lwd = 2 )
          lty_count <- lty_count - 1
          #print(k)
        }
      }
      #legend("topright",legend=legend_range,col=cols,lty=lty_status, cex = 2)
      dev.off()
    
  }
}
