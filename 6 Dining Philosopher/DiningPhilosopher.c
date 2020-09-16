#include<stdio.h>
#include<stdlib.h> 
#include <unistd.h>
#include<pthread.h>
#include<semaphore.h>
#define no_dp 5

monitor DP{
	enum {THINKING; HUNGRY; EATING} state[no_dp];
	condition self[no_dp];
	
	void pickup(int i) {
		state[i] = HUNGRY;
		test(i);
		if(state[i] != EATING) self[i].wait();
	}
	
	void putdown(int i) {
		state[i]=THINKING;
		test(LEFT);
		test(RIGHT);
	}
	
	void test(int i) {
		if(state[(i+4)%no_dp] != EATING && state[i] == HUNGRY && state[(i+1)%no_dp] != EATING){
			state[i] = EATING;
			self[i].signal();
		}
	}
	
	init_code() {
		for(int i=0; i<no_dp; i++){
			state[i]=THINKING;
		}
	}
};

int main(){
	
}
