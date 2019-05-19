
#include "../include/ViModules.h"

bool ViModules::connectAuth(std::vector <Data> configVector)
{
    const char *AUTH_ADDR = configVector[0].ip.c_str();
    const int AUTH_PORT = configVector[0].port;

    sockaddr_in sockaddr_;

    sockaddr_.sin_family = AF_INET;
    sockaddr_.sin_port = htons(AUTH_PORT);
    sockaddr_.sin_addr.s_addr = inet_addr(AUTH_ADDR);
    std::cout<<sockAuth<<' '<<std::endl;
    int status = connect(sockAuth, (sockaddr*) &sockaddr_, sizeof(sockaddr_));
    if (status){
        std::cout << "errno=" << errno << std::endl << strerror(errno) <<std::endl;
        return false;
    }
    return true;
}

int ViModules::communicationWthAuth(char (&sendMess)[4096],char (&recvMess)[4096])
{

    send(sockAuth, (void*)sendMess, sizeof(sendMess), 0);
    recv(sockAuth, recvMess, sizeof(recvMess), 0);

    std::cout << recvMess << " - auth says" << std:: endl;

    return 0;
}
bool ViModules::closeSockAuth()
{

    auto status = close(sockAuth);

    if(!status) {

        return false;

    }

    return true;
}

bool ViModules::connectConfig(std::vector<Data> configVector)
{
    const char *CONFIG_ADDR = configVector[1].ip.c_str();
    const int CONFIG_PORT = configVector[1].port;

    sockaddr_in sockaddr_;

    sockaddr_.sin_family = AF_INET;
    sockaddr_.sin_port = htons(CONFIG_PORT);
    sockaddr_.sin_addr.s_addr = inet_addr(CONFIG_ADDR);

    int status = connect(sockConfig, (sockaddr*) &sockaddr_, sizeof(sockaddr_));
    if (!status){
        std::cout << "errno=" << errno << std::endl << strerror(errno) <<std::endl;
        return false;
    }
    return true;
}

int ViModules::communicationWthConfig(char (&sendMess)[4096],char (&recvMess)[4096])
{
    send(sockConfig, (void*)sendMess, sizeof(sendMess), 0);
    recv(sockConfig, recvMess, sizeof(recvMess), 0);

    std::cout << recvMess << " - cfg says" << std:: endl;
    return 0;
}

bool ViModules::closeSockConfig()
{
    return false;
}

bool ViModules::connectConnect(std::vector<Data> configVector)
{
    const char *CONNECT_ADDR = configVector[2].ip.c_str();
    const int CONNECT_PORT = configVector[2].port;

    sockaddr_in sockaddr_;

    sockaddr_.sin_family = AF_INET;
    sockaddr_.sin_port = htons(CONNECT_PORT);
    sockaddr_.sin_addr.s_addr = inet_addr(CONNECT_ADDR);

    int status = connect(sockConnect, (sockaddr*) &sockaddr_, sizeof(sockaddr_));
    if (!status){
        std::cout << "errno=" << errno << std::endl << strerror(errno) <<std::endl;
        return false;
    }
    return true;
}

int ViModules::communicationWthConnect(char (&sendMess)[4096],char (&recvMess)[4096])
{
    send(sockConnect, (void*)sendMess, sizeof(sendMess), 0);
    recv(sockConnect, recvMess, sizeof(recvMess), 0);

    std::cout << recvMess << " - connect says" << std:: endl;

    return 0;
}

bool ViModules::closeSockConnect()
{
    return false;
}
