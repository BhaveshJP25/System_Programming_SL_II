#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int binarySearch(int arr[], int l, int r, int x){
	if(r>=l){			// While Element Not Found
		int mid=l+(r-l)/2;
		if(arr[mid]==x){	// Element Found
			return mid;
		}
		if(arr[mid]>x){	// Element At Left
			return binarySearch(arr,l,mid-1,x);
		}
		return binarySearch(arr,mid+1,r,x);	//Element At Right
	}
	return -1;		// Element Not Found
}

int main(int argc, char const *argv[]){
	int ele[10], search_ele, res, i=0, n;
	sscanf(argv[1], "%d %d %d %d %d %d %d %d %d %d %d",&search_ele, &ele[0], &ele[1],&ele[2],&ele[3],&ele[4],&ele[5],&ele[6],&ele[7],&ele[8],&ele[9]);
	//printf("\n\nFrom Child Code : %d %d\n",getpid(),getppid());
	//printf("%s",argv[1]);
	n=sizeof(ele)/sizeof(ele[0]);					// Here 10
	res=binarySearch(ele,0,n-1,search_ele);		
	if(res==-1)							// Element Not Found
		printf("Element Not Found.\n");
	else
		printf("Element Is Present At Index : %d \n", res);	// Element Found
	return 0;
}
