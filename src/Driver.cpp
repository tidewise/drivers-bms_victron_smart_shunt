#include <bms_victron_smart_shunt/Driver.hpp>
#include <bms_victron_smart_shunt/Protocol.hpp>

using namespace bms_victron_smart_shunt;

Driver::Driver()
    : iodrivers_base::Driver::Driver(INTERNAL_BUFFER_SIZE)
{
    m_processed_packets_counter = 0;
}

int Driver::extractPacket(uint8_t const* buffer, size_t buffer_size) const
{
    return protocol::extractPacket(buffer, buffer_size);
}

SmartShuntFeedback Driver::processOne(int needed_packets)
{
    if (m_processed_packets_counter >= needed_packets) {
        // Reset feedback
        m_feedback = SmartShuntFeedback();
        m_processed_packets_counter = 0;
    }
    int packet_size = readPacket(m_read_buffer, INTERNAL_BUFFER_SIZE);
    protocol::parseSmartShuntFeedback(m_read_buffer, packet_size, m_feedback);
    m_processed_packets_counter += 1;
    return m_feedback;
}

int Driver::packetsCounter()
{
    return m_processed_packets_counter;
}
