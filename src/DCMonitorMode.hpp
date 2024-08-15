#ifndef BMS_VICTRON_SMART_SHUNT_DCMONITORMODE_HPP
#define BMS_VICTRON_SMART_SHUNT_DCMONITORMODE_HPP

namespace bms_victron_smart_shunt {
    enum DCMonitorMode {
        SolarCharger = -9,
        WindTurbine = -8,
        ShaftGenerator = -7,
        Alternator = -6,
        FuelCell = -5,
        WaterGenerator = -4,
        DCToDCCharger = -3,
        ACCharger = -2,
        GenericSource = -1,
        BatteryMonitor = 0,
        GenericLoad = 1,
        ElectricDrive = 2,
        Fridge = 3,
        WaterPump = 4,
        BilgePump = 5,
        DCSystem = 6,
        Inverter = 7,
        WaterHeater = 8
    };
}

#endif