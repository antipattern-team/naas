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

#include "include/Config.h"
#include "include/ViModules.h"
#include "include/Authentification.h"
#include "include/ThreadTun.h"

const int BUFF_SIZE = 4 * 1024;

const char *SERVER_ADDR = "172.16.87.16";  // mb std::string
const int SERVER_PORT = 10000;
const char *tun_name = "vpn_tun";
int sock_fd;
int tap_fd;

void create_tun(const std::string &vip) {
    std::string syscall = "bash scripts/tun.sh ";
    syscall += tun_name;
    syscall += " ";
    syscall += vip;
    system(syscall.c_str());
}

void delete_tun() {
    std::string syscall = "bash scripts/tun_del.sh ";
    syscall += tun_name;
    system(syscall.c_str());
}

void term_handler(int i){
    int s = socket(AF_INET, SOCK_STREAM, 0);
    in_addr in;
    int res = inet_aton(SERVER_ADDR, &in);
    if (!res) {
        exit;
    }

    sockaddr_in sockaddr_ = {
            .sin_family = AF_INET,
            .sin_port = htons(SERVER_PORT),
            .sin_addr = in
    };
    connect(s, (sockaddr*) &sockaddr_, sizeof(sockaddr_));
    send(s, (void *)"disconnect", strlen("disconnect"), 0);

    close(sock_fd);
    close(tap_fd);
    delete_tun();

    exit(EXIT_SUCCESS);
}




int main() {
    Data data;
    std::cout << "lol1" << std::endl;
    ViModules viModules;
    //ThreadTun threadTun;
    std::vector<Data> configVector;
    //std::vector<authData> authVector;
    Config conf;
    std::cout << "lol2" << std::endl;

    conf.read(configVector);
    std::cout << "lol3" << std::endl;
    conf.write(configVector);

    std::cout << "lol4" << std::endl;
    //auth.write(authVector);
    char recMessage[BUFF_SIZE];
    char sendMessage[BUFF_SIZE];
    int answer = 0;


    std::cout << "pupa"<< std::endl;

    //connect to UI modules

//    viModules.connectAuth(configVector);
//    viModules.connectConfig(configVector);
//    viModules.connectConnect(configVector);




    std::cout << std::endl << "choose what do you want to connect (1,2,3)" << std::endl;
    int switcher = 0;
    std::cin >> switcher;


    switch (switcher) {

        case (1) : //auth

            std::cout << "1-auth" << "      " << "2-create new acc" <<"     "<<"3 - user list"<<std::endl;
            std::cin >> answer;
            switch(answer){

                case (1) :
                    std::cout << "Enter your login" << std::endl;
                    std::cin >> sendMessage;
                    viModules.communicationWthAuth(sendMessage, recMessage);
                //create_token as string func of auth? discuss with Sanya
                    break;
                case (2) :
                    std::cout << "Create your login" << std::endl; //creating log and pass if no such user
                    std::cin >> sendMessage;
                    viModules.communicationWthAuth(sendMessage, recMessage);
                    std::cout << "Create your password" << std::endl;
                    std::cin >> sendMessage;
                    viModules.communicationWthAuth(sendMessage, recMessage);
                    break;
                case (3) :
                    //auth.write(authVector);
                default:

                    break;
            }
        case (2) : //connect
            std::cout << "1 - ask for vip list access" <<"       "<<"2 - get list"<<"       "<<"3  -  connect to permitted serv"<<std::endl;
            std::cin >> answer;
            switch(answer) {

                case (1):
                    std::cout << "Enter your login" << std::endl;
                    std::cin >> sendMessage;
                    viModules.communicationWthConnect(sendMessage, recMessage);
                    std::cout << "Enter your token" << std::endl;
                    std::cin >> sendMessage;
                    viModules.communicationWthConnect(sendMessage, recMessage);
                    break;
                case (2):
                    conf.write(configVector);
                    break;
                case (3):
                {
                    int s = socket(AF_INET, SOCK_STREAM, 0);
                    in_addr in;
                    int res = inet_aton(SERVER_ADDR, &in);
                    if (!res) {
                        return -2;
                    }

                    sockaddr_in sockaddr_ = {
                            .sin_family = AF_INET,
                            .sin_port = htons(SERVER_PORT),
                            .sin_addr = in
                    };




                    connect(s, (sockaddr*) &sockaddr_, sizeof(sockaddr_));

                    char buff[BUFF_SIZE];
                    recv(s, buff, BUFF_SIZE, 0);
                    std::stringstream dhcp_input(buff);

                    std::string vip;
                    dhcp_input >> vip;

                    std::cout << buff << std::endl;

                    if (vip == "ERR") {
                        std::string error_type;
                        dhcp_input >> error_type;
                        std::cout << "Error occured: " << error_type << std::endl;
                        return 55;
                    }
                    close(s);

                    create_tun(vip);

                    int pid = fork();

                    if (pid == -1) // если не удалось запустить потомка
                    {
                        // выведем на экран ошибку и её описание
                        printf("Error: Start Daemon failed (%s)\n", strerror(errno));

                        return -1;
                    }
                    else if (!pid) // если это потомок
                    {
                        // создаём новый сеанс, чтобы не зависеть от родителя
                        setsid();

                        //
                        printf("My pid is %i\n", getpid());

                        // закрываем дискрипторы ввода/вывода/ошибок, так как нам они больше не понадобятся
                        close(STDIN_FILENO);
                        close(STDOUT_FILENO);
                        close(STDERR_FILENO);

                        //
                        std::signal(SIGTERM, term_handler);

                        connect_to_server("vpn_tun", SERVER_ADDR, sock_fd, tap_fd);

                        return 0;
                    }
                    else // если это родитель
                    {
                        // завершим процес, т.к. основную свою задачу (запуск демона) мы выполнили
                        return 0;
                    }
                }


                    break;
                default:

                    break;
            }
        case (3) : //config
            std::cout<<"1 - get list of UIs"<<"     "<<"2 - add UI"<<std::endl;
            std::cin>>answer;
            switch(answer){
                case(1):
                conf.write(configVector);
                break;
                case(2):
                std::cout<<"Enter wanted UI"<<std::endl;
                    std::cin >> sendMessage;
                    viModules.communicationWthConfig(sendMessage, recMessage); // tho still 8 bits rcdv, idk
                    std::cout << "Enter port" << std::endl;
                    std::cin >> sendMessage;
                    viModules.communicationWthConfig(sendMessage, recMessage); // collision between int and string may happen, need converter?
                    break;
                default:
                    break;
            }
                default:
            break;
    }
    viModules.closeSockAuth();
    viModules.closeSockConnect();
    viModules.closeSockConfig();


    return 0;

}
