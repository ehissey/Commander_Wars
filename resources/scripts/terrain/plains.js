var Constructor = function()
{
    // loader for stuff which needs C++ Support
    this.init = function (terrain)
    {
        // default a terrain has no animation
        terrain.Animated = false;
    };
    this.getDefense = function()
    {
        return 1;
    };
    this.loadBaseSprite = function(terrain)
    {
        var random = globals.randInt(-1, 3);
        if (random >= 0)
        {
            terrain.loadBaseSprite("plains+" + random.toString());
        }
        else
        {
            terrain.loadBaseSprite("plains");
        }
    };
};
Constructor.prototype = TERRAIN;
var PLAINS = new Constructor();
