#ifndef LEDMANAGER_H
#define LEDMANAGER_H
#include "ledlight.h"
#include <QList>
#include <QTimer>

class ledmanager : public QObject
{
Q_OBJECT

    QList<ledlight*> lights1;
    QList<ledlight*> lights2;
    QList<ledlight*> lights3;
    QList<ledlight*> lights4;

    QList<QColor> colorMap;

    QTimer m_led1;
    QTimer m_led2;
    QTimer m_led3;
    QTimer m_led4;



    QColor& getNextColor(int idx);
    static int colorIdx;
public:

    ledmanager(int ledcnt);

    void asyncInit();

    QList<ledlight*>& getLights1() ;
    QList<ledlight*>& getLights2() ;
    QList<ledlight*>& getLights3() ;
    QList<ledlight*>& getLights4() ;


signals:

    void emitLed1(int, int);
    void emitLed2(int, int);
    void emitLed3(int, int);


private slots :
    void hTimeout1();
    void hTimeout2();
    void hTimeout3();
    void hTimeout4();

};

#endif // LEDMANAGER_H
