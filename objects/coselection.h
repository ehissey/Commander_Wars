#ifndef COSELECTION_H
#define COSELECTION_H

#include <QObject>

#include <QStringList>

#include <QVector>

#include <QColor>

#include "oxygine-framework.h"

class COSelection;
typedef oxygine::intrusive_ptr<COSelection> spCOSelection;

class COSelection : public QObject, public oxygine::Actor
{
    Q_OBJECT
public:
    explicit COSelection(QStringList coids = {});
    virtual ~COSelection();

signals:
    void armySelectedChange(QString army);
    void coSelected(QString coid);
    void sigHoveredCOChanged(QString coid);
public slots:
    void colorChanged(QColor color);
    void armyChanged(QString army);
    void hoveredCOChanged(QString);
protected:
    void armyBannerClicked(QString army, qint32 index);
    void loadArmy(QString army, qint32& bannerX, qint32& y, qint32 i);
    void addCO(QString coid, QString COArmy, qint32 x, qint32 y, QString army);
private:
    QStringList m_Armies;
    QVector<oxygine::spSprite> m_ArmyBanners;
    oxygine::spSprite m_BackgroundMask;

    QVector<oxygine::spActor> m_COFields;
    oxygine::spSprite m_Cursor;
    QStringList m_CoIDs;
    QString m_CurrentCO;
    QColor m_CurrentColor;


    oxygine::spTextField m_COName;
    oxygine::spTextField m_COBio;
    oxygine::spSlidingActor m_COBioRect;
    oxygine::spTextField m_CODesc;
    oxygine::spSlidingActor m_CODescRect;
    oxygine::spTextField m_COPower;
    oxygine::spTextField m_COSuperpower;

    QStringList m_Coids;
};

#endif // COSELECTION_H
