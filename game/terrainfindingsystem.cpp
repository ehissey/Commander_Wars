#include "terrainfindingsystem.h"

#include "game/gamemap.h"

#include "coreengine/interpreter.h"

#include "coreengine/mainapp.h"

TerrainFindingSystem::TerrainFindingSystem(QString terrainID, qint32 startX, qint32 startY)
    : PathFindingSystem(startX, startY,
                        GameMap::getInstance()->getMapWidth(),
                        GameMap::getInstance()->getMapHeight()),
      m_terrainID(terrainID)
{
    Mainapp* pApp = Mainapp::getInstance();
    this->moveToThread(pApp->getWorkerthread());
    Interpreter::setCppOwnerShip(this);
}

qint32 TerrainFindingSystem::getRemainingCost(qint32, qint32, qint32)
{
    return 1;
}

bool TerrainFindingSystem::finished(qint32, qint32, qint32)
{
    return false;
}
qint32 TerrainFindingSystem::getCosts(qint32 index, qint32 x, qint32 y, qint32, qint32)
{
    if (movecosts[index][0] == infinite)
    {
        GameMap* pMap = GameMap::getInstance();
        if (pMap->onMap(x, y))
        {
            if (pMap->getTerrain(x, y)->getID() == m_terrainID)
            {
                movecosts[index][0] = 1;
                return movecosts[index][0];
            }
        }
        movecosts[index][0] = -1;
        return movecosts[index][0];
    }
    else
    {
        return movecosts[index][0];
    }
}

void TerrainFindingSystem::killTerrainFindingSystem()
{
    delete this;
}
