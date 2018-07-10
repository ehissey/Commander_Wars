var Constructor = function()
{
    // loader for stuff which needs C++ Support
    this.init = function (terrain)
    {
        terrain.terrainName = qsTr("Destroyed Weld");
    };
	this.loadBaseTerrain = function(terrain)
    {
		terrain.loadBaseTerrain("PLAINS");
    };
    this.loadBaseSprite = function(terrain)
    {
        var surroundings = terrain.getSurroundings("PIPELINE", false, false, TERRAIN.Direct);
        if ((surroundings === ""))
        {
            terrain.loadBaseSprite("destroyedweld+E+W");
        }
        else if ((surroundings === "+N+S"))
        {
			
            terrain.loadBaseSprite("destroyedweld+N+S");
        }
        else if ((surroundings === "+E+W"))
        {
            terrain.loadBaseSprite("destroyedweld+E+W");
        }
    };
    this.canBePlaced = function(x, y)
    {
        var terrain = map.getTerrain(x, y);
        var surroundings = terrain.getSurroundings("PIPELINE", false, false, TERRAIN.Direct);
        if ((surroundings === "+E+W") || (surroundings === "+N+S"))
        {
            return true;
        }
        else
        {
            return false;
        }
    };
};
Constructor.prototype = TERRAIN;
var DESTROYEDWELD = new Constructor();
