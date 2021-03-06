#ifndef SETTINGS_H
#define SETTINGS_H

#include <Qt>
#include <QObject>

#include "oxygine-framework.h"

#include "game/GameEnums.h"

class GLGraphicsView;

class Settings : public QObject
{
    Q_OBJECT
public:
    Settings();
    virtual ~Settings() = default;

    static void loadSettings();
    static void saveSettings();
    static void setup();

    static quint16 getServerPort();
    static void setServerPort(const quint16 &ServerPort);

    static QString getServerAdress();
    static void setServerAdress(const QString &ServerAdress);

    static void setServer(bool Server);

    static QString getLastSaveGame();
    static void setLastSaveGame(const QString &LastSaveGame);


    static void setUsername(const QString &Username);


public slots:
    static bool getStaticMarkedFields();
    static void setStaticMarkedFields(bool StaticMarkedFields);

    static qint32 getMenuItemCount();
    static void setMenuItemCount(const qint32 &MenuItemCount);

    static QString getModConfigString();

    static quint32 getMultiTurnCounter();
    static void setMultiTurnCounter(const quint32 &value);

    static bool getShowCursor();
    static void setShowCursor(bool ShowCursor);

    static bool getAutoEndTurn();
    static void setAutoEndTurn(bool AutoEndTurn);

    static GameEnums::BattleAnimationMode getBattleAnimations();
    static void setBattleAnimations(const GameEnums::BattleAnimationMode &value);

    static QString getUsername();
    inline static qint32 getX()
    {
        return m_x;
    }
    inline static qint32 getY()
    {
        return m_y;
    }
    inline static qint32 getWidth()
    {
        return m_width;
    }
    inline static qint32 getHeight()
    {
        return m_height;
    }

    inline static bool getBorderless()
    {
        return m_borderless;
    }

    inline static bool getFullscreen()
    {
        return m_fullscreen;
    }

    inline Qt::Key getKeyConsole()
    {
        return m_key_console;
    }

    inline void setTotalVolume(qint32 value)
    {
        m_TotalVolume = value;
    }
    inline qint32 getTotalVolume()
    {
        return m_TotalVolume;
    }

    inline void setMusicVolume(qint32 value)
    {
        m_MusicVolume = value;
    }
    inline qint32 getMusicVolume()
    {
        return m_MusicVolume;
    }

    inline void setSoundVolume(qint32 value)
    {
        m_SoundVolume = value;
    }
    inline qint32 getSoundVolume()
    {
        return m_SoundVolume;
    }

    static inline quint16 getGamePort()
    {
        return m_GamePort;
    }
    static inline void setGamePort(quint16 value)
    {
        m_GamePort = value;
    }
    static inline bool getServer()
    {
        return m_Server;
    }
    static inline QStringList getMods()
    {
        return m_activeMods;
    }
    static void addMod(QString mod)
    {
        if (!m_activeMods.contains(mod))
        {
            m_activeMods.append(mod);
        }
    }
    static void removeMod(QString mod)
    {
        if (m_activeMods.contains(mod))
        {
            m_activeMods.removeOne(mod);
        }
    }
    static float getMouseSensitivity();
    static void setMouseSensitivity(float value);

    static GameEnums::AnimationMode getShowAnimations();
    static void setShowAnimations(GameEnums::AnimationMode value);

    static void setFullscreen(bool fullscreen);

    static void setBorderless(bool borderless);

    static void setWidth(const qint32 &width);
    static void setHeight(const qint32 &height);

    static float getAnimationSpeedValue();
    static float getAnimationSpeed();
    static void setAnimationSpeed(const quint32 &value);

    static float getBattleAnimationSpeedValue();
    static float getBattleAnimationSpeed();
    static void setBattleAnimationSpeed(const quint32 &value);

    static Qt::Key getKey_up();
    static void setKey_up(const Qt::Key &key_up);

    static Qt::Key getKey_down();
    static void setKey_down(const Qt::Key &key_down);

    static Qt::Key getKey_right();
    static void setKey_right(const Qt::Key &key_right);

    static Qt::Key getKey_left();
    static void setKey_left(const Qt::Key &key_left);

    static Qt::Key getKey_confirm();
    static void setKey_confirm(const Qt::Key &key_confirm);

    static Qt::Key getKey_cancel();
    static void setKey_cancel(const Qt::Key &key_cancel);

    static Qt::Key getKey_next();
    static void setKey_next(const Qt::Key &key_next);

    static Qt::Key getKey_previous();
    static void setKey_previous(const Qt::Key &key_previous);

    static Qt::Key getKey_quicksave1();
    static void setKey_quicksave1(const Qt::Key &key_quicksave1);

    static Qt::Key getKey_quicksave2();
    static void setKey_quicksave2(const Qt::Key &key_quicksave2);

    static Qt::Key getKey_quickload1();
    static void setKey_quickload1(const Qt::Key &key_quickload1);

    static Qt::Key getKey_quickload2();
    static void setKey_quickload2(const Qt::Key &key_quickload2);

    static Qt::Key getKey_moveMapUp();
    static void setKey_moveMapUp(const Qt::Key &key_moveMapUp);

    static Qt::Key getKey_moveMapDown();
    static void setKey_moveMapDown(const Qt::Key &key_moveMapDown);

    static Qt::Key getKey_moveMapRight();
    static void setKey_moveMapRight(const Qt::Key &key_moveMapRight);

    static Qt::Key getKey_moveMapLeft();
    static void setKey_moveMapLeft(const Qt::Key &key_moveMapLeft);

    static Qt::Key getKey_information();
    static void setKey_information(const Qt::Key &key_information);

    static Qt::Key getKey_MapZoomOut();
    static void setKey_MapZoomOut(const Qt::Key &key_MapZoomOut);

    static Qt::Key getKey_MapZoomIn();
    static void setKey_MapZoomIn(const Qt::Key &key_MapZoomIn);
private:
    // setting variables
    static qint32 m_x;
    static qint32 m_y;
    static qint32 m_width;
    static qint32 m_height;

    static bool m_borderless;
    static bool m_fullscreen;

    static Qt::Key m_key_escape;
    static Qt::Key m_key_console;
    static Qt::Key m_key_up;
    static Qt::Key m_key_down;
    static Qt::Key m_key_right;
    static Qt::Key m_key_left;
    static Qt::Key m_key_confirm;
    static Qt::Key m_key_cancel;
    static Qt::Key m_key_next;
    static Qt::Key m_key_previous;
    static Qt::Key m_key_quicksave1;
    static Qt::Key m_key_quicksave2;
    static Qt::Key m_key_quickload1;
    static Qt::Key m_key_quickload2;
    static Qt::Key m_key_information;
    static Qt::Key m_key_moveMapUp;
    static Qt::Key m_key_moveMapDown;
    static Qt::Key m_key_moveMapRight;
    static Qt::Key m_key_moveMapLeft;
    static Qt::Key m_key_MapZoomOut;
    static Qt::Key m_key_MapZoomIn;

    static QString m_language;
    // Sound
    static qint32 m_TotalVolume;
    static qint32 m_MusicVolume;
    static qint32 m_SoundVolume;
    // Network
    static quint16 m_GamePort;
    static quint16 m_ServerPort;
    static QString m_ServerAdress;
    static QString m_Username;
    static bool m_Server;

    // ingame options
    static GameEnums::AnimationMode showAnimations;
    static GameEnums::BattleAnimationMode battleAnimations;
    static quint32 animationSpeed;
    static quint32 battleAnimationSpeed;
    static quint32 multiTurnCounter;
    static QString m_LastSaveGame;
    static bool m_ShowCursor;
    static bool m_AutoEndTurn;
    static qint32 m_MenuItemCount;
    static bool m_StaticMarkedFields;

    // internal members
    static Settings* m_pInstance;
    static const QString m_settingFile;
    static QStringList m_activeMods;

    static float m_mouseSensitivity;
};

#endif // SETTINGS_H
