#include <bms_victron_smart_shunt/Driver.hpp>
#include <bms_victron_smart_shunt/Protocol.hpp>
#include <iomanip>
#include <iostream>

using namespace std;
using namespace bms_victron_smart_shunt;

int usage()
{
    cerr << "Usage: "
         << "bms_victron_smart_shunt_ctl URI PERIOD NEEDED_PACKETS \n"
         << "URI is a valid iodrivers_base URI, e.g. serial:///dev/ttyUSB0:19200\n"
         << "PERIOD is time interval in seconds between two outputs, the default value "
            "is 0.1 seconds\n"
         << "NEEDED_PACKETS The number of packets needed to have a full feedback update\n"

         << flush;
    return 0;
}
int main(int argc, char const* argv[])
{
    if (argc < 2) {
        cerr << "not enough arguments" << endl;
        return usage();
    }
    string uri(argv[1]);
    Driver driver;
    driver.setReadTimeout(base::Time::fromMilliseconds(1000));
    driver.setWriteTimeout(base::Time::fromMilliseconds(1000));
    driver.openURI(uri);
    int poll_period_usec = 100000;
    if (argc >= 3) {
        poll_period_usec = atof(argv[2]) * 1000000;
    }
    int needed_packets = 2;
    if (argc >= 4) {
        needed_packets = atof(argv[3]);
    }

    while (true) {
        auto feedback = driver.processOne(needed_packets);
        if (driver.packetsCounter() >= 2) {
            cout << fixed << std::left << std::setw(42)
                 << "\nTimestamp: " << feedback.timestamp << std::left << std::setw(42)
                 << "\nProduct ID: " << feedback.product_id << std::left << std::setw(42)
                 << "\nVoltage: " << setprecision(3) << feedback.voltage << std::left
                 << std::setw(42) << "\nCurrent: " << feedback.current << std::left
                 << std::setw(42) << "\nInstantaneous power: " << setprecision(0)
                 << feedback.instantaneous_power << std::left << std::setw(42)
                 << "\nConsumed charge: " << setprecision(3) << feedback.consumed_charge
                 << std::left << std::setw(42) << "\nState of charge: " << setprecision(0)
                 << feedback.state_of_charge << std::left << std::setw(42)
                 << "\nTime to go (s): " << feedback.time_to_go.toSeconds() << std::left
                 << std::setw(42)
                 << "\nAlarm condition active: " << feedback.alarm_condition_active
                 << std::left << std::setw(42)
                 << "\nAlarm reason: " << feedback.alarm_reason << std::left
                 << std::setw(42) << "\nModel description: " << feedback.model_description
                 << std::left << std::setw(42)
                 << "\nFirmware version: " << feedback.firmware_version << std::left
                 << std::setw(42) << "\nDC monitor mode: " << feedback.dc_monitor_mode
                 << std::left << std::setw(42)
                 << "\nCharged energy: " << feedback.charged_energy << std::left
                 << std::setw(42)
                 << "\nDeepest discharge depth: " << feedback.deepest_discharge_depth
                 << std::left << std::setw(42)
                 << "\nLast discharge depth: " << feedback.last_discharge_depth
                 << std::left << std::setw(42)
                 << "\nAverage discharge depth: " << feedback.average_discharge_depth
                 << std::left << std::setw(42)
                 << "\nCharge cycles number: " << feedback.charge_cycles_number
                 << std::left << std::setw(42)
                 << "\nFull discharges number: " << feedback.full_discharges_number
                 << std::left << std::setw(42)
                 << "\nCumulative charge drawn: " << feedback.cumulative_charge_drawn
                 << std::left << std::setw(42) << "\nMinimum voltage: " << setprecision(3)
                 << feedback.minimum_voltage << std::left << std::setw(42)
                 << "\nMaximum voltage: " << feedback.maximum_voltage << std::left
                 << std::setw(42)
                 << "\nSeconds since last full charge: " << setprecision(0)
                 << feedback.seconds_since_last_full_charge.toSeconds() << std::left
                 << std::setw(42) << "\nNumber of automatic synchronizations: "
                 << feedback.automatic_synchronizations_number << std::left
                 << std::setw(42) << "\nNumber of low voltage alarms: "
                 << feedback.low_voltage_alarms_number << std::left << std::setw(42)
                 << "\nNumber of high voltage alarms: "
                 << feedback.high_voltage_alarms_number << std::left << std::setw(42)
                 << "\nMinimum auxiliary battery voltage: " << setprecision(3)
                 << feedback.minimum_auxiliary_battery_voltage << std::left
                 << std::setw(42) << "\nMaximum auxiliary battery voltage: "
                 << feedback.maximum_auxiliary_battery_voltage << std::left
                 << std::setw(42) << "\nDischarged energy: " << setprecision(0)
                 << feedback.discharged_energy << std::left << std::setw(42)
                 << "\nCharged energy: " << feedback.charged_energy << endl;
        }
        usleep(poll_period_usec);
    }
}
