#include<iostream>
#include<sstream>
#include<vector>
#include<unistd.h>
#include<fstream>
#include<utility>
#include<sys/stat.h>
#include<fcntl.h>
#include <wait.h>
#include <cstring>

const char* in_name = "/home/box/in.fifo";
const char* out_name = "/home/box/out.fifo";

int main(int argc, char **argv) {
    int fd_in = -1;
    int fd_out = -1;
    char buffer[1024];
    int len_read;
    int len_write;

    if (mkfifo(in_name, 0666) == -1) {
        perror("error creating in pipe\n");
        return 1;
    }
    printf("in pipe is creating\n");

    if (mkfifo(out_name, 0666) == -1) {
        perror("error creating out pipe\n");
        return 1;
    }
    printf("out pipe is creating\n");

    if ((fd_in = open(in_name, O_RDONLY )) < 0) {
        perror("error open in.fifo\n");
        return 1;
    }

    if ((fd_out = open(out_name, O_RDWR)) < 0) {
        perror("error open out.fifo\n");
        return 1;
    }


    while (len_read = read(fd_in, buffer, 1024)) {
        size_t len2 = write(fd_out, buffer, len_read);
        if (len2 < len_read) {
            perror("error write");
            break;
        }
    }
    close(fd_in);
    close(fd_out);
    remove(in_name);
    remove(out_name);
    return 0;




}
