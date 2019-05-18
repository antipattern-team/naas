//
// Created by moira-q on 13.05.19.
//

#include <server/NetworkPool.h>


NetworkPool::NetworkPool() {

}

NetworkPool::~NetworkPool() {

}

void NetworkPool::listenConfig() {
    std::cout << "Создаю РОутер"  << std::endl;
    this->createAndServRouter(basicVip + std::to_string(currentVip++) +".0/24", this->port++);

}

bool NetworkPool::createAndServRouter(std::string ipRoutera, unsigned int port) {
    this->routers.emplace_back(ipRoutera, port, basicVip + std::to_string(currentVip));
    //добавляется роутер(3 параметр это 122.120.текущее значение кастомайза)
    std::cout << "Доабвляю роутер"  << std::endl;
    //std::thread th(routers[routers.size()-1].work());
    std::thread th(&Router::work, &routers[routers.size()-1]);
    th.join();

    return false;
}




