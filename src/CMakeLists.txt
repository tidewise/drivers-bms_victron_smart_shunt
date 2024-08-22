rock_library(bms_victron_smart_shunt
    SOURCES
        Driver.cpp
        Protocol.cpp
    HEADERS
        Driver.hpp
        Protocol.hpp
        SmartShuntFeedback.hpp
        DCMonitorMode.hpp
        Alarms.hpp
    DEPS_PKGCONFIG iodrivers_base)