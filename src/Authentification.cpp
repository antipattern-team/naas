#include "Authentification.h"

void auth::read(std::vector <authData> &authVector) {
    authData data;
    std::ifstream fin("authFile.txt");
    while (!fin.eof()) {

        fin >> data.login >> data.password;
        authVector.push_back(data);
    }
    fin.close();
}
// splitted into 2 in case of recording into file
void auth::write(std::vector <authData> &authVector) {
    std::cout << "Log-pass list thus far" << std::endl;
    for (int i = 0; i <= authVector.size() - 1; ++i) {
        std::cout << i + 1 << ") " << authVector[i].login << "   " << authVector[i].password << std::endl;
    }
}
    void auth::record(std::vector <authData> &authVector, authData &Data) {
       authVector.push_back(Data);
       std::ofstream fout("authFile.txt", std::ios::app);
       fout<<Data.login<<" "<<Data.password<<std::endl;
       fout.close();
    }
