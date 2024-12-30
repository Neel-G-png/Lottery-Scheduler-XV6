#include "types.h"
#include "stat.h"
#include "user.h"

int getDecimalArg(char* arg){
    int i, pos;
    int n;
    if (arg[0] == '-')
    {
        pos = 0;
    }
    if (pos){
        n = arg[0] - '0';
    }
    else{
        n = 0;
    }
    for (i = 1; i < strlen(arg); i++)
    {
        n *= 10;
        n += (int)(arg[i] - '0');
    }
    if (!pos){
        n = -n;
    }
    return n;
}

int main(int argc, char *argv[]) 
{
    int n=-10;
    int pid = getpid();

    if (argc < 2 || argc>3){
        printf(2, "\nInvalid usage of nice!\n\nCommand takes these arguments\n\tInt PID (Optional) - \t The process ID for which you want to change the nice priority value\n\tInt PVAL - \t\t The new priority value for the process\n\nIf no PID is specified, nice will take the PID of current process\n\n");
        exit();
    }
    if (argc == 2){
        pid = getpid();
        n = getDecimalArg(argv[1]);
    }
    else if (argc == 3){
        pid = atoi(argv[1]);
        n = getDecimalArg(argv[2]);
    }
    nice(pid,n);
    exit();
} 