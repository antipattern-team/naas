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
#include "src/Authentification.h"

const int BUFF_SIZE = 4 * 1024;



int main() {
    Data data;
    ViModules viModules;
    std::vector<Data> configVector;
    //std::vector<authData> authVector;
    Config conf;
    //auth auth;
    conf.read(configVector);
    //conf.write(configVector);
    //auth.read(authVector);
    //auth.write(authVector);
    char recMessage[BUFF_SIZE];
    char sendMessage[BUFF_SIZE];
    int answer = 0;


    std::cout << "pupa"<< std::endl;

    //connect to UI modules

    viModules.connectAuth(configVector);
    viModules.connectConfig(configVector);
    viModules.connectConnect(configVector);




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
                    //connect to allowed server, discuss with Sanya
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
