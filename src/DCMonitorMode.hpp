#ifndef BMS_VICTRON_SMART_SHUNT_DCMONITORMODE_HPP
#define BMS_VICTRON_SMART_SHUNT_DCMONITORMODE_HPP

namespace bms_victron_smart_shunt {
    enum DCMonitorMode {
        SolarCharger,
        WindTurbine,
        ShaftGenerator,
        Alternator,
        FuelCell,
        WaterGenerator,
        DCToDCCharger,
        ACCharger,
        GenericSource,
        BatteryMonitor,
        GenericLoad,
        ElectricDrive,
        Fridge,
        WaterPump,
        BilgePump,
        DCSystem,
        Inverter,
        WaterHeater,
        Unknown // Todo: should  I  keep this? using it in case of unknown code
    };
}

#endif