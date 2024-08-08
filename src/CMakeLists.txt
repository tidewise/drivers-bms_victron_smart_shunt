rock_library(bms_victron_smart_shunt
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(bms_victron_smart_shunt_bin Main.cpp
    DEPS bms_victron_smart_shunt)

