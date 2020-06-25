#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
struct data{
    char host[1000];
    char ip[80];
    int num;

};
struct msgba
{
    /* data */
    long mtype;
    struct data da;
};


int main(void){
    key_t key;
    int msgid, len;
    struct msgba mesg;
    
    key = ftok("soyeon",1);
    
    if ( (msgid = msgget(key,0))<0) {
    perror("msgget");
    exit(1);
    }
    

    while (1)
    {
        if(msgrcv(msgid, &mesg, sizeof(struct data), 0, IPC_NOWAIT) < 0){
             if(errno == ENOMSG) {
             printf("bind:Connection refused \n");
             break;
          }

        perror("msgrcv error:");
        exit(0);
    }else{
   
        printf("Get From Server - My Host Name = %s \n", mesg.da.host);
        printf("Get From Server - My IP Address = %s \n", mesg.da.ip);
        printf("Get From Server - My Port Number = %d \n", mesg.da.num);
    break;
    }
    }

    
     msgctl(msgid, IPC_RMID, 0);
  

    return 0;
}