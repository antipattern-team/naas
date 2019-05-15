#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <map>
#include <sstream>
#include <thread>
#include <csignal>
#include <sys/stat.h>
#include <vector>
#include <string>

const char *AUTH_ADDR = "192.168.1.66"; //your local ip
const int AUTH_PORT = 12345;
const int SERVER_PORT = 10000;
const int BUFF_SIZE = 4* 1024;
const char request[BUFF_SIZE] = "darova";


void Fooo(char& addr);

int main() {
    int s = socket(AF_INET, SOCK_STREAM, 0 );

//    in_addr in;                                     - this all I changed
//    int res = inet_aton(SERVER_ADDR, &in);          - because for me it
//    if (!res) {                                     - was questionably -_-
//        return -1;                                  -
//    }                                               -
    sockaddr_in sockaddr_;

    sockaddr_.sin_family = AF_INET;
    sockaddr_.sin_port = htons(AUTH_PORT);
//            .sin_addr = in                          -
    sockaddr_.sin_addr.s_addr = inet_addr(AUTH_ADDR);

    char buff[BUFF_SIZE];

    connect(s, (sockaddr*) &sockaddr_, sizeof(sockaddr_));
    recv(s, buff, sizeof(buff), 0);

    std::cout << buff << "- auth says" << std:: endl;

    close(s);

    Fooo(*buff);

    return 0;

}

void Fooo(char& addr){
    int s1 = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in sockaddr_;
    sockaddr_.sin_family = AF_INET;
    sockaddr_.sin_port = htons(SERVER_PORT);
    sockaddr_.sin_addr.s_addr = inet_addr(&addr);


    auto res = connect(s1, (sockaddr*) &sockaddr_,  sizeof(sockaddr_));

    if (res) {
        std::cout << "errno=" << errno << std::endl << strerror(errno) <<std::endl;
        exit(1);
    }

    char buff[BUFF_SIZE];
    recv(s1, buff, BUFF_SIZE, 0);
    std::cout << buff << " - serv says" << std::endl;
}