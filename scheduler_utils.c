#include "types.h"
#include "user.h"

//created here so that lottery_test is not forked and children dont get out of hand
int fork_child(int newPval){
    int pid;
    pid = fork();
    if(pid == 0){
        nice(getpid(), newPval);
        while(1);
    }
    else
        return pid;
}