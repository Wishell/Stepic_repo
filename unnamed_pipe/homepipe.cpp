#include<iostream>
#include<sstream>
#include<vector>
#include<unistd.h>
#include<fstream>
#include<utility>
#include<sys/stat.h>
#include<fcntl.h>
#include <wait.h>


std::vector<std::string> ParseCommandline(const std::string str){
    std::vector<std::string> vector;
    std::string str1;
    for (int i =0;i<str.size();++i){
        if(str[i] =='|' ){
            vector.push_back(str1);
            str1.clear();
            continue;
        }
        str1.push_back(str[i]);
    }
    vector.push_back(str1);
    str1.clear();
return vector;
}

void parse_arg(std::string str , std::string *command , std::string *args){
    for (int i=0; i<str.size();++i){
        if (isspace(str[i])) continue;
        if(str[i]=='-') {
            while (str[i] != ' ' && i < str.size()) {
                args->push_back(str[i]);
                ++i;
            }
            continue;
        }
        if(isalnum(str[i])) command->push_back(str[i]);
    }
}

void exec_line(std::string str){
    std::string command , args ="";
    parse_arg(str,&command,&args);
    if (args.size()){
        execlp(command.c_str(),command.c_str(),args.c_str(),NULL);
    }
    else{
        execlp(command.c_str(),command.c_str(),NULL);
    }
}

void Processor(std::vector<std::string>* vector,size_t index ){

    if(index > 1)
        Processor(vector,index-1);
        pid_t chld = -1;
        int pfd[2];
        pipe(pfd);

        if(index != vector->size() && !(chld = fork())){
            //child
            close(STDOUT_FILENO);
            dup2(pfd[1],STDOUT_FILENO);
            close (pfd[0]);
            close (pfd[1]);
            exec_line(vector->at(index-1));
        }else if (index != vector->size()){

            waitpid(chld,NULL,0);
                close(STDIN_FILENO);
                dup2(pfd[0], STDIN_FILENO);
                close (pfd[1]);
                close (pfd[0]);


        } else if (index == vector->size()){
            int fd = open("/home/box/result.out",O_RDWR | O_CREAT , S_IRUSR | S_IWUSR);
            dup2(fd,STDOUT_FILENO);
            close(pfd[1]);
            close(pfd[0]);
            close(fd);
            exec_line(vector->at(index-1));
        }
}

int main(int argc, char **argv){
    std::string str;
    std::getline(std::cin,str);
    std::vector<std::string> vector(ParseCommandline(str));
    Processor(&vector, vector.size());


return 0;

}
