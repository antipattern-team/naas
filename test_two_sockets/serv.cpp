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

const char message[30] = "darova from serv";
const int BUFF_SIZE = 4* 1024;


int main() {
    int sock;
    int s = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in sockaddr_ = {
            .sin_family = AF_INET,
            .sin_port = htons(10000),
    };
    bind(s, (sockaddr *) &sockaddr_, sizeof(sockaddr_));


    listen(s, 1);

    while(1)
    {

        sock = accept(s, NULL, NULL);

        send(sock,(void *)message, sizeof(message), 1);
        std::cout << "zbs" << std::endl;

        close(sock);
    }

    return 0;
    
}