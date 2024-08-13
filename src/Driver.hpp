#ifndef BMS_VICTRON_SMART_SHUNT_DRIVER_HPP
#define BMS_VICTRON_SMART_SHUNT_DRIVER_HPP

#include <iodrivers_base/Driver.hpp>
namespace bms_victron_smart_shunt {
    /**
     *
     */
    class Driver : iodrivers_base::Driver {
        // TODO: define MAX_PACKET_SIZE
        static const int MAX_PACKET_SIZE = 32;
        static const int INTERNAL_BUFFER_SIZE = MAX_PACKET_SIZE * 4;

    public:
        Driver();

    private:
        virtual int extractPacket(uint8_t const* buffer, size_t buffer_size) const;
    };
}

#endif