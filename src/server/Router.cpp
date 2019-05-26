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
#include <thread>


Router::Router() {

}

Router::~Router() {

}
int Router::foo() {
#define DHCP_BUFSIZE 4096
#define BUFSIZE 20000
#define DHCP_PORT 10000
#define PORT 55555

    int dhcp_s = socket(AF_INET, SOCK_STREAM, 0);
    in_addr in;
    int res = inet_aton("0.0.0.0", &in);
    if (!res) {
        return -2;
    }

    sockaddr_in sockaddr_ = {
            .sin_family = AF_INET,
            .sin_port = htons(DHCP_PORT),
            .sin_addr = in
    };

    res = bind(dhcp_s, (sockaddr*) &sockaddr_, sizeof(sockaddr_));
    if (res) {
        std::cout << std::strerror(errno);
        return -1;
    }

    listen(dhcp_s, 5);

    sockaddr_in  peer_addr;

    socklen_t peer_addr_size;

    while(true)  {
        std::cout<<"aaaaaa"<<std::endl;
        int ss = accept(dhcp_s, (struct sockaddr *)  &peer_addr, &peer_addr_size);

        std::string ip = inet_ntoa(peer_addr.sin_addr);

        std::cout << "Recieved request from " << ip << std::endl;
        std::string vip;
        vip = addUser();
        std::cout << "Generated VIP is: " << vip << std::endl;
        std::cout << "Returning vip to the peer." << std::endl;
        send(ss, (void *) vip.c_str(), vip.size(), 0);
        close(ss);
    }
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
    std::cout<<"work"<<std::endl;

    char buffer[1024];
    sockaddr_in local, remote;
    unsigned short int port = 55555;
    int sock_fd, optval = 1;
    socklen_t remotelen;
    unsigned long int tap2net = 0;

    if ( (sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()");
        exit(1);
    }
    if(setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&optval, sizeof(optval)) < 0) {
        perror("setsockopt()");
        exit(1);
    }

    fcntl(sock_fd, F_SETFL, O_NONBLOCK);

    memset(&local, 0, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_port = htons(port);

    if (bind(sock_fd, (struct sockaddr*) &local, sizeof(local)) < 0) {
        perror("bind()");
        exit(1);
    }
    std::cerr << "SERVER OPENED" << std::endl;
    if (listen(sock_fd, 5) < 0) {
        perror("listen()");
        exit(1);
    }
    std::set<int> clients;
    clients.clear();


//
//    std::thread th(&Router::foo, &routers[routers.size()-1);
//    th.detach();

//    std::thread th(&Router::foo, this);
    std::thread th(&Router::foo, this);


    std::cout<<"проверка"<<std::endl;

/*    std::vector<int> array2 = { 10000, 10001, 10002 };
    for (int i ; i<array2.size(); i++)
        if(port != array2[i])
            connect_router(array2[i]);*/



    while (!shut) {
        // Заполняем множество сокетов
        remotelen = sizeof(remote);
        memset(&remote, 0, remotelen);
        fd_set readset;
        uint16_t nread, nwrite, plength;
        FD_ZERO(&readset);
        FD_SET(sock_fd, &readset);
        for(auto it: clients) {
            FD_SET(it, &readset);
        }


        std::cout<<"select"<<std::endl;
        // Ждём события в одном из сокетов
        int mx;
        if (clients.size() > 0) {
            mx = std::max(sock_fd, *max_element(clients.begin(), clients.end()));
        } else {
            mx = sock_fd;
        }
        if (select(mx + 1, &readset, NULL, NULL, NULL) <= 0) {
            perror("select");
            exit(3);
        }

        // Определяем тип события и выполняем соответствующие действия
        if (FD_ISSET(sock_fd, &readset)) {
            // Поступил новый запрос на соединение, используем accept
            int net_fd = accept(sock_fd, NULL, NULL);
            std::cerr << "SERVER: Client connected from " << inet_ntoa(remote.sin_addr) << std::endl;
            this->vip_table.end()->second=net_fd;
            fcntl(net_fd, F_SETFL, O_NONBLOCK);

            clients.insert(net_fd);
        }
        for(auto it: clients) {
            if(FD_ISSET(it, &readset)) {
                char buff[1024];
                recv(it,buff, sizeof(buff),0);
                std::cout<<buff<<std::endl;
                std::string destination = std::to_string((int(buff[0]) + 256) % 256) +
                                          "." + std::to_string((int(buff[1]) + 256) % 256) +
                                          "." + std::to_string((int(buff[2]) + 256) % 256) +
                                          "." + std::to_string((int(buff[3]) + 256) % 256);
                std::cout<<destination<<std::endl;
                std::cout<<buff[4]<<std::endl;
                send(vip_table[destination+"/32"], buff, 1024, 0);

            }
        }

    usleep(500);
    }
    close(sock_fd);
    th.join();

    for(auto it: clients) {
        close(it);
    }

}
std::string Router::generateVip() {
    std::cout << "Делаю айпи" << std::endl;
    return ip_area + std::to_string(ip_part++);
}

std::string Router::addUser() {
    std::cout << "Добавляю пользователя"  << std::endl;
    std::string vip = generateVip();
    this->vip_table[vip+"/32"] = 1233;
    vip = vip + "/24";
    return vip;
}

int Router::choiceUrSocket(std::string ip) {

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






int Router::connect_router (int port) {
    const char *SERVER_ADDR = "172.16.87.16";  // ip server

    int s = socket(AF_INET, SOCK_STREAM, 0);
    in_addr in;
    int res = inet_aton(SERVER_ADDR, &in);
    if (!res) {
        return -2;
    }


    sockaddr_in sockaddr_ = {
            .sin_family = AF_INET,
            .sin_port = htons(port),
            .sin_addr = in

    };
    std::cout<<"connect"<<std::endl;

    connect(s, (sockaddr*) &sockaddr_, sizeof(sockaddr_));
    return 0;

}
