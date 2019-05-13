//
// Created by moira-q on 13.05.19.
//

#ifndef NAAS_ROUTER_H
#define NAAS_ROUTER_H

#include <string>
class Router{
public:
    Router();
    Router(std::string m_ip, unsigned m_port) { ip = m_ip; port = m_port};
    bool work();
    ~Router();

private:
    std::string ip;
    unsigned int port;




};

#endif //NAAS_ROUTER_H
