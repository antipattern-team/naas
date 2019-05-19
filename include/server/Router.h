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
    Router(std::string m_ip, unsigned m_port, std::string m_ip_part) {
        ip = m_ip; port = m_port; ip_area = m_ip_part + ".";
    };
    void work();
    std::string generateVip();
    std::string addUser(int sd);
    int choiceUrSocket(std::string ip);
    void getVip();
    ~Router();

private:
    int compareIp(std::string aip, std::string bip);// сравнивает значимые байты двух ip и возвращает количество совпадений
    std::string ip;
    unsigned int port;
    unsigned int ip_part = 1;
    std::string ip_area;//область которую охватывает роутер (122.120.х.)
    std::map<std::string, int> vip_table;
    //std::map<std::string, int> vip_table_routers;
    //bool inTable(int sock_desk);



};

#endif //NAAS_ROUTER_H
