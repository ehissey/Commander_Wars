#ifndef VERYEASYAI_H
#define VERYEASYAI_H

#include "qvector.h"

#include "ai/coreai.h"
#include "ai/decisiontree.h"

class QmlVectorUnit;
class QmlVectorBuilding;
class QmlVectorPoint;
class Building;

class VeryEasyAI : public CoreAI
{
    Q_OBJECT
public:

    VeryEasyAI();
public slots:
    /**
     * @brief process
     */
    virtual void process() override;
protected:
    /**
     * @brief performActionSteps
     * @param pUnits
     * @param pEnemyUnits
     * @param pBuildings
     * @param pEnemyBuildings
     * @return
     */
    bool performActionSteps(QmlVectorUnit* pUnits, QmlVectorUnit* pEnemyUnits,
                            QmlVectorBuilding* pBuildings, QmlVectorBuilding* pEnemyBuildings);
    /**
     * @brief buildCOUnit
     * @param pUnits
     * @return
     */
    bool buildCOUnit(QmlVectorUnit* pUnits);
    /**
     * @brief captureBuildings
     * @param pUnits
     * @return
     */
    bool captureBuildings(QmlVectorUnit* pUnits);
    /**
     * @brief fireWithIndirectUnits
     * @param pUnits
     * @return
     */
    bool fireWithIndirectUnits(QmlVectorUnit* pUnits);
    /**
     * @brief fireWithDirectUnits
     * @param pUnits
     * @return
     */
    bool fireWithDirectUnits(QmlVectorUnit* pUnits);
    /**
     * @brief attack
     * @param pUnit
     * @return
     */
    bool attack(Unit* pUnit);
    /**
     * @brief moveUnits
     * @param pUnits
     * @param pBuildings
     * @param pEnemyUnits
     * @param pEnemyBuildings
     * @return
     */
    bool moveUnits(QmlVectorUnit* pUnits, QmlVectorBuilding* pBuildings,
                    QmlVectorUnit* pEnemyUnits, QmlVectorBuilding* pEnemyBuildings);

    bool moveTransporters(QmlVectorUnit* pUnits, QmlVectorUnit* pEnemyUnits, QmlVectorBuilding* pEnemyBuildings);

    /**
     * @brief loadUnits
     * @param pUnits
     * @return
     */
    bool loadUnits(QmlVectorUnit* pUnits);
    /**
     * @brief VeryEasyAI::moveUnit
     * @param pAction
     * @param pUnit
     * @param actions
     * @param targets
     * @param transporterTargets
     * @return
     */
    bool moveUnit(GameAction* pAction, Unit* pUnit, QStringList& actions,
                  QVector<QVector3D>& targets, QVector<QVector3D>& transporterTargets, bool unload = false);
    /**
     * @brief buildUnits
     * @param pBuildings
     * @param pUnits
     * @return
     */
    bool buildUnits(QmlVectorBuilding* pBuildings, QmlVectorUnit* pUnits);
    /**
     * @brief finishTurn
     */
    virtual void finishTurn() override;
protected:    
private:
    DecisionTree m_COUnitTree;
    DecisionTree m_GeneralBuildingTree;
    DecisionTree m_AirportBuildingTree;
    DecisionTree m_HarbourBuildingTree;
    bool rebuildIslandMaps{true};
};

#endif // VERYEASYAI_H
