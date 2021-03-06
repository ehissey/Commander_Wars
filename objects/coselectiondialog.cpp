#include "coselectiondialog.h"

#include "coreengine/mainapp.h"

#include "resource_management/objectmanager.h"

#include "resource_management/fontmanager.h"

#include "resource_management/cospritemanager.h"

#include "objects/coinfodialog.h"

#include "game/co.h"


COSelectionDialog::COSelectionDialog(QString coid, QColor color, qint32 player, QStringList coids)
    : QObject(),
      m_player(player)
{
    Mainapp* pApp = Mainapp::getInstance();
    this->moveToThread(pApp->getWorkerthread());
    ObjectManager* pObjectManager = ObjectManager::getInstance();
    oxygine::spBox9Sprite pSpriteBox = new oxygine::Box9Sprite();
    oxygine::ResAnim* pAnim = pObjectManager->getResAnim("codialog");
    pSpriteBox->setResAnim(pAnim);
    pSpriteBox->setSize(pApp->getSettings()->getWidth(), pApp->getSettings()->getHeight());
    pSpriteBox->setVerticalMode(oxygine::Box9Sprite::TILING_FULL);
    pSpriteBox->setHorizontalMode(oxygine::Box9Sprite::TILING_FULL);
    this->addChild(pSpriteBox);
    pSpriteBox->setPosition(0, 0);
    pSpriteBox->setPriority(static_cast<short>(Mainapp::ZOrder::Objects));
    this->setPriority(static_cast<short>(Mainapp::ZOrder::Dialogs));

    m_COSelection = new COSelection(coids);
    m_COSelection->colorChanged(color);
    m_COSelection->setPosition(30, 30);
    m_COSelection->setScale((pSpriteBox->getSize().x - 70) / (m_COSelection->getWidth() + 208));
    pSpriteBox->addChild(m_COSelection);
    if (m_COSelection->getScaledHeight() > pApp->getSettings()->getHeight() - 150)
    {
        m_COSelection->setScale((pApp->getSettings()->getHeight() - 150) / static_cast<float>(m_COSelection->getHeight()));
    }

    m_pCurrentCO = new oxygine::Sprite();
    m_pCurrentCO->setPosition(40 + m_COSelection->getScaledWidth(), 30);
    m_pCurrentCO->setScale(m_COSelection->getScale());
    pSpriteBox->addChild(m_pCurrentCO);
    selectedCOIDChanged(coid);

    connect(m_COSelection.get(), &COSelection::coSelected, this, &COSelectionDialog::selectedCOIDChanged);
    // ok button
    m_OkButton = pObjectManager->createButton(tr("Ok"), 150);
    m_OkButton->setPosition(pApp->getSettings()->getWidth() - m_OkButton->getWidth() - 30, pApp->getSettings()->getHeight() - 30 - m_OkButton->getHeight());
    pSpriteBox->addChild(m_OkButton);
    m_OkButton->addEventListener(oxygine::TouchEvent::CLICK, [ = ](oxygine::Event*)
    {
        emit editFinished(m_currentCOID, m_player);
        detach();
    });

    // cancel button
    m_ExitButton = pObjectManager->createButton(tr("Cancel"), 150);
    m_ExitButton->setPosition(30, pApp->getSettings()->getHeight() - 30 - m_OkButton->getHeight());
    pSpriteBox->addChild(m_ExitButton);
    m_ExitButton->addEventListener(oxygine::TouchEvent::CLICK, [ = ](oxygine::Event*)
    {
        emit canceled();
        detach();
    });

    // show co info button
    m_ShowCOInfoButton = pObjectManager->createButton(tr("Show CO Info"), 150);
    m_ShowCOInfoButton->setPosition(pApp->getSettings()->getWidth() / 2 - m_ShowCOInfoButton->getWidth() / 2, pApp->getSettings()->getHeight() - 30 - m_ShowCOInfoButton->getHeight());
    pSpriteBox->addChild(m_ShowCOInfoButton);
    m_ShowCOInfoButton->addEventListener(oxygine::TouchEvent::CLICK, [ = ](oxygine::Event*)
    {
        emit sigShowCOInfo();
    });
    connect(this, &COSelectionDialog::sigShowCOInfo, this, &COSelectionDialog::showCOInfo, Qt::QueuedConnection);
}

void COSelectionDialog::showCOInfo()
{
    QString coid = m_currentCOID;
    if (coid.isEmpty())
    {
        coid = COSpriteManager::getInstance()->getCOID(0);
    }
    Player* pPlayer = GameMap::getInstance()->getPlayer(m_player);
    spCO co = new CO(coid, pPlayer);
    addChild(new COInfoDialog(co, pPlayer, [=](spCO& pCurrentCO, spPlayer&, qint32 direction)
    {
        COSpriteManager* pCOSpriteManager = COSpriteManager::getInstance();
        qint32 index = pCOSpriteManager->getCOIndex(pCurrentCO->getCoID());
        index += direction;
        QString coid;
        if (index < 0)
        {
            coid = pCOSpriteManager->getCOID(pCOSpriteManager->getCOCount() - 1);
        }
        else if (index >= pCOSpriteManager->getCOCount())
        {
            coid = pCOSpriteManager->getCOID(0);
        }
        else
        {
            coid = pCOSpriteManager->getCOID(index);
        }
        pCurrentCO = new CO(coid, pPlayer);
    }, false));
}

void COSelectionDialog::selectedCOIDChanged(QString coid)
{
    Mainapp* pApp = Mainapp::getInstance();
    pApp->suspendThread();
    COSpriteManager* pCOSpriteManager = COSpriteManager::getInstance();
    oxygine::ResAnim* pAnim = nullptr;
    if (!coid.isEmpty())
    {
        pAnim = pCOSpriteManager->getResAnim((coid + "+nrm"));
    }
    m_pCurrentCO->setResAnim(pAnim);
    m_currentCOID = coid;
    pApp->continueThread();
}
