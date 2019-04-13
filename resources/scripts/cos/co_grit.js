var Constructor = function()
{
    this.init = function(co)
    {
        co.setPowerStars(3);
        co.setSuperpowerStars(3);
    };

    this.getDirectUnitIDS = function()
    {
        return ["BOMBER", "CANNONBOAT", "CRUISER", "DESTROYER", "DUSTER",
                "FIGHTER", "FLAK", "FLARE", "HEAVY_HOVERCRAFT", "HEAVY_TANK",
                "HOVERCRAFT", "HOVERFLAK", "K_HELI", "LIGHT_TANK", "MEGATANK",
                "NEOTANK", "RECON", "STEALTHBOMBER", "SUBMARINE", "WATERPLANE"];
    };
    this.getIndirectUnitIDS = function()
    {
        return ["AIRCRAFTCARRIER", "ANTITANKCANNON", "ARTILLERY", "BATTLESHIP",
                "MISSILE", "PIPERUNNER", "ROCKETTHROWER", "SNIPER"];
    };

    this.loadCOMusic = function(co)
    {
        // put the co music in here.
        switch (co.getPowerMode())
        {
            case GameEnums.PowerMode_Power:
                audio.addMusic("resources/music/cos/power.mp3");
                break;
            case GameEnums.PowerMode_Superpower:
                audio.addMusic("resources/music/cos/superpower.mp3");
                break;
            default:
                audio.addMusic("resources/music/cos/grit.mp3")
                break;
        }
    };

    this.activatePower = function(co)
    {
        var units = co.getPlayer().getUnits();
        var animations = [];
        var counter = 0;
        var tankUnits = CO_GRIT.getIndirectUnitIDS();
        units.randomize();
        for (var i = 0; i < units.size(); i++)
        {
            var unit = units.at(i);
            if (tankUnits.indexOf(unit.getUnitID()) >= 0)
            {
                var animation = GameAnimationFactory.createAnimation(unit.getX(), unit.getY());
                if (animations.length < 5)
                {
                    animation.addSprite("power9", -map.getImageSize() * 1.27, -map.getImageSize() * 1.27, 0, 1.5, globals.randInt(0, 400));
                    animations.push(animation);
                }
                else
                {
                    animation.addSprite("power9", -map.getImageSize() * 1.27, -map.getImageSize() * 1.27, 0, 1.5);
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
        CO_GRIT.loadCOMusic(co);
        audio.playRandom();
    };

    this.activateSuperpower = function(co)
    {
        var units = co.getPlayer().getUnits();
        var animations = [];
        var counter = 0;
        var tankUnits = CO_GRIT.getIndirectUnitIDS();
        units.randomize();
        for (var i = 0; i < units.size(); i++)
        {
            var unit = units.at(i);
            if (tankUnits.indexOf(unit.getUnitID())  >= 0)
            {
                var animation = GameAnimationFactory.createAnimation(unit.getX(), unit.getY());
                if (animations.length < 5)
                {
                    animation.addSprite("power12", -map.getImageSize() * 2, -map.getImageSize() * 2, 0, 1.5, globals.randInt(0, 400));
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
        CO_GRIT.loadCOMusic(co);
        audio.playRandom();
    };

    this.getCOUnitRange = function(co)
    {
        return 2;
    };
    this.getOffensiveBonus = function(co, attacker, atkPosX, atkPosY,
                                 defender, defPosX, defPosY, isDefender)
    {
        var tankUnits = CO_GRIT.getDirectUnitIDS();
        var indirectUnits = CO_GRIT.getIndirectUnitIDS();
        switch (co.getPowerMode())
        {
            case GameEnums.PowerMode_Superpower:
                if (indirectUnits.indexOf(attacker.getUnitID()) >= 0)
                {
                    return 70;
                }
                break;
            case GameEnums.PowerMode_Power:
                if (indirectUnits.indexOf(attacker.getUnitID()) >= 0)
                {
                    return 50;
                }
                break;
            default:
                if (indirectUnits.indexOf(attacker.getUnitID()) >= 0)
                {
                    if (co.inCORange(Qt.point(atkPosX, atkPosY)))
                    {
                        return 30;
                    }
                    return 15;
                }
                break;
        }
        if (tankUnits.indexOf(attacker.getUnitID()) >= 0)
        {
            return -20;
        }
        return 0;
    };
    this.getFirerangeModifier = function(co, unit, posX, posY)
    {
        var indirectUnits = CO_GRIT.getIndirectUnitIDS();
        switch (co.getPowerMode())
        {
            case GameEnums.PowerMode_Superpower:
                if (indirectUnits.indexOf(unit.getUnitID()) >= 0)
                {
                    return 3;
                }
                break;
            case GameEnums.PowerMode_Power:
                if (indirectUnits.indexOf(unit.getUnitID()) >= 0)
                {
                    return 2;
                }
                break;
            default:
                if (indirectUnits.indexOf(unit.getUnitID()) >= 0)
                {
                    return 1;
                }
                break;
        }
        return 0;
    };
    this.getCOArmy = function()
    {
        return "BM";
    };

    // CO - Intel
    this.getBio = function()
    {
        return qsTr("A laid-back style masks his dependability. A peerless marksman. Works well with Olaf.");
    };
    this.getHits = function()
    {
        return qsTr("Cats");
    };
    this.getMiss = function()
    {
        return qsTr("Rats");
    };
    this.getCODescription = function()
    {
        return qsTr("Indirect-combat units cause more damage and have increased firerange. Weak in non-infantry direct combat.");
    };
    this.getPowerDescription = function()
    {
        return qsTr("Increases range of indirect units by one space. Firepower of these units also rise.");
    };
    this.getPowerName = function()
    {
        return qsTr("Snipe Attack");
    };
    this.getSuperPowerDescription = function()
    {
        return qsTr("Increases range of indirect units by two spaces. Firepower of these units greatly rise.");
    };
    this.getSuperPowerName = function()
    {
        return qsTr("Super Snipe");
    };
    this.getPowerSentences = function()
    {
        return [qsTr("Once you're in my sights, there's no gettin' away!"),
                qsTr("Reckon it's time to take you down!"),
                qsTr("Where's the fool who wants to help me with target practice?"),
                qsTr("Y'all can run, but you can't hide!"),
                qsTr("Y'all gimme no choice... Time to bring in the big guns!"),
                qsTr("Aw, shucks. I was hopin' it wouldn't come to this.")];
    };
    this.getVictorySentences = function()
    {
        return [qsTr("This ain't for show."),
                qsTr("Maybe now I can get some shut-eye."),
                qsTr("I hope this gets easier. That was harder'n college!")];
    };
    this.getDefeatSentences = function()
    {
        return [qsTr("Aw, possum spit!"),
                qsTr("Just as I reckoned... This ain't gonna be no Sunday stroll.")];
    };
    this.getName = function()
    {
        return qsTr("Grit");
    };
}

Constructor.prototype = CO;
var CO_GRIT = new Constructor();
