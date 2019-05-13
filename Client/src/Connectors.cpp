//
// Created by sancho on 12.05.19.
//

#include <Client/include/Connectors.h>

#include "../include/Connectors.h"




int connectors::AuthConnector::connectFunc(const char* AUTH_ADDR,const int AUTH_PORT)
{

    in_addr in;
    int res = inet_aton(AUTH_ADDR, &in);

    if (!res) {
        return -2;
    }

    sockaddr_in sockaddr_ = {
            .sin_family = AF_INET,
            .sin_port = htons(AUTH_PORT),
            .sin_addr = in
    };

    auto status = connect(sock, (sockaddr*) &sockaddr_, sizeof(sockaddr_));

    if(status){
        std::cout << "auth connected"<< std::endl;
        return 0;
    }


}

int connectors::AuthConnector::disconnectFunc()
{
    auto status = send(sock, (void *)disconnectRequest.c_str(), strlen(disconnectRequest.c_str()), 0);
    if(status){
        std::cout<<"Auth disconnected" << std::endl;
        return 0;
    }
    return 0;
}

int connectors::AuthConnector::auth(std::string loginAndPass)
{
    auto status = send(sock, (void *)loginAndPass.c_str(), strlen(loginAndPass.c_str()), 0);

    if(status){
        std::cout<<"yep" << std::endl;
        return 0;
    }

    char message[100];
    auto statusRec = recv(sock, message, sizeof(message), 0);

    if(statusRec) {
        std::cout << "message recieved" << std::endl;
    }
    return 0;

}




int connectors::ConnectConnector::connectFunc(const char *CONNECT_ADDR, const int CONNECT_PORT)
{
    in_addr in;
    int res = inet_aton(CONNECT_ADDR, &in);

    if (!res) {
        return -2;
    }

    sockaddr_in sockaddr_ = {
            .sin_family = AF_INET,
            .sin_port = htons(CONNECT_PORT),
            .sin_addr = in
    };

    auto status = connect(sock, (sockaddr*) &sockaddr_, sizeof(sockaddr_));

    if(status){
        std::cout << "auth connected"<< std::endl;
        return 0;
    }
}

int connectors::ConnectConnector::disconnectFunc()
{
    auto status = send(sock, (void *)disconnectRequest.c_str(), strlen(disconnectRequest.c_str()), 0);

    if(status){
        std::cout<<"Connect disconnected" << std::endl;
        return 0;
    }
    return 0;
}

int connectors::ConnectConnector::connectInfo()
{
    auto status = send(sock, (void *)connectRequest.c_str(), strlen(connectRequest.c_str()), 0);
    if(status){
        std::cout<<"yep" << std::endl;
        return 0;
    }
    char message[100];
    auto statusRec = recv(sock, message, sizeof(message), 0);//возращает

    if(statusRec) {
        std::cout << "message recieved" << std::endl;
    }
    return 0;

}

char connectors::ConnectConnector::connectToNet(std::string connectTo)
{
    auto status = send(sock, (void *)connectTo.c_str(), strlen(connectTo.c_str()), 0);

    if(!status){
        std::cout<<"no" << std::endl;
        return -1;
    }

    char message[100];
    auto statusRec = recv(sock, message, sizeof(message), 0);//возращает

    if(statusRec) {
        std::cout << "message recieved" << std::endl;//
        return *disconnectAll;//отправляет сообщение контроллеру отключить все подключения ко всем модулям
    }


}

