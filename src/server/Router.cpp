//
// Created by moira-q on 13.05.19.
//

#include <server/Router.h>
#include <iostream>

Router::Router() {

}

Router::~Router() {

}

void Router::work() {
    int sock;
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

