/*
Neel Gandhi OS-A1
*/
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define MAX_LINE_LENGTH 1024

char* lowercase(char *s1){
    int length = strlen(s1);
    char* modifiedString = (char*)malloc(length + 1);

    int n = 0;
    for (n = 0; n<length; n++){
        modifiedString[n] = (s1[n] >= 'A' && s1[n] <= 'Z') ? (s1[n] + 32) : s1[n];
    }
    modifiedString[length] = '\0';
    // printf(1, "Modified - %s\noriginal - %s\n",modifiedString,s1);
    return modifiedString;
}

void uniq(int fd, int do_i, int do_c, int do_d, char* fullFile){
    char prev_line[MAX_LINE_LENGTH] = "";
    int group_count = 1;
    char *modified_prev = 0;
    char *modified_curr = 0;
    char *p = 0;
    char *q;
    
    p = fullFile;
    while ((q = strchr(p, '\n')) != 0 || (q = strchr(p, '\0'))){
        *q = 0;

        /*
            initializing modified_prev and curr so that later we can call
            lowercase function to change the value of these pointers and 
            keep the prev_line and p intact for printing later.
        */
        modified_prev = prev_line;
        modified_curr = p;

        /* 
            if -i is set, covert both the lines to lower case and compare 
            these new strings
        */ 
        if(do_i){
            char *s1 = prev_line;
            char *s2 = p;
            modified_prev = lowercase(s1);
            modified_curr = lowercase(s2);
        }

        /*
            Compare prev and curr, if they are not equal print the prev after
            checking -c and -d conditions 
        */
        if (strcmp(modified_prev, modified_curr) != 0){
            if (strcmp(modified_prev, "") != 0){
                /* 
                    if -c and -d then only print if group count is greater
                    than 1. if -d and not -c then only print line if group 
                    count is greater than 1. and if not -d just print the
                    line.
                */ 
                if (do_c && !do_d){
                    printf(1,"%d ",group_count);
                }
                if (do_d && group_count>1){
                    if (do_c){
                        printf(1,"%d ",group_count);
                    }
                    printf(1,"%s\n",prev_line);
                }
                else if (do_d == 0){
                    printf(1,"%s\n",prev_line);
                }
            }
            strcpy(prev_line,p);

            /*
                reset group count back to 1 so that next line start
            */
            group_count = 1;
        }
        else{
            /*
                incrementing group_count if line is same as prev
            */
            group_count += 1;
        }
        p = q+1;
    }
    /*
        since im printing the prev line always, the current line at the
        end is the last unique line that never gets printed. Im doing the same
        operations as the inner while loop for the last two lines and print
        the last line if its not same as the prev or not print and just increase
        the count if its the same.
    */
    modified_curr = prev_line;
    modified_prev = p;
    if(do_i){
        char *s1 = prev_line;
        char *s2 = p;
        modified_prev = lowercase(s1);
        modified_curr = lowercase(s2);
    }
    // printf(1,"prev line - %s\nline - %s\ngc - %d\n",modified_prev,modified_curr,group_count);
    if (strcmp(modified_prev, modified_curr) == 0){
        group_count+=1;
        if (do_c && ((do_d && group_count>1) || !do_d)){
            printf(1,"%d ",group_count);
            // group_count = 1;
        }
        if (!do_d || (do_d && group_count>1)){
            printf(1,"%s\n",prev_line);
        }
        group_count = 1;
    }
    else{
        if (do_c && ((do_d && group_count>1) || !do_d)){
            printf(1,"%d ",group_count);
        }
        if (!do_d || (do_d && group_count>1)){
            printf(1,"%s\n",prev_line);
        }
        //printing the last line 
        group_count = 1;
        if (do_c && ((do_d && group_count>1) || !do_d)){
            printf(1,"%d ",group_count);
        }
        if (!do_d || (do_d && group_count>1)){
            printf(1,"%s\n",p);
        }
    }
}

void strcat(char* s1, char* s2,int bytesRead){
    /*
        function to concatinate two string only taking the first "bytesRead" 
        bytes of the source to the destination
    */
    while (*s1 != '\0') {
        s1++;
        // i++;
    }
    int i=0;
    while (*s2 != '\0' && i<bytesRead) {
        *s1 = *s2;
        s1++;
        s2++;
        i++;
    }
    *s1 = '\0';
}

int main(int argc, char *argv[]) {
    int fd = 0;
    char buf[MAX_LINE_LENGTH];
    int n;
    int i;
    int case_insensitive, count_occur, only_dups;
    case_insensitive = count_occur = only_dups = 0;

    if(argc <= 1){
        fd = 0;
        char* fullFile = (char*)malloc(5000);
        while ((n = read(fd, buf, sizeof(buf)))>0) {
            /*
                strcat takes the exact number of bytes read as a parameter because buf
                contains previously read values as well until they arent overwritten.
                so i only concate the characters that are read in this iteration of
                the while loop. 
            */
            strcat(fullFile,buf,n);
        }
        uniq(fd,0,0,0,fullFile);
        exit();
    }
    
    i = 1;

    /*
        was running loop from 1 to argc-1 but that wont let me take arguments 
        like -c and -d if uniq was used with pipe. so now, only checking if
        file name passed. if not, ill take all the other arguments and set fd=0
    */

    /*
        Now it should also work for cat README | uniq -c -i -d
    */
    while(i<argc){
        char* argument = argv[i];
        if (argument[0]=='-'){
            char option;
            option = argv[i][1];
            switch(option){
                case 'c':
                count_occur = 1;
                break;
                case 'd':
                only_dups = 1;
                break;
                case 'i':
                case_insensitive = 1;
                break;
                default:
                printf(1, "\n-%s is not a recognised command\n",option);
                break;
            }
        }
        else{
            fd = open(argv[i], O_RDONLY);
        }
        i+=1;
    }
    if (fd < 0){
        printf(1, "uniq: cannot open %s\n", argv[0]);
        exit();
    }

    /*
        instead of passing fd to the function and reading the file there.
        i am now reading the entire file first, storing it into a long string that
        can accomodate entire file and passing a pointer to that string to my function.
        this will ensure that all the bytes are properly read before being operated
        on
    */
    char* fullFile = (char*)malloc(5000);
    while ((n = read(fd, buf, sizeof(buf)))>0) {
        /*
            Same as the if argc<=1
        */
        strcat(fullFile,buf,n);
    }

    uniq(fd,case_insensitive,count_occur,only_dups,fullFile);
    close(fd);
    exit();
}