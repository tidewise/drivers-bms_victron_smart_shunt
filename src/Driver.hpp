#ifndef BMS_VICTRON_SMART_SHUNT_DRIVER_HPP
#define BMS_VICTRON_SMART_SHUNT_DRIVER_HPP

#include <bms_victron_smart_shunt/SmartShuntFeedback.hpp>
#include <iodrivers_base/Driver.hpp>
namespace bms_victron_smart_shunt {
    /**
     *
     */
    class Driver : public iodrivers_base::Driver {
    public:
        static const int MAX_PACKET_SIZE = 22 * 45;
        static const int INTERNAL_BUFFER_SIZE = MAX_PACKET_SIZE * 4;

        /**
         * @brief Construct a new Driver object
         *
         */
        Driver();
        /**
         * @brief Process the internal buffer and parses the a found packet
         *
         * @return SmartShuntFeedback
         */
        SmartShuntFeedback processOne();

    private:
        /**
         * @brief iodrivers_base extractPacket implementation
         *
         * @param buffer The buffer
         * @param buffer_size The buffer size
         * @return int
         */
        virtual int extractPacket(uint8_t const* buffer, size_t buffer_size) const final;
        /**
         * @brief The read buffer
         *
         */
        uint8_t m_read_buffer[INTERNAL_BUFFER_SIZE];
        /**
         * @brief The Victron Smart Shunt Feedback
         *
         */
        SmartShuntFeedback m_feedback;
    };
}

#endif