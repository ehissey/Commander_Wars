#ifndef SCRIPTEVENTDEFEATPLAYER_H
#define SCRIPTEVENTDEFEATPLAYER_H

#include <QObject>

#include "scriptevent.h"

class ScriptEventDefeatPlayer : public ScriptEvent
{
    Q_OBJECT
public:
    ScriptEventDefeatPlayer();
    /**
     * @brief readEvent
     * @param rStream
     */
    virtual void readEvent(QTextStream& rStream) override;
    /**
     * @brief writeEvent
     * @param rStream
     */
    virtual void writeEvent(QTextStream& rStream) override;
    /**
     * @brief getPlayer
     * @return
     */
    qint32 getPlayer() const;
    /**
     * @brief setPlayer
     * @param value
     */
    void setPlayer(const qint32 &value);
    /**
     * @brief getDescription
     * @return
     */
    virtual QString getDescription() override
    {
        return tr("Defeat: ") + QString::number(player + 1);
    }
    /**
     * @brief showEditEvent
     */
    virtual void showEditEvent(spScriptEditor pScriptEditor) override;
    /**
     * @brief getVersion
     * @return
     */
    virtual qint32 getVersion() override
    {
        return 0;
    }
private:
    qint32 player{0};
};

#endif // SCRIPTEVENTDEFEATPLAYER_H
