var Constructor = function()
{
    this.getTerrainGroup = function()
    {
        return 1;
    };
    // loader for stuff which needs C++ Support
    this.init = function (terrain)
    {
        terrain.setTerrainName(MOUNTAIN.getName());
    };
    this.getName = function()
    {
        return qsTr("Mountain");
    };
    this.getDefense = function()
    {
        return 4;
    };
    this.loadBaseTerrain = function(terrain, currentTerrainID)
    {
		terrain.loadBaseTerrain("PLAINS");
    };
    this.loadBaseSprite = function(terrain)
    {
        var surroundings = terrain.getSurroundings("MOUNTAIN", false, false, GameEnums.Directions_East, false);
        surroundings += terrain.getSurroundings("MOUNTAIN", false, false, GameEnums.Directions_West, false);
        terrain.loadBaseSprite("mountain" + surroundings);
    };
    this.getMiniMapIcon = function()
    {
        return "minimap_mountain";
    };
    this.getBonusVision = function(unit)
    {
        var infantry = ["INFANTRY", "MECH", "SNIPER", "MOTORBIKE"];
        if (infantry.indexOf(unit.getUnitID()) >= 0)
        {
            return 3;
        }
        else
        {
            return 0;
        }
    };
    this.getTerrainAnimationForeground = function(unit, terrain)
    {
        return "fore_mountain";
    };
    this.getTerrainAnimationBackground = function(unit, terrain)
    {
        return "back_mountain";
    };
    this.getDescription = function()
    {
        return "<r>" + qsTr("Clear view. In Fog of War, Infantry unit's gain ") + "</r>" +
               "<div c='#00ff00'>" + qsTr("vision +3.") + "</div>";
    };
    this.getTerrainSprites = function()
    {
        // array of sprites that can be selected as fix sprites for this terrain
        return ["mountain.png",
                "mountain+E",
                "mountain+E+W",
                "mountain+W"];
    };
};
Constructor.prototype = TERRAIN;
var MOUNTAIN = new Constructor();
