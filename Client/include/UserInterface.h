
/*юзер интерфейс - работа человека с клиентом, т.е. прем данные -> консоль, консоль -> отправка донные*/

#ifndef NAAS_USERINTERFACE_H
#define NAAS_USERINTERFACE_H

namespace ui {


    class Controller {
    public:
        int main(); // передает управление сразу какому-то начальному вью
        //changeView();

    private:
        //View[] views;
    };


    class View {
    public:
        //main();
    };


    class AuthView : View {
    public:
        //main();

    private:
        Controller controller;
        //состояние...;
    };


    class ConfigView : View {
    public:
        //main();

    private:
        Controller controller;
        //состояние...;
    };


};


#endif //NAAS_USERINTERFACE_H
