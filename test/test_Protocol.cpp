#include <bms_victron_smart_shunt/Protocol.hpp>
#include <gtest/gtest.h>
#include <iostream>

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
    ASSERT_EQ(-5, protocol::extractPacket(&buffer[0], 9));
}
TEST_F(ProtocolTest, it_finds_a_packet_start_within_the_packet_2)
{
    buffer[5] = protocol::PACKET_START_MARKER;
    buffer[6] = protocol::PACKET_START_MARKER;
    ASSERT_EQ(-5, protocol::extractPacket(&buffer[0], 9));
}
TEST_F(ProtocolTest, it_handles_a_start_byte_at_the_very_end_of_the_buffer)
{
    buffer[9] = PACKET_START_MARKER;
    ASSERT_EQ(-9, protocol::extractPacket(&buffer[0], 10));
}