#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    printf(1, "\nTesting Nice\n");
    int pid = getpid();
    printf(1, "Process ID: %d\n", pid);
    printf(1, "\n=========== All Processes ===========\n");
    ps();

    printf(1, "\n\nSetting a lower priority for this process - 17\n");
    printf(1, "\n=========== All Processes ===========\n");
    nice(pid, 17);
    ps();

    printf(1, "\n\nSetting a higher priority for this process - -5\n");
    printf(1, "\n=========== All Processes ===========\n");
    nice(pid, -5);
    ps();

    printf(1, "\n\nSetting a invalid priority for this process - 21\n");
    printf(1, "\n=========== All Processes ===========\n");
    nice(pid, 21);
    ps();
    exit();
}