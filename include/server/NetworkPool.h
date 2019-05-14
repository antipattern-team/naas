//
// Created by moira-q on 13.05.19.
//

#ifndef NAAS_NETWORKPOOL_H
#define NAAS_NETWORKPOOL_H

#include <string>
#include <vector>
#include <thread>
#include "Router.h"

class NetworkPool{
public:
    NetworkPool();
    void listenConfig();
    bool createAndServRouter(std::string ipRoutera, unsigned int port);
    ~NetworkPool();

private:
    unsigned int port = 10000;
    unsigned int ip_part = 22;
    std::vector<Router> routers;

};

#endif //NAAS_NETWORKPOOL_H
