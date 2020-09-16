#include<stdio.h>
#include<stdlib.h> 
#include <unistd.h>
#include<pthread.h>
#include<semaphore.h>
pthread_mutex_t m, writer;
int k=0, readcount=0;

void writerfunc(void *ptr){
	int i=(int *)ptr;

	while(1){
		//sleep(rand()%5);
		printf("\nWriter %d Wants To Write", i);
		//sleep(rand()%3);
		sleep(1);
		pthread_mutex_lock(&writer);
		printf("\n\n-------------------------------------------------------");
		printf("\nWriter %d Is Writing: Value Of k Is Now : %d", i, ++k);
		printf("\n-------------------------------------------------------\n");
		sleep(rand()%10);
		pthread_mutex_unlock(&writer);
		printf("\nWriter %d Has Finished Writing", i);
		sleep(1);
		//sleep(rand()%20);
		
	}
}

void readerfunc(void *ptr){
	int i=(int *)ptr;

	while(1){
		//sleep(rand()%5);
		printf("\nReader %d Wants To Read", i);
		//sleep(rand()%3);
		sleep(1);
		pthread_mutex_lock(&m);
		readcount++;
		if(readcount==1)
			pthread_mutex_lock(&writer);
		pthread_mutex_unlock(&m);
		printf("\n\n-------------------------------------------------------");
		printf("\nReader %d Is Reading: Value Of k Is Now : %d", i, k);
		printf("\n-------------------------------------------------------\n");
		sleep(rand()%5);
		pthread_mutex_lock(&m);
		readcount--;
		if(readcount==0)
			pthread_mutex_unlock(&writer);
		pthread_mutex_unlock(&m);
		printf("\nReader %d Has Finished Reading", i);
		sleep(rand()%15);
		
	}
}

int main(){
	int r,w,i;
	pthread_mutex_init(&m, NULL);
	pthread_mutex_init(&writer, NULL);
	pthread_t rea[10], wri[10];
	
	printf("Enter Number Of Readers And Writers : ");
	scanf("%d%d",&r,&w);
	
	for(i=0;i<r;i++){
		pthread_create(&rea[i],NULL,readerfunc,(void *) i);
		sleep(1);
	}
	
	for(i=0;i<w;i++){
		pthread_create(&wri[i],NULL,writerfunc,(void *) i);
		sleep(1);
	}
	
	for(i=0;i<r;i++){
		pthread_join(&rea[i],NULL);
		sleep(1);
	}
	
	for(i=0;i<w;i++){
		pthread_join(&wri[i],NULL);
		sleep(1);
	}
	
	pthread_mutex_destroy(&m);
	pthread_mutex_destroy(&writer);
	return 0;
	
}
