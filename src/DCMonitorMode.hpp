#ifndef BMS_VICTRON_SMART_SHUNT_DCMONITORMODE_HPP
#define BMS_VICTRON_SMART_SHUNT_DCMONITORMODE_HPP

namespace bms_victron_smart_shunt {
    /**
     * @brief The DC monitor modes
     *
     */
    enum DCMonitorMode {
        SOLAR_CHARGER = -9,
        WIND_TURBINE = -8,
        SHAFT_GENERATOR = -7,
        ALTERNATOR = -6,
        FUEL_CELL = -5,
        WATER_GENERATOR = -4,
        DC_TO_DC_CHARGER = -3,
        AC_CHARGER = -2,
        GERNERIC_SOURCE = -1,
        BATTERY_MONITOR = 0,
        GENERIC_LOAD = 1,
        ELETRIC_DRIVE = 2,
        FRIDGE = 3,
        WATER_PUMP = 4,
        BILGE_PUMP = 5,
        DC_SYSTEM = 6,
        INVERTER = 7,
        WATER_HEATER = 8
    };
}

#endif