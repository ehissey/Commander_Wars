#include "game/GameEnums.h"

#include "coreengine/mainapp.h"

#include "coreengine/interpreter.h"

void GameEnums::registerEnums()
{
    Interpreter* pInterpreter = Mainapp::getInstance()->getInterpreter();
    QJSValue value = pInterpreter->newQObject(new GameEnums());
    value.setProperty("Alliance_Friend", Alliance_Friend);
    value.setProperty("Alliance_Enemy", Alliance_Enemy);

    value.setProperty("PowerMode_Unknown", PowerMode_Unknown);
    value.setProperty("PowerMode_Off", PowerMode_Off);
    value.setProperty("PowerMode_Power", PowerMode_Power);
    value.setProperty("PowerMode_Superpower", PowerMode_Superpower);
    value.setProperty("PowerMode_Tagpower", PowerMode_Tagpower);

    value.setProperty("RocketTarget_Money", RocketTarget_Money);
    value.setProperty("RocketTarget_HpHighMoney", RocketTarget_HpHighMoney);
    value.setProperty("RocketTarget_HpLowMoney", RocketTarget_HpLowMoney);

    value.setProperty("UnitRank_None", UnitRank_None);
    value.setProperty("UnitRank_Lieutenant", UnitRank_Lieutenant);
    value.setProperty("UnitRank_General", UnitRank_General);
    value.setProperty("UnitRank_Veteran", UnitRank_Veteran);
    value.setProperty("UnitRank_CO0", UnitRank_CO0);
    value.setProperty("UnitRank_CO1", UnitRank_CO1);

    value.setProperty("Directions_None", Directions_None);
    value.setProperty("Directions_North", Directions_North);
    value.setProperty("Directions_NorthEast", Directions_NorthEast);
    value.setProperty("Directions_East", Directions_East);
    value.setProperty("Directions_SouthEast", Directions_SouthEast);
    value.setProperty("Directions_South", Directions_South);
    value.setProperty("Directions_SouthWest", Directions_SouthWest);
    value.setProperty("Directions_West", Directions_West);
    value.setProperty("Directions_NorthWest", Directions_NorthWest);
    value.setProperty("Directions_All", Directions_All);
    value.setProperty("Directions_Direct", Directions_Direct);
    value.setProperty("Directions_Diagnonal", Directions_Diagnonal);

    value.setProperty("AIQuestionType_Equal", AIQuestionType_Equal);
    value.setProperty("AIQuestionType_Smaler", AIQuestionType_Smaler);
    value.setProperty("AIQuestionType_Greater", AIQuestionType_Greater);
    value.setProperty("AIQuestionType_Between", AIQuestionType_Between);

    value.setProperty("DefeatType_Alive", DefeatType_Alive);
    value.setProperty("DefeatType_Defeated", DefeatType_Defeated);
    value.setProperty("DefeatType_ByCurrentPlayer", DefeatType_ByCurrentPlayer);
    value.setProperty("DefeatType_Domination", DefeatType_Domination);

    value.setProperty("Fog_Off", Fog_Off);
    value.setProperty("Fog_OfWar", Fog_OfWar);
    value.setProperty("Fog_OfShroud", Fog_OfShroud);

    value.setProperty("VisionType_Shrouded", VisionType_Shrouded);
    value.setProperty("VisionType_Fogged", VisionType_Fogged);
    value.setProperty("VisionType_Clear", VisionType_Clear);

    value.setProperty("COMood_Normal", COMood_Normal);
    value.setProperty("COMood_Happy", COMood_Happy);
    value.setProperty("COMood_Sad", COMood_Sad);

    value.setProperty("LuckDamageMode_Off", LuckDamageMode_Off);
    value.setProperty("LuckDamageMode_On", LuckDamageMode_On);
    value.setProperty("LuckDamageMode_Average", LuckDamageMode_Average);

    value.setProperty("GameRecord_SpecialEvents_Power", GameRecord_SpecialEvents_Power);
    value.setProperty("GameRecord_SpecialEvents_SuperPower", GameRecord_SpecialEvents_SuperPower);
    value.setProperty("GameRecord_SpecialEvents_HQCaptured", GameRecord_SpecialEvents_HQCaptured);
    value.setProperty("GameRecord_SpecialEvents_HQLost", GameRecord_SpecialEvents_HQLost);

    value.setProperty("GameAi_Normal", GameAi_Normal);
    value.setProperty("GameAi_Offensive", GameAi_Offensive);
    value.setProperty("GameAi_Defensive", GameAi_Defensive);
    value.setProperty("GameAi_Hold", GameAi_Hold);

    value.setProperty("AnimationMode_None", AnimationMode_None);
    value.setProperty("AnimationMode_All", AnimationMode_All);
    value.setProperty("AnimationMode_Own", AnimationMode_Own);
    value.setProperty("AnimationMode_Ally", AnimationMode_Ally);
    value.setProperty("AnimationMode_Enemy", AnimationMode_Enemy);
    value.setProperty("AnimationMode_OnlyBattleAll", AnimationMode_OnlyBattleAll);
    value.setProperty("AnimationMode_OnlyBattleOwn", AnimationMode_OnlyBattleOwn);
    value.setProperty("AnimationMode_OnlyBattleAlly", AnimationMode_OnlyBattleAlly);
    value.setProperty("AnimationMode_OnlyBattleEnemy", AnimationMode_OnlyBattleEnemy);


    value.setProperty("BuildingTarget_All", BuildingTarget_All);
    value.setProperty("BuildingTarget_Own", BuildingTarget_Own);
    value.setProperty("BuildingTarget_Enemy", BuildingTarget_Enemy);

    value.setProperty("UnitType_Ground", UnitType_Ground);
    value.setProperty("UnitType_Air", UnitType_Air);
    value.setProperty("UnitType_Naval", UnitType_Naval);

    value.setProperty("AiTurnMode_StartOfDay", AiTurnMode_StartOfDay);
    value.setProperty("AiTurnMode_DuringDay", AiTurnMode_DuringDay);
    value.setProperty("AiTurnMode_EndOfDay", AiTurnMode_EndOfDay);

    pInterpreter->setGlobal("GameEnums", value);
}

QString GameEnums::getUnitTypeText(UnitType type)
{
    switch (type)
    {
        case UnitType_Air:
        {
            return tr("Air");
        }
        case UnitType_Naval:
        {
            return tr("Naval");
        }
        case UnitType_Ground:
        {
            return tr("Ground");
        }
    }
    return tr("Ground");
}
