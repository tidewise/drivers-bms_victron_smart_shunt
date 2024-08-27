#include <algorithm>
#include <bms_victron_smart_shunt/Protocol.hpp>
#include <cstring>
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
    auto checksum_begin_it = std::search(buffer,
        buffer + buffer_size,
        CHECKSUM_STR,
        CHECKSUM_STR + CHECKSUM_STR_LEN);
    if (checksum_begin_it == buffer + buffer_size) {
        // There is still no checksum, wait for more bytes
        return 0;
    }
    int packet_size = checksum_begin_it - buffer + CHECKSUM_STR_LEN + 2;
    int checksum = 0;
    for (int i = 0; i < packet_size; i++) {
        // Take modulo 256 in account
        checksum = (checksum + buffer[i]) & 255;
    }
    if (checksum == 0) {
        // Returns the packet size without the checksum field
        return checksum_begin_it - buffer - 2;
    }
    else {
        return -1;
    }
}

SmartShuntFeedback protocol::parseSmartShuntFeedback(uint8_t const* buffer,
    int buffer_size)
{
    SmartShuntFeedback data;
    std::string data_str(reinterpret_cast<const char*>(buffer), buffer_size);
    std::istringstream stream(data_str);
    std::string line;
    while (std::getline(stream, line, PACKET_START_MARKER)) {
        if (!line.empty()) {
            size_t field_delimiter_pos = line.find(FIELD_DELIMITER);
            if (field_delimiter_pos == std::string::npos) {
                throw std::runtime_error("invalid line found " + line);
            }
            string field = line.substr(1, field_delimiter_pos - 1);
            string value_s = line.substr(field_delimiter_pos + 1, line.size() - 1);
            if (field == "V") {
                int val = stoi(value_s);
                data.voltage = static_cast<float>(val) / 1000;
            }
            else if (field == "VM") {
                int val = stoi(value_s);
                data.mid_point_voltage = static_cast<float>(val) / 1000;
            }
            else if (field == "VS") {
                int val = stoi(value_s);
                data.auxiliary_voltage = static_cast<float>(val) / 1000;
            }
            else if (field == "DM") {
                int val = stoi(value_s);
                data.mid_point_deviation = val;
            }
            else if (field == "I") {
                int val = stoi(value_s);
                data.current = static_cast<float>(val) / 1000;
            }
            else if (field == "T") {
                int val = stoi(value_s);
                data.temperature = base::Temperature::fromCelsius(val);
            }
            else if (field == "P") {
                int val = stoi(value_s);
                data.instantaneous_power = val;
            }
            else if (field == "CE") {
                int val = stoi(value_s);
                data.consumed_charge = static_cast<float>(val) * 3.6;
            }
            else if (field == "SOC") {
                int val = stoi(value_s);
                data.state_of_charge = val;
            }
            else if (field == "TTG") {
                int val = stoi(value_s);
                data.time_to_go = base::Time::fromSeconds(val * 60);
            }
            else if (field == "Alarm") {
                data.alarm_condition_active = value_s;
            }
            else if (field == "Relay") {
                data.relay_state = value_s;
            }
            else if (field == "AR") {
                int val = stoi(value_s);
                data.alarm_reason = Alarms(val);
            }
            else if (field == "H1") {
                int val = stoi(value_s);
                data.deepest_discharge_depth = static_cast<float>(val) * 3.6;
            }
            else if (field == "H2") {
                int val = stoi(value_s);
                data.last_discharge_depth = static_cast<float>(val) * 3.6;
            }
            else if (field == "H3") {
                int val = stoi(value_s);
                data.average_discharge_depth = static_cast<float>(val) * 3.6;
            }
            else if (field == "H4") {
                int val = stoi(value_s);
                data.charge_cycles_number = val;
            }
            else if (field == "H5") {
                int val = stoi(value_s);
                data.full_discharges_number = val;
            }
            else if (field == "H6") {
                int val = stoi(value_s);
                data.cumulative_charge_drawn = static_cast<float>(val) * 3.6;
            }
            else if (field == "H7") {
                int val = stoi(value_s);
                data.minimum_voltage = static_cast<float>(val) / 1000;
            }
            else if (field == "H8") {
                int val = stoi(value_s);
                data.maximum_voltage = static_cast<float>(val) / 1000;
            }
            else if (field == "H9") {
                int val = stoi(value_s);
                data.seconds_since_last_full_charge = base::Time::fromSeconds(val);
            }
            else if (field == "H10") {
                int val = stoi(value_s);
                data.automatic_synchronizations_number = val;
            }
            else if (field == "H11") {
                int val = stoi(value_s);
                data.low_voltage_alarms_number = val;
            }
            else if (field == "H12") {
                int val = stoi(value_s);
                data.high_voltage_alarms_number = val;
            }
            else if (field == "H13") {
                int val = stoi(value_s);
                data.minimum_auxiliary_voltage = static_cast<float>(val) / 1000;
            }
            else if (field == "H14") {
                int val = stoi(value_s);
                data.maximum_auxiliary_voltage = static_cast<float>(val) / 1000;
            }
            else if (field == "H17") {
                int val = stoi(value_s);
                data.discharged_energy = val * 36000;
            }
            else if (field == "H18") {
                int val = stoi(value_s);
                data.charged_energy = val * 36000;
            }
            else if (field == "BMV") {
                data.model_description = value_s;
            }
            else if (field == "FW") {
                data.firmware_version = value_s;
            }
            else if (field == "PID") {
                data.product_id = value_s;
            }
            else if (field == "MON") {
                int val = stoi(value_s);
                if (val < SOLAR_CHARGER || val > WATER_HEATER) {
                    ostringstream msg;
                    msg << "unsupported DC Monitor Mode " << value_s;
                    throw invalid_argument(msg.str());
                }
                data.dc_monitor_mode = DCMonitorMode(val);
            }
        }
    }
    return data;
}
