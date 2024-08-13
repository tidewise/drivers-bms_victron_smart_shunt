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
    buffer[6] = protocol::PACKET_START_MARKER;
    ASSERT_EQ(-5, protocol::extractPacket(&buffer[0], 20));
}
TEST_F(ProtocolTest, it_handles_a_start_byte_at_the_very_end_of_the_buffer)
{
    buffer[19] = PACKET_START_MARKER;
    ASSERT_EQ(-19, protocol::extractPacket(&buffer[0], 20));
}
TEST_F(ProtocolTest, it_accepts_a_packet)
{
    std::vector<uint8_t> buffer = {0x0d,
        0x0a,
        0x50,
        0x49,
        0x44,
        0x09,
        0x30,
        0x78,
        0x32,
        0x30,
        0x33,
        0x0d,
        0x0a,
        0x56,
        0x09,
        0x32,
        0x36,
        0x32,
        0x30,
        0x31,
        0x0d,
        0x0a,
        0x49,
        0x09,
        0x30,
        0x0d,
        0x0a,
        0x50,
        0x09,
        0x30,
        0x0d,
        0x0a,
        0x43,
        0x45,
        0x09,
        0x30,
        0x0d,
        0x0a,
        0x53,
        0x4f,
        0x43,
        0x09,
        0x31,
        0x30,
        0x30,
        0x30,
        0x0d,
        0x0a,
        0x54,
        0x54,
        0x47,
        0x09,
        0x2d,
        0x31,
        0x0d,
        0x0a,
        0x41,
        0x6c,
        0x61,
        0x72,
        0x6d,
        0x09,
        0x4f,
        0x46,
        0x46,
        0x0d,
        0x0a,
        0x52,
        0x65,
        0x6c,
        0x61,
        0x79,
        0x09,
        0x4f,
        0x46,
        0x46,
        0x0d,
        0x0a,
        0x41,
        0x52,
        0x09,
        0x30,
        0x0d,
        0x0a,
        0x42,
        0x4d,
        0x56,
        0x09,
        0x37,
        0x30,
        0x30,
        0x0d,
        0x0a,
        0x46,
        0x57,
        0x09,
        0x30,
        0x33,
        0x30,
        0x37,
        0x0d,
        0x0a,
        0x43,
        0x68,
        0x65,
        0x63,
        0x6b,
        0x73,
        0x75,
        0x6d,
        0x09,
        0xd8};
    ASSERT_EQ(112, extractPacket(&buffer[0], 112));
}
