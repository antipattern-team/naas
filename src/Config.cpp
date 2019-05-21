
#include "../include/Config.h"




void Config::read(std::vector <Data> &configVector) {

    Data data;
    std::ifstream fin("files/configFile.txt");
    while (!fin.eof()) {

        fin >> data.ip >> data.port;
        configVector.push_back(data);

    }
    std::cout << "kek " << std::endl;
    fin.close();

}
void Config::write(std::vector <Data> &configVector) {
    std::cout << "Ip of UI modules" << std::endl;
    for (int i = 0; i <= configVector.size() - 1; ++i) {
        std::cout << i + 1 << ") " << configVector[i].ip << "   " << configVector[i].port << std::endl;
    }


}

