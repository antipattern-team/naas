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


const char * SERVER_ADDR = "192.168.43.192";  // mb char* idk
const int SERVER_PORT = 12345;
const int SERVERS_PORT = 10000;
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
void threadfunc(const std::string& addr) {
    int s1 = socket(AF_INET, SOCK_STREAM, 0);
    in_addr inn;
    const char* c= addr.c_str(); //сокетовские библиотеки умеют или в char*, или в пакет, лучше уж char*
    int res = inet_aton(c, &inn);
    if (!res)
    {
        std::cout<<errno;
        exit;
    }

    sockaddr_in sockaddr_ = {
            .sin_family = AF_INET,
            .sin_port = htons(SERVERS_PORT), //счетчик сюда
            .sin_addr = inn
    };

    std::string request = "1";

    // -----------------------------------------
    std::cout<<"lol228   "<<addr<<"  "<< c << std::endl;

    connect(s1, (sockaddr*) &sockaddr_,  sizeof(sockaddr_));

    std::cout<<"lol7"<< std::endl;
    //send(s1, (void *)request.c_str(), strlen(request.c_str()), 0);

    char buff[BUFF_SIZE];
    recv(s1, buff, BUFF_SIZE, 0);
    std::stringstream dhcp_input(buff);

    std::string vip;
    dhcp_input >> vip;
//
//    // std::cout << buff << std::endl;
//
//    // if (vip == "ERR")
//    // {
//    //     std::string error_type;
//    //     dhcp_input >> error_type;
//    //     std::cout << "Error occured: " << error_type << std::endl;
//    //     return 55;
//    // }
//    close(s);
    std::cout<<"lol23222"<< std::endl;
    create_tun(vip);
    // записываем в название потока его номер
    auto name = "vpn_tun" + std::to_string(1);
    connect_to_server(name, c, sock_fd, tap_fd);

    delete_tun();
}

int main() {


    // <-- получаем айпишники серверов

    std::vector<std::string> ip(2);

    int s = socket(AF_INET, SOCK_STREAM, 0);
    in_addr in;
    int res = inet_aton(SERVER_ADDR, &in);
    if (!res) {
        return -1;
    }
    sockaddr_in sockaddr_ = {
            .sin_family = AF_INET,
            .sin_port = htons(SERVER_PORT),
            .sin_addr = in
    };
    int connection_result = connect(s, (sockaddr*) &sockaddr_, sizeof(sockaddr_));
    if (connection_result) {
        std::cout << connection_result << std::endl;
        std::cout << errno << "gg" << std::endl;


    }
    int n = 0;
    char buff[1024];
    ip[0] = "";

    std::cout<<"Hello world"<<std::endl;
    for(int i = 0; i <= n; i++) {
        std::cout<<"HUI"<<std::endl;
        recv(s, buff, sizeof(buff), 0);
        std::cout << buff << std::endl;
        std::string str = std::string(buff);
        std::cout<<str<<std::endl;
        ip[i] =  str;

        //sleep(0);
    }


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



        std::signal(SIGTERM, term_handler);
        int threadnumber = 1;
        close(s);
        std::vector<std::thread> threads(2);
        std::cout<<ip[0]<< std::endl;
        std::cout<<"lol5"<< std::endl;
        threads.emplace_back(threadfunc, std::cref(ip[0])); // передаем номер потока





        std::cout<<"lol6"<< std::endl;
        for (auto& thread : threads) {

            thread.join();
        }
        std::cout<<"lol"<< std::endl;
        close(STDIN_FILENO);
        std::cout<<"lol2"<< std::endl;
        close(STDOUT_FILENO);
        std::cout<<"lol3"<< std::endl;
        close(STDERR_FILENO);
        return 0;
    }
    else // если это родитель
    {
        // завершим процес, т.к. основную свою задачу (запуск демона) мы выполнили
        return 0;
    }
}