
#ifndef TEST_TWO_SOCKETS_THREADTUN_H
#define TEST_TWO_SOCKETS_THREADTUN_H


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

#include "simpletun.h"



class ThreadTun {
public:
    int connectToServ();
    void create_tun(const std::string &vip);
    void delete_tun();
    void term_handler(int i);


    int tun();

private:
    const char *SERVER_ADDR = "192.168.43.192";
    const int SERVER_PORT = 10000;
    const int BUFF_SIZE = 4* 1024;
    const char *tun_name = "vpn_tun";
    int sock_fd;
    int tap_fd;


};


#endif //TEST_TWO_SOCKETS_THREADTUN_H
