#ifndef CREDITSMENUE_H
#define CREDITSMENUE_H

#include <QObject>

#include "oxygine-framework.h"

#include <QObject>
#include <QVector>
#include <QTime>

class CreditsMenue : public QObject, public oxygine::Actor
{
    Q_OBJECT
public:
    explicit CreditsMenue();

    virtual void doUpdate(const oxygine::UpdateState&) override;
signals:
    void sigExitMenue();

public slots:
    void exitMenue();

private:
    QTime speedTimer;
    QVector<QString> m_Headlines;
    QVector<QVector<QString>> m_Authors;
    qint32 m_creditsHeigth{100};
    oxygine::spActor creditsActor;
};

#endif // CREDITSMENUE_H
