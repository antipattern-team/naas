//
// Created by bless on 19.05.19.
//

#ifndef TEST_TWO_SOCKETS_AUTH_H
#define TEST_TWO_SOCKETS_AUTH_H
#include <iostream>
#include <errno.h>
#include <fstream>
#include <vector>
#include <string>

struct authData{
    std::string login;
    std::string password;
};

class auth {
public:
    void read(std::vector <authData> &loginPasswordVector);
    void write(std::vector <authData> &loginPasswordVector);
    void record(std::vector <authData> &loginPasswordVector, authData &Data);
private:
    //const char* configFile = "configFile";


};


#endif //TEST_TWO_SOCKETS_AUTH_H