#ifndef BMS_VICTRON_SMART_SHUNT_FIELDS_HPP
#define BMS_VICTRON_SMART_SHUNT_FIELDS_HPP

#include <base/Float.hpp>
#include <string>

namespace bms_victron_smart_shunt {
    /**
     *
     */
    struct Fields {
        /**
         * @brief Main or channel 1 (battery) voltage
         * Label: V
         * Unit: mV
         *
         */
        double voltage = base::unknown<double>();
        /**
         * @brief Auxiliary (starter) voltage
         * Label: VS
         * Unit: mV
         *
         */
        double auxiliary_voltage = base::unknown<double>();
        /**
         * @brief Mid-point voltage of the battery bank
         * Label: VM
         * Unit: mV
         *
         */
        double mid_point_voltage = base::unknown<double>();
        /**
         * @brief Mid-point deviation of the battery bank
         * Label: DM
         * Unit: Percentage
         *
         */
        double mid_point_deviation = base::unknown<double>();
        /**
         * @brief Main or channel 1 battery currents
         * Label: I
         * Unit: mA
         *
         */
        double current = base::unknown<double>();
        /**
         * @brief Battery temperature
         * Label: T
         * Unit: Celsius
         *
         */
        double temperature = base::unknown<double>();
        /**
         * @brief
         * Label: P
         * Unit: W
         *
         */
        double intantaneous_power = base::unknown<double>();
        /**
         * @brief Consumed Amp Hours
         * Label: CE
         * Unit: mAh
         *
         */
        // TODO: Is it a good name?
        double consumed_charge = base::unknown<double>();
        /**
         * @brief State-of-charge
         * Label: SOC
         * Unit: Percentage
         *
         */
        // TODO base time
        double state_of_charge = base::unknown<double>();
        /**
         * @brief Time-to-go
         * Label: TTG
         * Unit: Minutes
         *
         */
        double time_to_go = base::unknown<double>();
        /**
         * @brief Alarm condition active
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
         * @brief Alarm reason
         * Label: AR
         *
         */
        std::string alarm_reason;
        /**
         * @brief Depth of the deepest discharge
         * Label: H1
         * Unit: mAh
         *
         */
        double deepest_discharge_depth = base::unknown<double>();
        /**
         * @brief Depth of the last discharge
         * Label: H2
         * Unit: mAh
         *
         */
        double last_discharge_depth = base::unknown<double>();
        /**
         * @brief Depth of the average discharge
         * Label: H3
         * Unit: mAh
         *
         */
        double average_discharge_depth = base::unknown<double>();
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
         * Unit: mAh11
         *
         */
        double cumulative_charge_drawn = base::unknown<double>();
        /**
         * @brief Minimum main (battery) voltage
         * Label: H7
         * Unit: mV
         *
         */
        double minimum_voltage = base::unknown<double>();
        /**
         * @brief Maximum main (battery) voltage
         * Label: H8
         * Unit: mV
         *
         */
        double maximum_voltage = base::unknown<double>();
        /**
         * @brief Number of seconds since last full charge;
         * Label: H9
         * Unit: Seconds
         *
         */
        // todo base time
        double seconds_since_last_full_charge = base::unknown<double>();
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
         * Unit: mV
         *
         */
        double minimum_auxiliary_voltage = base::unknown<double>();
        /**
         * @brief Maximum auxiliary (battery) voltage;
         * Label: H14
         * Unit: mV
         *
         */
        double maximum_auxiliary_voltage = base::unknown<double>();
        /**
         * @brief Amount of discharged energy (BMV) / Amount of produced energy (DC
         * monitor);
         * Label: H17
         * Unit: 0.01 kWh
         *
         */
        double h17 = base::unknown<double>();
        /**
         * @brief Amount of charged energy(BMV) / Amount of consumed energy(DC monitor);
         * Label: H18
         * Unit: 0.01 kWh
         *
         */
        double h18 = base::unknown<double>();
        /**
         * @brief Model Description
         * Label: BMV
         *
         */
        // todo check type
        std::string model_description;
        /**
         * @brief Firmware Version
         * Label: FWE
         *
         */
        // todo check type
        std::string firmware_version;
        /**
         * @brief Product ID
         * Label: PID
         *
         */
        double product_id;
        /**
         * @brief DC monitor mode
         * Label: MON
         *
         */
        // todo check type
        std::string dc_monitor_mode;
    };
}

#endif