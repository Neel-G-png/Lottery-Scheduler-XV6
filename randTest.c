#include "types.h"
#include "stat.h"
#include "user.h"

#define max 10

void disHist(int histogram[max]){
    int i,j;

    for (i = 0; i < max; ++i)
    {
        printf(1, "%d: ", i);
        for (j = 0; j < histogram[i]/2; j++)
        {
            printf(1, "*");
        }
        printf(1, "\n");
    }
    printf(1, "\n---------- Rough Probability of each number ----------\n");
    for (i = 0; i < max; i++)
    {
        int pb = histogram[i] / 10;
        printf(1, "%d: %d%\n", i, pb);
    }
}

int main(int argc, char *argv[])
{
    // uint seed = 12345;
    int i;
    int bin;
    int histogram[max] = {0};

    for (i = 0; i < 1000; i++) //generate PRN from 0 to 10
    {
        bin = random(0,9); 
        // int bin = seed % max; // bring the value between 0 and 10
        histogram[bin]++;
    }
    disHist(histogram);
    exit();
}