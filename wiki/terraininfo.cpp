#include "terraininfo.h"

#include "resource_management/fontmanager.h"

#include "resource_management/movementtablemanager.h"

#include "resource_management/unitspritemanager.h"

#include "game/gamemap.h"

#include "game/player.h"

#include "game/co.h"

#include "ai/coreai.h"

TerrainInfo::TerrainInfo(Terrain* pTerrain, qint32 width)
    : QObject()
{
    Mainapp* pApp = Mainapp::getInstance();
    this->moveToThread(pApp->getWorkerthread());
    Interpreter::setCppOwnerShip(this);

    setWidth(width);

    oxygine::TextStyle style = FontManager::getMainFont();
    style.color = QColor(255, 255, 255, 255);
    style.vAlign = oxygine::TextStyle::VALIGN_DEFAULT;
    style.hAlign = oxygine::TextStyle::HALIGN_LEFT;
    style.multiline = true;
    QString name = pTerrain->getTerrainName();
    QString description = pTerrain->getDescription();
    Building* pBuilding = pTerrain->getBuilding();
    if (pBuilding != nullptr)
    {
        name = pBuilding->getName();
        description = pBuilding->getDescription();
    }
    // no the fun begins create checkboxes and stuff and a panel down here
    qint32 y = 0;
    oxygine::spTextField pLabel = new oxygine::TextField();
    pLabel->setStyle(style);
    pLabel->setHtmlText((tr("Terrain Information ") + name));
    pLabel->setScale(2.0f);
    pLabel->setPosition(width / 2 - pLabel->getTextRect().getWidth(), 0);
    addChild(pLabel);
    y += 60;

    pLabel = new oxygine::TextField();
    pLabel->setWidth(width - 10);
    pLabel->setStyle(style);
    pLabel->setHtmlText(description);
    pLabel->setScale(1.0f);
    pLabel->setPosition(0, y);
    addChild(pLabel);
    y += 20 + pLabel->getTextRect().getHeight();

    qint32 xOffset = 200;
    // Income
    pLabel = new oxygine::TextField();
    pLabel->setWidth(width - 10);
    pLabel->setStyle(style);
    pLabel->setHtmlText(tr("Defense:"));
    pLabel->setScale(1.0f);
    pLabel->setPosition(0, y);
    addChild(pLabel);
    pLabel = new oxygine::TextField();
    pLabel->setWidth(width - 10);
    pLabel->setStyle(style);
    pLabel->setHtmlText((QString::number(pTerrain->getDefense(nullptr))));
    pLabel->setScale(1.0f);
    pLabel->setPosition(xOffset, y);
    addChild(pLabel);
    y += 40;

    if (pBuilding != nullptr)
    {
        // Income
        pLabel = new oxygine::TextField();
        pLabel->setWidth(width - 10);
        pLabel->setStyle(style);
        pLabel->setHtmlText(tr("Income:"));
        pLabel->setScale(1.0f);
        pLabel->setPosition(0, y);
        addChild(pLabel);
        pLabel = new oxygine::TextField();
        pLabel->setWidth(width - 10);
        pLabel->setStyle(style);
        pLabel->setHtmlText((QString::number(pBuilding->getIncome())));
        pLabel->setScale(1.0f);
        pLabel->setPosition(xOffset, y);
        addChild(pLabel);
        y += 40;

        QStringList productionList = pBuilding->getConstructionList();
        if (productionList.size() > 0)
        {
            pLabel = new oxygine::TextField();
            pLabel->setStyle(style);
            if (pBuilding->getActionList().contains(CoreAI::ACTION_BUILD_UNITS))
            {
                pLabel->setHtmlText(tr("Builds and Supplies"));
            }
            else
            {
                pLabel->setHtmlText(tr("Supplies"));
            }
            pLabel->setScale(2.0f);
            pLabel->setPosition(width / 2 - pLabel->getTextRect().getWidth(), y);
            addChild(pLabel);
            y += 80;
            qint32 x = 0;
            GameMap* pMap = GameMap::getInstance();

            if (pMap != nullptr)
            {
                m_pPlayer = pMap->getSpCurrentPlayer();
            }
            if (m_pPlayer.get() == nullptr)
            {
                m_pPlayer = new Player();
                m_pPlayer->init();
            }
            for (qint32 i = 0; i < productionList.size(); i++)
            {
                spUnit pDummy = new Unit(productionList[i], m_pPlayer.get(), false);
                pDummy->setPosition(x, y);
                addChild(pDummy);
                x += GameMap::Imagesize * 2;
                if (x + GameMap::Imagesize * 2 > width && i < productionList.size() - 1)
                {
                    x = 0;
                    y += 40;
                }
            }
            y += 40;
        }
    }

    pLabel = new oxygine::TextField();
    pLabel->setStyle(style);
    pLabel->setHtmlText(tr("Movement Costs"));
    pLabel->setScale(2.0f);
    pLabel->setPosition(width / 2 - pLabel->getTextRect().getWidth(), y);
    addChild(pLabel);
    y += 60;

    MovementTableManager* pMovementTableManager = MovementTableManager::getInstance();
    qint32 x = 0;
    for (qint32 i = 0; i < pMovementTableManager->getMovementTableCount(); i++)
    {
        QString name = pMovementTableManager->getMovementName(pMovementTableManager->getMovementID(i));
        qint32 costs = pMovementTableManager->getBaseMovementPoints(pMovementTableManager->getMovementID(i), pTerrain, pTerrain, nullptr);

        pLabel = new oxygine::TextField();
        pLabel->setWidth(width);
        pLabel->setStyle(style);
        pLabel->setHtmlText((name + ":"));
        pLabel->setScale(1.0f);
        pLabel->setPosition(x, y);
        addChild(pLabel);
        pLabel = new oxygine::TextField();
        pLabel->setWidth(width);
        pLabel->setStyle(style);
        if (costs >= 0)
        {
            pLabel->setHtmlText(QString::number(costs));
        }
        else
        {
            pLabel->setHtmlText("-");
        }
        pLabel->setScale(1.0f);
        pLabel->setPosition(x + 120, y);
        addChild(pLabel);
        x += 170;
        if (x + 210 > width && i < pMovementTableManager->getMovementTableCount() - 1)
        {
            x = 0;
            y += 40;
        }
    }
    y += 40;
    setHeight(y);
}
