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
        float voltage = base::unset<double>();
        /**
         * @brief Auxiliary (starter) voltage
         * Label: VS
         * Unit: V
         *
         */
        float auxiliary_voltage = base::unset<double>();
        /**
         * @brief Mid-point voltage of the battery bank
         * Label: VM
         * Unit: V
         *
         */
        float mid_point_voltage = base::unset<double>();
        /**
         * @brief Mid-point deviation of the battery bank
         * Label: DM
         * Unit: Percentage
         *
         */
        float mid_point_deviation = base::unset<double>();
        /**
         * @brief Main or channel 1 battery current
         * Label: I
         * Unit: A
         *
         */
        float current = base::unset<double>();
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
        float instantaneous_power = base::unset<double>();
        /**
         * @brief Consumed charge
         * Label: CE
         * Unit: Coulomb
         *
         */
        float consumed_charge = base::unset<double>();
        /**
         * @brief State-of-charge
         * Label: SOC
         * Unit: Percentage
         *
         */
        float state_of_charge = base::unset<double>();
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
         * Unit: Coulomb
         *
         */
        float deepest_discharge_depth = base::unset<double>();
        /**
         * @brief Depth of the last discharge
         * Label: H2
         * Unit: Coulomb
         *
         */
        float last_discharge_depth = base::unset<double>();
        /**
         * @brief Depth of the average discharge
         * Label: H3
         * Unit: Coulomb
         *
         */
        float average_discharge_depth = base::unset<double>();
        /**
         * @brief Number of charge cycles
         * Label: H4
         *
         */
        int charge_cycles_number = 0;
        /**
         * @brief Number of full discharges
         * Label: H5
         *
         */
        int full_discharges_number = 0;
        /**
         * @brief Cumulative charge drawn
         * Label: H6
         * Unit: Coulomb
         *
         */
        float cumulative_charge_drawn = base::unset<double>();
        /**
         * @brief Minimum main (battery) voltage
         * Label: H7
         * Unit: V
         *
         */
        float minimum_voltage = base::unset<double>();
        /**
         * @brief Maximum main (battery) voltage
         * Label: H8
         * Unit: V
         *
         */
        float maximum_voltage = base::unset<double>();
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
        int automatic_synchronizations_number = 0;
        /**
         * @brief Number of low main voltage alarms;
         * Label: H11
         *
         */
        int low_voltage_alarms_number = 0;
        /**
         * @brief Number of high main voltage alarms;
         * Label: H12
         *
         */
        int high_voltage_alarms_number = 0;
        /**
         * @brief Minimum auxiliary (battery) voltage;
         * Label: H13
         * Unit: V
         *
         */
        float minimum_auxiliary_voltage = base::unset<double>();
        /**
         * @brief Maximum auxiliary (battery) voltage;
         * Label: H14
         * Unit: V
         *
         */
        float maximum_auxiliary_voltage = base::unset<double>();
        /**
         * @brief Amount of discharged energy (BMV) / Amount of produced energy (DC
         * monitor);
         * Label: H17
         * Original device unit: 0.01 kWh
         * Unit: Joule
         */
        float discharged_energy = base::unset<double>();
        /**
         * @brief Amount of charged energy(BMV) / Amount of consumed energy(DC monitor);
         * Label: H18
         * Original device unit: 0.01 kWh
         * Unit: Joule
         */
        float charged_energy = base::unset<double>();
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
        /**
         * @brief The Feedback timestamp
         *
         */
        base::Time timestamp;
    };
}

#endif