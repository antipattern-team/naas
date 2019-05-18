

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <vector>
#include <string>

const char ip[4 * 1024] = "192.168.111.166.1.1.1.1323";

int main(){
    int sock;
    int s = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in sockaddr_ = {
            .sin_family = AF_INET,
            .sin_port = htons(12345),
    };
    bind(s, (sockaddr *) &sockaddr_, sizeof(sockaddr_));

    listen(s, 1);

    while(1)
    {
        char buff[100];
        sock = accept(s, NULL, NULL);
        recv(sock, buff, sizeof(buff), 0);
        send(sock, ip, sizeof(ip), 0);
        std::cout << ip << std::endl;
        std::cout << buff << std::endl;
        close(sock);
    }

}