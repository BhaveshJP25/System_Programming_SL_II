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
			  
// Ascending Selection SOrt
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

// Convert Integer Array To String
void converttostr(int nums[], int tofind, char* buffer){
	sprintf(buffer, "%d %d %d %d %d %d %d %d %d %d %d",tofind, nums[0], nums[1],nums[2],nums[3],nums[4],nums[5],nums[6],nums[7],nums[8],nums[9]);
}

int main(int argc, char *argv[])
{
	
	int ele[10], search_ele, i;
	char char_arr[100];
	
	printf("Enter 10 Elements : \n");	
	// Input 10 Elements
	for (i = 0; i < 10; i++)
        {
        	printf("\nEnter %dth element :",i);
           	scanf("%d",&ele[i]);
    	}
    	// Enter Element To Find
	printf("Enter number to find : \n");
	scanf("%d", &search_ele);
         
        pid_t cpid;
	cpid = fork();
        // Sort Input Array For Binary Search  
        bubbleSort(ele,10);
           
	
           
	if (cpid == -1) {
		perror("FORK FAILURE");
		exit(EXIT_FAILURE);
	}

	if (cpid == 0) {	//Child Process
		printf("\nChild Process . . . .\n");
		//printf("\n\nFrom Parent Code : %d %d\n",getpid(),getppid());
           	sleep(5);
        	//bubbleSort(ele,10);
           	converttostr(ele, search_ele, char_arr);
           	char *const ps_argv[]={"./bs", char_arr, 0};
		execv("/home/bhavesh/OS/Assignment/2b/bs", ps_argv);
	}
	else 			//Parent Process
	{      
		printf("\nParent Process . . . . .\n");
           	printf("Sorting Array Using Bubble Sort..... \nSorted Output : ");
           	//bubbleSort(ele,10);
           	printArray(ele,10);
           	wait(NULL);      	// Wait Till Child Process Ends      
     	}
}
