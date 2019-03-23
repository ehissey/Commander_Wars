#include "slider.h"

#include "coreengine/mainapp.h"
#include "resource_management/objectmanager.h"
#include "resource_management/fontmanager.h"

Slider::Slider(qint32 width, qint32 minValue, qint32 maxValue)
    : V_Scrollbar (width, width * (maxValue - minValue) / 10),
      m_minValue(minValue),
      m_maxValue(maxValue)
{
    m_Textfield = new oxygine::TextField();
    oxygine::TextStyle style = FontManager::getMainFont();
    style.color = oxygine::Color(255, 255, 255, 255);
    style.vAlign = oxygine::TextStyle::VALIGN_DEFAULT;
    style.hAlign = oxygine::TextStyle::HALIGN_LEFT;
    style.multiline = false;
    m_Textfield->setStyle(style);
    m_CurrentValue = minValue;
    m_Textfield->setText((QString::number(minValue) + " %").toStdString().c_str());
    addChild(m_Textfield);
    m_Textfield->setX(getWidth() + 10);
    connect(this, &Slider::V_Scrollbar::sigScrollValueChanged, this, &Slider::slotSliderValueChanged, Qt::QueuedConnection);
}

void Slider::slotSliderValueChanged(float value)
{
    m_CurrentValue = (m_maxValue - m_minValue) * value + m_minValue;
    m_Textfield->setText((QString::number(m_CurrentValue) + " %").toStdString().c_str());
    emit sliderValueChanged(m_CurrentValue);
}

qint32 Slider::getCurrentValue() const
{
    return m_CurrentValue;
}

void Slider::setCurrentValue(const qint32 &CurrentValue)
{
    m_CurrentValue = CurrentValue;
    if (m_CurrentValue < m_minValue)
    {
        m_CurrentValue = m_minValue;
    }
    else if (m_CurrentValue > m_maxValue)
    {
        m_CurrentValue = m_maxValue;
    }
    else
    {
        // all fine do nothing
    }
    m_Textfield->setText((QString::number(m_CurrentValue) + " %").toStdString().c_str());
    float scrollValue = static_cast<float>(m_CurrentValue - m_minValue) / static_cast<float>(m_maxValue - m_minValue);
    V_Scrollbar::setScrollvalue(scrollValue);
}