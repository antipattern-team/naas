//
// Created by moira-q on 13.05.19.
//
#include "server/NetworkPool.h"
#include <unistd.h>

int main() {
    std::cout << "Начинаю работу" << std::endl;
    NetworkPool pool;
    pool.listenConfig();
 /*   std::cout << "2 поток"  << std::endl;
    pool.listenConfig();
    std::cout << "3 поток"  << std::endl;
    pool.listenConfig();*/
    while(1){
        sleep(99999);

    }
    return 0;
}

