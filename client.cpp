#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <map>
#include <sstream>
#include <thread>
#include <csignal>
#include <sys/stat.h>
#include <vector>
#include <string>

#include "client/simpletun.h"


const char *SERVER_ADDR = "194.67.201.7";  // mb std::string
const int SERVER_PORT = 12345;
const int BUFF_SIZE = 4* 1024;
const char *tun_name = "vpn_tun";
int sock_fd;
int tap_fd;

bool is_everything_ok = true;

void create_tun(const std::string &vip) {
    std::string syscall = "bash scripts/tun.sh ";
    syscall += tun_name;
    syscall += " ";
    syscall += vip;
    system(syscall.c_str());
}

void delete_tun() {
    std::string syscall = "bash scripts/tun_del.sh ";
    syscall += tun_name;
    system(syscall.c_str());
}

void term_handler(int i){
    // int s = socket(AF_INET, SOCK_STREAM, 0);
    // in_addr in;
    // int res = inet_aton(SERVER_ADDR, &in);
    // if (!res) {
    //     exit;
    // }

    // sockaddr_in sockaddr_ = {
    //         .sin_family = AF_INET,
    //         .sin_port = htons(SERVER_PORT),
    //         .sin_addr = in
    // };
    // connect(s, (sockaddr*) &sockaddr_, sizeof(sockaddr_));
    // send(s, (void *)"disconnect", strlen("disconnect"), 0);

    // close(sock_fd);
    // close(tap_fd);
    // delete_tun();

    // exit(EXIT_SUCCESS);
    is_everything_ok = false;
}

int main() {


    // <-- получаешь айпишники серверов

    std::vector<std::string> ips;

    int pid = fork();

    

    if (pid == -1) // если не удалось запустить потомка
    {
        // выведем на экран ошибку и её описание
        printf("Error: Start Daemon failed (%s)\n", strerror(errno));

        return -1;
    }
    else if (!pid) // если это потомок
    {
        // создаём новый сеанс, чтобы не зависеть от родителя
        setsid();

        //
        printf("My pid is %i\n", getpid());

        // закрываем дискрипторы ввода/вывода/ошибок, так как нам они больше не понадобятся
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        //
        std::signal(SIGTERM, term_handler);

        std::vector<std::thread> threads;
        for (const auto& ip : ips) {
            threads.emplace_back(threadfunc, std::cref(ip)); // передай номер потока
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        return 0;
    }
    else // если это родитель
    {
        // завершим процес, т.к. основную свою задачу (запуск демона) мы выполнили
        return 0;
    }
}


void threadfunc(const std::string& addr) {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    in_addr in;
    int res = inet_aton(SERVER_ADDR, &in);
    // if (!res)
    // {
    //     return -2;
    // }

    sockaddr_in sockaddr_ = {
        .sin_family = AF_INET,
        .sin_port = htons(SERVER_PORT),
        .sin_addr = in};

    std::string request = "1";

    // -----------------------------------------

    connect(s, (sockaddr *)&sockaddr_, sizeof(sockaddr_));
    send(s, (void *)request.c_str(), strlen(request.c_str()), 0);

    char buff[BUFF_SIZE];
    int recv_bytes = recv(s, buff, BUFF_SIZE, 0);
    std::stringstream dhcp_input(buff);

    std::string vip;
    dhcp_input >> vip;

    // std::cout << buff << std::endl;

    // if (vip == "ERR")
    // {
    //     std::string error_type;
    //     dhcp_input >> error_type;
    //     std::cout << "Error occured: " << error_type << std::endl;
    //     return 55;
    // }
    close(s);

    create_tun(vip);
                                                                            // работай с интерфейсом vpn_tun(номер потока)
    connect_to_server("vpn_tun", SERVER_ADDR, sock_fd, tap_fd);

    delete_tun();                                                           // перепиши (наверное)
}