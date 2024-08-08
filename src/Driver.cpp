#include <bms_victron_smart_shunt/Driver.hpp>

using namespace bms_victron_smart_shunt;

Driver::Driver()
    : iodrivers_base::Driver::Driver(INTERNAL_BUFFER_SIZE)
{
}