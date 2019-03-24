var Constructor = function()
{
    // loader for stuff which needs C++ Support
    this.init = function (terrain)
    {
        terrain.setTerrainName(qsTr("Plains"));
    };
	this.getDefense = function()
    {
        return 1;
    };
    this.loadBaseSprite = function(terrain)
    {
        var surroundings = terrain.getSurroundings("PLAINS_PLASMA", false, false, GameEnums.Directions_Direct, false);
        terrain.loadBaseSprite("plains+plasma" + surroundings);
    };
    this.getMiniMapIcon = function()
    {
        return "minimap_plains";
    };
};
Constructor.prototype = TERRAIN;
var PLAINS_PLASMA = new Constructor();
