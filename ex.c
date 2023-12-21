#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF_SIZE 1024

int main(void)
{
    char *str_tmp[100000];
    char *strr[1000];
    FILE *fp = fopen("Test.csv","r");

    if(fp == NULL)
    {
        printf("안열림");
        return -1;
    }

    while(!feof(fp))
    {
        fgets(str_tmp, sizeof(str_tmp), fp);
        char *ptr = strtok(str_tmp,",");
        for (int i = 0; i < 4; i++)
        {
            strr[i] = ptr;
            ptr = strtok(NULL,",");
            printf("%s \n",strr[i]);
        }
    }
    fclose(fp);
    return 0;
}
