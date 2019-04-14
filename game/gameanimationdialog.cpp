#include "gameanimationdialog.h"

#include "coreengine/mainapp.h"

#include "resource_management/gamemanager.h"
#include "resource_management/fontmanager.h"
#include "resource_management/cospritemanager.h"

GameAnimationDialog::GameAnimationDialog(quint32 frameTime)
    : GameAnimation (frameTime)
{
    Interpreter::setCppOwnerShip(this);

    connect(&finishTimer, &QTimer::timeout, this, &GameAnimationDialog::onFinished, Qt::QueuedConnection);

    Settings* pSetting = Mainapp::getInstance()->getSettings();

    float scale = 2.0f;

    GameManager* pGameManager = GameManager::getInstance();
    oxygine::ResAnim* pAnim = pGameManager->getResAnim("dialogfield+mask");
    m_TextMask = new oxygine::Sprite();
    m_TextMask->setScaleY(scale);
    m_TextMask->setScaleX(pSetting->getWidth() / pAnim->getWidth());
    m_TextMask->setResAnim(pAnim);
    addChild(m_TextMask);

    pAnim = pGameManager->getResAnim("dialogfield");
    m_TextBackground = new oxygine::Sprite();
    m_TextBackground->setScaleY(scale);
    m_TextBackground->setScaleX(pSetting->getWidth() / pAnim->getWidth());
    m_TextBackground->setResAnim(pAnim);
    addChild(m_TextBackground);

    oxygine::TextStyle style = FontManager::getMainFont();
    style.color = oxygine::Color(255, 255, 255, 255);
    style.vAlign = oxygine::TextStyle::VALIGN_DEFAULT;
    style.hAlign = oxygine::TextStyle::HALIGN_LEFT;
    style.multiline = true;

    oxygine::spClipRectActor pRect = new oxygine::ClipRectActor();
    pRect->setPosition(48 * scale + 5, 4 * scale);
    pRect->setSize(pSetting->getWidth() - pRect->getX(), 42 * scale);

    m_TextField = new oxygine::TextField();
    m_TextField->setPosition(0, -9);
    m_TextField->setScale(textScale);
    m_TextField->setSize(pRect->getWidth() / textScale - 2, pRect->getHeight());
    m_TextField->setStyle(style);
    pRect->addChild(m_TextField);
    addChild(pRect);

    m_COSprite = new oxygine::Sprite();
    m_COSprite->setScale(scale);
    m_COSprite->setX(1);
    addChild(m_COSprite);

    setPositionTop(false);
    textTimer.start();
}

void GameAnimationDialog::update(const oxygine::UpdateState& us)
{
    if (textTimer.elapsed() > textSpeed)
    {
        writePosition += 1;
        if (writePosition > m_Text.size())
        {
            writePosition = m_Text.size();
        }
        m_TextField->setText(m_Text.mid(0, writePosition).toStdString().c_str());
        float textHeight = m_TextField->getTextRect().getHeight();
        m_TextField->setHeight(textHeight);
        if (textHeight > 48)
        {
            m_TextField->setY((-textHeight + 48) * textScale - 9);
        }
        textTimer.start();
    }
    GameAnimation::update(us);
}


bool GameAnimationDialog::onFinished()
{
    if (writePosition >= m_Text.size())
    {
        return GameAnimation::onFinished();
    }
    else if (writePosition == m_Text.size())
    {
        writePosition = 0;
        if (writePosition >= m_Text.size())
        {
            if (autoFinishMs >= 0)
            {
                finishTimer.setSingleShot(true);
                finishTimer.start(autoFinishMs);
            }
        }
    }
    else
    {
        writePosition = m_Text.size();
    }
    return false;
}

void GameAnimationDialog::setPositionTop(bool value)
{
    if (value)
    {
        setY(0);
    }
    else
    {
        setY(Mainapp::getInstance()->getSettings()->getHeight() - m_TextBackground->getScaledHeight());
    }
}

void GameAnimationDialog::setColor(QColor color)
{
    m_TextMask->setColor(static_cast<quint8>(color.red()), static_cast<quint8>(color.green()), static_cast<quint8>(color.blue()), 255);
}

void GameAnimationDialog::setDialog(QString text)
{
    m_Text = text;
}

void GameAnimationDialog::setCO(QString coid, GameEnums::COMood mood)
{
    COSpriteManager* pCOSpriteManager = COSpriteManager::getInstance();
    QString resAnim = coid.toLower() + "+face";
    oxygine::ResAnim* pAnim = pCOSpriteManager->getResAnim(resAnim.toStdString().c_str());
    m_COSprite->setResAnim(pAnim, static_cast<qint32>(mood));
}

void GameAnimationDialog::setFinishDelay(qint32 valueMs)
{
    autoFinishMs = valueMs;
}

void GameAnimationDialog::setTextSpeed(qint32 speed)
{
    textSpeed = speed;
}