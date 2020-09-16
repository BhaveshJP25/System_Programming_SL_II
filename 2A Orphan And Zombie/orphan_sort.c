       #include <sys/types.h>
       #include <sys/wait.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <unistd.h>
       #include <string.h>
           void swap(int *xp, int *yp)  
			{  
			    int temp = *xp;  
			    *xp = *yp;  
			    *yp = temp;  
			}  
			  
			// A function to implement bubble sort 
			void bubbleSort(int arr[], int n) 
			{ 
			   int i, j; 
			   for (i = 0; i < n-1; i++)       
			  
			       // Last i elements are already in place    
			       for (j = 0; j < n-i-1; j++)  
			           if (arr[j] > arr[j+1]) 
			              swap(&arr[j], &arr[j+1]); 
			} 
			  
			/* Function to print an array */
			void printArray(int arr[], int size) 
			{ 
			    int i; 
			    for (i=0; i < size; i++) 
			        printf("%d ", arr[i]); 
			    printf("\n"); 
			} 
			  
			void selectionSort(int arr[], int n) 
			{ 
			    int i, j, min_idx; 
			  
			    // One by one move boundary of unsorted subarray 
			    for (i = 0; i < n-1; i++) 
			    { 
			        // Find the minimum element in unsorted array 
			        min_idx = i; 
			        for (j = i+1; j < n; j++) 
			          if (arr[j] < arr[min_idx]) 
			            min_idx = j; 
			  
			        // Swap the found minimum element with the first element 
			        swap(&arr[min_idx], &arr[i]); 
			    } 
			}


       int main(int argc, char *argv[])
       {
         //  int pipefd[2];
           pid_t cpid;
       
           int arr[5];
           for (int i = 0; i < 5; ++i)
           {
           	 printf("\nEnter %dth element :",i);
           	 scanf("%d",&arr[i]);
           }
           cpid = fork();
           /*both if and else will execute as fork returns 2 values*/
           /*One value in if and other in else*/
           if (cpid == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
           }

           if (cpid == 0) {    /* Child reads from pipe */
           printf("\n Child Process . . . . .");
           printf("\n Child Process ID : %d",getpid());
           printf("\n Parent Process ID : %d",getppid());
           sleep(4);    
           printf("\n Child Process ID : %d",getpid());   
           printf("\n New Parent Process ID : %d\n",getppid()); 
           bubbleSort(arr,5);
           printf("\nBubble Sort\n");
           printArray(arr,5);
           }
           else 
           {            /* Parent writes argv[1] to pipe */
		        sleep(1);        
		        selectionSort(arr,5); 
		        printf("\nSelection Sort\n");
		        printArray(arr,5);    
            printf("\n Parent Process . . . . . .I m Exiting\n"); 
           }
 
       }
