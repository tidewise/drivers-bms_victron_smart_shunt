#include <bms_victron_smart_shunt/Driver.hpp>
#include <bms_victron_smart_shunt/Protocol.hpp>
#include <gtest/gtest.h>
#include <iodrivers_base/FixtureGTest.hpp>
#include <iostream>

using namespace bms_victron_smart_shunt;
using namespace std;

struct DriverTest : public ::testing::Test, iodrivers_base::Fixture<Driver> {
    void openDriver()
    {
        driver.openURI("test://");
    }

    void pushDataToDriver(char const* msg)
    {
        uint8_t const* msg_int8 = reinterpret_cast<uint8_t const*>(msg);
        std::vector<uint8_t> packet(msg_int8, msg_int8 + strlen(msg));
        iodrivers_base::Fixture<Driver>::pushDataToDriver(packet);
    }
};

TEST_F(DriverTest, bla)
{
    openDriver();
    IODRIVERS_BASE_MOCK();
    // 4 trash bytes at the beggining and 4 trash bytes at the end
    char const* msg =
        "\x50\x49\x44\x09\x0d\x0a\x50\x49\x44\x09\x30\x78\x32\x30\x33\x0d\x0a"
        "\x56\x09\x32\x36\x32\x30\x31\x0d\x0a\x49\x09\x30\x0d\x0a"
        "\x50\x09\x30\x0d\x0a\x43\x45\x09\x30\x0d\x0a\x53\x4f\x43"
        "\x09\x31\x30\x30\x30\x0d\x0a\x54\x54\x47\x09\x2d\x31\x0d"
        "\x0a\x41\x6c\x61\x72\x6d\x09\x4f\x46\x46\x0d\x0a\x52\x65"
        "\x6c\x61\x79\x09\x4f\x46\x46\x0d\x0a\x41\x52\x09\x30\x0d"
        "\x0a\x42\x4d\x56\x09\x37\x30\x30\x0d\x0a\x46\x57\x09\x30"
        "\x33\x30\x37\x0d\x0a\x43\x68\x65\x63\x6b\x73\x75\x6d\x09"
        "\xd8\x56\x09\x32\x36";
    pushDataToDriver(msg);
    auto feedback = driver.processOne();
    ASSERT_EQ(feedback.product_id, "0x203");
    ASSERT_NEAR(feedback.voltage, 26.201, 1e-3);
    ASSERT_EQ(feedback.current, 0);
    ASSERT_EQ(feedback.intantaneous_power, 0);
    ASSERT_EQ(feedback.consumed_charge, 0);
    ASSERT_EQ(feedback.state_of_charge, 1000);
    ASSERT_EQ(feedback.time_to_go.toSeconds(), -60);
    ASSERT_EQ(feedback.alarm_condition_active, "OFF");
    ASSERT_EQ(feedback.relay_state, "OFF");
    ASSERT_EQ(feedback.alarm_reason, 0);
    ASSERT_EQ(feedback.model_description, "700");
}