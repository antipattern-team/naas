//
// Created by moira-q on 13.05.19.
//

#include <server/Router.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <algorithm>
#include <set>
#include <cstring>
#include <vector>

Router::Router() {

}

Router::~Router() {

}

void Router::work() {
    /* int sock;
     int s = socket(AF_INET, SOCK_STREAM, 0);
     std::string vip;

     sockaddr_in sockaddr_ = {
             .sin_family = AF_INET,
             .sin_port = htons(port),
     };

     bind(s, (sockaddr *) &sockaddr_, sizeof(sockaddr_));

     listen(s, 5);
     std::cout << "Захожу в цикл" << std::endl;
     while(1) {
         sock = accept(s, NULL, NULL);
         std::cout << "XDDDDDDDDD"  << std::endl;
         vip = this->addUser(sock);
         std::cout << vip  << std::endl;
         std::cout << vip_table[vip]  << std::endl;

         auto tmp = vip + "-это ты";
         send(sock, tmp.c_str(), tmp.size(), 0);
         std::cout << "Отправил vip Челам"  << std::endl;

     }*/

    int listener;
    struct sockaddr_in addr;
    char buf[1024];
    int bytes_read;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0) {
        perror("socket");
        exit(1);
    }

    fcntl(listener, F_SETFL, O_NONBLOCK);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(listener, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(2);
    }

    listen(listener, 5);

    std::set<int> clients;
    clients.clear();



    while (1) {
        // Заполняем множество сокетов
        fd_set readset;
        FD_ZERO(&readset);
        FD_SET(listener, &readset);

        for (std::set<int>::iterator it = clients.begin(); it != clients.end(); it++)
            FD_SET(*it, &readset);

        // Задаём таймаут
        timeval timeout;
        timeout.tv_sec = 15;
        timeout.tv_usec = 0;

        // Ждём события в одном из сокетов
        int mx = std::max(listener, *max_element(clients.begin(), clients.end()));
        if (select(mx + 1, &readset, NULL, NULL, &timeout) <= 0) {
            perror("select");
            exit(3);
        }

        // Определяем тип события и выполняем соответствующие действия
        if (FD_ISSET(listener, &readset)) {
            // Поступил новый запрос на соединение, используем accept
            int sock = accept(listener, NULL, NULL);
            if (sock < 0) {
                perror("accept");
                exit(3);
            }

            fcntl(sock, F_SETFL, O_NONBLOCK);

            clients.insert(sock);
            this->addUser(sock);
        }
    }
}
std::string Router::generateVip() {
    std::cout << "Делаю айпи" << std::endl;
    return ip_area + std::to_string(ip_part++) + "/32";
}

std::string Router::addUser(const int sd) {
    std::cout << "Добавляю пользователя"  << std::endl;
    std::string vip = generateVip();
    this->vip_table[vip] = sd;
    return vip;
}

int Router::choiceUrSocket(std::string ip) {
    /*for(auto& str : vip_table) {
        if (str.first == ip) {
            return str.second;
        }
    }*/
    std::vector<int> m;
    for(auto& str : vip_table) {
        m.push_back(compareIp(ip, str.first));
    }

    int id_max = 0;
    int max = 0;

    for(int i = 0; i < m.size(); i++) {
        if (m[i] > max) {
            max = m[i];
            id_max = i;
        }
    }

    if(max == 0) {
        return 0;
    }
    auto it = vip_table.begin();
    for(int i = 0; i < id_max; i++) {
        it++;
    }
    return it->second;//сокет следущего звена в маршруте до получателя
}

int Router::compareIp(std::string aip, std::string bip) {

    std::string a[5];
    int i = 0;
    char * pch = std::strtok (const_cast<char*>(aip.c_str()),"./");

    while (pch != NULL && i!=5)                         // пока есть лексемы
    {
        std::cout << pch  << "\n";
        a[i] = pch;
        pch = strtok (NULL, "./");
        i++;
    }

    std::string b[5];
    i = 0;
    char * pch1 = std::strtok (const_cast<char*>(bip.c_str()),"./");

    while (pch1 != NULL && i!=5)                         // пока есть лексемы
    {
        std::cout << pch1  << "\n";
        b[i] = pch1;
        pch1 = strtok (NULL, "./");
        i++;
    }

    int mask = atoi(b[4].c_str());
    for(i = 0; i < mask/8; i++){
        if(a[i] != b[i]) {
            return 0;
        }
    }
    return i;
}


/*bool Router::inTable(int sock_desk) {
    if(vip_table.find(sock_desk) != vip_table.end()) {
        //vip = network_list[network]->add_peer(password, ip);

        return false;
}*/

