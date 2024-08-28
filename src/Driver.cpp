#include <bms_victron_smart_shunt/Driver.hpp>
#include <bms_victron_smart_shunt/Protocol.hpp>

using namespace bms_victron_smart_shunt;

Driver::Driver()
    : iodrivers_base::Driver::Driver(INTERNAL_BUFFER_SIZE)
{
}

int Driver::extractPacket(uint8_t const* buffer, size_t buffer_size) const
{
    return protocol::extractPacket(buffer, buffer_size);
}

SmartShuntFeedback Driver::processOne()
{
    int packet_size = readPacket(m_read_buffer, INTERNAL_BUFFER_SIZE);
    return protocol::parseSmartShuntFeedback(m_read_buffer, packet_size);
}