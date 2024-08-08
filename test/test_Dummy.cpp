#include <bms_victron_smart_shunt/Dummy.hpp>
#include <boost/test/unit_test.hpp>

using namespace bms_victron_smart_shunt;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    bms_victron_smart_shunt::DummyClass dummy;
    dummy.welcome();
}
