#ifndef BMS_VICTRON_SMART_SHUNT_ALARMS_HPP
#define BMS_VICTRON_SMART_SHUNT_ALARMS_HPP

namespace bms_victron_smart_shunt {
    /**
     * @brief The alarm reasons
     *
     * Since multiple alarm conditions can be present at the same time the values of the
     * separate alarm conditions are added. The value total is sent in decimal notation.
     *
     */
    enum Alarms {
        LowVoltage = 1,
        HighVoltage = 2,
        LowStateOfCharge = 4,
        LowStarterVoltage = 8,
        HighStarterVoltage = 16,
        LowTemperature = 32,
        HighTemperature = 64,
        MidVoltage = 128
    };
}

#endif