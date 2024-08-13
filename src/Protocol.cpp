#include <bms_victron_smart_shunt/Protocol.hpp>

using namespace bms_victron_smart_shunt;

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
    // todo: checksum
    return packet_start;
}