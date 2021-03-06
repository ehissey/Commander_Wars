var Constructor = function()
{
    this.getTerrainGroup = function()
    {
        return 2;
    };
    // loader for stuff which needs C++ Support
    this.init = function (terrain)
    {
        terrain.setTerrainName(DESERT_PATH.getName());
    };
    this.getName = function()
    {
        return qsTr("Path");
    };
    this.loadBaseTerrain = function(terrain, currentTerrainID)
    {
        if (currentTerrainID === "SNOW")
        {
            terrain.loadBaseTerrain("SNOW");
        }
        else if (currentTerrainID === "PLAINS")
        {
            terrain.loadBaseTerrain("PLAINS");
        }
        else
        {
            terrain.loadBaseTerrain("DESERT");
        }
    };
    this.getFirerangeModifier = function(terrain, unit)
    {
        return -1;
    };
    this.loadBaseSprite = function(terrain)
    {
        var surroundings = terrain.getSurroundings("STREET,BRIDGE,DESERT_PATH",
                                                   false, false, GameEnums.Directions_Direct, false, true);
        terrain.loadBaseSprite("desert_path" + surroundings);
    };
    this.getMiniMapIcon = function()
    {
        return "minimap_street";
    };
    this.getTerrainAnimationForeground = function(unit, terrain)
    {
        return "fore_street";
    };
    this.getDescription = function()
    {
        return qsTr("Kinda well-surfaced path through the desert provides optimum mobility but little cover. It reduces the firerange of indirect units by 1.");
    };

    this.getTerrainSprites = function()
    {
        // array of sprites that can be selected as fix sprites for this terrain
        return ["desert_path",
                "desert_path+E",
                "desert_path+E+S",
                "desert_path+E+S+W",
                "desert_path+E+W",
                "desert_path+N",
                "desert_path+N+E",
                "desert_path+N+E+S",
                "desert_path+N+E+S+W",
                "desert_path+N+E+W",
                "desert_path+N+S",
                "desert_path+N+S+W",
                "desert_path+N+W",
                "desert_path+S",
                "desert_path+S+W",
                "desert_path+W"];
    };
};
Constructor.prototype = TERRAIN;
var DESERT_PATH = new Constructor();
