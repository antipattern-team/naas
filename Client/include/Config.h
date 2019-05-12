
/*начало начал*/
/*туть хранятся данные необходимые для подключения к (конфиг, коннект, аутх) */

#ifndef NAAS_CONFIG_H
#define NAAS_CONFIG_H


namespace config {


    class Config {
    public:
        read();
    private:
        const char* configFile = "files/ConfigFile.txt";

    };


}


#endif //NAAS_CONFIG_H
