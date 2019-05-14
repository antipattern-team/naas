//
// Created by moira-q on 13.05.19.
//

#include <server/Router.h>

Router::Router() {

}

Router::~Router() {

}

bool Router::work() {
    int sock;
    int s = socket(AF_INET, SOCK_STREAM, 0);
    std::string vip;

    sockaddr_in sockaddr_ = {
            .sin_family = AF_INET,
            .sin_port = htons(12345),
    };
    bind(s, (sockaddr *) &sockaddr_, sizeof(sockaddr_));

    listen(s, 5);

    while(1) {
        sock = accept(s, NULL, NULL);

        vip = this->addUser(sock);

        send(sock, vip.c_str(), sizeof(vip), 0);
    }


    return false;

}

std::string Router::generateVip() {
    return "123.32." + std::to_string(ip_part++) + ".12/24";
}

std::string Router::addUser(const int sd) {

    std::string vip = generateVip();
    this->vip_table[sd] = vip;
    return vip;
}

/*bool Router::inTable(int sock_desk) {
    if(vip_table.find(sock_desk) != vip_table.end()) {
        //vip = network_list[network]->add_peer(password, ip);

        return false;
}*/

