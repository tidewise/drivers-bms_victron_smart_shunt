#include "TestHelpers.hpp"
#include <bms_victron_smart_shunt/Driver.hpp>
#include <bms_victron_smart_shunt/Protocol.hpp>
#include <gtest/gtest.h>
#include <iodrivers_base/FixtureGTest.hpp>

using namespace bms_victron_smart_shunt;
using namespace std;

#define ASSERT_THROW_MESSAGE(code, exception, message)                                   \
    ASSERT_THROW(                                                                        \
        {                                                                                \
            try {                                                                        \
                code;                                                                    \
            }                                                                            \
            catch (exception & e) {                                                      \
                ASSERT_EQ(message, string(e.what()));                                    \
                throw;                                                                   \
            }                                                                            \
        },                                                                               \
        exception)

struct DriverTest : public ::testing::Test, iodrivers_base::Fixture<Driver> {
    void openDriver()
    {
        driver.openURI("test://");
    }

    void pushDataToDriver(std::vector<uint8_t> const& msg)
    {
        iodrivers_base::Fixture<Driver>::pushDataToDriver(msg);
    }

    void pushDataToDriver(char const* msg)
    {
        uint8_t const* msg_int8 = reinterpret_cast<uint8_t const*>(msg);
        std::vector<uint8_t> packet(msg_int8, msg_int8 + strlen(msg));
        iodrivers_base::Fixture<Driver>::pushDataToDriver(packet);
    }
};

TEST_F(DriverTest, it_accepts_a_full_packet)
{
    openDriver();
    IODRIVERS_BASE_MOCK();
    char const* msg = "\x0d\x0a\x50\x49\x44\x09\x30\x78\x32\x30\x33\x0d\x0a"
                      "\x56\x09\x32\x36\x32\x30\x31\x0d\x0a\x49\x09\x30\x0d\x0a"
                      "\x50\x09\x30\x0d\x0a\x43\x45\x09\x30\x0d\x0a\x53\x4f\x43"
                      "\x09\x31\x30\x30\x30\x0d\x0a\x54\x54\x47\x09\x2d\x31\x0d"
                      "\x0a\x41\x6c\x61\x72\x6d\x09\x4f\x46\x46\x0d\x0a\x52\x65"
                      "\x6c\x61\x79\x09\x4f\x46\x46\x0d\x0a\x41\x52\x09\x30\x0d"
                      "\x0a\x42\x4d\x56\x09\x37\x30\x30\x0d\x0a\x46\x57\x09\x30"
                      "\x33\x30\x37\x0d\x0a\x43\x68\x65\x63\x6b\x73\x75\x6d\x09"
                      "\xd8";
    pushDataToDriver(msg);
    auto feedback = driver.processOne();
    ASSERT_EQ(feedback.product_id, "0x203");
    ASSERT_NEAR(feedback.voltage, 26.201, 1e-3);
    ASSERT_EQ(feedback.current, 0);
    ASSERT_NEAR(feedback.instantaneous_power, 0, 1e-3);
    ASSERT_EQ(feedback.consumed_charge, 0);
    ASSERT_NEAR(feedback.state_of_charge, 100, 1e-3);
    ASSERT_EQ(feedback.time_to_go.toSeconds(), -60);
    ASSERT_EQ(feedback.alarm_condition_active, "OFF");
    ASSERT_EQ(feedback.relay_state, "OFF");
    ASSERT_EQ(feedback.alarm_reason, 0);
    ASSERT_EQ(feedback.model_description, "700");
}

TEST_F(DriverTest, it_rejects_a_packet_because_the_checksum_is_wrong)
{
    openDriver();
    IODRIVERS_BASE_MOCK();
    char const* msg = "\x0d\x0a\x50\x49\x44\x09\x30\x78\x32\x30\x33\x0d\x0a"
                      "\x56\x09\x32\x36\x32\x30\x31\x0d\x0a\x49\x09\x30\x0d\x0a"
                      "\x50\x09\x30\x0d\x0a\x43\x45\x09\x30\x0d\x0a\x53\x4f\x43"
                      "\x09\x31\x30\x30\x30\x0d\x0a\x54\x54\x47\x09\x2d\x31\x0d"
                      "\x0a\x41\x6c\x61\x72\x6d\x09\x4f\x46\x46\x0d\x0a\x52\x65"
                      "\x6c\x61\x79\x09\x4f\x46\x46\x0d\x0a\x41\x52\x09\x30\x0d"
                      "\x0a\x42\x4d\x56\x09\x37\x30\x30\x0d\x0a\x46\x57\x09\x30"
                      "\x33\x30\x37\x0d\x0a\x43\x68\x65\x63\x6b\x73\x75\x6d\x09"
                      "\xd7";
    pushDataToDriver(msg);
    ASSERT_THROW_MESSAGE(driver.processOne(),
        std::runtime_error,
        "readPacket(): no data to read while a packet_timeout of 0 was given");
}

TEST_F(DriverTest, the_packet_arrives_little_by_little)
{
    openDriver();
    IODRIVERS_BASE_MOCK();
    char const* msg = "\x0d\x0a\x50\x49\x44\x09\x30\x78\x32\x30\x33\x0d\x0a"
                      "\x56\x09\x32\x36\x32\x30\x31\x0d\x0a\x49\x09\x30\x0d\x0a"
                      "\x50\x09\x30\x0d\x0a\x43\x45\x09\x30\x0d\x0a\x53\x4f\x43"
                      "\x09\x31\x30\x30\x30\x0d\x0a\x54\x54\x47\x09\x2d\x31\x0d"
                      "\x0a\x41\x6c\x61\x72\x6d\x09\x4f\x46\x46\x0d\x0a\x52\x65"
                      "\x6c\x61\x79\x09\x4f\x46\x46\x0d\x0a\x41\x52\x09\x30\x0d"
                      "\x0a\x42\x4d\x56\x09\x37\x30\x30\x0d\x0a\x46\x57\x09\x30";
    pushDataToDriver(msg);
    ASSERT_THROW_MESSAGE(driver.processOne(),
        std::runtime_error,
        "readPacket(): no data to read while a packet_timeout of 0 was given");
    msg = "\x33\x30\x37\x0d\x0a\x43\x68\x65\x63\x6b\x73\x75\x6d\x09\xd8";
    pushDataToDriver(msg);
    auto feedback = driver.processOne();
    ASSERT_EQ(feedback.product_id, "0x203");
    ASSERT_NEAR(feedback.voltage, 26.201, 1e-3);
    ASSERT_EQ(feedback.current, 0);
    ASSERT_NEAR(feedback.instantaneous_power, 0, 1e-3);
    ASSERT_EQ(feedback.consumed_charge, 0);
    ASSERT_NEAR(feedback.state_of_charge, 100, 1e-3);
    ASSERT_EQ(feedback.time_to_go.toSeconds(), -60);
    ASSERT_EQ(feedback.alarm_condition_active, "OFF");
    ASSERT_EQ(feedback.relay_state, "OFF");
    ASSERT_EQ(feedback.alarm_reason, 0);
    ASSERT_EQ(feedback.model_description, "700");
}

TEST_F(DriverTest, it_accepts_a_packet_with_garbage_at_the_beginning)
{
    openDriver();
    IODRIVERS_BASE_MOCK();
    // 4 bytes of thash at the beginning
    char const* msg =
        "\x43\x45\x09\x30\x0d\x0a\x50\x49\x44\x09\x30\x78\x32\x30\x33\x0d\x0a"
        "\x56\x09\x32\x36\x32\x30\x31\x0d\x0a\x49\x09\x30\x0d\x0a"
        "\x50\x09\x30\x0d\x0a\x43\x45\x09\x30\x0d\x0a\x53\x4f\x43"
        "\x09\x31\x30\x30\x30\x0d\x0a\x54\x54\x47\x09\x2d\x31\x0d"
        "\x0a\x41\x6c\x61\x72\x6d\x09\x4f\x46\x46\x0d\x0a\x52\x65"
        "\x6c\x61\x79\x09\x4f\x46\x46\x0d\x0a\x41\x52\x09\x30\x0d"
        "\x0a\x42\x4d\x56\x09\x37\x30\x30\x0d\x0a\x46\x57\x09\x30\x33\x30\x37\x0d\x0a\x43"
        "\x68\x65\x63\x6b\x73\x75\x6d\x09\xd8";
    pushDataToDriver(msg);
    auto feedback = driver.processOne();
    ASSERT_EQ(feedback.product_id, "0x203");
    ASSERT_NEAR(feedback.voltage, 26.201, 1e-3);
    ASSERT_EQ(feedback.current, 0);
    ASSERT_NEAR(feedback.instantaneous_power, 0, 1e-3);
    ASSERT_EQ(feedback.consumed_charge, 0);
    ASSERT_NEAR(feedback.state_of_charge, 100, 1e-3);
    ASSERT_EQ(feedback.time_to_go.toSeconds(), -60);
    ASSERT_EQ(feedback.alarm_condition_active, "OFF");
    ASSERT_EQ(feedback.relay_state, "OFF");
    ASSERT_EQ(feedback.alarm_reason, 0);
    ASSERT_EQ(feedback.model_description, "700");
}

TEST_F(DriverTest, rejects_a_partial_packet_and_accepts_following_full_one)
{
    openDriver();
    IODRIVERS_BASE_MOCK();
    // Partial packet
    char const* msg = "\x0d\x0a\x41\x52\x09\x30\x0d"
                      "\x0a\x42\x4d\x56\x09\x37\x30\x30\x0d\x0a\x46\x57\x09\x30"
                      "\x33\x30\x37\x0d\x0a\x43\x68\x65\x63\x6b\x73\x75\x6d\x09"
                      "\xd8";
    pushDataToDriver(msg);
    ASSERT_THROW_MESSAGE(driver.processOne(),
        std::runtime_error,
        "readPacket(): no data to read while a packet_timeout of 0 was given");
    // Full packet
    msg = "\x0d\x0a\x50\x49\x44\x09\x30\x78\x32\x30\x33\x0d\x0a"
          "\x56\x09\x32\x36\x32\x30\x31\x0d\x0a\x49\x09\x30\x0d\x0a"
          "\x50\x09\x30\x0d\x0a\x43\x45\x09\x30\x0d\x0a\x53\x4f\x43"
          "\x09\x31\x30\x30\x30\x0d\x0a\x54\x54\x47\x09\x2d\x31\x0d"
          "\x0a\x41\x6c\x61\x72\x6d\x09\x4f\x46\x46\x0d\x0a\x52\x65"
          "\x6c\x61\x79\x09\x4f\x46\x46\x0d\x0a\x41\x52\x09\x30\x0d"
          "\x0a\x42\x4d\x56\x09\x37\x30\x30\x0d\x0a\x46\x57\x09\x30"
          "\x33\x30\x37\x0d\x0a\x43\x68\x65\x63\x6b\x73\x75\x6d\x09"
          "\xd8";
    pushDataToDriver(msg);
    auto feedback = driver.processOne();
    ASSERT_EQ(feedback.product_id, "0x203");
    ASSERT_NEAR(feedback.voltage, 26.201, 1e-3);
    ASSERT_EQ(feedback.current, 0);
    ASSERT_NEAR(feedback.instantaneous_power, 0, 1e-3);
    ASSERT_EQ(feedback.consumed_charge, 0);
    ASSERT_NEAR(feedback.state_of_charge, 100, 1e-3);
    ASSERT_EQ(feedback.time_to_go.toSeconds(), -60);
    ASSERT_EQ(feedback.alarm_condition_active, "OFF");
    ASSERT_EQ(feedback.relay_state, "OFF");
    ASSERT_EQ(feedback.alarm_reason, 0);
    ASSERT_EQ(feedback.model_description, "700");
}

TEST_F(DriverTest, it_correctly_parses_the_MON_0_field)
{
    openDriver();
    IODRIVERS_BASE_MOCK();
    // Partial packet
    auto buffer = readTextFile(TEST_PATH "mon_0.dat");
    pushDataToDriver(buffer);
    auto result = driver.processOne();
    ASSERT_EQ(0, result.dc_monitor_mode);
}

TEST_F(DriverTest, it_does_not_increase_bad_rx_number_for_valid_packets_processing)
{
    openDriver();
    IODRIVERS_BASE_MOCK();
    auto buffer = readTextFile(TEST_PATH "mon_0.dat");
    pushDataToDriver(buffer);
    auto result = driver.processOne();
    auto stats = driver.getStats();
    ASSERT_EQ(0, result.dc_monitor_mode);
    pushDataToDriver(buffer);
    result = driver.processOne();
    stats = driver.getStats();
    ASSERT_EQ(0, stats.bad_rx);
}

TEST_F(DriverTest, it_accepts_a_packet_receiving_byte_by_byte)
{
    openDriver();
    IODRIVERS_BASE_MOCK();
    // Partial packet
    auto buffer = readTextFile(TEST_PATH "mon_0.dat");
    driver.setReadTimeout(base::Time());
    SmartShuntFeedback feedback;
    for (unsigned int i = 0; i < buffer.size(); ++i) {
        std::vector<uint8_t> fragment = {buffer[i]};
        pushDataToDriver(fragment);
        try {
            feedback = driver.processOne();
        }
        catch (iodrivers_base::TimeoutError) {
            continue;
        }
    }
    auto stats = driver.getStats();
    ASSERT_EQ(0, stats.bad_rx);
    ASSERT_NEAR(feedback.voltage, 13.771, 1e-3);
}
