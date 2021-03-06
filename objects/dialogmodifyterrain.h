#ifndef DIALOGMODIFYTERRAIN_H
#define DIALOGMODIFYTERRAIN_H

#include <QObject>

#include "oxygine-framework.h"

#include "objects/panel.h"

#include "objects/textbox.h"

class Terrain;

class DialogModifyTerrain;
typedef oxygine::intrusive_ptr<DialogModifyTerrain> spDialogModifyTerrain;

class DialogModifyTerrain : public QObject, public oxygine::Actor
{
    Q_OBJECT
public:
    explicit DialogModifyTerrain(Terrain* pTerrain);

signals:
    void sigFinished();
    void sigTerrainClicked(QString id);
    void sigShowLoadDialog();
public slots:
    void terrainClicked(QString id);
    void showLoadDialog();
    void loadCustomSprite(QString id);
private:
    Terrain* m_pTerrain{nullptr};
    spPanel m_pPanel;
    spTextbox m_pTextbox;
    oxygine::spButton m_OkButton;

};

#endif // DIALOGMODIFYTERRAIN_H
