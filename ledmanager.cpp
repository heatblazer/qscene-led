#include "ledmanager.h"
#include <iostream>
#include <qrandom.h>


QColor &ledmanager::getNextColor(int idx)
{
    return colorMap[idx++ % colorMap.count()];
}

ledmanager::ledmanager(int ledcnt)
{
    for(int i=0; i < ledcnt; i++) {
        ledlight *led = new ledlight;
        led->setRect(QRect{15*i+1, 15, 15, 15});
        lights1.append(led);
    }

    for(int i=0; i < ledcnt; i++) {
        ledlight *led = new ledlight;
        led->setRect(QRect{15*i+1, 15* 2, 15, 15});
        lights2.append(led);
    }

    for(int i=0; i < ledcnt; i++) {
        ledlight *led = new ledlight;
        led->setRect(QRect{15*i+1, 15 * 3, 15, 15});
        lights3.append(led);
    }

    for(int i=0; i < ledcnt; i++) {
        ledlight *led = new ledlight;
        led->setRect(QRect{15*i+1, 15 * 4, 15, 15});
        lights4.append(led);
    }
    for(int i=0; i < 255; i++) {
        colorMap.append(QColor{qrand() % 0xff, qrand() % 0xff, qrand() % 0xff, 128});
    }


    QObject::connect(&m_led1, SIGNAL(timeout()), this, SLOT(hTimeout1()));
    QObject::connect(&m_led2, SIGNAL(timeout()), this, SLOT(hTimeout2()));
    QObject::connect(&m_led3, SIGNAL(timeout()), this, SLOT(hTimeout3()));
    QObject::connect(&m_led4, SIGNAL(timeout()), this, SLOT(hTimeout4()));


    m_led1.setInterval(200);
    m_led2.setInterval(300);
    m_led3.setInterval(400);
    m_led4.setInterval(100);

}

void ledmanager::asyncInit()
{
    m_led1.start();
    m_led2.start();
    m_led3.start();
    m_led4.start();
}



QList<ledlight *> &ledmanager::getLights1()
{
    return lights1;
}

QList<ledlight *> &ledmanager::getLights2()
{
    return lights2;
}

QList<ledlight *> &ledmanager::getLights3()
{
    return lights3;
}

QList<ledlight *> &ledmanager::getLights4()
{
    return lights4;
}

void ledmanager::hTimeout1()
{
    static int colidex=0,ledidx=0;

    lights1[ledidx++ % lights1.count()]->setColor(getNextColor(colidex++));
}

void ledmanager::hTimeout2()
{
    static int colidex=0,ledidx=0;
    lights2[ledidx++ % lights2.count()]->setColor(getNextColor(colidex++));
}

void ledmanager::hTimeout3()
{
    static int colidex=0,ledidx=0;
    lights3[ledidx++ % lights3.count()]->setColor(getNextColor(colidex++));

}

void ledmanager::hTimeout4()
{
    static int colidex=0,ledidx=0;
    lights4[ledidx++ % lights4.count()]->setColor(getNextColor(colidex++));
}
