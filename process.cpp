#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#define NUM_PROCESS     16
void Process_id(){
    int i=0;
    printf("Hello World! It's me, filho #%d!\n", getpid());
    //variável que será incrementada pelo processo e retornará quando o processo for encerrado    
    i=i+1;
    exit(i);
}
int main()
{
    FILE *arq;
    int i=0;
    int total=0;;
    int status;
    pid_t  pid;

    for (int k = 0; k < NUM_PROCESS; ++k)
    {
        // criando os filhos
        pid = fork();
        //caso de erro
        if(pid<0)
            perror("fork");
        //caso funcione
        else if(pid==0)
        {
            Process_id();
        }

    }
        
    for (int j = 0; j < NUM_PROCESS; ++j)
    {
        //printf("PID = %d\n", getpid());
        pid = wait(&status);
        i = WEXITSTATUS(status);
        total += i;
    }
    printf("\nTotal de filhos encerrados %d\n", total);

    return 0;
}
