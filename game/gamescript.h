#ifndef GAMESCRIPT_H
#define GAMESCRIPT_H

#include <QObject>
#include <QVector>
#include "coreengine/fileserializable.h"
#include "coreengine/scriptvariables.h"

#include "oxygine-framework.h"

class GameScript;
typedef oxygine::intrusive_ptr<GameScript> spGameScript;

class GameScript : public QObject, public FileSerializable, public oxygine::ref_counter
{
    Q_OBJECT
public:
    explicit GameScript();
    virtual ~GameScript();
    /**
     * @brief serialize stores the object
     * @param pStream
     */
    virtual void serializeObject(QDataStream& pStream) override;
    /**
     * @brief deserialize restores the object
     * @param pStream
     */
    virtual void deserializeObject(QDataStream& pStream) override;
    /**
     * @brief getVersion stream version for serialization
     * @return
     */
    inline virtual qint32 getVersion() override
    {
        return 1;
    }
    /**
     * @brief init loads the script and stores the script in the script variable
     */
    void init();
    /**
     * @brief immediateStart call function to check if the rule and player selection menu should be shown and used
     * @return
     */
    bool immediateStart();
    /**
     * @brief victory call function when a team wins the game
     * @param team
     */
    bool victory(qint32 team);
    /**
     * @brief gameStart call function before the game starts
     */
    void gameStart();
    /**
     * @brief actionDone call function after an action has been finished
     */
    void actionDone();
    /**
     * @brief turnStart called on the start of each player
     * @param turn current day
     * @param player current player id
     */
    void turnStart(qint32 turn, qint32 player);

    QString getScriptFile() const;
    void setScriptFile(const QString &value);

    QString getVictoryInfo();
signals:

public slots:
    /**
     * @brief getVariables returns the enviroment variables of this game script
     * @return
     */
    inline ScriptVariables* getVariables()
    {
        return &m_Variables;
    }
private:
    bool victoryCalled{false};
    QString script;
    QString scriptFile;
    ScriptVariables m_Variables;
    bool loaded{false};
    static const QString scriptName;
};

#endif // GAMESCRIPT_H
