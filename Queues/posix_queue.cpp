#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>
#include <stdio.h>
#include <memory.h>
#include <unistd.h>

#define MQNAME "/test.mq"


int main(){
    if (0 == mq_unlink(MQNAME)){
    printf(mq removed);
    }
    struct mq_attr attr;
    attr.mq_flags=0;
    attr.mq_maxmsg =10;
    attr.mq_msgsize=128;
    attr.mq_curmsgs=0;


    mqd_t mq = mq_open(MQNAME, O_CREAT | O_RDWR | O_NONBLOCK,0666, &attr);
    if(-1 == mq){
        printf("Error in mq_open %d", errno);
        return 1;
    }

    char buffer[128];
    memset(buffer,0,sizeof(buffer));

    int fd = open("/home/box/message.txt", O_CREAT | O_WRONLY |O_TRUNC, 0666);
    if (-1 == fd){
        printf("error open file message.txt %d", errno);
        return 1;
    }
    while (1){
     int size = mq_receive(mq,buffer,attr.mq_msgsize,0);
                printf("readed msg size %d", attr.mq_msgsize);
            if(errno != EAGAIN){
                printf("error read message %d", errno);
                return 1;
            } else if (size > 0){
                write(fd,buffer,attr.mq_msgsize);
                printf("message read sucsess %s", buffer);
                mq_unlink(MQNAME);
                break;
            }

    }
return 0;

}
