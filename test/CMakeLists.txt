rock_gtest(test_suite suite.cpp
   test_Protocol.cpp
   test_Driver.cpp
   TestHelpers.cpp
   DEPS bms_victron_smart_shunt)

target_compile_definitions(test_suite
  PRIVATE TEST_PATH="${PROJECT_SOURCE_DIR}/test/data/"
)