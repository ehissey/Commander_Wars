// this is the base class for terrain
var BUILDING =
{

    // loader for stuff which needs C++ Support
    init : function (building)
    {
    },
    getName : function()
    {
        return "";
    },
    // returns the defense of this terrain
    getDefense : function()
    {
        return 3;
    },

    // vision bonus for units created by this building
    getVisionBonus : function()
    {
        return 0;
    },

    getBuildingWidth : function()
    {
        // one field width default for most buildings
        return 1;
    },
    getBuildingHeigth : function()
    {
        // one field heigth default for most buildings
        return 1;
    },
    // called for loading the main sprites
    loadSprites : function(building, neutral)
    {
    },
    // the terrain on which a building can be placed
    // if the current terrain isn't in the list. it'll be replaced by the first :)
    getBaseTerrain : function(building)
    {
        return ["PLAINS", "STREET", "SNOW", "DESERT", "DESERT_PATH"];
    },

    addCaptureAnimationBuilding : function(animation, building, startColor, capturedColor)
    {
        animation.addBuildingSprite("town+mask", startColor , capturedColor, true);
        animation.addBuildingSprite("town", startColor , capturedColor, false);
    },

    canLargeBuildingPlaced : function(terrain, building, width, heigth)
    {
        var placeX = terrain.getX();
        var placeY = terrain.getY();
        var baseTerrains = building.getBaseTerrain();
        for (var x = 0; x < width; x++)
        {
            for (var y = 0; y < heigth; y++)
            {
                if (map.onMap(placeX - x, placeY - y))
                {
                    if (baseTerrains.indexOf(map.getTerrain(placeX - x, placeY - y).getTerrainID()) < 0)
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
        }
        return true;
    },

    canBuildingBePlaced : function(terrain, building)
    {
        var baseTerrains = building.getBaseTerrain();
        if (baseTerrains.indexOf(terrain.getTerrainID()) >= 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    },

    getBaseIncome : function()
    {
        return 1000;
    },

    getConstructionList : function(building)
    {
        return [];
    },

    getActions : function()
    {
        return "";
    },
    startOfTurn : function(building)
    {
        if (building.getOwner() !== null)
        {
            BUILDING.replenishUnit(building);
        }
    },

    getOffensiveBonus : function(building)
    {
        return 0;
    },

    getDefensiveBonus : function(building)
    {
        return 0;
    },
    getActionTargetFields : function(building)
    {
        // targets of a building. For most things this is a null pointer
        // return must be null or a QmlVectorPoint
        return null;
    },
    getActionTargetOffset : function(building)
    {
        // offset for large buildings since there reference point is bound to the lower right corner.
        return Qt.point(0, 0);
    },
    getIsAttackable : function(building, x, y)
    {
        return true;
    },

    replenishUnit: function(building)
    {
        // default impl replenishes our units
        // gets called at the start of a turn
        var constructionList = building.getConstructionList();
        var unit = building.getTerrain().getUnit();
        if ((unit !== null) &&
            (unit.getOwner() === building.getOwner()) &&
            (constructionList.indexOf(unit.getUnitID()) >= 0))
        {

            var x = unit.getX();
            var y = unit.getY();
            if (unit.canBeRepaired(Qt.point(x, y)))
            {
                // our unit and a repairable one
                // replenish it
                unit.refill();
                var repairAmount = 2 + unit.getRepairBonus(Qt.point(x, y));
                UNIT.repairUnit(unit, repairAmount);
                if (!unit.isStealthed(map.getCurrentViewPlayer()))
                {
                    var animation = GameAnimationFactory.createAnimation(x, y);
                    animation.addSprite("repair", map.getImageSize() / 2, map.getImageSize() / 3, 1400);
                    animation.addText(qsTr("REPAIR"), map.getImageSize() / 2 + 15, map.getImageSize() / 3, 0.7);
                }
            }
        }
    },

    getMiniMapIcon : function()
    {
        return "minimap_building";
    },

    onDestroyed : function(building)
    {
        // called when the building is destroyed and replacing of this building starts
    },

    getTerrainAnimationBase : function(unit, terrain)
    {
        return "base_air";
    },

    getDamage : function(building, unit)
    {
        return 0;
    },

    getBuildingTargets : function()
    {
        // hint for the ai
        return GameEnums.BuildingTarget_Own;
    },

    getTerrainAnimationForeground : function(unit, terrain)
    {
        if (globals.randInt(0, 1) === 0)
        {
            return "fore_town";
        }
        else
        {
            return "fore_town+0";
        }
    },

    getTerrainAnimationBackground : function(unit, terrain)
    {
        return "back_town";
    },

    getDescription : function()
    {
        return "";
    },

    // vision created by this field
    getVision : function()
    {
        return 0;
    },
};
