#include "qmlvector.h"

#include "coreengine/mainapp.h"

#include "ai/coreai.h"

QmlVectorPoint::QmlVectorPoint()
    : QObject()
{
    Mainapp* pApp = Mainapp::getInstance();
    this->moveToThread(pApp->getWorkerthread());
    Interpreter::setCppOwnerShip(this);
}

QmlVectorUnit::QmlVectorUnit()
    : QObject()
{
    Mainapp* pApp = Mainapp::getInstance();
    this->moveToThread(pApp->getWorkerthread());
    Interpreter::setCppOwnerShip(this);
}

void QmlVectorUnit::randomize()
{
    QVector<Unit*> randVector;
    while (m_Vector.size() > 0)
    {
        qint32 value = Mainapp::randInt(0, m_Vector.size() - 1);
        randVector.push_back(m_Vector[value]);
        m_Vector.removeAt(value);
    }
    m_Vector.swap(randVector);
}

void QmlVectorUnit::sortExpensive()
{
    QVector<Unit*> sortedVector;
    QVector<qint32> costs;
    for (qint32 i = 0; i < m_Vector.size(); i++)
    {
        costs.append(m_Vector[i]->getUnitValue());
    }
    while (m_Vector.size() > 0)
    {
        qint32 item = 0;
        qint32 value = std::numeric_limits<qint32>::lowest();
        for (qint32 i = 0; i < m_Vector.size(); i++)
        {
            if (costs[i] > value)
            {
                item = i;
                value = costs[i];
            }
        }
        sortedVector.append(m_Vector[item]);
        m_Vector.removeAt(item);
        costs.removeAt(item);
    }
    m_Vector.swap(sortedVector);
}

void QmlVectorUnit::sortShortestMovementRange(bool infantriesLast)
{
    QVector<Unit*> sortedVector;


    QVector<QVector<Unit*>> units;
    QVector<QVector<qint32>> costs;
    if (infantriesLast)
    {
        units.append(QVector<Unit*>());
        costs.append(QVector<qint32>());
        units.append(QVector<Unit*>());
        costs.append(QVector<qint32>());
        for (qint32 i = 0; i < m_Vector.size(); i++)
        {
            if (m_Vector[i]->getActionList().contains(CoreAI::ACTION_CAPTURE))
            {
                costs[1].append(m_Vector[i]->getMovementpoints(QPoint(m_Vector[i]->getX(), m_Vector[i]->getY())));
                units[1].append(m_Vector[i]);
            }
            else
            {
                costs[0].append(m_Vector[i]->getMovementpoints(QPoint(m_Vector[i]->getX(), m_Vector[i]->getY())));
                units[0].append(m_Vector[i]);
            }
        }
    }
    else
    {
        units.append(QVector<Unit*>());
        costs.append(QVector<qint32>());
        for (qint32 i = 0; i < m_Vector.size(); i++)
        {
            costs[0].append(m_Vector[i]->getMovementpoints(QPoint(m_Vector[i]->getX(), m_Vector[i]->getY())));
            units[0].append(m_Vector[i]);
        }
    }

    for (qint32 i2 = 0; i2 < units.size(); i2++)
    {
        while (units[i2].size() > 0)
        {
            qint32 item = 0;
            qint32 value = std::numeric_limits<qint32>::max();
            for (qint32 i = 0; i < units[i2].size(); i++)
            {
                if (costs[i2][i] < value)
                {
                    item = i;
                    value = costs[i2][i];
                }
            }
            sortedVector.append(units[i2][item]);
            units[i2].removeAt(item);
            costs[i2].removeAt(item);
        }
    }
    m_Vector.swap(sortedVector);
}

QmlVectorBuilding::QmlVectorBuilding()
    : QObject()
{
    Mainapp* pApp = Mainapp::getInstance();
    this->moveToThread(pApp->getWorkerthread());
    Interpreter::setCppOwnerShip(this);
}

void QmlVectorBuilding::randomize()
{
    QVector<Building*> randVector;
    while (m_Vector.size() > 0)
    {
        qint32 value = Mainapp::randInt(0, m_Vector.size() - 1);
        randVector.push_back(m_Vector[value]);
        m_Vector.removeAt(value);
    }
    m_Vector.swap(randVector);
}
