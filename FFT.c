#include<stdio.h>
#include<stdlib.h>
#include<complex.h>
#include<math.h>

#define PI 3.14159

//Function to perform Bit-reversal
int bit_reverse(int num,int N)
{
   int bits = 3; 
   int reverse_num = 0, i, temp;

    for (i = 0; i < bits; i++)
    {
        temp = (num & (1 << i));
        if(temp)
            reverse_num |= (1 << ((bits - 1) - i));
    }

    return reverse_num;
}

//Implementation of butterfly technique is done here
int main() {
    int i , N = 8;
    float complex stage_One[8];
    float complex stage_Two[8];
    float complex stage_Three[8];
    float complex temp= 0 + 0*I;
    float inputs[8] ;
    for (i = 0 ; i < 8 ; i++) {
        scanf("%f", &inputs[i]);
    }
    int k;
    for(k=0;k<4;k++) {
        stage_One[k] = inputs[k] + inputs[k+4];
        stage_One[k+4] = (inputs[k]-inputs[k+4])*cexp(-2*PI*k*I/8);
    }
    int l,r;
    for(l=0;l<2;l++) {
        stage_Two[l] = stage_One[l]+stage_One[l+2] ;
        stage_Two[l+2] = (stage_One[l]-stage_One[l+2])*cexp(-2*PI*l*I/4);
        stage_Two[l+4] = stage_One[l+4]+stage_One[l+6] ;
        stage_Two[l+6] = (stage_One[l+4]-stage_One[l+6])*cexp(-2*PI*l*I/4);
    }
    int h;
    for (h=0;h<8;h+=2) {
        stage_Three[h]=stage_Two[h]+stage_Two[h+1];
        stage_Three[h+1]=stage_Two[h]-stage_Two[h+1];
    }
    int p,q;

    //Now performing bit-reversal and storing the elements in bit reversed order
    for (p=0; p<N/2; p++){
        q = bit_reverse(p,N);
            temp=0+0*I;
            temp=stage_Three[p];
            stage_Three[p]=stage_Three[q];
            stage_Three[q]=temp;
    }
    int m;
    for (m=0;m<8;m++){
        printf("X(%d) : ", (m));
        printf("%.3f + %.3fj \n",creal(stage_Three[m]),cimag(stage_Three[m]));
    }
    return 0;
}