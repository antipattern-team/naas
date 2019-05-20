
#include "../include/ThreadTun.h"

int ThreadTun::connectToServ() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    in_addr in;
    int res = inet_aton(SERVER_ADDR, &in);
    if (!res) {
        return -2;
    }

    sockaddr_in sockaddr_ = {
            .sin_family = AF_INET,
            .sin_port = htons(SERVER_PORT),
            .sin_addr = in
    };
    connect(s, (sockaddr*) &sockaddr_, sizeof(sockaddr_));
    char buff[BUFF_SIZE];
    int recv_bytes = recv(s, buff, BUFF_SIZE, 0);
    std::stringstream dhcp_input(buff);

    std::string vip;
    dhcp_input >> vip;

    std::cout << buff << std::endl;

    if (vip == "ERR") {
        std::string error_type;
        dhcp_input >> error_type;
        std::cout << "Error occured: " << error_type << std::endl;
        return 55;
    }
    close(s);

    create_tun(vip);

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


        connect_to_server("vpn_tun", SERVER_ADDR, sock_fd, tap_fd);

        return 0;
    }
    else // если это родитель
    {
        // завершим процес, т.к. основную свою задачу (запуск демона) мы выполнили
        return 0;
    }
    return 0;
}

int ThreadTun::tun() {
    return 0;
}

void ThreadTun::create_tun(const std::string &vip) {
    std::string syscall = "bash scripts/tun.sh ";
    syscall += tun_name;
    syscall += " ";
    syscall += vip;
    system(syscall.c_str());

}

void ThreadTun::delete_tun() {
    std::string syscall = "bash scripts/tun_del.sh ";
    syscall += tun_name;
    system(syscall.c_str());

}

void ThreadTun::term_handler(int i) {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    in_addr in;
    int res = inet_aton(SERVER_ADDR, &in);
    if (!res) {
        exit;
    }

    sockaddr_in sockaddr_ = {
            .sin_family = AF_INET,
            .sin_port = htons(SERVER_PORT),
            .sin_addr = in
    };
    connect(s, (sockaddr*) &sockaddr_, sizeof(sockaddr_));
    send(s, (void *)"disconnect", strlen("disconnect"), 0);

    close(sock_fd);
    close(tap_fd);
    delete_tun();

    exit(EXIT_SUCCESS);

}

