

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <vector>
#include <string>
const char ip[30] = "192.168.1.66";

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
        sock = accept(s, NULL, NULL);
        send(sock, ip, sizeof(ip), 0);
        close(sock);
    }

}