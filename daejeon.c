#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <locale.h>
#define BUF_SIZE 10240
void error_handling(char *message); // 에러 메시지
void send_13data(int sd, FILE *fp,char str_tmp[BUF_SIZE],char str[BUF_SIZE]); //13년 데이터 전송 함수 전방선언
void send_14data(int sd, FILE *fp1, char str_tmp1[BUF_SIZE], char str[BUF_SIZE]); // 14년 데이터 전송 함수 전방선언
int main(int argc, char *argv[])
{
    int sd;
    FILE *fp,*fp1, *fp2; //파일 변수
    char str_tmp[BUF_SIZE]; // 13년 파일 열고 넣을 배열
    char str_tmp1[BUF_SIZE];//14년 데이터 파일 오픈 후 문자열 저장할 배열
    char str_tmp2[BUF_SIZE]; // 22년 데이터 파일 오픈 후 문자열 저장할 배열
    char *str[BUF_SIZE]; // 13년 파일 오픈 후 문자열 저장할 배열
    char *str1[BUF_SIZE]; // 14년 파일 오픈 후 문자열 저장할 배열
    char *str2[BUF_SIZE]; // 22년 파일 오픈 후 문자열 저장할 배열
    // char Max,Min,Average,Price; // 최소 최대 평균 예상가격
    char buf[BUF_SIZE]; // read용
    int read_cnt;// read용

    struct sockaddr_in serv_adr;

    if(argc !=3)
    {
        printf("Usage : %s <IP> <port> \n", argv[0]);
        exit(1);
    }
    fp = fopen("13daejeon.csv", "rt");//13파일 열기
    fp1 = fopen("14daejeon.csv","rt");//14파일 열기
    fp2 = fopen("22daejeon.csv","rt");//22파일 열기
    sd = socket(PF_INET,SOCK_STREAM,0); //소켓생성
    setlocale(LC_ALL, "en_US.UTF-8"); // 유니코드 변환

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    connect(sd,(struct sockaddr*)&serv_adr,sizeof(serv_adr)); // 연결

    send_13data(sd,fp,str_tmp[BUF_SIZE],*str[BUF_SIZE]); //13년 데이터 전송
    fclose(fp); // 닫고 14 보내면 따로 가려나

    send_14data(sd,fp1,str_tmp1[BUF_SIZE],*str1[BUF_SIZE]);// 14년 데이터 전송
    fclose(fp1);

    puts("13,14 daejeon data send finish"); // 확인용

    while (read_cnt = read(sd,buf,sizeof(buf)) !=0) // fp2 끝 아니라면 반복
    {   
        while (!feof(fp2)) // fp2 파일의 끝이 아니라면 반복
        {
            fgets(str_tmp2, sizeof(str_tmp2), fp2);//받는다
            char *ptr2 = strtok(str_tmp2,",");//자른다 쉼표기준으로
            for (int i = 0; i < 17; i++) // 문자열 15번 반복
            {
                str2[i] = ptr2;
                if (i==0 ||  i==5 || i==16) // 문자열내의 0,1,5,14 번 뽑는다
                {
                    printf("%s,",str2[i]); 
                    send(sd, str2[i], strlen(str2[i]), 0); // 출력한것들 보낸다 한 줄씩
                    send(sd,",",1,0);
                }
                ptr2 = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
            send(sd,"\n",1,0);
            printf("\n");
            break;
        }
    }
    // fclose(fp);
    // fclose(fp1);
    close(sd);
    return 0;
}
void error_handling(char *message)
{
    fputs(message,stderr);
    fputc('\n', stderr);
    exit(1);
}
void send_13data(int sd,FILE *fp,char str_tmp[BUF_SIZE],char str[BUF_SIZE])
{
     while (!feof(fp)) // fp1 끝 아니라면 반복
    {   
        while (!feof(fp)) // fp1 파일의 끝이 아니라면 반복
        {
            fgets(str_tmp, sizeof(str_tmp), fp);//받는다
            char *ptr = strtok(str_tmp,",");//자른다 쉼표기준으로
            for (int i = 0; i < 15; i++) // 문자열 15번 반복
            {
                str[i] = ptr;
                if (i==0 || i==1 || i==5 || i==14) // 문자열내의 0,1,5,14 번 뽑는다
                {
                    printf("%s,",str[i]); 
                    send(sd, str[i], strlen(str[i]), 0); // 출력한것들 보낸다 한 줄씩
                    send(sd,",",1,0);
                }
                ptr = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
            send(sd,"\n",1,0);
            printf("\n");
            break;
        }
    }
}

void send_14data(int sd, FILE *fp1, char str_tmp1[BUF_SIZE], char str1[BUF_SIZE])
{
     while (!feof(fp1)) // fp1 끝 아니라면 반복
    {   
        while (!feof(fp1)) // fp1 파일의 끝이 아니라면 반복
        {
            fgets(str_tmp1, sizeof(str_tmp1), fp1);//받는다
            char *ptr1 = strtok(str_tmp1,",");//자른다 쉼표기준으로
            for (int i = 0; i < 15; i++) // 문자열 15번 반복
            {
                str1[i] = ptr1;
                if (i==0 || i==1 || i==5 || i==14) // 문자열내의 0,1,5,14 번 뽑는다
                {
                    printf("%s,",str1[i]); 
                    send(sd, str1[i], strlen(str1[i]), 0); // 출력한것들 보낸다 한 줄씩
                    send(sd,",",1,0);
                }
                ptr1 = strtok(NULL,","); // 다음 문자열 자르고 포인터 반환
            }
            send(sd,"\n",1,0);
            printf("\n");
            break;
        }
    }
}