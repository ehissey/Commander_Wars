var Constructor = function()
{
    this.getRuleDescription = function(itemNumber)
    {
        if (itemNumber === 0)
        {
            return qsTr("The player who reaches the number of buildings wins.")
        }
        else
        {
            return qsTr("If checked the Team needs to capture the given number of buildings else a single player needs to capture them.");
        }
    };

    this.getRuleName = function(itemNumber)
    {
        if (itemNumber === 0)
        {
            return qsTr("Capture Victory");
        }
        else
        {
            return qsTr("Team Counter");
        }
    };
    // the type how the rule will be represented in the map selection ui
    this.getRuleType = function()
    {
        // for now checkbox or spinbox
        return ["spinbox", "checkbox"];
    };
    // defines the default value during map selection for this rule
    this.getDefaultRuleValue = function(itemNumber)
    {
        if (itemNumber === 0)
        {
            return VICTORYRULE_BUILDINGLIMIT.getMinimumCount();
        }
        else
        {
            return 0;
        }
    };
    this.getInfiniteValue = function(itemNumber)
    {
        if (itemNumber === 0)
        {
            // disable value of the rule for spinboxes. :)
            return VICTORYRULE_BUILDINGLIMIT.getMinimumCount();
        }
        else
        {
            return 0;
        }
    };

    this.getMinimumCount = function()
    {
        var players = map.getPlayerCount();
        var buildingCount = 0;
        for (var i = 0; i < players; i++)
        {
            var count = map.getPlayer(i).getBuildingCount();
            if (count > buildingCount)
            {
                buildingCount = count;
            }
        }
        return buildingCount;
    };
	
    // create and initialize the variables for this rule
    this.init = function(rule)
    {
    };

    this.getBuildings = function(rule, player)
    {
        var count = player.getBuildingCount();
        var players = map.getPlayerCount();
        var teamVictory = VICTORYRULE_BUILDINGLIMIT.getRuleValue(rule, 1);
        if (teamVictory === 1)
        {
            for (var i = 0; i < players; i++)
            {
                var ally = map.getPlayer(i);
                if ((player !== ally) &&
                    (player.getTeam() === ally.getTeam()))
                {
                    count += ally.getBuildingCount();
                }
            }
        }
        return count;
    };
    // checks if the selected player is declared defeated by this rule
    this.checkDefeat = function(rule, player)
    {
        var buildings = VICTORYRULE_BUILDINGLIMIT.getBuildings(rule, player);
        var buildingLimit = VICTORYRULE_BUILDINGLIMIT.getRuleValue(rule);
        if (buildings >= buildingLimit)
		{
            // defeat all other player
            var players = map.getPlayerCount();
            for (var i = 0; i < players; i++)
            {
                var defeatPlayer = map.getPlayer(i);
                if (player.getTeam() !== defeatPlayer.getTeam())
                {
                    defeatPlayer.setIsDefeated(true);
                }
            }
        }
        return GameEnums.DefeatType_Alive;
    };
    this.getRuleProgress = function(rule, player)
    {
        return VICTORYRULE_BUILDINGLIMIT.getBuildings(rule, player);
    };
};

Constructor.prototype = VICTORYRULE;
var VICTORYRULE_BUILDINGLIMIT = new Constructor();
