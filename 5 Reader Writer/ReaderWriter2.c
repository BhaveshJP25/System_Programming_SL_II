#include<stdio.h>
#include<stdlib.h> 
#include <unistd.h>
#include<pthread.h>
#include<semaphore.h>
sem_t x, y, z, wsem, rsem;
int k=0, readcount=0, writecount=0;

void writerfunc(void *ptr){
	int i=(int *)ptr;

	while(1){
		printf("\nWriter %d Wants To Write", i);
		//sleep(rand()%3);
		sleep(1);
		sem_wait(&y);
			writecount++;
			if(writecount==1)
				sem_wait(&rsem);
		sem_post(&y);
		sem_wait(&wsem);
		printf("\n\n-------------------------------------------------------");
		printf("\nWriter %d Is Writing: Value Of k Is Now : %d", i, ++k);
		printf("\n-------------------------------------------------------\n");
		sleep(rand()%10);
		sem_post(&wsem);
		
		sem_wait(&y);
		writecount--;
		if(writecount==0)
			sem_post(&rsem);
		sem_post(&y);
		printf("\nWriter %d Has Finished Writing", i);
		sleep(1);
	}
}

void readerfunc(void *ptr){
	int i=(int *)ptr;

	while(1){
		sem_wait(&z);
			sem_wait(&rsem);
				printf("\nReader %d Wants To Read", i);
				sem_wait(&x);
				readcount++;
				if(readcount==1)
					sem_wait(&wsem);
				sem_post(&x);
			sem_post(&rsem);
		sem_post(&z);
		
		printf("\n\n-------------------------------------------------------");
		printf("\nReader %d Is Reading: Value Of k Is Now : %d", i, k);
		printf("\n-------------------------------------------------------\n");
		sleep(rand()%5);
		
		sem_wait(&x);
		readcount--;
		if(readcount==0)
			sem_post(&wsem);
		sem_post(&x);
		printf("\nReader %d Has Finished Reading", i);
		sleep(rand()%15);		
	}
}

int main(){
	int r,w,i;
	
	sem_init(&x,0,1);
	sem_init(&y,0,1);
	sem_init(&z,0,1);
	sem_init(&rsem,0,1);
	sem_init(&wsem,0,1);
	
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
	
	sem_destroy(&x);
	sem_destroy(&y);
	sem_destroy(&z);
	sem_destroy(&wsem);
	sem_destroy(&rsem);
	
	return 0;
	
}
