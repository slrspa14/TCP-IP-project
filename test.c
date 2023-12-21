#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS 
int main()
{
    char str_tmp[1024];
    FILE *fp=fopen("Test.txt","r");
    // char s1[30]="한글,좆까";
    // char *ptr = strtok(s1,",");
    // while (ptr !=NULL)
    // {
    //     printf("%s \n",ptr);
    //     ptr = strtok(NULL," ");
    // }
    fgets(str_tmp, sizeof(str_tmp), fp);
    printf("%s", fp);
}