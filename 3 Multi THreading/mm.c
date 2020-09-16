#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <time.h>
struct threadArg 			// Passing Arguments To Thread
{
	int **m1, **m2;
	int row, col, k;
};
void *thread_function(void *arg);

void Matinit(int ***arr, int n, int m) 	// Pointer To Matrix Double Pointer
{
	*arr = (int **)malloc(n * sizeof(int *));
	for(int i = 0; i < n; i++)
	{
		(*arr)[i] = (int *)malloc(m * sizeof(int));
	}
	printf("Enter Matrix Values for %d * %d\n", n, m);
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			printf("Element [%d] [%d] : ", i, j);
			scanf("%d", &((*arr)[i][j]));
		}
	}
}

int main()
{
	int m, k1, k2, n, res;
	printf("Enter Dimension of Matrix 1 (m x n) : ");
	scanf("%d %d", &m, &k1);
	printf("Enter Dimension of Matrix 2 (m x n) : ");
	scanf("%d %d", &k2, &n);
	
	if(k1 == k2) {
		int **m1;
		int **m2;
		int **ans;
		int ch;
		Matinit(&m1, m, k1);
		Matinit(&m2, k2, n);
		ans = (int **)malloc(m * sizeof(int *));
		for(int i = 0; i < m; i++)
			ans[i] = (int *)malloc(n * sizeof(int));
		clock_t b;
		while(1) {
			printf("Enter Choice : \n1. Parallel Threads\n2. Single Thread\n");
			scanf("%d", &ch);
			b = clock();
			if(ch==1)
			{
				pthread_t test, thread[m][n];
				void *thread_result;
				struct threadArg P[m][n];
				for(int i = 0; i < m; i++)
				{
					for(int j = 0; j < n; j++)
					{
						P[i][j].m1 = m1;
						P[i][j].m2 = m2;
						P[i][j].k  = k1;
						P[i][j].row = i;
						P[i][j].col = j;
					}
				}
				for(int i = 0; i < m; i++)
				{
					for(int j = 0; j < n; j++)
					{
						int res = pthread_create(&thread[i][j], NULL, thread_function, (void *)(&P[i][j]));
					}
				}
				for(int i = 0; i < m; i++)
				{
					for(int j = 0; j < n; j++)
					{
						res = pthread_join(thread[i][j], &thread_result);
						ans[i][j] = *(int *)(thread_result);
					}
				}
			}
			else if(ch == 2)
			{
				for(int i = 0; i < m; i++)
				{
					for(int j = 0; j < n; j++)
					{
						int sum = 0;
						for(int w = 0; w < k1; w++)
						{
							sum += m1[i][w]*m2[w][j];
						}
						ans[i][j] = sum;
					}
				}	
			}
			else{
				printf("\nInvalid Choice\n");
				return 1;
			}
			clock_t en = clock();
			float time = ((double)(en - b))/CLOCKS_PER_SEC;
			printf("Matric Multiplication : \n");
			for(int i = 0; i < m; i++)
			{
				for(int j = 0; j < n; j++)
				{
					printf("%d ", ans[i][j]);
				}
				printf("\n");
			}
			printf("Time taken : %f\n", time);
		}
	}
	else{
		printf("\nMatrix Dimesnions Are Inappropriate\n");
	}
	exit(EXIT_SUCCESS);
}
void *thread_function(void *arg)
{
	// sleep(1); // Uncomment in case of buggy output
	int ret = 0;
	struct threadArg temp = *((struct threadArg *)arg);
	for(int i = 0; i < (temp).k; i++)
	{
		int val1 = temp.m1[temp.row][i];
		int val2 = temp.m2[i][temp.col];
		ret += val1*val2;
	}
	(*(struct threadArg *)(arg)).k = ret; // Storing result in k of *arg from main // Do not return pointer to object created in thread, as it shall cease to exist after thread terminates. 
	void *u = &((*(struct threadArg *)arg).k);
	pthread_exit(u);
	// pthread_exit(NULL); // to-do
}
