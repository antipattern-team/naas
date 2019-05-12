#include "include/Config.h"


int main(){
    config::Config config;
    config.read();

    connectors::Controller connController;
    connController.connectAll();

    ui::Controller uiController(connController);
    uiController.main();

}