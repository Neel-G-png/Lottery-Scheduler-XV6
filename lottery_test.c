#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "scheduler_utils.c"

#define max_children 5

int proc_count = 0;
int procs[30];

void test12(int chpr[max_children], int pvals[max_children]){
	int i;
	for(i=0;i<max_children;i++){
		//reset amount of ticks for each process back to zero
		resetticks(chpr[i]);
	}
	//changing the pvals of all the child processes
	for(i=0;i<max_children;i++){
		nice(chpr[i],pvals[i]);
	}
	sleep(1000);
	ps();
}

void test3(){
	int i;
	int chpr[max_children];
	int killcount = 0;
	int Test1Vals[max_children] = {15,10,-10,-15,-19};
	for(i=0;i<max_children;i++){
		chpr[i] = fork_child(Test1Vals[i]);
	}
	sleep(10);
	printf(1,"\nEvery Process Starts at ticks = 0");
	for(i=0;i<max_children;i++){
		resetticks(chpr[i]);
	}
	ps();
	while (killcount!=max_children){
		for(i=0;i<max_children;i++){
			//killifticks - Will only kill the process if it reaches 200 ticks of run time. Imagine 200 as the finish line, its a race between all the child processes.
			if(killifticks(chpr[i]) >= 0){
				printf(1,"Process %d finished the race\n",chpr[i]);
				killcount++;
			}
		}
		sleep(10);
	}
	for(i=0;i<max_children;i++){
		wait();
	}
}

int
main(int argc, char* argv[])
{
	int i;
	int chpr[max_children];
	//first test - one child higher than all other, second test - one child lower than all other children, third test - all child equal 
	
	int Test1Vals[max_children] = {-15,5,5,5,5};
	for(i=0;i<max_children;i++){
		chpr[i] = fork_child(Test1Vals[i]);
	}

	//TEST 1
	printf(1,"\n\n\t\t ################# TEST 1 #################\nOne Child has a higher priority than all other children and it gets to run more often\n(Please Wait)\n");
	test12(chpr,Test1Vals);

	//TEST 2
	printf(1,"\n\n\t\t ################# TEST 2 #################\nOne Child has a lower priority than all other children and it gets to run less often\n(Please Wait)\n");
	int Test2Vals[max_children] = {20,-5,-5,-5,-5};
	test12(chpr,Test2Vals);

	for(i=0;i<max_children;i++){
		kill(chpr[i]);
		// printf(1,"\nReturned - %d\n",val);
	}
	for(i=0;i<max_children;i++){
		wait();
	}

	//TEST 3
	printf(1,"\n\n\t\t ################# TEST 3 #################\nAll children have different priorities\nIt is a race between them to reach 200 ticks\nWhoever reaches there first, gets killed and wins the race\nWe will soon see the results of the race\n(Please Wait)\n");
	test3();
	exit();
}