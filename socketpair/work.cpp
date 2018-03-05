#include<iostream>
#include<unistd.h>
#include<sys/socket.h>

#define BUF_SIZE 1024
void child(int socket) {
    const char hello[] = "I am your child, Wherever you go, You take me too, Whatever I knowm I learned from you";
    write(socket, hello, sizeof(hello));
    while (1);
}

void parent(int socket) {
    char buf[BUF_SIZE];
    int n = read(socket, buf, sizeof(buf));
    printf("parent received '%.*s'\n", n, buf);
    while (1);
}

int main(int argc, char** argv){
    int sv[2]; // socket descriptors
    int res; // for check result from functions;
    int pid =-1;

    res = socketpair(AF_UNIX,SOCK_STREAM,0,sv);
    if (res == -1){
        perror("error in creating pair of socket");
        return 1;
    }

    pid =fork();
    switch (pid){
        case 0:             // child routine
            close(sv[0]);
            child(sv[1]);
            break;
        case -1:            //error
            perror("error pid id");
            break;
        default:            //parent routine;
            close(sv[1]);
            parent(sv[0]);
            break;
    }

    return 0;
}