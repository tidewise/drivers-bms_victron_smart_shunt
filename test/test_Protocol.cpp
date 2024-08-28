#include "TestHelpers.hpp"
#include <bms_victron_smart_shunt/Protocol.hpp>
#include <gtest/gtest.h>

using namespace bms_victron_smart_shunt;
using namespace protocol;
using namespace std;

struct ProtocolTest : public ::testing::Test {
    std::vector<uint8_t> buffer;
    ProtocolTest()
    {
        buffer.resize(256, 0);
    }
};

TEST_F(ProtocolTest, it_waits_for_more_bytes_if_the_buffer_is_too_small)
{
    ASSERT_EQ(0, protocol::extractPacket(&buffer[0], 4));
}
TEST_F(ProtocolTest, it_finds_a_packet_start_within_the_packet)
{
    buffer[5] = protocol::PACKET_START_MARKER;
    buffer[6] = protocol::PACKET_START_MARKER;
    ASSERT_EQ(-5, protocol::extractPacket(&buffer[0], 20));
}
TEST_F(ProtocolTest, it_handles_a_start_byte_at_the_very_end_of_the_buffer)
{
    buffer[19] = PACKET_START_MARKER;
    ASSERT_EQ(-19, protocol::extractPacket(&buffer[0], 20));
}
TEST_F(ProtocolTest, it_accepts_a_packet_and_correctly_parse_it)
{
    auto buffer = bms_victron_smart_shunt::readTextFile(TEST_PATH "data");

    // Checksum field addition
    std::vector<uint8_t> checksum_field =
        {0x0d, 0x0a, 0x43, 0x68, 0x65, 0x63, 0x6b, 0x73, 0x75, 0x6d, 0x09, 0xbe};
    buffer.insert(buffer.end(), checksum_field.begin(), checksum_field.end());
    SmartShuntFeedback feedback;
    parseSmartShuntFeedback(&buffer[0], 631, feedback);
    ASSERT_EQ(619, extractPacket(&buffer[0], 631));
    ASSERT_NEAR(feedback.voltage, 32.456, 1e-3);
    ASSERT_NEAR(feedback.auxiliary_starter_voltage, 14.45, 1e-3);
    ASSERT_NEAR(feedback.mid_point_voltage, 15.5, 1e-3);
    ASSERT_NEAR(feedback.mid_point_deviation, 5, 1e-3);
    ASSERT_NEAR(feedback.current, 4.5, 1e-3);
    ASSERT_NEAR(feedback.temperature.getCelsius(), 27, 1e-3);
    ASSERT_NEAR(feedback.instantaneous_power, 600, 1e-3);
    ASSERT_NEAR(feedback.consumed_charge, 54720, 1e-3);
    ASSERT_NEAR(feedback.state_of_charge, 8.5, 1e-3);
    ASSERT_EQ(feedback.time_to_go.toSeconds(), 120 * 60);
    ASSERT_EQ(feedback.alarm_condition_active, "ON");
    ASSERT_EQ(feedback.relay_state, "ON");
    ASSERT_EQ(feedback.alarm_reason, 5);
    ASSERT_NEAR(feedback.deepest_discharge_depth, 432000, 1e-3);
    ASSERT_NEAR(feedback.last_discharge_depth, 28800, 1e-3);
    ASSERT_NEAR(feedback.average_discharge_depth, 36000, 1e-3);
    ASSERT_EQ(feedback.charge_cycles_number, 3000);
    ASSERT_EQ(feedback.full_discharges_number, 10);
    ASSERT_NEAR(feedback.cumulative_charge_drawn, 126000, 1e-3);
    ASSERT_NEAR(feedback.minimum_voltage, 111, 1e-3);
    ASSERT_NEAR(feedback.maximum_voltage, 160, 1e-3);
    ASSERT_EQ(feedback.seconds_since_last_full_charge.toSeconds(), 345600);
    ASSERT_EQ(feedback.automatic_synchronizations_number, 15);
    ASSERT_EQ(feedback.low_voltage_alarms_number, 25);
    ASSERT_EQ(feedback.high_voltage_alarms_number, 35);
    ASSERT_NEAR(feedback.minimum_auxiliary_voltage, 0.045, 1e-3);
    ASSERT_NEAR(feedback.maximum_auxiliary_voltage, 0.055, 1e-3);
    ASSERT_NEAR(feedback.discharged_energy, 18000000, 1e-3);
    ASSERT_NEAR(feedback.charged_energy, 108000000, 1e-3);
    ASSERT_EQ(feedback.model_description, "700");
    ASSERT_EQ(feedback.firmware_version, "0408");
    ASSERT_EQ(feedback.product_id, "0x204");
    ASSERT_EQ(feedback.dc_monitor_mode, DCMonitorMode::AC_CHARGER);
    ASSERT_NEAR(feedback.minimum_auxiliary_battery_voltage, 111, 1e-3);
    ASSERT_NEAR(feedback.maximum_auxiliary_battery_voltage, 160, 1e-3);
}
