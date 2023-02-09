#ifndef APP_H
#define APP_H

#include <QObject>

class App:public QObject{
    Q_OBJECT
public:
    App(){};
    ~App(){};
    Q_INVOKABLE void showAbout();
};

#endif //APP_H
