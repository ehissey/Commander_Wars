#ifndef TERRAIN_H
#define TERRAIN_H

#include <QObject>
#include <QVector>

#include "oxygine-framework.h"

#include "coreengine/fileserializable.h"

#include "game/unit.h"

#include "game/building.h"

class Player;
class TerrainFindingSystem;

class Terrain;
typedef oxygine::intrusive_ptr<Terrain> spTerrain;

class Terrain : public QObject, public oxygine::Actor, public FileSerializable
{
    Q_OBJECT
public:
    /**
     * @brief The DrawPriority enum z-priority for sprites
     */
    enum class DrawPriority
    {
        MarkedFieldMap,
        Terrain = 0,
        Shroud,
        Building,
        MarkedField,
        Arrow
    };
    static spTerrain createTerrain(QString terrainID, qint32 x, qint32 y, QString  currentTerrainID);

    virtual ~Terrain();

    void init();
    /**
     * @brief syncAnimation call this on all terrains to make their animation synchronized.
     */
    void syncAnimation();
    /**
     * @brief setBaseTerrain replace base terrain
     * @param terrain
     */
    void setBaseTerrain(spTerrain terrain);
    /**
     * @brief setUnit will place the units on this terrain ignoring all rules nullptr to delete it.
     * @param pUnit
     */
    void setUnit(spUnit pUnit);
    /**
     * @brief getUnit the unit on this terrain
     * @return
     */
    spUnit getSpUnit();
    /**
     * @brief setBuilding
     * @param pBuilding
     * @param * @param OnlyDownStream normally the terrain knows the building and vice versa for large buildings like black hole cannon. This rule doesn't apply only the terrain knows the building.
     */
    void setSpBuilding(spBuilding pBuilding, bool OnlyDownStream);
    spBuilding getSpBuilding();
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
        return 4;
    }
    /**
     * @brief update
     * @param us
     */
    virtual void update(const oxygine::UpdateState& us) override;

    /**
     * @brief getFixedSprite only avaible for ingame editor
     * @return
     */
    bool getFixedSprite() const;
    /**
     * @brief setFixedSprite only avaible for ingame editor
     * @return
     */
    void setFixedSprite(bool FixedSprite);
    /**
     * @brief getTerrainSpriteName only avaible for ingame editor
     * @return
     */
    QString getTerrainSpriteName() const;
    /**
     * @brief setTerrainSpriteName only avaible for ingame editor
     * @return
     */
    void setTerrainSpriteName(const QString &terrainSpriteName);
    /**
     * @brief setSpriteVisibility
     * @param value
     */
    void setSpriteVisibility(bool value);
public slots:
    /**
     * @brief getTerrainGroup
     * @return
     */
    qint32 getTerrainGroup();
    /**
     * @brief getDescription
     * @return
     */
    QString getDescription();
    /**
     * @brief loadSprites loads all sprites we won't to show. Updates all sprite data
     */
    void loadSprites();
    /**
     * @brief getMinimapIcon
     * @return
     */
    QString getMinimapIcon();
    /**
     * @brief getTerrainID
     * @return
     */
    QString getTerrainID() const;

    QString getTerrainName() const;
    void setTerrainName(const QString &value);

    qint32 getX() const;
    void setX(const qint32 &value);

    qint32 getHp() const;
    void setHp(const qint32 &value);

    qint32 getY() const;
    void setY(const qint32 &value);
    /**
     * @brief Terrain::getVision
     * @return
     */
    qint32 getVision();
    /**
     * @brief getBonusVision
     * @param pUnit
     * @return
     */
    qint32 getBonusVision(Unit* pUnit);
    /**
     * @brief getUnit the unit on this terrain
     * @return
     */
    Unit* getUnit();
    /**
     * @brief getBuilding the building on this terrain
     * @return
     */
    Building* getBuilding();
    /**
     * @brief createBaseTerrain creates the base terrain for this terrain if it's a nullptr
     */
    void createBaseTerrain(QString  currentTerrainID);
    /**
     * @brief loadBaseTerrain loads a base terrain with the given id
     * @param terrainID
     */
    void loadBaseTerrain(QString terrainID);
    /**
     * @brief loadBaseSprite loads the sprite for this terrain
     * @param spriteID
     */
    void loadBaseSprite(QString spriteID);
    /**
     * @brief getSurroundings returns a string containing the directions which fulfill the given rule
     * @param list the list as string split with ,
     * @param blacklist use black or whitelist for given arguments
     * @param searchType use GameMap::Directions here
     * @param useMapBorder if true the terrain is treated as searched terrain
     * @param useBuildingID if building ID's are used or only terrain id's
     * @param recursionCount how deep the game searches for base terrain id's -1 for infinite
     * @return
     */
    QString getSurroundings(QString list, bool useBaseTerrainID, bool blacklist, qint32 searchType, bool useMapBorder = true, bool useBuildingID = false, qint32 recursionCount = -1);
    /**
     * @brief loadOverlaySprite loads overlay sprites of this terrain
     * @param spriteID
     */
    void loadOverlaySprite(QString spriteID);
    /**
     * @brief getBaseTerrainID finds the base terrain id of the real base terrain recursivly
     * @return the base terrainID
     */
    inline QString getBaseTerrainID()
    {
        if (m_pBaseTerrain.get() != nullptr)
        {
            return m_pBaseTerrain->getBaseTerrainID();
        }
        else
        {
            return terrainID;
        }
    }
    /**
     * @brief getBaseTerrainID recursivly
     * @param count maximum recursion
     * @return
     */
    inline QString getBaseTerrainID(qint32 count)
    {
        if (m_pBaseTerrain.get() != nullptr &&
           ((count > 0) || (count < 0)))
        {
            return m_pBaseTerrain->getBaseTerrainID(count - 1);
        }
        else
        {
            return terrainID;
        }
    }
    /**
     * @brief getID the overall id of this terrain either terrain id or building id
     * @return
     */
    QString getID();
    /**
     * @brief setBuilding will place the building on this terrain ignoring all rules nullptr to delete it.
     * @param pBuilding
     */
    void setBuilding(Building* pBuilding);
    /**
     * @brief getFirerangeModifier
     * @param pUnit
     * @return
     */
    qint32 getFirerangeModifier(Unit* pUnit);
    /**
     * @brief removeBuilding
     */
    void removeBuilding();
    /**
     * @brief loadBuilding deletes the current building by loading the given building ID.
     * @param buildingID
     */
    void loadBuilding(QString buildingID);
    /**
     * @brief getDefense
     */
    qint32 getDefense(Unit* pUnit);
    /**
     * @brief getDefense
     */
    qint32 getBaseDefense();
    /**
     * @brief getVisionHide
     * @return
     */
    bool getVisionHide(Player* pPlayer);
    /**
     * @brief createTerrainFindingSystem
     * @return a path finding system that contains
     */
    TerrainFindingSystem* createTerrainFindingSystem();
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
     * @brief getTerrainSprites
     * @return
     */
    QStringList getTerrainSprites();
protected:
    /**
     * @brief createBuildingDownStream
     */
    void createBuildingDownStream();
    /**
     * @brief removeDownstream
     */
    void removeDownstream();
private:
    explicit Terrain(QString terrainID, qint32 x, qint32 y);
    /**
     * @brief terrainName terrain name shown in the game
     */
    QString terrainName;
    /**
     * @brief terrainID our terrain id
     */
    QString terrainID;
    /**
     * @brief m_pTerrainSprite actor holding our sprite data
     */
    oxygine::spSprite m_pTerrainSprite{nullptr};
    /**
     * @brief m_pOverlaySprites
     */
    QVector<oxygine::spSprite> m_pOverlaySprites;
    /**
     * @brief fixedSprite stores if the selected sprite is fixed or will be loaded based on the surrounding and random factors
     */
    bool m_FixedSprite{false};
    /**
     * @brief terrainSprite which terrain sprite we loaded
     */
    QString m_terrainSpriteName;
    /**
     * @brief m_SpriteAnim
     */
    oxygine::spResAnim m_SpriteAnim;
    /**
     * @brief loadSprite
     */
    bool loadSprite{false};
    /**
     * @brief m_pBaseTerrain base terrain of this terrain
     */
    spTerrain m_pBaseTerrain{nullptr};
    /**
     * @brief x coordinates in x direction in the map array
     */
    qint32 x{-1};
    /**
     * @brief y coordinates in y direction in the map array
     */
    qint32 y{-1};
    /**
      * the building at this position
      */
    spBuilding m_Building{nullptr};
    /**
      * the unit at this position
      */
    spUnit m_Unit{nullptr};
    /**
      * hp of this unit
      */
    qint32 hp{-1};

};

#endif // TERRAIN_H
