var Constructor = function()
{
    // called for loading the main sprite
    this.canBePerformed = function(action)
    {
        var building = action.getTargetBuilding();
        if (building.getFireCount() >= 1)
        {
            if (ACTION_MINICANNON_FIRE.getTargets(building).length > 0)
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    };
    this.getActionText = function()
    {
        return qsTr("Fire");
    };
    this.getIcon = function()
    {
        return "fire";
    };
    this.getStepInputType = function(action)
    {
        return "FIELD";
    };
    this.getStepCursor = function(action, cursorData)
    {
        cursorData.setCursor("cursor+attack");
        cursorData.setXOffset(- map.getImageSize() / 3);
        cursorData.setYOffset(- map.getImageSize() / 3);
        cursorData.setScale(1.5);
    };
    this.isFinalStep = function(action)
    {
        if (action.getInputStep() === 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    };
    this.getTargets = function(building)
    {
        var x = building.getX();
        var y = building.getY();
        var fields = Global[building.getBuildingID()].getActionTargetFields(building);
        var ret = [];
        for (var i = 0; i < fields.size(); i++)
        {
            var point = fields.at(i);
            var unit = map.getTerrain(x + point.x, y + point.y).getUnit();
            if ((unit !== null) &&
                (building.getOwner().isEnemyUnit(unit)))
            {
                if (building.getOwner().getFieldVisible(unit.getX(), unit.getY()))
                {
                    if (!unit.isStealthed(building.getOwner()))
                    {
                        ret.push(Qt.point(x + point.x, y + point.y));
                    }
                }
            }
        }
        fields.remove();
        return ret;
    };
    this.getStepData = function(action, data)
    {
        var building = action.getTargetBuilding();
        var targets = ACTION_MINICANNON_FIRE.getTargets(building);
        for (var i = 0; i < targets.length; i++)
        {
            data.addPoint(Qt.point(targets[i].x, targets[i].y));
            data.addZInformation(30);
        }
        data.setColor("#FF0000");
        data.setZLabelColor("#ff4500");
        data.setZLabelText(qsTr("Damage"))
        data.setShowZData(true);
    };

    this.perform = function(action)
    {
        // we need to move the unit to the target position
        var building = action.getTargetBuilding();
        var x = building.getX();
        var y = building.getY();
        building.setFireCount(building.getFireCount() - 1);
        action.startReading();
        var targetX = action.readDataInt32();
        var targetY = action.readDataInt32();
        var unit = map.getTerrain(targetX, targetY).getUnit();
        unit.setHp(unit.getHpRounded() - 3);
        if (unit.getHp() <= 0)
        {
            unit.killUnit();
        }
    };
}

Constructor.prototype = ACTION;
var ACTION_MINICANNON_FIRE = new Constructor();