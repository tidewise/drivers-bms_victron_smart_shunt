rock_library(bms_victron_smart_shunt
    SOURCES Dummy.cpp
        Driver.cpp
        Protocol.cpp
    HEADERS Dummy.hpp
        Driver.hpp
        Protocol.hpp
        Fields.hpp
        DCMonitorMode.hpp
    DEPS_PKGCONFIG iodrivers_base)

rock_executable(bms_victron_smart_shunt_bin Main.cpp
    DEPS bms_victron_smart_shunt)

