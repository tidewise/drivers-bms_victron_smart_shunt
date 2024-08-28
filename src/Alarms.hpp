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
        NORMAL_OPERATION = 0,
        LOW_VOLTAGE = 1,
        HIGH_VOLTAGE = 2,
        LOW_STATE_OF_CHARGE = 4,
        LOW_STATER_VOLTAGE = 8,
        HIGH_STATER_VOLTAGE = 16,
        LOW_TEMPERATURE = 32,
        HIGH_TEMPERATURE = 64,
        MID_VOLTAGE = 128
    };
}

#endif