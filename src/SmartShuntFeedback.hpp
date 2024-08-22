#ifndef BMS_VICTRON_SMART_SHUNT_SMARTSHUNTFEEDBACK_HPP
#define BMS_VICTRON_SMART_SHUNT_SMARTSHUNTFEEDBACK_HPP

#include <base/Float.hpp>
#include <base/Temperature.hpp>
#include <base/Time.hpp>
#include <bms_victron_smart_shunt/Alarms.hpp>
#include <bms_victron_smart_shunt/DCMonitorMode.hpp>
#include <string>

namespace bms_victron_smart_shunt {
    /**
     * @brief The Victron Smart Shunt Feedback. More information about the
     * SmartShuntFeedback can be obtained inn the following webpage:
     * https://www.victronenergy.com/upload/documents/VE.Direct-Protocol-3.33.pdf
     *
     */
    struct SmartShuntFeedback {
        /**
         * @brief Main or channel 1 (battery) voltage
         * Label: V
         * Unit: V
         *
         */
        float voltage;
        /**
         * @brief Auxiliary (starter) voltage
         * Label: VS
         * Unit: V
         *
         */
        float auxiliary_voltage;
        /**
         * @brief Mid-point voltage of the battery bank
         * Label: VM
         * Unit: V
         *
         */
        float mid_point_voltage;
        /**
         * @brief Mid-point deviation of the battery bank
         * Label: DM
         * Unit: Percentage
         *
         */
        int mid_point_deviation;
        /**
         * @brief Main or channel 1 battery current
         * Label: I
         * Unit: A
         *
         */
        float current;
        /**
         * @brief Battery temperature
         * Label: T
         *
         */
        base::Temperature temperature;
        /**
         * @brief Instantaneous power
         * Label: P
         * Unit: W
         *
         */
        int intantaneous_power;
        /**
         * @brief Consumed Amp Hours
         * Label: CE
         * Unit: Ah
         *
         */
        float consumed_charge;
        /**
         * @brief State-of-charge
         * Label: SOC
         * Unit: Percentage
         *
         */
        int state_of_charge;
        /**
         * @brief Time-to-go
         * Label: TTG
         *
         */
        base::Time time_to_go;
        /**
         * @brief Alarm condition active. During normal operation, this will be “OFF”.
         * When a buzzer alarm occurs the value will change to “ON”.
         * Label: Alarm
         *
         */
        std::string alarm_condition_active;
        /**
         * @brief Relay state
         * Label: Relay
         *
         */
        std::string relay_state;
        /**
         * @brief Alarm reason. This field describes the cause of the alarm. Since
         * multiple alarm conditions can be present at same time the values of the
         * separate alarm conditions are added. The value total is sent in decimal
         * notation.
         * Label: AR
         *
         */
        bms_victron_smart_shunt::Alarms alarm_reason;
        /**
         * @brief Depth of the deepest discharge
         * Label: H1
         * Unit: Ah
         *
         */
        float deepest_discharge_depth;
        /**
         * @brief Depth of the last discharge
         * Label: H2
         * Unit: Ah
         *
         */
        float last_discharge_depth;
        /**
         * @brief Depth of the average discharge
         * Label: H3
         * Unit: Ah
         *
         */
        float average_discharge_depth;
        /**
         * @brief Number of charge cycles
         * Label: H4
         *
         */
        int charge_cycles_number;
        /**
         * @brief Number of full discharges
         * Label: H5
         *
         */
        int full_discharges_number;
        /**
         * @brief Cumulative Amp Hours drawn
         * Label: H6
         * Unit: Ah
         *
         */
        float cumulative_charge_drawn;
        /**
         * @brief Minimum main (battery) voltage
         * Label: H7
         * Unit: V
         *
         */
        float minimum_voltage;
        /**
         * @brief Maximum main (battery) voltage
         * Label: H8
         * Unit: V
         *
         */
        float maximum_voltage;
        /**
         * @brief Number of seconds since last full charge;
         * Label: H9
         *
         */
        base::Time seconds_since_last_full_charge;
        /**
         * @brief Number of automatic_synchronizations;
         * Label: H10
         *
         */
        int automatic_synchronizations_number;
        /**
         * @brief Number of low main voltage alarms;
         * Label: H11
         *
         */
        int low_voltage_alarms_number;
        /**
         * @brief Number of high main voltage alarms;
         * Label: H12
         *
         */
        int high_voltage_alarms_number;
        /**
         * @brief Minimum auxiliary (battery) voltage;
         * Label: H13
         * Unit: V
         *
         */
        float minimum_auxiliary_voltage;
        /**
         * @brief Maximum auxiliary (battery) voltage;
         * Label: H14
         * Unit: V
         *
         */
        float maximum_auxiliary_voltage;
        /**
         * @brief Amount of discharged energy (BMV) / Amount of produced energy (DC
         * monitor);
         * Label: H17
         * Original device unit: 0.01 kWh
         * Unit: Wh
         */
        int discharged_energy;
        /**
         * @brief Amount of charged energy(BMV) / Amount of consumed energy(DC monitor);
         * Label: H18
         * Original device unit: 0.01 kWh
         * Unit: Wh
         */
        int charged_energy;
        /**
         * @brief Model Description
         * Label: BMV
         *
         */
        std::string model_description;
        /**
         * @brief Firmware Version
         * Label: FWE
         *
         */
        std::string firmware_version;
        /**
         * @brief Product ID
         * Label: PID
         *
         */
        std::string product_id;
        /**
         * @brief DC monitor mode
         * Label: MON
         *
         */
        DCMonitorMode dc_monitor_mode;
    };
}

#endif