#include "mapselection.h"

#include "coreengine/mainapp.h"
#include "resource_management/objectmanager.h"
#include "resource_management/fontmanager.h"

#include "game/gamemap.h"

#include "QDir"

MapSelection::MapSelection(qint32 heigth, qint32 width, QString folder)
    : QObject()
{
    oxygine::spButton pArrowUp = new oxygine::Button();
    oxygine::ResAnim* pAnim = ObjectManager::getInstance()->getResAnim("arrow+down");
    pArrowUp->setResAnim(pAnim);
    pArrowUp->setPriority(static_cast<short>(Mainapp::ZOrder::Objects));
    pArrowUp->setFlippedY(true);
    pArrowUp->addEventListener(oxygine::TouchEvent::OVER, [ = ](oxygine::Event*)
    {
        pArrowUp->addTween(oxygine::Sprite::TweenAddColor(oxygine::Color(16, 16, 16, 0)), 300);
    });
    pArrowUp->addEventListener(oxygine::TouchEvent::OUTX, [ = ](oxygine::Event*)
    {
        pArrowUp->addTween(oxygine::Sprite::TweenAddColor(oxygine::Color(0, 0, 0, 0)), 300);
    });
    pArrowUp->addEventListener(oxygine::TouchEvent::TOUCH_DOWN, [ = ](oxygine::Event*)
    {
        emit changeSelection(currentStartIndex - 1);
    });
    pArrowUp->setScaleX(4.0f);
    pArrowUp->setPosition(width / 2 - pAnim->getWidth() * 2, 0);
    this->addChild(pArrowUp);

    qint32 arrowHeigth = static_cast<qint32>(pAnim->getHeight());
    qint32 y = arrowHeigth + 5;


    this->setPriority(static_cast<short>(Mainapp::ZOrder::Objects));
    ObjectManager* pObjectManager = ObjectManager::getInstance();
    pAnim = pObjectManager->getResAnim("mapSelectionTop");
    oxygine::spBox9Sprite pBackground = new oxygine::Box9Sprite();
    pBackground->setVerticalMode(oxygine::Box9Sprite::STRETCHING);
    pBackground->setHorizontalMode(oxygine::Box9Sprite::STRETCHING);
    pBackground->setResAnim(pAnim);
    pBackground->setSize(width, pAnim->getHeight());
    pBackground->setPosition(0, y);
    y += pAnim->getHeight();
    this->addChild(pBackground);

     pAnim = pObjectManager->getResAnim("mapSelectionSelectedMap");
    m_SelectedItem = new oxygine::Box9Sprite();
    m_SelectedItem->setVerticalMode(oxygine::Box9Sprite::STRETCHING);
    m_SelectedItem->setHorizontalMode(oxygine::Box9Sprite::STRETCHING);
    m_SelectedItem->setResAnim(pAnim);
    m_SelectedItem->setSize(width - 12, itemHeigth);
    m_SelectedItem->setPosition(5, y);
    m_SelectedItem->setPriority(1);
    this->addChild(m_SelectedItem);
    m_SelectedItem->addEventListener(oxygine::TouchEvent::CLICK, [=](oxygine::Event*)
    {
        emit itemClicked(currentItem);
    });

    itemCount = (heigth - 10 - 2 * static_cast<qint32>(pAnim->getHeight()) - arrowHeigth * 2) / itemHeigth;
    for (qint32 i = 0; i < itemCount; i++)
    {
        pAnim = pObjectManager->getResAnim("mapSelectionItem");
        pBackground = new oxygine::Box9Sprite();
        pBackground->setVerticalMode(oxygine::Box9Sprite::STRETCHING);
        pBackground->setHorizontalMode(oxygine::Box9Sprite::STRETCHING);
        pBackground->setResAnim(pAnim);
        pBackground->setSize(width, itemHeigth);
        pBackground->setPosition(0, y);
        oxygine::spClipRectActor pClipActor = new oxygine::ClipRectActor();
        pBackground->addChild(pClipActor);
        oxygine::spTextField pTextfield = new oxygine::TextField();
        oxygine::TextStyle style = FontManager::getMainFont();
        style.color = oxygine::Color(255, 255, 255, 255);
        style.vAlign = oxygine::TextStyle::VALIGN_DEFAULT;
        style.hAlign = oxygine::TextStyle::HALIGN_LEFT;
        style.multiline = false;
        pTextfield->setStyle(style);
        pTextfield->setText("");
        pClipActor->addChild(pTextfield);
        pClipActor->setX(10);
        pClipActor->setSize(width - 20, itemHeigth);
        this->addChild(pBackground);
        m_Items.append(pTextfield);
        qint32 itemPos = m_Items.size() - 1;
        pBackground->addEventListener(oxygine::TouchEvent::OVER, [=](oxygine::Event*)
        {
            if (m_Items[itemPos]->getText() != "")
            {
                m_SelectedItem->setY(y);
                currentItem = files[currentStartIndex + i];
                currentIdx = currentStartIndex + i;
                emit itemChanged(currentItem);
            }
        });

        y += itemHeigth;
    }
    pAnim = pObjectManager->getResAnim("mapSelectionBottom");
    pBackground = new oxygine::Box9Sprite();
    pBackground->setVerticalMode(oxygine::Box9Sprite::STRETCHING);
    pBackground->setHorizontalMode(oxygine::Box9Sprite::STRETCHING);
    pBackground->setResAnim(pAnim);
    pBackground->setSize(width, pAnim->getHeight());
    pBackground->setPosition(0, y);
    y += pAnim->getHeight();
    this->addChild(pBackground);

    oxygine::spButton pArrowDown = new oxygine::Button();
    pAnim = ObjectManager::getInstance()->getResAnim("arrow+down");
    pArrowDown->setResAnim(pAnim);
    pArrowDown->setPriority(static_cast<short>(Mainapp::ZOrder::Objects));
    pArrowDown->addEventListener(oxygine::TouchEvent::OVER, [ = ](oxygine::Event*)
    {
        pArrowDown->addTween(oxygine::Sprite::TweenAddColor(oxygine::Color(16, 16, 16, 0)), 300);
    });
    pArrowDown->addEventListener(oxygine::TouchEvent::OUTX, [ = ](oxygine::Event*)
    {
        pArrowDown->addTween(oxygine::Sprite::TweenAddColor(oxygine::Color(0, 0, 0, 0)), 300);
    });
    pArrowDown->addEventListener(oxygine::TouchEvent::TOUCH_DOWN, [ = ](oxygine::Event*)
    {
        emit changeSelection(currentStartIndex + 1);
    });
    pArrowDown->setScaleX(4.0f);
    pArrowDown->setPosition(width / 2 - pAnim->getWidth() * 2, y + 5);
    this->addChild(pArrowDown);
    changeFolder(folder);
    connect(this, SIGNAL(changeSelection(qint32)), this, SLOT(updateSelection(qint32)), Qt::QueuedConnection);
    connect(this, SIGNAL(itemClicked(QString)), this, SLOT(changeFolder(QString)), Qt::QueuedConnection);
}

MapSelection::~MapSelection()
{

}

void MapSelection::changeFolder(QString folder)
{

    QString newFolder = folder;
    if (folder == "")
    {
        newFolder = QCoreApplication::applicationDirPath() + "/maps/";
    }
    if (folder == "..")
    {
        newFolder = m_currentFolder + "/..";
    }
    QDir dir(newFolder);
    if (dir.exists())
    {
        QFileInfo newFolderInfo(newFolder);
        newFolder = newFolderInfo.absoluteFilePath() + "/";
        files.clear();
        if ((newFolder != QCoreApplication::applicationDirPath() + "/maps//") &&
            (newFolder != QCoreApplication::applicationDirPath() + "/maps/"))
        {
            files.append("..");
        }
        QFileInfoList infoList;
        QFileInfo upFolder(newFolder + "..");
        QString list = "*.map";
        infoList.append(QDir(newFolder).entryInfoList(QDir::Dirs));
        infoList.append(QDir(newFolder).entryInfoList(list.split(";"), QDir::Files));
        for (qint32 i = 1; i < infoList.size(); i++)
        {
            QString myPath = infoList[i].absoluteFilePath();
            if ((myPath == newFolder) ||
                (upFolder == infoList[i]))
            {
                // skip ourself
                continue;
            }

            if (infoList[i].isDir())
            {
                files.append(infoList[i].absoluteFilePath().replace(folder, ""));
            }
            else if (infoList[i].isFile())
            {
                files.append(infoList[i].fileName());
            }
        }
        m_currentFolder = newFolder;
        updateSelection(0);        
        currentItem = files[currentIdx];
        emit itemChanged(currentItem);
    }
}

void MapSelection::updateSelection(qint32 startIndex)
{
    currentStartIndex = startIndex;
    if (currentStartIndex < 0)
    {
        currentStartIndex = 0;
    }
    else if (currentStartIndex >= files.size() - itemCount)
    {
        currentStartIndex = files.size() - itemCount;
        if (currentStartIndex < 0)
        {
            currentStartIndex = 0;
        }
    }
    for (qint32 i = 0; i < itemCount; i++)
    {
        if (currentStartIndex + i >= files.size())
        {
            m_Items[i]->setText("");
        }
        else
        {
            QDir dir(files[currentStartIndex + i]);
            if (files[currentStartIndex + i] == "..")
            {
                m_Items[i]->setText(files[currentStartIndex + i].toStdString().c_str());
            }
            else if (dir.exists())
            {
                QStringList data = files[currentStartIndex + i].split("/");
                QStringList data2 = data[data.size() - 1].split(".");
                QStringList data3 = data2[0].split("_");
                QString item;
                for (qint32 i2 = 0; i2 < data3.size(); i2++)
                {
                    if (i2 > 0)
                    {
                        item += " ";
                    }
                    item += data3[i2].replace(0, 1, data3[i2][0].toUpper());
                }
                m_Items[i]->setText(item.toStdString().c_str());
            }
            else
            {
                // it's a map
                QFile file(m_currentFolder + files[currentStartIndex + i]);
                file.open(QIODevice::ReadOnly);
                QDataStream pStream(&file);
                QString name = GameMap::readMapName(pStream);
                if (name.isEmpty())
                {
                    QStringList data = files[currentStartIndex + i].split("/");
                    QStringList data2 = data[data.size() - 1].split(".");
                    QStringList data3 = data2[0].split("_");
                    QString item;
                    for (qint32 i2 = 0; i2 < data3.size(); i2++)
                    {
                        if (i2 > 0)
                        {
                            item += " ";
                        }
                        item += data3[i2].replace(0, 1, data3[i2][0].toUpper());
                    }
                    m_Items[i]->setText(item.toStdString().c_str());
                }
                else
                {
                    m_Items[i]->setText(name.toStdString().c_str());
                }
            }
        }
    }
}