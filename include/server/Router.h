//
// Created by moira-q on 13.05.19.
//

#ifndef NAAS_ROUTER_H
#define NAAS_ROUTER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <map>
class Router{
public:
    Router();
    Router(std::string m_ip, unsigned m_port) { ip = m_ip; port = m_port;};
    void work();
    std::string generateVip();
    std::string addUser(int sd);
    ~Router();

private:
    std::string ip;
    unsigned int port;
    unsigned int ip_part = 1;
    std::map<std::string, int> vip_table;
    //bool inTable(int sock_desk);



};

#endif //NAAS_ROUTER_H
