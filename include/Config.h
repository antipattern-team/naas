#ifndef TEST_TWO_SOCKETS_CONFIG_H
#define TEST_TWO_SOCKETS_CONFIG_H


#include <iostream>
#include <errno.h>
#include <fstream>
#include <vector>
#include <string>

struct Data{
    std::string ip;
    int port = 0;
};

class Config {
public:
    void read(std::vector <Data> &configVector);

private:
    //const char* configFile = "configFile";


};





#endif //TEST_TWO_SOCKETS_CONFIG_H
