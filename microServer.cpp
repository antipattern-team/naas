//
// Created by moira-q on 13.05.19.
//
#include "server/NetworkPool.h"

int main() {
    std::cout << "Начинаю работу" << std::endl;
    NetworkPool pool;
    pool.listenConfig();

    return 0;
}

