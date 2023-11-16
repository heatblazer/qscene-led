#include "userdatatimer.h"

userdatatimer::userdatatimer(const QList<ledlight *> &userdata, QObject *parent) :
    QTimer{parent}
{
    pLights = userdata;
    idx = 0;
}


void userdatatimer::hTimeout()
{
    static int  colidx=0;
    pLights[idx++ % pLights.count()]->setColor(getNextColor(colidx++));
}
