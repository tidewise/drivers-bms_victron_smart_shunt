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
    int checksum = 0;
    for (int i = 0; i < buffer_size; i++) {
        checksum = (checksum + buffer[i]) & 255; /* Take modulo 256 in account */
    }
    if (checksum == 0) {
        return packet_start;
    }
    else{
        // todo: check
        return -1;
    }
}