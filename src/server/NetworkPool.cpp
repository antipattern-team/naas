//
// Created by moira-q on 13.05.19.
//

#include <server/NetworkPool.h>


NetworkPool::NetworkPool() {

}

NetworkPool::~NetworkPool() {

}
void NetworkPool::listenConfig() {
    auto ip = "123.32.23.0";
    std::cout << "Создаю РОутер"  << std::endl;
    this->createAndServRouter(ip, this->port++);

}

bool NetworkPool::createAndServRouter(std::string ipRoutera, unsigned int port) {
    this->routers.emplace_back(ipRoutera, port);
    std::cout << "Доабвляю роутер"  << std::endl;
    //std::thread th(routers[routers.size()-1].work());
    std::thread th(&Router::work, &routers[routers.size()-1]);
    th.join();

    return false;
}




