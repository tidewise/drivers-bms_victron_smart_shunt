#include <bms_victron_smart_shunt/Protocol.hpp>
#include <sstream>
#include <string>

using namespace bms_victron_smart_shunt;
using namespace std;

int protocol::extractPacket(const uint8_t* buffer, int buffer_size)
{
    if (buffer_size < MIN_PACKET_SIZE) {
        return 0;
    }
    int packet_start = 0;
    while (packet_start != buffer_size && buffer[packet_start] != PACKET_START_MARKER) {
        ++packet_start;
    }
    if (packet_start) {
        return -packet_start;
    }
    int checksum = 0;
    for (int i = 0; i < buffer_size; i++) {
        checksum = (checksum + buffer[i]) & 255; /* Take modulo 256 in account */
    }
    if (checksum == 0) {
        return buffer_size;
    }
    else {
        // todo: check
        return -1;
    }
}

DCMonitorMode protocol::unmarshalMode(int value)
{
    // todo how to deal witch error
    switch (value) {
        case -9:
            return DCMonitorMode(SolarCharger);
        case -8:
            return DCMonitorMode(WindTurbine);
        case -7:
            return DCMonitorMode(ShaftGenerator);
        case -6:
            return DCMonitorMode(Alternator);
        case -5:
            return DCMonitorMode(FuelCell);
        case -4:
            return DCMonitorMode(WaterGenerator);
        case -3:
            return DCMonitorMode(DCToDCCharger);
        case -2:
            return DCMonitorMode(ACCharger);
        case -1:
            return DCMonitorMode(GenericSource);
        case 0:
            return DCMonitorMode(BatteryMonitor);
        case 1:
            return DCMonitorMode(GenericLoad);
        case 2:
            return DCMonitorMode(ElectricDrive);
        case 3:
            return DCMonitorMode(Fridge);
        case 4:
            return DCMonitorMode(WaterPump);
        case 5:
            return DCMonitorMode(BilgePump);
        case 6:
            return DCMonitorMode(DCSystem);
        case 7:
            return DCMonitorMode(Inverter);
        case 8:
            return DCMonitorMode(WaterHeater);
        default:
            // todo: throw exception?
            return DCMonitorMode(Unknown);
    }
}

Fields protocol::parseFields(uint8_t const* buffer, int buffer_size)
{
    Fields data;
    std::string data_str(reinterpret_cast<const char*>(buffer), buffer_size);
    std::istringstream stream(data_str);
    std::string line;
    while (std::getline(stream, line, char(LINE_DELIMITER))) {
        size_t field_delimiter_pos = line.find(FIELD_DELIMITER);
        std::string field;
        std::string value;
        if (field_delimiter_pos != std::string::npos) {
            field = line.substr(0, field_delimiter_pos);
            value = line.substr(field_delimiter_pos + 1);
            value.erase(value.size() - 1);
        }
        int val;
        std::stringstream(value) >> val;
        if (field == "V") {
            data.voltage = val;
        }
        if (field == "VS") {
            data.auxiliary_voltage = val;
        }
        if (field == "VM") {
            data.mid_point_voltage = val;
        }
        if (field == "DM") {
            data.mid_point_deviation = val;
        }
        if (field == "I") {
            data.current = val;
        }
        if (field == "T") {
            data.temperature = val;
        }
        if (field == "P") {
            data.intantaneous_power = val;
        }
        if (field == "CE") {
            data.consumed_charge = val;
        }
        if (field == "SOC") {
            data.state_of_charge = val;
        }
        if (field == "TTG") {
            data.time_to_go = val;
        }
        if (field == "Alarm") {
            data.alarm_condition_active = value;
        }
        if (field == "Relay") {
            data.relay_state = value;
        }
        if (field == "AR") {
            data.alarm_reason = val;
        }
        if (field == "H1") {
            data.deepest_discharge_depth = val;
        }
        if (field == "H2") {
            data.last_discharge_depth = val;
        }
        if (field == "H3") {
            data.average_discharge_depth = val;
        }
        if (field == "H4") {
            data.charge_cycles_number = val;
        }
        if (field == "H5") {
            data.full_discharges_number = val;
        }
        if (field == "H6") {
            data.cumulative_charge_drawn = val;
        }
        if (field == "H7") {
            data.minimum_voltage = val;
        }
        if (field == "H8") {
            data.maximum_voltage = val;
        }
        if (field == "H9") {
            data.seconds_since_last_full_charge = val;
        }
        if (field == "H10") {
            data.automatic_synchronizations_number = val;
        }
        if (field == "H11") {
            data.low_voltage_alarms_number = val;
        }
        if (field == "H12") {
            data.high_voltage_alarms_number = val;
        }
        if (field == "H13") {
            data.minimum_auxiliary_voltage = val;
        }
        if (field == "H14") {
            data.maximum_auxiliary_voltage = val;
        }
        if (field == "H17") {
            data.h17 = val;
        }
        if (field == "H18") {
            data.h18 = val;
        }
        if (field == "BMV") {
            data.model_description = val;
        }
        if (field == "FWE") {
            data.firmware_version = val;
        }
        if (field == "PID") {
            data.product_id = val;
        }
        if (field == "MON") {
            data.dc_monitor_mode = protocol::unmarshalMode(val);
        }
    }
    return data;
}
