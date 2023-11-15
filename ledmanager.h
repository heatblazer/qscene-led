#ifndef LEDMANAGER_H
#define LEDMANAGER_H
#include "ledlight.h"
#include "userdatatimer.h"
#include <QList>
#include <QTcpServer>

class ledmanager : public QObject
{
Q_OBJECT
    QList<QList<ledlight*>> lights;
    QList<userdatatimer*>   timers;
    QList<QColor> colorMap;
    QTcpServer *pServer;

    static int colorIdx;
    struct {
        int ledcnt,leds,width,height;
    } info;

public:

    ledmanager(int ledcnt, int leds, int w, int h);
    void asyncInit();    
    QList<ledlight*>& getLedAt(unsigned int);


    static QColor& getNextColor(int idx);

signals:

private slots :
    void hConnection();
};

#endif // LEDMANAGER_H
