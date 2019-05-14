//
// Created by moira-q on 13.05.19.
//

#include <server/NetworkPool.h>


NetworkPool::NetworkPool() {

}

NetworkPool::~NetworkPool() {

}
void NetworkPool::listenConfig() {
    auto ip = "123.32.23.0/24";
    //this->createAndServRouter("123.32." + std::to_string(ip_part++) + ".12/24", this->port++);
    this->createAndServRouter(ip, this->port++);

}

bool NetworkPool::createAndServRouter(std::string ipRoutera, unsigned int port) {
    this->routers.emplace_back(ipRoutera, port);
    std::thread(routers[routers.size()-1].work());

    return false;
}




