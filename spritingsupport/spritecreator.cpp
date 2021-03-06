#include "coreengine/console.h"

#include "coreengine/mainapp.h"

#include "qdir.h"
#include "qfile.h"
#include "qfileinfo.h"
#include "qdiriterator.h"

#include "spritingsupport/spritecreator.h"

const qint32 SpriteCreator::colorBoxSize = 43;

void SpriteCreator::createSprites(QString input, QString colorTable, QString maskTable)
{
    if (!QFile::exists(colorTable) && colorTable.endsWith(".png"))
    {
        Console::print(tr("The color table is not an existing file. ") + colorTable, Console::eERROR);
        return;
    }
    QImage colorTableImg(colorTable);
    if (!QFile::exists(maskTable) && maskTable.endsWith(".png"))
    {
        Console::print(tr("The mask table is not an existing file. ") + maskTable, Console::eERROR);
        return;
    }
    QImage maskTableImg(maskTable);
    if (maskTableImg.width() < colorTableImg.width())
    {
        Console::print(tr("The mask table is to small. ") + maskTable, Console::eERROR);
        return;
    }
    QFileInfo inputInfo(input);
    if (inputInfo.isDir())
    {
        QStringList filter;
        filter << "*.png";
        QDirIterator dirIter(input, filter, QDir::Files);
        while (dirIter.hasNext())
        {
            dirIter.next();
            createSprites(dirIter.fileInfo().absoluteFilePath(), colorTableImg, maskTableImg);
        }
    }
    else if (inputInfo.isFile() && input.endsWith(".png"))
    {
        createSprites(input, colorTableImg, maskTableImg);
    }
    else
    {
        Console::print(tr("Input directory or file doesn't exists. ") + input, Console::eERROR);
    }
}

void SpriteCreator::createSprites(QString file, QImage& colorTable, QImage maskTable)
{
    QString orgFile = file;
    QString maskFile = file;
    maskFile = maskFile.replace(".png", "+mask.png");
    QFile::copy(file, orgFile.replace(".png", "_org.png"));
    QImage orgImg(orgFile);
    QImage mainImg(orgImg.size(), QImage::Format_RGBA8888);
    QImage maskImg(orgImg.size(), QImage::Format_RGBA8888);
    for (qint32 x = 0; x < orgImg.width(); x++)
    {
        for (qint32 y = 0; y < orgImg.height(); y++)
        {
            // color pixel or another one?
            QColor org = orgImg.pixelColor(x, y);
            for (qint32 i = 0; i < colorTable.width(); i++)
            {
                QColor mask = colorTable.pixelColor(i, 0);
                if (mask.rgba() == org.rgba())
                {
                    mainImg.setPixelColor(x, y, Qt::transparent);
                    maskImg.setPixelColor(x, y, maskTable.pixelColor(i, 0));
                    break;
                }
                else if (i == colorTable.width() - 1)
                {
                    mainImg.setPixelColor(x, y, orgImg.pixelColor(x, y));
                    maskImg.setPixelColor(x, y, Qt::transparent);
                }
            }
        }
    }
    QFile::remove(file);
    QFile::remove(maskFile);
    mainImg.save(file);
    maskImg.save(maskFile);
}

oxygine::ResAnim* SpriteCreator::createAnim(QString input, QString colorTable, QString newTable, bool useColorBox,
                                      qint32 columns, qint32  rows, float scaleFactor)
{
    if (!QFile::exists(colorTable) && colorTable.endsWith(".png"))
    {
        Console::print(tr("The color table is not an existing file. ") + colorTable, Console::eERROR);
        return nullptr;
    }
    QImage colorTableImg(colorTable);
    if (!QFile::exists(newTable) && newTable.endsWith(".png"))
    {
        Console::print(tr("The mask table is not an existing file. ") + newTable, Console::eERROR);
        return nullptr;
    }
    QImage maskTableImg(newTable);
    if (maskTableImg.width() < colorTableImg.width())
    {
        Console::print(tr("The mask table is to small. ") + newTable, Console::eERROR);
        return nullptr;
    }
    return createAnim(input, colorTableImg, maskTableImg, useColorBox, columns, rows, scaleFactor);
}

oxygine::ResAnim* SpriteCreator::createAnim(QString input, QImage& colorTableImg, QImage& maskTableImg, bool useColorBox,
                                      qint32 columns, qint32  rows, float scaleFactor)
{
    QFileInfo inputInfo(input);
    if (inputInfo.isFile() && inputInfo.exists())
    {
        createSprite(input, colorTableImg, maskTableImg, useColorBox);
        oxygine::SingleResAnim* pRet = new oxygine::SingleResAnim();
        pRet->setResPath(input);
        pRet->init("temp.png", columns, rows, scaleFactor);
        QFile::remove("temp.png");
        return pRet;
    }
    return nullptr;
}

void SpriteCreator::createSprite(QString input, QImage& colorTableImg, QImage maskTableImg, bool useColorBox)
{
    QImage orgImg(input);
    QImage mainImg(orgImg.size(), QImage::Format_RGBA8888);
    for (qint32 x = 0; x < orgImg.width(); x++)
    {
        for (qint32 y = 0; y < orgImg.height(); y++)
        {
            // color pixel or another one?
            QColor org = orgImg.pixelColor(x, y);
            QColor orgBox = getColorBox(org);
            for (qint32 i = 0; i < colorTableImg.width(); i++)
            {
                QColor pixel = colorTableImg.pixelColor(i, 0);
                QColor boxColor = getColorBox(pixel);
                if (useColorBox)
                {
                    if (boxColor.rgba() == orgBox.rgba())
                    {
                        mainImg.setPixelColor(x, y, getImageColor(maskTableImg.pixelColor(i, 0), org));
                        break;
                    }
                    else if (i == colorTableImg.width() - 1)
                    {
                        mainImg.setPixelColor(x, y, orgImg.pixelColor(x, y));
                    }
                }
                else
                {
                    if (pixel.rgba() == org.rgba())
                    {
                        mainImg.setPixelColor(x, y, maskTableImg.pixelColor(i, 0));
                        break;
                    }
                    else if (i == colorTableImg.width() - 1)
                    {
                        mainImg.setPixelColor(x, y, orgImg.pixelColor(x, y));
                    }
                }
            }
        }
    }
    QFile::remove("temp.png");
    mainImg.save("temp.png");
}

QImage SpriteCreator::createColorTable(QImage& image)
{
    auto tableVector = image.colorTable();
    qint32 maxSize = 200;
    QImage ret(maxSize, 1, QImage::Format_RGBA8888);
    qint32 width = 0;
    for (qint32 x = 0; x < image.width(); x++)
    {
        for (qint32 y = 0; y < image.height(); y++)
        {
            QColor pixel = image.pixelColor(x, y);
            if (pixel.alpha() == 255)
            {
                pixel = getColorBox(pixel);
                bool found = false;
                for (qint32 i = 0; i < width; i++)
                {
                    if (ret.pixelColor(i, 0) == pixel)
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    ret.setPixelColor(width, 0, pixel);
                    width++;
                }
                if (width >= maxSize)
                {
                    break;
                }
            }
        }
    }
    return ret.copy(0, 0, width, 1);
}

QColor SpriteCreator::getColorBox(QColor color)
{
    qint32 red = color.red();
    qint32 green = color.green();
    qint32 blue = color.blue();
    return QColor((red / colorBoxSize) * colorBoxSize,
                  (green / colorBoxSize) * colorBoxSize,
                  (blue / colorBoxSize) * colorBoxSize,
                  color.alpha());
}

QColor SpriteCreator::getImageColor(QColor maskColor, QColor imageColor)
{
    qint32 red = maskColor.red() + imageColor.red() % colorBoxSize;
    qint32 green = maskColor.green() + imageColor.green() % colorBoxSize;
    qint32 blue = maskColor.blue() + imageColor.blue() % colorBoxSize;
    if (red > 255)
    {
        red = 255;
    }
    if (green > 255)
    {
        green = 255;
    }
    if (blue > 255)
    {
        blue = 255;
    }
    return QColor(red,
                  green,
                  blue,
                  imageColor.alpha());
}

void SpriteCreator::updateMaskImages(QString& folder, QString& filter, qint32 min)
{
    QStringList filters;
    filters << filter;
    QDirIterator dirIter(folder, filters, QDir::Files, QDirIterator::IteratorFlag::Subdirectories);
    while (dirIter.hasNext())
    {
        dirIter.next();
        QString file = dirIter.fileInfo().absoluteFilePath();
        updateMaskImage(file, min);
    }
}

void SpriteCreator::updateMaskImage(QString& file, qint32 min)
{
    QImage mask(file);
    QVector<QColor> colors;
    QColor maskMin(min, min, min);
    QColor maskMax (255, 255, 255);
    for (qint32 x = 0; x < mask.width(); x++)
    {
        for (qint32 y = 0; y < mask.height(); y++)
        {
            // color pixel or another one?
            QColor org = mask.pixelColor(x, y);
            if (!colors.contains(org) && org.alpha() == 255)
            {
                qint32 sum = org.red() + org.green() + org.blue();
                bool inserted = false;
                if (colors.size() == 1)
                {
                    if (sum > colors[0].red() + colors[0].green() + colors[0].blue())
                    {
                        colors.append(org);
                    }
                    else
                    {
                        colors.insert(0, org);
                    }
                }
                else
                {
                    if (colors.size() > 0)
                    {
                        if (sum < colors[0].red() + colors[0].green() + colors[0].blue())
                        {
                            colors.insert(0, org);
                            inserted = true;
                        }
                        else
                        {
                            for (qint32 i = 0; i < colors.size() - 1; i++)
                            {
                                if (sum > colors[i].red() + colors[i].green() + colors[i].blue() &&
                                    sum < colors[i + 1].red() + colors[i + 1].green() + colors[i + 1].blue())
                                {
                                    colors.insert(i + 1, org);
                                    inserted = true;
                                }
                            }
                        }
                    }
                    if (!inserted)
                    {
                        colors.append(org);
                    }
                }
            }
        }
    }
    for (qint32 x = 0; x < mask.width(); x++)
    {
        for (qint32 y = 0; y < mask.height(); y++)
        {
            // color pixel or another one?
            QColor org = mask.pixelColor(x, y);
            if (org.alpha() == 255)
            {
                qint32 index = colors.indexOf(org);
                float factor = static_cast<float>(index) / static_cast<float>(colors.size() - 1);
                QColor newColor(factor * (maskMax.red() - maskMin.red()) + maskMin.red(),
                                factor * (maskMax.green() - maskMin.green()) + maskMin.green(),
                                factor * (maskMax.blue() - maskMin.blue()) + maskMin.blue());
                mask.setPixelColor(x, y, newColor);
            }
        }
    }
    QFile::remove(file);
    mask.save(file);
}
