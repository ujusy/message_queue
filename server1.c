#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>
 
#define BUFFSIZE 30
 
int main(int argc, char *argv[])
{
    fd_set reads, temps; 
    int result;
 
    char message[BUFFSIZE];
    int str_len;
    
    struct timeval timeout;
 
    FD_ZERO(&reads); 
    FD_SET(0,&reads); 
 
    while(1)
    {
        temps = reads; 
 
        timeout.tv_sec = 5; 
        timeout.tv_usec = 0;
 
        result = select(1, &temps, 0, 0, &timeout); 
 
        if(result == -1) 
        {
            puts("select() :: 오류 발생");
            exit(1);
        }
 
        else if(result == 0) 
        {
            puts("select() :: 시간이 초과 되었습니다. ");
        }
        
        else 
        {
            if(FD_ISSET(0,&temps))
            {
                str_len = read(0, message, BUFFSIZE);
                message[str_len] = 0;
                fputs(message, stdout);
            }
        }
    }
 
    return 0;
}


