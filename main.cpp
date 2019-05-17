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


const int BUFF_SIZE = 4 * 1024;



int main() {
    Data data;
    ViModules viModules;
    std::vector<Data> configVector;
    Config conf;

    conf.read(configVector);

    char recMessage[BUFF_SIZE];
    char sendMessage[BUFF_SIZE];
    int answer = 0;


    //connect to UI modules
    viModules.connectAuth(configVector);
    viModules.connectConnect(configVector);
    viModules.connectConfig(configVector);

    std::cin >> sendMessage;

    viModules.communicationWthAuth(sendMessage, recMessage);
    viModules.communicationWthAuth(sendMessage, recMessage);




//    std::cout << std::endl << "choose what you want to connect (1,2,3)" << std::endl;
//    int switcher = 0;
//    std::cin >> switcher;
//

//    switch (switcher) {
//
//        case (1) :
//
//            std::cout << "1-auth" << "          " << "2-create new acc" << std::endl;
//            std::cin >> answer;
//            switch(answer){
//
//                case (1) :
//                    std::cout << "Enter your login" << std::endl;
//                    std::cin >> sendMessage;
//
//                    viModules.communicationWthAuth(sendMessage, recMessage);
//
//                    break;
//                case (2) :
//                    //viModules.communicationWthAuth(sendMessage, recMessage);
//                    break;
//                default:
//
//                    break;
//            }
//
//        case (2) :
//
//            break;
//        case (3) :
//
//            break;
//        default:
//            break;
//    }


    viModules.closeSockAuth();
    viModules.closeSockConnect();
    viModules.closeSockConfig();


    return 0;

}
