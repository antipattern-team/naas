//
// Created by sancho on 12.05.19.
//

#include <Client/include/Connectors.h>

#include "../include/Connectors.h"




int connectors::AuthConnector::connectFunc(const char* AUTH_ADDR, uint16_t  AUTH_PORT)
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

    if(!status){
        std::cout << "auth not connected"<< std::endl;
        return -1;
    }
    return  0;


}

int connectors::AuthConnector::disconnectFunc()
{
    auto status = send(sock, (void *)disconnectRequest.c_str(), strlen(disconnectRequest.c_str()), 0);
    if(!status){
        std::cout<<"Auth not disconnected" << std::endl;
        return -1;
    }
    return 0;
}

int connectors::AuthConnector::auth(std::string loginAndPass)
{
    auto status = send(sock, (void *)loginAndPass.c_str(), strlen(loginAndPass.c_str()), 0);

    if(!status){
        std::cout<<"not sended" << std::endl;
        return -1;
    }

    char message[100];
    auto statusRec = recv(sock, message, sizeof(message), 0);

    if(!statusRec) {
        std::cout << "message not recieved" << std::endl;
        return -1;
    }
    return  0;

}




int connectors::ConnectConnector::connectFunc(const char *CONNECT_ADDR,  uint16_t CONNECT_PORT)
{
    in_addr in;
    int res = inet_aton(CONNECT_ADDR, &in);

    if (!res) {
        return -1;
    }

    sockaddr_in sockaddr_ = {
            .sin_family = AF_INET,
            .sin_port = htons(CONNECT_PORT),
            .sin_addr = in
    };

    auto status = connect(sock, (sockaddr*) &sockaddr_, sizeof(sockaddr_));

    if(!status){
        std::cout << "auth not connected"<< std::endl;
        return -1;
    }
}

int connectors::ConnectConnector::disconnectFunc()
{
    auto status = send(sock, (void *)disconnectRequest.c_str(), strlen(disconnectRequest.c_str()), 0);

    if(!status){
        std::cout<<"Connect not disconnected" << std::endl;
        return -1;
    }
    return 0;
}

int connectors::ConnectConnector::connectInfo()
{
    auto status = send(sock, (void *)connectRequest.c_str(), strlen(connectRequest.c_str()), 0);
    if(!status){
        std::cout<<"looser" << std::endl;
        return -1;
    }
    char message[100];
    auto statusRec = recv(sock, message, sizeof(message), 0);//возращает

    if(!statusRec) {
        std::cout << "message not recieved" << std::endl;
    }
    return 0;

}

int connectors::ConnectConnector::connectToNet(std::string connectTo)
{
    auto status = send(sock, (void *)connectTo.c_str(), strlen(connectTo.c_str()), 0);

    if(!status){
        std::cout<<"no" << std::endl;
        return -1;
    }

    char message[100];
    auto statusRec = recv(sock, message, sizeof(message), 0);//возращает

    if(!statusRec) {
        std::cout << "message not recieved" << std::endl;
        return -1;

    }
    return *disconnectAll;//отправляет сообщение контроллеру отключить все подключения ко всем модулям

}




//называется коннект алл, а по сути коннектит только одно :DDDDDDDD
void connectors::Controller::connectAll(const char *SERVER_ADDR,  uint16_t SERVER_PORT)
{
    connector->connectFunc(SERVER_ADDR, SERVER_PORT);
}

void connectors::Controller::disconnectAll()
{
    connector->disconnectFunc();
}




