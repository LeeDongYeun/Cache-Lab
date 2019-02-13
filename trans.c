/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
 
// student id : 20160444
// name : ÀÌµ¿¿¬ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
	//s=5 E=1 b=5 -> 32 block bytes can store 8 ints. (sizeof(int)=4)
	int i=0, k=0, l=0;
	int a1,a2,a3,a4,a5,a6,a7,a8;
	//case1 32x32
	if(M==32){
		for(k=0; k<N; k+=8){
			for(l=0;l<M; l+=8){
				for(i=0;i<8;i++){
					a1 = A[k+i][l+0];
					a2 = A[k+i][l+1];
					a3 = A[k+i][l+2];
					a4 = A[k+i][l+3];
					a5 = A[k+i][l+4];
					a6 = A[k+i][l+5];
					a7 = A[k+i][l+6];
					a8 = A[k+i][l+7];
					B[l+0][k+i] = a1;
					B[l+1][k+i] = a2;
					B[l+2][k+i] = a3;
					B[l+3][k+i] = a4;
					B[l+4][k+i] = a5;
					B[l+5][k+i] = a6;
					B[l+6][k+i] = a7;
					B[l+7][k+i] = a8;
					
				}
			}
		}
	}
	//case2 64x64
	// cache of b[i][j] and cache of b[i+4][j] is same.
	// so divide case to 1-4, 5-8
	else if(M==64){
		for(k=0; k<N; k+=8){
			for(l=0;l<M; l+=8){
				for(i=0;i<8;i++){
					a1 = A[k+i][l+0];
					a2 = A[k+i][l+1];
					a3 = A[k+i][l+2];
					a4 = A[k+i][l+3];
					B[l+0][k+i] = a1;
					B[l+1][k+i] = a2;
					B[l+2][k+i] = a3;
					B[l+3][k+i] = a4;
	
				}
				for(i=0;i<8;i++){
					a5 = A[k+i][l+4];
					a6 = A[k+i][l+5];
					a7 = A[k+i][l+6];
					a8 = A[k+i][l+7];
					B[l+4][k+i] = a5;
					B[l+5][k+i] = a6;
					B[l+6][k+i] = a7;
					B[l+7][k+i] = a8;
				}
			}
		}
		
	}
	//case 3 61x67
	else{
		//64x56
		for(k=0;k<64;k+=8){
			for(l=0;l<56;l+=8){
				for(i=0;i<8;i++){
					a1 = A[k+i][l+0];
					a2 = A[k+i][l+1];
					a3 = A[k+i][l+2];
					a4 = A[k+i][l+3];
					a5 = A[k+i][l+4];
					a6 = A[k+i][l+5];
					a7 = A[k+i][l+6];
					a8 = A[k+i][l+7];
					B[l+0][k+i] = a1;
					B[l+1][k+i] = a2;
					B[l+2][k+i] = a3;
					B[l+3][k+i] = a4;
					B[l+4][k+i] = a5;
					B[l+5][k+i] = a6;
					B[l+6][k+i] = a7;
					B[l+7][k+i] = a8;
				}
			}
		}
		//67x5
		for(k=0;k<67;k++){
			a1 = A[k][56+0];
			a2 = A[k][56+1];
			a3 = A[k][56+2];
			a4 = A[k][56+3];
			a5 = A[k][56+4];
			B[56][k] = a1;
			B[57][k] = a2;
			B[58][k] = a3;
			B[59][k] = a4;
			B[60][k] = a5;
			
		}
		//3x56
		for(l=0;l<56;l+=8){
			for(i=0;i<3;i++){
				a1 = A[64+i][l+0];
				a2 = A[64+i][l+1];
				a3 = A[64+i][l+2];
				a4 = A[64+i][l+3];
				a5 = A[64+i][l+4];
				a6 = A[64+i][l+5];
				a7 = A[64+i][l+6];
				a8 = A[64+i][l+7];
				B[l+0][64+i] = a1;
				B[l+1][64+i] = a2;
				B[l+2][64+i] = a3;
				B[l+3][64+i] = a4;
				B[l+4][64+i] = a5;
				B[l+5][64+i] = a6;
				B[l+6][64+i] = a7;
				B[l+7][64+i] = a8;
			}
		}
	}
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_simple_desc[]="A simple transpose";
void trans_simple(int M, int N, int A[N][M],int B[M][N])
{
	int t0,t1,tmp;
	int i,j,k,l;
	int a1,a2,a3,a4,a5,a6,a7,a8;
	//case1 32*32
	if((M==32)&&(N==32))
	{
		//block size = 8
		//save 0 through 7 for decreasing miss.
		for(i=0; i<N; i+=16){
			for(j=0; j<M; j+=16){
				for(k=0;k<16;k++){
					for(l=0;l<16;l++){
						B[j+l][i+k]=A[i+k][j+l];
					}
				}
		
			}
		}
	}
	else if(M==64){
		for(k=0; k<N; k+=8){
			for(l=0;l<M; l+=8){
				for(i=0;i<4;i++){
					a1 = A[k+i][l+0];
					a2 = A[k+i][l+1];
					a3 = A[k+i][l+2];
					a4 = A[k+i][l+3];
					a5 = A[k+i][l+4];
					a6 = A[k+i][l+5];
					a7 = A[k+i][l+6];
					a8 = A[k+i][l+7];
					B[l+0][k+i] = a1;
					B[l+1][k+i] = a2;
					B[l+2][k+i] = a3;
					B[l+3][k+i] = a4;
					B[l+0][k+i+4] = a8;
					B[l+1][k+i+4] = a7;
					B[l+2][k+i+4] = a6;
					B[l+3][k+i+4] = a5;
				}
				for(i=0;i<8;i++){
					B[l+4][k+i] = B[l+3][k+i+4];
					B[l+5][k+i] = B[l+2][k+i+4];
					B[l+6][k+i] = B[l+1][k+i+4];
					B[l+7][k+i] = B[l+0][k+i+4];
				}
				
				for(i=4;i<8;i++){
					a1 = A[k+i][l+0];
					a2 = A[k+i][l+1];
					a3 = A[k+i][l+2];
					a4 = A[k+i][l+3];
					B[l+0][k+i] = a1;
					B[l+1][k+i] = a2;
					B[l+2][k+i] = a3;
					B[l+3][k+i] = a4;
	
				}
				for(i=4;i<8;i++){
					a5 = A[k+i][l+4];
					a6 = A[k+i][l+5];
					a7 = A[k+i][l+6];
					a8 = A[k+i][l+7];
					B[l+4][k+i] = a5;
					B[l+5][k+i] = a6;
					B[l+6][k+i] = a7;
					B[l+7][k+i] = a8;
				}
			}
		}
	}
	else if(M==61&&N==67)
	{
		//block size = 16 (because matrix size increase 32 to 61 and 67, we can increase block size to reduce miss.
		//increase block size to 16 can reduce miss.
		for(i=0;i<N;i+=16)
		 for(j=0;j<M;j+=16)
		//if block is in edge, check for out of bounding.
		  for(t0=i;(t0<N&&t0<i+16);t0++)
		  {
		   for(t1=j;(t1<M&&t1<j+16);t1++)
		   {
			//for diagonal, we save separately with tmp,
			//then, it can reduce miss.
			if((t0-i)==(t1-j))
			{
				tmp=A[t0][t1];
			}
			else		
				B[t1][t0]=A[t0][t1];
		   }
		   //transpose for diagonal element.
		   for(t1=j;(t1<M&&t1<j+16);t1++)
			   if((t0-i)==(t1-j))
				 B[t1][t0]=tmp;
		   }
	}
		
	
}
 
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans_simple,trans_simple_desc);
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}
