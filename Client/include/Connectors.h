
/*обмен данными между клиентом и остальными сервисами (конфиг, коннект, аутх)*/

#ifndef NAAS_CONNECTORS_H
#define NAAS_CONNECTORS_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sstream>
#include <thread>
#include <csignal>
#include <sys/stat.h>
#include <vector>


#include "Config.h"
#include "simpletun.h"

namespace connectors {

    class Connector {
    protected:
        virtual int connectFunc(const char *SERVER_ADDR, const int SERVER_PORT) = 0;

        virtual int disconnectFunc() = 0;

        const std::string disconnectRequest = "Kill";

    public:
        virtual ~Connector();
    };


    class Controller { //паттерн стратегия
    public:

        Controller(Connector* conn) : connector(conn) {}
        ~Controller() {delete connector;}

        bool connectAll();

        bool disconnectAll();


        int getAuthConnector();
        // getConfigConnector();
        int getConnectConnector();

    private:
        Connector* connector;
    };


    class AuthConnector : Connector {
    public:
        ~AuthConnector() override;

        int auth(std::string loginAndPass);

    protected:
        int connectFunc(const char *AUTH_ADDR, const int AUTH_PORT) override;

        int disconnectFunc() override;

    private:
        int sock = socket(AF_INET, SOCK_STREAM, 0);


    };


/*class ConfigConnector : Connector {
public:
    ConfigConnector(config::Config config);
    //fetchConfig();
    //saveConfig(config);

protected:
    //connect();
    //disconnect();

private:
    //соединение;
};*/

    class ConnectConnector : Connector {
    public:
        ~ConnectConnector() override;

        int connectInfo();//узнаем ко скольки соединениям мы можем подключиться
        char connectToNet(std::string connectTo);

        const std::string connectRequest = "Connect";
        const char *disconnectAll = "Disconnect all";//когда мы подключаемся напрямую
        //к сети, то мы получаем это сообщение,
        //чтобы контроллер начал отключать модули
        //в то время модуль "коннект" говорил "нет менеджеру",
        //что к сети хотят подключиться, тот открывает сокет
        //ииииии клиент напрямую коннектится к нету :D


    protected:
        int connectFunc(const char *CONNECT_ADDR, const int CONNECT_PORT) override;

        int disconnectFunc() override;

    private:
        int sock = socket(AF_INET, SOCK_STREAM, 0);


    };


}


#endif //NAAS_CONNECTORS_H
