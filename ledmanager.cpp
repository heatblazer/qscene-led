#include "ledmanager.h"
#include <iostream>
#include <QRandomGenerator>
#include <QTcpSocket>

int ledmanager::colorIdx = 0;

QColor &ledmanager::getNextColor(int idx)
{
    return colorMap[idx++ % colorMap.count()];
}

ledmanager::ledmanager(int ledcnt, int leds, int w, int h)
{
    info.ledcnt = ledcnt;
    info.leds = leds;
    info.width = w;
    info.height = h;

    for(int i=0; i < 255; i++) {
        colorMap.append(QColor{qrand() % 0xff, qrand() % 0xff, qrand() % 0xff, 128});
    }

    lights.reserve(leds);
    for(int i=0 ; i < leds; i++) {
        lights.append(QList<ledlight*>{});
    }

    for(int i=0; i < leds; i++)
        lights[i].reserve(ledcnt);

    for(int i=0; i < leds; i++)
    {
        for(int j=0; j < ledcnt; j++) {
            ledlight *led = new ledlight;
            led->setRect(QRect{w*j+1, h * (i+1), w, h});
            lights[i].append(led);
        }
    }

    for(int i=0; i < ledcnt; i++)
    {
        timers.push_back(new userdatatimer{this});
    }
//
    for(int i=0; i < ledcnt; i++) {
//        QObject::connect(timers[i], SIGNAL(timeout()), this, SLOT(hTimeout()));
        timers[i]->setInterval((i+1) * 100);
    }
    pServer = new QTcpServer{this};
}

void ledmanager::asyncInit()
{
    QObject::connect(pServer, SIGNAL(newConnection()), this, SLOT(hConnection()));

    if (!pServer->listen(QHostAddress::Any, 12345)) {
        qDebug() << "ERROR, couln't listen to 12345";
    }
    for(int i=0; i < info.leds; i++)
    {
        timers[i]->start();
    }
}

QList<ledlight*> &ledmanager::getLedAt(unsigned int idx)
{
    if (idx >= 0 && idx < lights.size()) {
        return lights[idx];
    }
}


void ledmanager::hConnection()
{
    QTcpSocket *socket = pServer->nextPendingConnection();

    static char infodata[512] ;
    snprintf(infodata, sizeof(infodata), "Led lines [%d], leds per line [%d], Width = [%d], Height = [%d]\r\n",
             info.leds, info.ledcnt, info.width, info.height);
    socket->write(infodata);
    socket->flush();

    socket->waitForBytesWritten(3000);

    socket->close();
}

void ledmanager::hTimeout()
{
    static int rowidx=0,colidx=0, colormap=0;
    //auto it =
    lights[rowidx++ % info.leds][0]->setColor(getNextColor(colormap++)); //
//    for(int i=0; i < it.count(); i++) {
 //       it[i]->setColor(getNextColor(colormap++));
 //   }
}
