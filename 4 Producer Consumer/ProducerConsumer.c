#include<stdio.h>
#include<stdlib.h> 
#include <unistd.h>
#include<pthread.h>
#include<semaphore.h>
#define no_ele 8
sem_t full, empty;
pthread_mutex_t m;
int count=0, in=0, out=0, a[no_ele];

void producerfunc(void *ptr){
	int k=(int *)ptr;

	while(1){

		sem_wait(&empty);
		pthread_mutex_lock(&m);
		
		a[in]=rand()%100;
		printf("\nProducer %d Produced Item : %d\n",k,a[in]);
		printf("\n----------------------------\n");
		printf("Queue : ");
		//for(int i=count;i!=-1;i--){
		//	printf("%d  ", a[in-i]);
		//}
		for(int i=0;i<=count;i++){
			printf("%d  ", a[(out+i)%no_ele]);
			
		}
		printf("\n----------------------------\n");
		in=(in+1)%no_ele;
		count++;
		
		sleep(rand()%10);
		pthread_mutex_unlock(&m);
		sleep(1);
		sem_post(&full);
		
	}
}

void consumerfunc(void *ptr){
	int k=(int *)ptr;
	while(1){
		sem_wait(&full);
		pthread_mutex_lock(&m);
		
		printf("\nConsumer %d consumed item : %d\n",k,a[out]);
		out=(out+1)%no_ele;
		count--;
		printf("\n----------------------------\n");
		printf("Queue : ");
		for(int i=0;i<=count-1;i++){
			printf("%d  ", a[(out+i)%no_ele]);
			
		}
		printf("\n----------------------------\n");
		
		sleep(rand()%7);
		pthread_mutex_unlock(&m);
		sem_post(&empty);
		
	}
}

int main(){
	int i,p,c;
	pthread_t pth[10], cth[10];
	
	pthread_mutex_init(&m, NULL);
	sem_init(&full,0,0);
	sem_init(&empty,0,no_ele);
	
	printf("Enter Number OF Producers And Consumers : ");
	scanf("%d%d",&p,&c);
	
	for(i=0;i<p;i++){
		pthread_create(&pth[i],NULL,producerfunc,(void *) i);
		
		sleep(1);
	}
	
	for(i=0;i<c;i++){
		pthread_create(&cth[i],NULL,consumerfunc,(void *) i);
		
		sleep(1);
	}
	
	for(i=0;i<p;i++){
		pthread_join(&pth[i],NULL);
		
		sleep(1);
	}
	
	for(i=0;i<c;i++){
		pthread_join(&cth[i],NULL);
		
		sleep(1);
	}
	
	pthread_mutex_destroy(&m);
	sem_destroy(&full);
	sem_destroy(&empty);
	
	return 0;
	
}
