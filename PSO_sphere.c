#include<stdio.h>
#include<stdlib.h>
#include<time.h>

double ran0(){//0~1の実数の乱数を出力するメソッド
    return (double)rand()/((double)RAND_MAX+1);
}

double sphere(int j,double x[100][2]){//sphere関数値の計算をするメソッド
    double f;
    f = x[j][0]*x[j][0]+x[j][1]*x[j][1];
    return f;
}

int main( void ){//メインの操作
    double x[100][2];//個体番号 * ベクトルの次元 の配列でxを表す
    //xjiの配列
    srand(time(NULL));
    for(int j=0;j<100;j++){//探索点10個の初期値をランダムに設定
        for(int i=0;i<2;i++){
            x[j][i]=ran0()*10.0-5.0;
        }
    }
    //自己ベストなxの初期設定
    double p_best_x[100][2];
    double p_best_f[100];
    for(int j=0;j<100;j++){
        for(int i=0;i<2;i++){
            p_best_x[j][i]=x[j][i];
        }
        p_best_f[j]=sphere(j,x);
    }
    //大域的ベストなxの初期設定
    double g_best_f;
    double g_best_x[2];
    for(int i=0;i<2;i++){
        g_best_x[i]=x[0][i];
    }
    g_best_f=sphere(0,x);
    

    //自己ベストなx,大域的ベストなxを更新する
    for(int j=0;j<100;j++){
        if(sphere(j,x)<p_best_f[j]){
            p_best_f[j]=sphere(j,x);
            for(int i=0;i<2;i++){
                p_best_x[j][i]=x[j][i];
            }
        }
        if(sphere(j,x)<g_best_f){
            g_best_f=sphere(j,x);
            for(int i=0;i<2;i++){
                g_best_x[i]=x[j][i];
            }
        }
    }
    
    //vの初期設定
    double v[100][2];
    for(int j=0;j<100;j++){
        for(int i=0;i<2;i++){
            v[j][i]=0.0;
        }
    }
    //vの式の中の係数の設定
    double w=1.0;
    double c1=0.5;
    double c2=0.5;
    
    //反復回数設定
    int num=1000;
    for(int k=0;k<num;k++){
        //vの更新
        for(int j=0;j<100;j++){
            double r1=ran0();
            double r2=ran0();
            for(int i=0;i<2;i++){
                v[j][i]=w*v[j][i]
                +c1*r1*(p_best_x[j][i]-x[j][i])
                +c2*r2*(g_best_x[i]-x[j][i]);
            }
        }
        //xの更新
        for(int j=0;j<100;j++){
            for(int i=0;i<2;i++){
                x[j][i]=x[j][i]+v[j][i];
                //xの範囲条件
                if(x[j][i]<-5.0){
                    x[j][i]=-5.0;
                }
                if(x[j][i]>5.0){
                    x[j][i]=5.0;
                }
            }
        }
        //自己ベストなx,大域的ベストなxを更新する
        for(int j=0;j<100;j++){
            if(sphere(j,x)<p_best_f[j]){
                p_best_f[j]=sphere(j,x);
                for(int i=0;i<2;i++){
                    p_best_x[j][i]=x[j][i];
                }
            }
            if(sphere(j,x)<g_best_f){
                g_best_f=sphere(j,x);
                for(int i=0;i<2;i++){
                    g_best_x[i]=x[j][i];
                }
            }
        }
        if(k%2==0){//2の倍数ごとに結果をプリント
            // printf("%f \n",g_best_f);
            // printf("%f %f %f  \n",g_best_f, p_best_f[0], p_best_f[1]);
        }
    }        
printf("%f \n",g_best_f);
}







///粒子数10次元3

// #include<stdio.h>
// #include<stdlib.h>
// #include<time.h>

// double ran0(){//0~1の実数の乱数を出力するメソッド
//     return (double)rand()/((double)RAND_MAX+1);
// }

// double sphere(int j,double x[10][3]){//sphere関数値の計算をするメソッド
//     double f;
//     f = x[j][0]*x[j][0]+x[j][1]*x[j][1]+x[j][2]*x[j][2];
//     return f;
// }

// int main( void ){//メインの操作
//     double x[10][3];//個体番号 * ベクトルの次元 の配列でxを表す
//     //xjiの配列
//     srand(time(NULL));
//     for(int j=0;j<10;j++){//探索点10個の初期値をランダムに設定
//         for(int i=0;i<3;i++){
//             x[j][i]=ran0()*10.0-5.0;
//         }
//     }
//     //自己ベストなxの初期設定
//     double p_best_x[10][3];
//     double p_best_f[10];
//     for(int j=0;j<10;j++){
//         for(int i=0;i<3;i++){
//             p_best_x[j][i]=x[j][i];
//         }
//         p_best_f[j]=sphere(j,x);
//     }
//     //大域的ベストなxの初期設定
//     double g_best_f;
//     double g_best_x[3];
//     for(int i=0;i<3;i++){
//         g_best_x[i]=x[0][i];
//     }
//     g_best_f=sphere(0,x);
//     // g_best_f = min(p_best_f)

//     //自己ベストなx,大域的ベストなxを更新する
//     for(int j=0;j<10;j++){
//         if(sphere(j,x)<p_best_f[j]){
//             p_best_f[j]=sphere(j,x);
//             for(int i=0;i<3;i++){
//                 p_best_x[j][i]=x[j][i];
//             }
//         }
//     // g_best_f = min(p_best_f)
//     // for(int i=0;i<3;i++){
//     //     g_best_x[i]=x[argmin(p_best_f)][i];
//     // } 
//         if(sphere(j,x)<g_best_f){
//             g_best_f=sphere(j,x);
//             for(int i=0;i<3;i++){
//                 g_best_x[i]=x[j][i];
//             }
//         }
//     }
    
    
//     printf("%f %f %f %f\n",g_best_f,g_best_x[0],g_best_x[1],g_best_x[2]);
    
//     //vの初期設定
//     double v[10][3];
//     for(int j=0;j<10;j++){
//         for(int i=0;i<3;i++){
//             v[j][i]=0.0;
//         }
//     }
//     //vの式の中の係数の設定
//     double w=1.0;
//     double c1=0.1;
//     double c2=0.1;
    
//     //反復回数設定
//     int num=100;
//     for(int k=0;k<num;k++){
//         //vの更新
//         for(int j=0;j<10;j++){
//             double r1=ran0();
//             double r2=ran0();
//             for(int i=0;i<3;i++){
//                 v[j][i]=w*v[j][i]
//                 +c1*r1*(p_best_x[j][i]-x[j][i])
//                 +c2*r2*(g_best_x[i]-x[j][i]);
//             }
//         }
//         //xの更新
//         for(int j=0;j<10;j++){
//             for(int i=0;i<3;i++){
//                 x[j][i]=x[j][i]+v[j][i];
//                 //xの範囲条件
//                 if(x[j][i]<-5.0){
//                     x[j][i]=-5.0;
//                 }
//                 if(x[j][i]>5.0){
//                     x[j][i]=5.0;
//                 }
//             }
//         }
//         //自己ベストなx,大域的ベストなxを更新する
//         for(int j=0;j<10;j++){
//             if(sphere(j,x)<p_best_f[j]){
//                 p_best_f[j]=sphere(j,x);
//                 for(int i=0;i<3;i++){
//                     p_best_x[j][i]=x[j][i];
//                 }
//             }
//             if(sphere(j,x)<g_best_f){
//                 g_best_f=sphere(j,x);
//                 for(int i=0;i<3;i++){
//                     g_best_x[i]=x[j][i];
//                 }
//             }
//         }
//         if(k%2==0){//100の倍数ごとに結果をプリント
//             // printf("%f %f %f %f\n",g_best_f,g_best_x[0],g_best_x[1],g_best_x[2]);
//             printf("%f %f %f %f \n",g_best_f, p_best_f[0], p_best_f[1], p_best_f[2]);
//         }
//     }        
// }
