#ifndef TIMER_H
#define TIMER_H

#include "service.h"
#include <QDebug>

#include <QtWebSockets>
#include <QObject>
class timer : public QObject
{
    Q_OBJECT
public:
    timer();
public slots:
    void time();
};
#endif // TIMER_H
