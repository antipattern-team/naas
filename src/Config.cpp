
#include "../include/Config.h"




void Config::read(std::vector <Data> &configVector) {

    Data data;
    std::ifstream fin("configFile.txt");
    while (!fin.eof()) {

        fin >> data.ip >> data.port;
        configVector.push_back(data);

    }
// splitting into 2 in case of recording into file
//    std::cout << "Ip of UI modules" << std::endl;
//    for (int i = 0; i <= configVector.size() - 1; ++i) {
//        std::cout << i + 1 << ") " << configVector[i].ip << "   " << configVector[i].port << std::endl;
//    }
    fin.close();

}
void Config::write(std::vector <Data> &configVector) {
    std::cout << "Ip of UI modules" << std::endl;
    for (int i = 0; i <= configVector.size() - 1; ++i) {
        std::cout << i + 1 << ") " << configVector[i].ip << "   " << configVector[i].port << std::endl;
    }
    void Config::record(std::vector <Data> &configVector, Data &Data) {
        authVector.push_back(Data);
        std::ofstream fout("configFile.txt", std::ios::app);
        fout<<Data.login<<" "<<Data.password<<std::endl;
        fout.close();
    }

}

