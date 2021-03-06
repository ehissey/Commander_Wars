#ifndef SCRIPTEVENT_H
#define SCRIPTEVENT_H

#include <QObject>

#include "qtextstream.h"

#include "oxygine-framework.h"

class ScriptEvent;
typedef oxygine::intrusive_ptr<ScriptEvent> spScriptEvent;

class ScriptEditor;
typedef oxygine::intrusive_ptr<ScriptEditor> spScriptEditor;

class ScriptEvent : public QObject, public oxygine::ref_counter
{
    Q_OBJECT
public:
    static const QString EventDialog;
    static const QString EventSpawnUnit;
    static const QString EventDefeatPlayer;
    static const QString EventChangeBuildlist;
    static const QString EventAddFunds;
    static const QString EventChangeWeather;
    static const QString EventChangeCOBar;
    static const QString EventModifyUnit;
    static const QString EventAnimation;
    static const QString EventModifyTerrain;

    enum class EventType
    {
        dialog,
        spawnUnit,
        defeatPlayer,
        changeBuildlist,
        addFunds,
        changeWeather,
        changeCOBar,
        modifyTerrain,
        modifyUnit,
        animation,
    };

    static spScriptEvent createEvent(EventType type);
    /**
     * @brief createReadEvent
     * @param rStream
     * @return
     */
    static spScriptEvent createReadEvent(QTextStream& rStream);
    /**
     * @brief readEvent
     * @param rStream
     */
    virtual void readEvent(QTextStream& rStream) = 0;
    /**
     * @brief writeEvent
     * @param rStream
     */
    virtual void writeEvent(QTextStream& rStream) = 0;
    /**
     * @brief getEventType
     * @return
     */
    EventType getEventType()
    {
        return m_Type;
    }
    /**
     * @brief getDescription
     * @return
     */
    virtual QString getDescription() = 0;
    /**
     * @brief showEditEvent
     */
    virtual void showEditEvent(spScriptEditor pScriptEditor) = 0;
    /**
     * @brief getVersion
     * @return
     */
    virtual qint32 getVersion() = 0;
protected:
    explicit ScriptEvent(EventType type);
    EventType m_Type;
};

#endif // SCRIPTEVENT_H
