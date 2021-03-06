#ifndef GAMEENUMS_H
#define GAMEENUMS_H

#include <QObject>

class GameEnums : public QObject
{
    Q_OBJECT
public:
    enum Alliance
    {
        Alliance_Friend,
        Alliance_Enemy
    };
    Q_ENUM(Alliance)

    enum PowerMode
    {
        PowerMode_Unknown = -1,
        PowerMode_Off,
        PowerMode_Power,
        PowerMode_Superpower,
        PowerMode_Tagpower
    };
    Q_ENUM(PowerMode)

    enum RocketTarget
    {
        RocketTarget_Money, /**< targets the most money damage witht the rocket */
        RocketTarget_HpLowMoney, /**< targets most hp damage where units which costs less than half of the average funds count four time */
        RocketTarget_HpHighMoney /**< targets most hp damage where units which costs more than half of the average funds count four time */
    };
    Q_ENUM(RocketTarget)

    enum UnitRanks
    {
        UnitRank_None,
        UnitRank_Lieutenant,
        UnitRank_General,
        UnitRank_Veteran,
        UnitRank_CO0,
        UnitRank_CO1
    };
    Q_ENUM(UnitRanks)

    enum Directions
    {
        Directions_None = -1,
        Directions_North,
        Directions_NorthEast,
        Directions_East,
        Directions_SouthEast,
        Directions_South,
        Directions_SouthWest,
        Directions_West,
        Directions_NorthWest,
        Directions_All,
        Directions_Direct,
        Directions_Diagnonal
    };
    Q_ENUM(Directions)

    enum AIQuestionType
    {
        AIQuestionType_Equal,
        AIQuestionType_Smaler,
        AIQuestionType_Greater,
        AIQuestionType_Between
    };
    Q_ENUM(AIQuestionType)

    enum DefeatType
    {
        DefeatType_Alive, /**< the player will not loose the game cause of this rule for now */
        DefeatType_Defeated, /**< all units will get destroyed and the player looses the game */
        DefeatType_ByCurrentPlayer, /**< all buildings will get controlled by the current player and all units will get destroyed */
        DefeatType_Domination /**< all units and buildings will get controlled by the current player */
    };
    Q_ENUM(DefeatType)

    enum Fog
    {
        Fog_Off,
        Fog_OfWar,
        Fog_OfShroud
    };
    Q_ENUM(Fog)

    enum VisionType
    {
        VisionType_Shrouded,
        VisionType_Fogged,
        VisionType_Clear
    };
    Q_ENUM(VisionType)

    enum COMood
    {
        COMood_Normal,
        COMood_Happy,
        COMood_Sad
    };
    Q_ENUM(COMood)

    enum LuckDamageMode
    {
        LuckDamageMode_Off,
        LuckDamageMode_On,
        LuckDamageMode_Average
    };
    Q_ENUM(LuckDamageMode)

    enum GameRecord_SpecialEvents
    {
        GameRecord_SpecialEvents_Power,
        GameRecord_SpecialEvents_SuperPower,
        GameRecord_SpecialEvents_HQCaptured,
        GameRecord_SpecialEvents_HQLost
    };
    Q_ENUM(GameRecord_SpecialEvents)

    enum GameAi
    {
        GameAi_Normal,
        GameAi_Offensive,
        GameAi_Defensive,
        GameAi_Hold
    };
    Q_ENUM(GameAi)

    enum AnimationMode
    {
        AnimationMode_None,
        AnimationMode_All,
        AnimationMode_Own,
        AnimationMode_Ally,
        AnimationMode_Enemy,
        AnimationMode_OnlyBattleAll,
        AnimationMode_OnlyBattleOwn,
        AnimationMode_OnlyBattleAlly,
        AnimationMode_OnlyBattleEnemy,
    };
    Q_ENUM(AnimationMode)

    enum BattleAnimationMode
    {
        BattleAnimationMode_Detail,
        BattleAnimationMode_Overworld,
    };
    Q_ENUM(BattleAnimationMode)

    enum BuildingTarget
    {
        BuildingTarget_All,
        BuildingTarget_Own,
        BuildingTarget_Enemy,
    };
    Q_ENUM(BuildingTarget)

    enum UnitType
    {
        UnitType_Ground,
        UnitType_Air,
        UnitType_Naval,
    };
    Q_ENUM(UnitType)
    static QString getUnitTypeText(UnitType type);

    enum AiTurnMode
    {
        AiTurnMode_StartOfDay,
        AiTurnMode_DuringDay,
        AiTurnMode_EndOfDay,
    };
    Q_ENUM(AiTurnMode)

    static void registerEnums();
private:
    explicit GameEnums() = default;
    virtual ~GameEnums() = default;
};

#endif
