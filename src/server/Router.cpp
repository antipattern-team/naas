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
using namespace std;



Router::Router() {

}

Router::~Router() {

}

void Router::work() {
    /*int sock;
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

    }
*/
    int listener;
    struct sockaddr_in addr;
    char buf[1024];
    int bytes_read;
    std::string vip;


    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }

    fcntl(listener, F_SETFL, O_NONBLOCK);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    listen(listener, 2);

    set<int> clients;
    clients.clear();

    while(1)
    {
        // Заполняем множество сокетов
        fd_set readset;
        FD_ZERO(&readset);
        FD_SET(listener, &readset);

        for(set<int>::iterator it = clients.begin(); it != clients.end(); it++)
            FD_SET(*it, &readset);

        // Задаём таймаут
        timeval timeout;
        timeout.tv_sec = 15;
        timeout.tv_usec = 0;

        // Ждём события в одном из сокетов
        int mx = max(listener, *max_element(clients.begin(), clients.end()));
        if(select(mx+1, &readset, NULL, NULL, &timeout) <= 0)
        {
            perror("select");
            exit(3);
        }

        // Определяем тип события и выполняем соответствующие действия
        if(FD_ISSET(listener, &readset))
        {
            // Поступил новый запрос на соединение, используем accept
            int sock = accept(listener, NULL, NULL);
            if(sock < 0)
            {
                perror("accept");
                exit(3);
            }

            fcntl(sock, F_SETFL, O_NONBLOCK);
            vip = this->addUser(sock);

            clients.insert(sock);
        }

        for(set<int>::iterator it = clients.begin(); it != clients.end(); it++)
        {
            if(FD_ISSET(*it, &readset))
            {
                // Поступили данные от клиента, читаем их
                bytes_read = recv(*it, buf, 1024, 0);

                if(bytes_read <= 0)
                {
                    // Соединение разорвано, удаляем сокет из множества
                    close(*it);
                    clients.erase(*it);
                    continue;
                }

                // Отправляем данные обратно клиенту
                send(*it, buf, bytes_read, 0);
            }
        }
    }


}

std::string Router::generateVip() {
    std::cout << "Делаю айпи" << std::endl;
    return "123.32.23." + std::to_string(ip_part++) ;
}

std::string Router::addUser(const int sd) {
    std::cout << "Добавляю пользователя"  << std::endl;
    std::string vip = generateVip();
    this->vip_table[vip] = sd;
    return vip;
}


/*bool Router::inTable(int sock_desk) {
    if(vip_table.find(sock_desk) != vip_table.end()) {
        //vip = network_list[network]->add_peer(password, ip);

        return false;
}*/

