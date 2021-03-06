var Constructor = function()
{
    this.getMaxUnitCount = function()
    {
        return 1;
    };

    this.loadStandingAnimation = function(sprite, unit, defender, weapon)
    {
        var player = unit.getOwner();
        // get army name
        var armyName = "+" + player.getArmy().toLowerCase();
        if (armyName === "bg")
        {
            armyName = "bh"
        }
        if ((armyName !== "+os"))
        {
            armyName = "";
        }
        sprite.loadSprite("megatank" + armyName,  false,
                          BATTLEANIMATION_MEGATANK.getMaxUnitCount(), Qt.point(5, 10));
        sprite.loadSprite("megatank" + armyName + "+mask",  true,
                          BATTLEANIMATION_MEGATANK.getMaxUnitCount(), Qt.point(5, 10));
    };

    this.loadFireAnimation = function(sprite, unit, defender, weapon)
    {
        BATTLEANIMATION_MEGATANK.loadStandingAnimation(sprite, unit, defender, weapon);
        var offset = Qt.point(0, 0);
        if (weapon === 0)
        {
            offset = Qt.point(95, 83);
            var count = sprite.getUnitCount(5);
            for (var i = 0; i < count; i++)
            {
                var offset2 = Qt.point(0, 0);
                switch (i)
                {
                case 1:
                    offset2 = Qt.point(-5, -2);
                    break;
                case 2:
                    offset2 = Qt.point(-10, -4);
                    break;
                case 3:
                    offset2 = Qt.point(5, -30);
                    break;
                case 4:
                    offset2 = Qt.point(-13, -37);
                    break;
                }

                sprite.loadSingleMovingSprite("medium_shot", false,
                                              Qt.point(offset.x + offset2.x,
                                                       offset.y + offset2.y),
                                              Qt.point(0, 0), 0, true,
                                              1, 1.0, 5, 200 * i, false);
                sprite.loadSound("tank_shot.wav", 1, "resources/sounds/", 200 * i);
            }
        }
        else
        {
            // mg
            offset = Qt.point(105, 73);
            sprite.loadSprite("mg_shot",  false, sprite.getMaxUnitCount(), offset,
                              1, 1, 0, 0, false, true);
        }
    };

    this.getFireDurationMS = function()
    {
        // the time will be scaled with animation speed inside the engine
        return 1500;
    };

    this.loadImpactAnimation = function(sprite, unit, defender, weapon)
    {
        if (weapon === 0)
        {
            sprite.loadSprite("unit_explosion",  false, 5, Qt.point(0, 20),
                              1, 1.0, 0, 0);
            sprite.loadSound("impact_explosion.wav", 1, "resources/sounds/", 0);
        }
        else
        {
            sprite.loadSprite("mg_hit",  false, 5, Qt.point(0, 22),
                              1, 1.0, 0, 0);
            sprite.loadSound("mg_impact.wav", 1, "resources/sounds/", 0);
        }
    };
};

Constructor.prototype = BATTLEANIMATION;
var BATTLEANIMATION_MEGATANK = new Constructor();
