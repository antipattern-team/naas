//
// Created by moira-q on 13.05.19.
//

#ifndef NAAS_NETWORKPOOL_H
#define NAAS_NETWORKPOOL_H

#include <string>
#include <vector>
#include <thread>
#include <stdio.h>
#include <iostream>
#include "Router.h"

class NetworkPool{
public:
    NetworkPool();
    void listenConfig();
    bool createAndServRouter(std::string ipRoutera, unsigned int port);
    ~NetworkPool();

private:
    unsigned int port = 10000;
    unsigned int  currentVip = 3;//x начиная с 3
    std::string basicVip = "122.120.";//маршрутизаторы будут 122.120.x.0
    std::vector<Router> routers;

};

#endif //NAAS_NETWORKPOOL_H
