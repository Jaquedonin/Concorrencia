#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void ftext(const char *url, char ch[40]){
    int i=0;
    char nome[40] ;
    FILE *arq = fopen(url, "r");
    printf("PID = %d", getpid());

    if(arq == NULL)
        printf("Erro, nao foi possivel abrir o arquivo\n");
    else
    {
        while( fscanf(arq, "%s", nome)!=EOF )
        {
            if(strcmp(nome,ch)==0)
                i=i+1;
        }
        printf("\nTotal da procura neste filho i = %d\n",i);
        printf("\n");
        fclose(arq);

    }
    exit(i);
}
int main()
{
    char url[]="teste.txt";
    char url_1[]="teste_1.txt";
    char url_2[]="teste_2.txt";
    char url_3[]="teste_3.txt";
    char url_4[]="teste_4.txt";
    char ch[]="jaqueline";
    char ch_1[]="bem";
    char ch_2[]="tambem";
    char ch_3[]="Ai";
    char ch_4[]="La";
    FILE *arq;
    int i=0;
    int total=0;;
    int status;
    pid_t  pid;

    // primeiro filho
    pid = fork();
    if(pid<0)
        perror("fork");
    else if(pid==0)
    {
        ftext(url,ch);
    }

    // 2 filho
    pid = fork();
    if(pid<0)
        perror("fork");
    if(pid==0)
    {
        ftext(url_1,ch_1);
    }

    // 3 filho
    pid = fork();
    if(pid<0)
        perror("fork");
    if(pid==0)
    {
        ftext(url_2,ch_2);
    }

    // 4 filho
    pid = fork();
    if(pid<0)
        perror("fork");
    if(pid==0)
    {
        ftext(url_3,ch_3);
    }

    //5 filho
    pid = fork();
    if(pid<0)
        perror("fork");
    if(pid==0)
    {
        ftext(url_4,ch_4);
    }

    printf("PID = %d\n", getpid());
    pid = wait(&status);
    i = WEXITSTATUS(status);
    total += i;

    printf("PID = %d\n", getpid());
    pid = wait(&status);
    i = WEXITSTATUS(status);
    total += i;

    printf("PID = %d\n", getpid());
    pid = wait(&status);
    i = WEXITSTATUS(status);
    total += i;

    printf("PID = %d\n", getpid());
    pid = wait(&status);
    i = WEXITSTATUS(status);
    total += i;

    printf("PID = %d\n", getpid());
    pid = wait(&status);
    i = WEXITSTATUS(status);
    total += i;
    printf("\nTotal %d\n", total);

    return 0;
}
