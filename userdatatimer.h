#ifndef USERDATATIMER_H
#define USERDATATIMER_H

#include "ledlight.h"
#include <QTimer>

class userdatatimer : public QTimer
{
    Q_OBJECT
    QList<ledlight*> pLights;
    int idx;

public:
    userdatatimer(const QList<ledlight *> &userdata, QObject* parent );

public slots:

    void hTimeout();

};

#endif // USERDATATIMER_H
