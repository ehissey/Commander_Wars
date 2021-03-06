#ifndef MULTISLIDER_H
#define MULTISLIDER_H

#include <QObject>

#include <QString>

#include <QVector>

#include "oxygine-framework.h"

#include "objects/slider.h"
#include "objects/tooltip.h"

class Multislider;
typedef oxygine::intrusive_ptr<Multislider> spMultislider;

class Multislider : public Tooltip
{
    Q_OBJECT
public:
    explicit Multislider(QVector<QString> texts, qint32 width, QVector<qint32> values = {});

    qint32 getSliderValue(qint32 slider);
signals:
    void signalSliderChanged();
    void signalSliderValueChanged(qint32 slider);
public slots:
    void sliderValueChanged(qint32 slider);
private:
    QVector<oxygine::spTextField> m_Textfields;
    QVector<spSlider> m_Slider;
    qint32 currentSliderChange{0};
};

#endif // MULTISLIDER_H
