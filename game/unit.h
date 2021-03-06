#ifndef UNIT_H
#define UNIT_H

#include <QObject>
#include <QVector>
#include "oxygine-framework.h"

#include "coreengine/fileserializable.h"
#include "coreengine/scriptvariables.h"

#include "game/GameEnums.h"

class GameAction;

class Player;
class Terrain;
class Unit;
typedef oxygine::intrusive_ptr<Unit> spUnit;

class Unit : public QObject, public oxygine::VStyleActor, public FileSerializable
{
    Q_OBJECT
public:
    static const float animationSpeed;

    enum class Priorities
    {
        Waiting = 10,
        Icons = 20
    };

    enum ModdingFlags
    {
        None = 0x0,
        FlagAmmo1 = 0x1,
        FlagAmmo2 = 0x2,
        FlagFuel = 0x4,
    };

    /**
     * @brief Unit only for deserialization
     */
    explicit Unit();

    explicit Unit(QString unitID, Player* pOwner, bool aquireId);

    virtual ~Unit();
    /**
     * @brief setTerrain
     * @param pTerrain smart pointer to the terrain this building is placed on
     */
    void setTerrain(Terrain* pTerrain);
    /**
     * @brief serialize stores the object
     * @param pStream
     */
    virtual void serializeObject(QDataStream& pStream) override;
    /**
     * @brief deserialize restores the object
     * @param pStream
     */
    virtual void deserializeObject(QDataStream& pStream) override;
    /**
     * @brief getVersion stream version for serialization
     * @return
     */
    inline virtual qint32 getVersion() override
    {
        return 12;
    }


    /**
     * @brief initUnit loads all default unit value
     */
    void initUnit();

    /**
     * @brief getActionList
     * @return the string id list of actions this units can perform
     */
    QStringList getActionList();
    /**
     * @brief hasAction
     * @param action
     * @return
     */
    bool hasAction(QString action);
    /**
     * @brief updateIcons updates icons that can be modified by the co.
     * E.g Transport sign and health point sign
     */
    void updateIcons(Player* pPlayer);
    /**
     * @brief setModdingFlags
     * @param value
     */
    void setModdingFlags(ModdingFlags value);
    /**
     * @brief getModdingFlags
     * @return
     */
    Unit::ModdingFlags getModdingFlags() const;
    /**
     * @brief applyMod
     */
    void applyMod();

    void setVirtuellX(qint32 value)
    {
        virtuellX = value;
    }
    void setVirtuellY(qint32 value)
    {
        virtuellY = value;
    }
    QVector<QPoint> getMultiTurnPath() const;
    void setMultiTurnPath(const QVector<QPoint> &MultiTurnPath);
signals:

public slots:
    /**
     * @brief postBattleActions
     * @param damage
     * @param pUnit
     * @param gotAttacked
     */
    void postBattleActions(float damage, Unit* pUnit, bool gotAttacked);
    /**
     * @brief getDescription
     * @return
     */
    QString getDescription();
    /**
     * @brief hasWeapons
     * @return
     */
    bool hasWeapons();
    /**
     * @brief getUniqueID
     * @return returns the map wide unique id of this unit.
     */
    qint32 getUniqueID() const;
    /**
     * @brief spawnUnit
     * @param unitID
     * @return
     */
    Unit* spawnUnit(QString unitID);
    /**
     * @brief getAiMode
     * @return
     */
    GameEnums::GameAi getAiMode() const;
    /**
     * @brief setAiMode
     * @param AiMode
     */
    void setAiMode(const GameEnums::GameAi &AiMode);
    /**
     * @brief getTransportHidden
     * @param pPlayer
     * @return if the transported units of this unit are hidden from the given player
     */
    bool getTransportHidden(Player* pPlayer);
    /**
     * @brief getHpHidden
     * @param pPlayer
     * @return
     */
    bool getHpHidden(Player* pPlayer);
    /**
     * @brief getIgnoreUnitCollision
     * @return
     */
    bool getIgnoreUnitCollision() const;
    /**
     * @brief setIgnoreUnitCollision
     * @param IgnoreUnitCollision
     */
    void setIgnoreUnitCollision(bool IgnoreUnitCollision);
    /**
     * @brief getName
     * @return
     */
    QString getName();
    /**
     * @brief Unit::getUnitType
     * @return
     */
    GameEnums::UnitType getUnitType();
    /**
     * @brief getTerrainDefenseModifier the bonus defense for this unit
     * @return
     */
    qint32 getTerrainDefenseModifier(QPoint position);
    /**
     * @brief getFirstStrike
     * @param position
     * @return
     */
    bool getFirstStrike(QPoint position, Unit* pAttacker);
    /**
     * @brief getMovementpoints the movement points this unit can move
     * @param position
     * @return
     */
    qint32 getMovementpoints(QPoint position);
    /**
     * @brief getBonusMovementpoints
     * @param position
     * @return
     */
    qint32 getBonusMovementpoints(QPoint position);
    /**
     * @brief getBaseMovementPoints the base movement points of this unit
     * @return
     */
    qint32 getBaseMovementPoints() const;
    /**
     * @brief setBaseMovementPoints the base movement points of this unit
     * @param value
     */
    void setBaseMovementPoints(const qint32 &value);
    /**
     * @brief getBaseMovementCosts
     * @param x
     * @param y
     */
    qint32 getBaseMovementCosts(qint32 x, qint32 y, qint32 curX = -1, qint32 curY = -1);
    /**
     * @brief getMovementCosts
     * @param x
     * @param y
     */
    qint32 getMovementCosts(qint32 x, qint32 y, qint32 curX = -1, qint32 curY = -1);

    float getHp() const;
    void setHp(const float &value);
    qint32 getHpRounded() const;

    qint32 getAmmo1() const;
    void setAmmo1(const qint32 &value);
    bool hasAmmo1() const;
    void reduceAmmo1(qint32 value);

    qint32 getMaxAmmo1() const;
    void setMaxAmmo1(const qint32 &value);

    QString getWeapon1ID() const;
    void setWeapon1ID(const QString &value);

    qint32 getAmmo2() const;
    void setAmmo2(const qint32 &value);
    bool hasAmmo2() const;
    void reduceAmmo2(qint32 value);

    qint32 getMaxAmmo2() const;
    void setMaxAmmo2(const qint32 &value);

    QString getWeapon2ID() const;
    void setWeapon2ID(const QString &value);

    qint32 getFuel() const;
    void setFuel(const qint32 &value);

    qint32 getMaxFuel() const;
    void setMaxFuel(const qint32 &value);

    qint32 getCapturePoints() const;
    void setCapturePoints(const qint32 &value);

    qint32 getCosts() const;

    qint32 getMinRange() const;
    void setMinRange(const qint32 &value);

    qint32 getMaxRange(QPoint position);
    qint32 getBaseMaxRange();
    qint32 getMaxRangeAtPosition(QPoint position);
    qint32 getBonusMaxRange(QPoint position);
    void setMaxRange(const qint32 &value);

    bool getHidden() const;
    void setHidden(bool Hidden);
    /**
     * @brief isStealthed checks if the unit is invisible for the given player. Either by terrain, Out of Vision or Stealthmode
     * @param pPlayer
     * @return
     */
    bool isStealthed(Player* pPlayer, bool ignoreOutOfVisionRange = false, qint32 testX = -1, qint32 testY = -1);

    GameEnums::UnitRanks getUnitRank() const;
    void setUnitRank(const GameEnums::UnitRanks &UnitRank);

    qint32 getVision(QPoint position);
    void setVision(const qint32 &value);
    qint32 getBaseVision();
    /**
     * @brief loadSprites loads the given sprite
     * @param spriteID
     */
    void loadSprite(QString spriteID, bool addPlayerColor);
    /**
     * @brief addShineTween
     */
    void addShineTween();
    /**
     * @brief removeShineTween
     */
    void removeShineTween();
    /**
     * @brief setOwner changes the owner ship of this unit
     * @param pOwner
     */
    void setOwner(Player* pOwner);
    /**
     * @brief getOwner
     * @return the pointer to the owner of this unit
     */
    Player* getOwner();
    /**
     * @brief getMovementType the movement type id
     * @return
     */
    QString getMovementType();
    /**
     * @brief setMovementType
     * @param Movementtype
     */
    void setMovementType(const QString &movementType);;
    /**
     * @brief getLoadingPlace
     * @return
     */
    qint32 getLoadingPlace();
    /**
     * @brief getUnitID the unit id
     * @return
     */
    QString getUnitID();
    /**
     * @brief getUnitDamageID
     * @return
     */
    QString getUnitDamageID();
    /**
     * @brief getUnitDamage
     * @param weaponID
     * @return
     */
    float getUnitDamage(QString weaponID);
    /**
     * @brief getX
     * @return  x coordinates of this unit
     */
    qint32 getX() const;
    /**
     * @brief getY
     * @return  y coordinates of this unit
     */
    qint32 getY() const;
    /**
     * @brief getPosition the unit position as qpoint
     * @return
     */
    QPoint getPosition() const
    {
        return QPoint(getX(), getY());
    }
    /**
     * @brief refill fills up all ammo and fuel to max
     */
    void refill();

    /**
     * @brief setHasMoved  changes if the unit has been moved or not
     * @param value
     */
    void setHasMoved(bool value);
    /**
     * @brief getHasMoveed return if this unit has moved or not
     * @return
     */
    bool getHasMoved();
    /**
     * @brief getMovementFuelCostModifier fuel modification when moving this unit from a to b
     * @param fuelCost
     * @return
     */
    qint32 getMovementFuelCostModifier(qint32 fuelCost);
    /**
     * @brief moveUnit moves the unit to the target position of this unit
     * @param pAction
     */
    void moveUnitAction(GameAction* pAction);
    /**
     * @brief moveUnit moves the unit to the target path
     * @param movePath
     */
    void moveUnit(QVector<QPoint> movePath);
    /**
     * @brief moveUnitToField
     * @param x
     * @param y
     */
    void moveUnitToField(qint32 x, qint32 y);
    /**
     * @brief showCORange
     */
    void showCORange();
    /**
     * @brief removeUnit removes this from game
     */
    void removeUnit(bool killed = true);
    /**
     * @brief killUnit removes the unit from the game and let it explode
     */
    void killUnit();
    /**
     * @brief increaseCapturePoints increases the capture points of this unit based on units hp and ko owner
     */
    void increaseCapturePoints(QPoint position);
    /**
     * @brief loadIcon
     * @param iconID icon we want to load
     * @param x position of the icon
     * @param y position of the icon
     */
    void loadIcon(QString iconID, qint32 x, qint32 y);
    /**
     * @brief unloadIcon removes the given icon from this unit
     * @param iconID
     */
    void unloadIcon(QString iconID);
    /**
     * @brief startOfTurn
     */
    void startOfTurn();
    /**
     * @brief getTerrain
     * @return
     */
    Terrain* getTerrain();
    /**
     * @brief canMoveAndFire
     * @return if this unit can move and fire
     */
    bool canMoveAndFire(QPoint position);
    /**
     * @brief loadUnit adds a unit to the transport list
     * @param pUnit
     */
    void loadUnit(Unit* pUnit);
    /**
     * @brief getLoadedUnit
     * @param index
     */
    Unit* getLoadedUnit(qint32 index);
    /**
     * @brief unloadUnit removes a unit from the transport list
     * @param index
     */
    void unloadUnit(Unit* pUnit, QPoint position);
    /**
     * @brief unloadUnit
     * @param index
     * @param position
     */
    void unloadUnitAtIndex(qint32 index, QPoint position);
    /**
     * @brief getLoadedUnitCount
     * @return number of units loaded by this unit
     */
    qint32 getLoadedUnitCount();
    /**
     * @brief getTransportUnits
     * @return
     */
    QStringList getTransportUnits();
    /**
     * @brief canTransportUnit
     * @return checks if we have space and if the unit can be transported by this unit.
     */
    bool canTransportUnit(Unit* pUnit, bool ignoreLoadingPlace = false);
    /**
     * @brief postAction
     * @param pAction
     */
    void postAction();
    /**
     * @brief getBonusOffensive
     * @param position
     * @return offensive bonus at this position
     */
    qint32 getBonusOffensive(QPoint position, Unit* pDefender, QPoint defPosition, bool isDefender);
    /**
     * @brief getUnitBonusOffensive
     * @param position
     * @param pDefender
     * @param defPosition
     * @param isDefender
     * @return
     */
    qint32 getUnitBonusOffensive(QPoint position, Unit* pDefender, QPoint defPosition, bool isDefender);
    /**
     * @brief getDamageReduction
     * @param pAttacker
     * @param position
     * @param pDefender
     * @param defPosition
     * @param isDefender
     * @return
     */
    float getDamageReduction(float damage, Unit* pAttacker, QPoint position, qint32 attackerBaseHp,
                              QPoint defPosition, bool isDefender, GameEnums::LuckDamageMode luckMode);
    /**
     * @brief getTrueDamage
     * @param damage
     * @param position
     * @param attackerBaseHp
     * @param pDefender
     * @param defPosition
     * @param isDefender
     * @return
     */
    float getTrueDamage(float damage, QPoint position, qint32 attackerBaseHp,
                        Unit* pDefender, QPoint defPosition, bool isDefender);
    /**
     * @brief getTerrainDefense
     * @return
     */
    qint32 getTerrainDefense();
    /**
     * @brief getBonusDeffensive
     * @param position
     * @return defense bonus at this position
     */
    qint32 getBonusDefensive(QPoint position, Unit* pAttacker, QPoint atkPosition, bool isDefender);
    /**
     * @brief getUnitBonusDefensive
     * @param position
     * @param pAttacker
     * @param atkPosition
     * @param isDefender
     * @return
     */
    qint32 getUnitBonusDefensive(QPoint position, Unit* pAttacker, QPoint atkPosition, bool isDefender);
    /**
     * @brief useTerrainDefense
     * @return
     */
    bool useTerrainDefense();
    /**
     * @brief getAttackHpBonus
     * @param position
     * @return
     */
    qint32 getAttackHpBonus(QPoint position);
    /**
     * @brief getMisfortune
     * @param position
     * @return
     */
    qint32 getBonusMisfortune(QPoint position);
    /**
     * @brief getLuck
     * @param position
     * @return
     */
    qint32 getBonusLuck(QPoint position);
    /**
     * @brief getUnitCosts
     * @return
     */
    qint32 getUnitCosts();
    /**
     * @brief getRepairBonus
     * @return
     */
    qint32 getRepairBonus(QPoint position);
    /**
     * @brief setUnitVisible
     * @param value
     */
    void setUnitVisible(bool value);
    /**
     * @brief makeCOUnit
     * @param co
     */
    void makeCOUnit(quint8 co);
    /**
     * @brief createCORange
     */
    void createCORange(qint32 coRange);
    /**
     * @brief updateSprites reloads all sprites
     */
    void updateSprites();
    /**
     * @brief getFuelCostModifier
     * @param pUnit
     * @param costs
     * @return
     */
    qint32 getFuelCostModifier(QPoint position, qint32 costs);
    /**
     * @brief getVariables
     * @return
     */
    inline ScriptVariables* getVariables()
    {
        return &m_Variables;
    }
    /**
     * @brief getTerrainAnimationBase
     * @return
     */
    QString getTerrainAnimationBase();
    /**
     * @brief getTerrainAnimationForeground
     * @return
     */
    QString getTerrainAnimationForeground();
    /**
     * @brief getTerrainAnimationBackground
     * @return
     */
    QString getTerrainAnimationBackground();
    /**
     * @brief isAttackable
     * @param pDefender
     * @return
     */
    bool isAttackable(Unit* pDefender, bool ignoreOutOfVisionRange = false);
    /**
     * @brief isEnvironmentAttackable
     * @param terrainID
     * @return
     */
    bool isEnvironmentAttackable(QString terrainID);
    /**
     * @brief canMoveOver
     * @param x
     * @param y
     * @return
     */
    bool canMoveOver(qint32 x, qint32 y);
    /**
     * @brief getUnitValue the value of the unit -> which is unit cost * hp / 10
     * @return
     */
    qint32 getUnitValue();
    /**
     * @brief canBeRepaired
     * @return
     */
    bool canBeRepaired(QPoint position);
    /**
     * @brief addOffensiveBonus
     * @param value
     * @param duration
     */
    void addOffensiveBonus(qint32 value, qint32 duration = 1);
    /**
     * @brief addDefensiveBonus
     * @param value
     * @param duration
     */
    void addDefensiveBonus(qint32 value, qint32 duration = 1);
    /**
     * @brief addVisionBonus
     * @param value
     * @param duration
     */
    void addVisionBonus(qint32 value, qint32 duration = 1);
    /**
     * @brief addMovementBonus
     * @param value
     * @param duration
     */
    void addMovementBonus(qint32 value, qint32 duration = 1);
    /**
     * @brief addFirerangeBonus
     * @param value
     * @param duration
     */
    void addFirerangeBonus(qint32 value, qint32 duration = 1);
    /**
     * @brief modifyUnit
     * @param hpChange
     * @param ammo1Change
     * @param ammo2Change
     * @param fuelChange
     */
    void modifyUnit(qint32 hpChange, qint32 ammo1Change, qint32 ammo2Change, qint32 fuelChange);
protected:
    /**
     * @brief updateIconTweens creates the visibility toogle tweens for all icons
     */
    void updateIconTweens();
    /**
     * @brief updateBonus
     * @param data
     */
    void updateBonus(QVector<QPoint>& data);
    /**
     * @brief getBonus
     * @param data
     * @return
     */
    qint32 getBonus(QVector<QPoint>& data);


private:
    QVector<oxygine::spSprite> m_pUnitWaitSprites;
    QVector<oxygine::spSprite> m_pUnitSprites;
    /**
     * @brief m_pIconSprites vector containg all icon sprites
     */
    QVector<oxygine::spSprite> m_pIconSprites;
    /**
     * @brief m_CORange
     */
    oxygine::spActor m_CORange;
    /**
     * @brief m_UnitID the id of this unit
     */
    QString m_UnitID;
    /**
     * @brief m_Owner our owner a nullptr means we're a neutral building
     */
    Player* m_pOwner{nullptr};
    /**
     * @brief m_Terrain the terrain at which we are placed
     */
    Terrain* m_pTerrain{nullptr};
    // basic data of this unit
    float hp{10};
    qint32 ammo1{-1};
    qint32 maxAmmo1{-1};
    QString weapon1ID;
    qint32 ammo2{-1};
    qint32 maxAmmo2{-1};
    QString weapon2ID;
    qint32 fuel{-1};
    qint32 maxFuel{-1};
    qint32 baseMovementPoints{0};
    bool m_Moved{false};
    QVector<spUnit> m_TransportUnits;
    qint32 capturePoints{0};
    GameEnums::UnitRanks m_UnitRank{GameEnums::UnitRank_None};

    bool m_Hidden{false};

    bool m_IgnoreUnitCollision{false};

    qint32 minRange{1};
    qint32 maxRange{-1};
    qint32 vision{1};
    qint32 m_UniqueID{0};
    GameEnums::GameAi m_AiMode{GameEnums::GameAi::GameAi_Normal};
    ScriptVariables m_Variables;
    ModdingFlags m_ModdingFlags{ModdingFlags::None};

    qint32 virtuellX{-1};
    qint32 virtuellY{-1};

    QVector<QPoint> m_MultiTurnPath;
    oxygine::spTween m_ShineTween;
    QString m_MovementType;

    QVector<QPoint> m_OffensiveBonus;
    QVector<QPoint> m_DefensiveBonus;
    QVector<QPoint> m_VisionBonus;
    QVector<QPoint> m_MovementBonus;
    QVector<QPoint> m_FirerangeBonus;
};

#endif // UNIT_H

