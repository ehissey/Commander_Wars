var Constructor = function()
{
    // called for loading the main sprite
    this.canBePerformed = function(action)
    {
        var co = map.getCurrentPlayer().getCO(0);
        if ((co !== null) && co.canUsePower())
        {
            return true;
        }
        else
        {
            return false;
        }
    };
    this.getActionText = function()
    {
        return qsTr("Power of ") + map.getCurrentPlayer().getCO(0).getCOName();
    };
    this.getIcon = function()
    {
        return "power";
    };
    this.perform = function(action)
    {
        map.getCurrentPlayer().getCO(0).activatePower();
        map.getGameRecorder().addSpecialEvent(map.getCurrentPlayer().getPlayerID(),
                                              GameEnums.GameRecord_SpecialEvents_Power);
    };
    this.isFinalStep = function(action)
    {
        return true;
    };
}


Constructor.prototype = ACTION;
var ACTION_ACTIVATE_POWER_CO_0 = new Constructor();
