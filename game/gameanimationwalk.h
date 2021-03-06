#ifndef GAMEANIMATIONWALK_H
#define GAMEANIMATIONWALK_H

#include <QObject>

#include <QVector>

#include <QPoint>

#include "oxygine-framework.h"

#include "game/gameanimation.h"

#include "game/gamemap.h"

#include "game/GameEnums.h"

class Unit;

class GameAnimationWalk : public GameAnimation
{
    Q_OBJECT
public:
    explicit GameAnimationWalk(Unit* pUnit, QVector<QPoint> movePath);

signals:

public slots:
    /**
     * @brief loadSprite
     * @param spriteID the id of the sprite we want to create
     * @param addPlayerColor if the sprite should add some color
     * @param scaling scaling factor for the animation
     */
    void loadSprite(QString spriteID, bool addPlayerColor, float scaling);
    /**
     * @brief onFinished called when the animation has finished
     */
    virtual bool onFinished() override;
protected:
    /**
     * @brief getMovementDirection returns the movement direction of this unit
     * @param x current position
     * @param y current position
     * @param x2 next position
     * @param y2 next position
     * @return
     */
    GameEnums::Directions getMovementDirection(qint32 x, qint32 y, qint32 x2, qint32 y2);

private:
    Unit* m_pUnit;
    QVector<QPoint> m_movePath;
};

#endif // GAMEANIMATIONWALK_H
