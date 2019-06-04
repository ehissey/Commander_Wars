CO_SABAKI.postBattleActions = function(co, attacker, atkDamage, defender, gotAttacked)
{
    if (co.getIsCO0() === true)
    {
        if (gotAttacked === false)
        {
            var healPercent = 0.0;
            switch (co.getPowerMode())
            {
            case GameEnums.PowerMode_Tagpower:
            case GameEnums.PowerMode_Superpower:
                healPercent = 1.0;
                break;
            case GameEnums.PowerMode_Power:
                healPercent = 0.5;
                break;
            default:
                healPercent = 0.15;
                break;

            }
            // damage can be negativ if we can't do a counter attack the damge is -1
            // avoid loosing hp cause of our passive or power
            if (atkDamage > 0)
            {
                attacker.setHp(attacker.getHp() + atkDamage * healPercent);
            }
        }
    }
};