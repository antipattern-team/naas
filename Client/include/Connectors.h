
/*обмен данными между клиентом и остальными сервисами (конфиг, коннект, аутх)*/

#ifndef NAAS_CONNECTORS_H
#define NAAS_CONNECTORS_H


namespace connectors {


    class Controller() {
    public:
    Controller(config::Config config);

    connectAll();
    disconnectAll();

    getAuthConnector();
    getConfigConnector();

    private:
    Connector[] connectors;
}


class Connector {
protected:
    connect();
    disconnect();
}


class AuthConnector : Connector {
public:
    AuthConnector(config::Config config);
    auth(login, password);

protected:
    connect();
    disconnect();

private:
    соединение;
};


class ConfigConnector : Connector {
public:
    ConfigConnector(config::Config config);
    fetchConfig();
    saveConfig(config);

protected:
    connect();
    disconnect();

private:
    соединение;
};


}


#endif //NAAS_CONNECTORS_H
