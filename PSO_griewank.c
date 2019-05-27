#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
double ran0(){//0~1の実数の乱数を出力するメソッド
    return (double)rand()/((double)RAND_MAX+1);
}

double griewank(int j,double x[10][2]){//griewank関数値の計算をするメソッド
    double f;
    f = 1.0;
    for(int i=0;i<2;i++){
        f = f+(x[j][i]*x[j][i])/4000.0;
    }
    f = f-(
        cos(x[j][0] / 1.0)
        *cos(x[j][1] / sqrt(2.0))
        // *cos(x[j][2] / sqrt(3.0))
        // *cos(x[j][3] / sqrt(4.0))
        // *cos(x[j][4] / sqrt(5.0))
        // *cos(x[j][5] / sqrt(6.0))
        // *cos(x[j][6] / sqrt(7.0))
        // *cos(x[j][7] / sqrt(8.0))
        // *cos(x[j][8] / sqrt(9.0))
        // *cos(x[j][9] / sqrt(10.0))
        );
    return f;
}

 

int main( void ){//メインの操作
    double x[10][2];//個体番号 * ベクトルの次元 の配列でxを表す
    srand(time(NULL));
    for(int j=0;j<10;j++){//探索点100個の初期値をランダムに設定
        for(int i=0;i<2;i++){
            x[j][i]=ran0()*1200.0-600.0;
        }
    }
    //自己ベストなxの初期設定
    double p_best_x[10][2];
    double p_best_f[10];
    for(int j=0;j<10;j++){
        for(int i=0;i<2;i++){
            p_best_x[j][i]=x[j][i];
        }
        p_best_f[j]=griewank(j,x);
    }
    //大域的ベストなxの初期設定
    double g_best_f;
    double g_best_x[2];
    for(int i=0;i<2;i++){
        g_best_x[i]=x[0][i];//粒子番号0のx値(10次元)をg_bestの初期値に
    }
    g_best_f=griewank(0,x);//粒子番号0の関数値

    // //l_bestの設定
    // double l_best_f;
    // double l_best_x[5][10];
    // for(int i=0;i<10;i++){
    //     l_best_x[i]=x[0][i];
    // }
    // l_best_f[]=griewank(0,x);


    //自己ベストなx,大域的ベストなxを更新する
    for(int j=0;j<10;j++){//各粒子について
        if(griewank(j,x)<p_best_f[j]){
            p_best_f[j]=griewank(j,x);
            for(int i=0;i<2;i++){
                p_best_x[j][i]=x[j][i];
            }
        }
        if(griewank(j,x)<g_best_f){
            g_best_f=griewank(j,x);
            for(int i=0;i<2;i++){
                g_best_x[i]=x[j][i];
            }
        }   
    }
    
    // printf("%f %f %f %f\n",g_best_f,g_best_x[0],g_best_x[1],g_best_x[2]);
    
    //vの初期設定
    double v[10][2];
    for(int j=0;j<10;j++){
        for(int i=0;i<2;i++){
            v[j][i]=0.0;
        }
    }
    //vの式の中の係数の設定
    // double w=1.0;
    // double c1=0.5;
    // double c2=0.5;
    //①CM
    double w=0.729;
    double c1=1.4955;
    double c2=1.4955;

    // //②RIWM
    // double c1=1.4955;
    // double c2=1.4955;

    // //③LDIVM
    // double w=0.9;
    // double c1=2.0;
    // double c2=2.0;

    //試行回数
    // for(int epoch=0;epoch<100;epoch++){ 

        //反復回数設定
        int num=100;
        for(int k=0;k<num;k++){
        //wの更新式(モデル毎に変える)
        //②RIWM
        //wをイテレーションごとにランダムに設定
        // 最小値 + (int)( rand() * (最大値 - 最小値 + 1.0) / (1.0 + RAND_MAX) )
        // double w= 0.5 + (int)(rand()*(1.0 - 0.5 + 1.0) / (1.0 + RAND_MAX));
        // //③LDIVM
        // double w= w-0.005;//100回のイテレーションで0.4の安定領域まで減らす
            //vの更新
            for(int j=0;j<10;j++){
                double r1=ran0();
                double r2=ran0();
                for(int i=0;i<2;i++){
                    v[j][i]=w*v[j][i]+c1*r1*(p_best_x[j][i]-x[j][i])+c2*r2*(g_best_x[i]-x[j][i]);
                }
            }
            //xの更新
            for(int j=0;j<10;j++){
                for(int i=0;i<2;i++){
                    x[j][i]=x[j][i]+v[j][i];
                    //xの範囲条件
                    if(x[j][i]<-600.0){
                        x[j][i]=-600.0;
                    }
                    if(x[j][i]>600.0){
                        x[j][i]=600.0;
                    }
                }
            }
            //自己ベストなx,大域的ベストなxを更新する
            for(int j=0;j<10;j++){
                if(griewank(j,x)<p_best_f[j]){
                    p_best_f[j]=griewank(j,x);
                    for(int i=0;i<2;i++){
                        p_best_x[j][i]=x[j][i];
                    }
                }
                if(griewank(j,x)<g_best_f){
                    g_best_f=griewank(j,x);
                    for(int i=0;i<2;i++){
                        g_best_x[i]=x[j][i];
                    }
                }
            }
            // if(k%2==0){
            //     printf("%f %f %f \n",g_best_f,g_best_x[0],g_best_x[1]);
            // }
            if(k%2==0){
                printf("%f \n",g_best_f);
            }
        }    
    // printf("%f \n",g_best_f);

}


