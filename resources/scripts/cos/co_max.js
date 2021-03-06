var Constructor = function()
{
    this.getCOStyles = function()
    {
        // string array containing the endings of the alternate co style
        // e.g. co_adder has ["+alt"]
        return ["+alt"];
    };

    this.getAiUsePower = function(co, powerSurplus, unitCount, repairUnits, indirectUnits, directUnits, enemyUnits, turnMode)
    {
        return CO.getAiUsePowerAtUnitCount(co, powerSurplus, turnMode, directUnits);
    };

    this.init = function(co)
    {
        co.setPowerStars(3);
        co.setSuperpowerStars(3);
    };

    this.loadCOMusic = function(co)
    {
        // put the co music in here.
        switch (co.getPowerMode())
        {
            case GameEnums.PowerMode_Power:
                audio.addMusic("resources/music/cos/power.mp3", 992, 45321);
                break;
            case GameEnums.PowerMode_Superpower:
                audio.addMusic("resources/music/cos/superpower.mp3", 1505, 49515);
                break;
            case GameEnums.PowerMode_Tagpower:
                audio.addMusic("resources/music/cos/tagpower.mp3", 14611, 65538);
                break;
            default:
                audio.addMusic("resources/music/cos/max.mp3", 57, 70080)
                break;
        }
    };

    this.activatePower = function(co)
    {
        var dialogAnimation = co.createPowerSentence();
        var powerNameAnimation = co.createPowerScreen(GameEnums.PowerMode_Power);
        dialogAnimation.queueAnimation(powerNameAnimation);

        var units = co.getOwner().getUnits();
        var animations = [];
        var counter = 0;
        units.randomize();
        for (var i = 0; i < units.size(); i++)
        {
            var unit = units.at(i);
            if (unit.getBaseMaxRange() === 1)
            {
                var animation = GameAnimationFactory.createAnimation(unit.getX(), unit.getY());
                if (animations.length < 5)
                {
                    animation.addSprite("power6", -map.getImageSize() * 1.27, -map.getImageSize() * 1.27, 0, 1.5, globals.randInt(0, 400));
                    powerNameAnimation.queueAnimation(animation);
                    animations.push(animation);
                }
                else
                {
                    animation.addSprite("power6", -map.getImageSize() * 1.27, -map.getImageSize() * 1.27, 0, 1.5);
                    animations[counter].queueAnimation(animation);
                    animations[counter] = animation;
                    counter++;
                    if (counter >= animations.length)
                    {
                        counter = 0;
                    }
                }
            }
        }
        units.remove();

        audio.clearPlayList();
        CO_MAX.loadCOMusic(co);
        audio.playRandom();
    };

    this.activateSuperpower = function(co, powerMode)
    {
        var dialogAnimation = co.createPowerSentence();
        var powerNameAnimation = co.createPowerScreen(powerMode);
        dialogAnimation.queueAnimation(powerNameAnimation);

        var units = co.getOwner().getUnits();
        var animations = [];
        var counter = 0;
        units.randomize();
        for (var i = 0; i < units.size(); i++)
        {
            var unit = units.at(i);
            if (unit.getBaseMaxRange() === 1)
            {
                var animation = GameAnimationFactory.createAnimation(unit.getX(), unit.getY());
                if (animations.length < 5)
                {
                    animation.addSprite("power12", -map.getImageSize() * 2, -map.getImageSize() * 2, 0, 1.5, globals.randInt(0, 400));
                    powerNameAnimation.queueAnimation(animation);
                    animations.push(animation);
                }
                else
                {
                    animation.addSprite("power12", -map.getImageSize() * 2, -map.getImageSize() * 2, 0, 1.5);
                    animations[counter].queueAnimation(animation);
                    animations[counter] = animation;
                    counter++;
                    if (counter >= animations.length)
                    {
                        counter = 0;
                    }
                }
            }
        }
        units.remove();

        audio.clearPlayList();
        CO_MAX.loadCOMusic(co);
        audio.playRandom();
    };

    this.getCOUnitRange = function(co)
    {
        return 3;
    };
    this.getInfantryIDs = function()
    {
        return ["INFANTRY", "MECH", "SNIPER", "MOTORBIKE"];
    };
    this.getOffensiveBonus = function(co, attacker, atkPosX, atkPosY,
                                 defender, defPosX, defPosY, isDefender)
    {
        var unitInfantryIDs = CO_MAX.getInfantryIDs();
        switch (co.getPowerMode())
        {
            case GameEnums.PowerMode_Tagpower:
            case GameEnums.PowerMode_Superpower:
                if (attacker.getBaseMaxRange() === 1 && unitInfantryIDs.indexOf(attacker.getUnitID())  < 0)
                {
                    return 70;
                }                
                else if (attacker.getBaseMaxRange() > 1)
                {
                    return 0;
                }
                return 10;
            case GameEnums.PowerMode_Power:
                if (attacker.getBaseMaxRange() === 1 && unitInfantryIDs.indexOf(attacker.getUnitID())  < 0)
                {
                    return 45;
                }

                else if (attacker.getBaseMaxRange() > 1)
                {
                    return 0;
                }
                return 10;
            default:
                if (attacker.getBaseMaxRange() === 1 && unitInfantryIDs.indexOf(attacker.getUnitID())  < 0)
                {
                    if (co.inCORange(Qt.point(atkPosX, atkPosY), attacker))
                    {
                        return 35;
                    }
                    return 15;
                }
                break;
        }
        if (attacker.getBaseMaxRange() > 1)
        {
            return -10;
        }
        return 0;
    };
    this.getDeffensiveBonus = function(co, attacker, atkPosX, atkPosY,
                                       defender, defPosX, defPosY, isDefender)
    {
        if (co.inCORange(Qt.point(defPosX, defPosY), defender) ||
                co.getPowerMode() > GameEnums.PowerMode_Off)
        {
            return 10;
        }
        return 0;
    };
    this.getFirerangeModifier = function(co, unit, posX, posY)
    {
        if (unit.getBaseMaxRange() > 1)
        {
            return -1;
        }
    };
    this.getCOArmy = function()
    {
        return "OS";
    };
    this.getMovementpointModifier = function(co, unit, posX, posY)
    {
        var unitInfantryIDs = CO_MAX.getInfantryIDs();
        if (co.getPowerMode() === GameEnums.PowerMode_Power)
        {
            if (unit.getBaseMaxRange() === 1 && unitInfantryIDs.indexOf(unit.getUnitID())  < 0)
            {
                return 1;
            }
        }
        else if (co.getPowerMode() === GameEnums.PowerMode_Superpower ||
                 co.getPowerMode() === GameEnums.PowerMode_Tagpower)
        {
            if (unit.getBaseMaxRange() === 1 && unitInfantryIDs.indexOf(unit.getUnitID())  < 0)
            {
                return 2;
            }
        }
        return 0;
    };

    // CO - Intel
    this.getBio = function()
    {
        return qsTr("A brave and loyal friend, not to mention a strong fighter, Max hates any kind of treachery, preferring a good, old-fashioned brawl.");
    };
    this.getHits = function()
    {
        return qsTr("Weight Training");
    };
    this.getMiss = function()
    {
        return qsTr("Studying");
    };
    this.getCODescription = function()
    {
        return qsTr("Non-infantry direct-combat units are tops.");
    };
    this.getLongCODescription = function()
    {
        return qsTr("\nGlobal Effect:\nDirect Units gain 15% additional firepower and indirect Units loose 10% firepower and 1 firerange.") +
               qsTr("\nCO Zone Effect:\nDirect Units gain 35% additional firepower.");
    };
    this.getPowerDescription = function()
    {
        return qsTr("Firepower and movement of all non-infantry direct-combat units rises.");
    };
    this.getPowerName = function()
    {
        return qsTr("Max Force");
    };
    this.getSuperPowerDescription = function()
    {
        return qsTr("Firepower and movement of all non-infantry direct-combat units rises greatly.");
    };
    this.getSuperPowerName = function()
    {
        return qsTr("Max Blast");
    };
    this.getPowerSentences = function()
    {
        return [qsTr("Roll, tanks, roll!"),
                qsTr("Now you're gonna get hurt!"),
                qsTr("Hey!  Give up while you still can!"),
                qsTr("Wanna test might?  I won't lose!"),
                qsTr("That's enough!  Get outta the road!"),
                qsTr("Alright, the gloves are comin' off.")];
    };
    this.getVictorySentences = function()
    {
        return [qsTr("That was a piece of cake!"),
                qsTr("Ha! It'll take more than that to beat me!"),
                qsTr("I'm on a roll!")];
    };
    this.getDefeatSentences = function()
    {
        return [qsTr("Ouch... I let my guard down."),
                qsTr("Oh, man! Not good! What are we supposed to do now!?")];
    };
    this.getName = function()
    {
        return qsTr("Max");
    };
}

Constructor.prototype = CO;
var CO_MAX = new Constructor();
