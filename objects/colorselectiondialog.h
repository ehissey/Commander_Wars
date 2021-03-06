#ifndef COLORSELECTIONDIALOG_H
#define COLORSELECTIONDIALOG_H

#include <QObject>

#include <QColor>
#include <QVector>

#include "oxygine-framework.h"

#include "objects/panel.h"

#include "objects/colorselector.h"

class ColorSelectionDialog;
typedef oxygine::intrusive_ptr<ColorSelectionDialog> spColorSelectionDialog;

class ColorSelectionDialog : public QObject, public oxygine::Actor
{
    Q_OBJECT
public:
    explicit ColorSelectionDialog(QColor color);

    virtual ~ColorSelectionDialog() = default;
signals:
    void editFinished(QColor color);
    void canceled();
private:
    oxygine::spButton m_OkButton;
    oxygine::spButton m_ExitButton;
    spColorSelector m_pColorSelector;
};

#endif // COLORSELECTIONDIALOG_H
