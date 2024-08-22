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
    std::vector<uint8_t> checksum_vector(CHECKSUM_STR,
        CHECKSUM_STR + std::strlen(CHECKSUM_STR));
    auto checksum_begin_it = std::search(buffer,
        buffer + buffer_size,
        CHECKSUM_STR,
        CHECKSUM_STR + CHECKSUM_STR_LEN);
    if (checksum_begin_it == buffer + buffer_size) {
        // There is still no checksum, wait for more bytes
        return 0;
    }
    int packet_size = checksum_begin_it - buffer + checksum_vector.size() + 1;
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
        // todo: check
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
            data.voltage = static_cast<float>(val) / 1000;
        }
        else if (field == "VM") {
            data.mid_point_voltage = static_cast<float>(val) / 1000;
        }
        else if (field == "VS") {
            data.auxiliary_voltage = static_cast<float>(val) / 1000;
        }
        else if (field == "DM") {
            data.mid_point_deviation = val;
        }
        else if (field == "I") {
            data.current = static_cast<float>(val) / 1000;
        }
        else if (field == "T") {
            data.temperature = base::Temperature::fromCelsius(val);
        }
        else if (field == "P") {
            data.instantaneous_power = val;
        }
        else if (field == "CE") {
            data.consumed_charge = static_cast<float>(val) / 1000;
        }
        else if (field == "SOC") {
            data.state_of_charge = val;
        }
        else if (field == "TTG") {
            data.time_to_go = base::Time::fromSeconds(val * 60);
        }
        else if (field == "Alarm") {
            data.alarm_condition_active = value;
        }
        else if (field == "Relay") {
            data.relay_state = value;
        }
        else if (field == "AR") {
            data.alarm_reason = Alarms(val);
        }
        else if (field == "H1") {
            data.deepest_discharge_depth = static_cast<float>(val) / 1000;
        }
        else if (field == "H2") {
            data.last_discharge_depth = static_cast<float>(val) / 1000;
        }
        else if (field == "H3") {
            data.average_discharge_depth = static_cast<float>(val) / 1000;
        }
        else if (field == "H4") {
            data.charge_cycles_number = val;
        }
        else if (field == "H5") {
            data.full_discharges_number = val;
        }
        else if (field == "H6") {
            data.cumulative_charge_drawn = static_cast<float>(val) / 1000;
        }
        else if (field == "H7") {
            data.minimum_voltage = static_cast<float>(val) / 1000;
        }
        else if (field == "H8") {
            data.maximum_voltage = static_cast<float>(val) / 1000;
        }
        else if (field == "H9") {
            data.seconds_since_last_full_charge = base::Time::fromSeconds(val);
        }
        else if (field == "H10") {
            data.automatic_synchronizations_number = val;
        }
        else if (field == "H11") {
            data.low_voltage_alarms_number = val;
        }
        else if (field == "H12") {
            data.high_voltage_alarms_number = val;
        }
        else if (field == "H13") {
            data.minimum_auxiliary_voltage = static_cast<float>(val) / 1000;
        }
        else if (field == "H14") {
            data.maximum_auxiliary_voltage = static_cast<float>(val) / 1000;
        }
        else if (field == "H17") {
            data.discharged_energy = val * 10;
        }
        else if (field == "H18") {
            data.charged_energy = val * 10;
        }
        else if (field == "BMV") {
            data.model_description = value;
        }
        else if (field == "FWE") {
            data.firmware_version = value;
        }
        else if (field == "PID") {
            data.product_id = value;
        }
        else if (field == "MON") {
            if (val < SolarCharger || val > WaterHeater) {
                ostringstream msg;
                msg << "unsupported DC Monitor Mode " << value;
                throw invalid_argument(msg.str());
            }
            data.dc_monitor_mode = DCMonitorMode(val);
        }
    }
    return data;
}
