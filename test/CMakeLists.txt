find_package(Catch2 3 REQUIRED)
file(GLOB SRCTEST "*.cxx")
file(GLOB SRCTARGET "../src/*")
# Must ignore main.cxx so that Catch2 can provide its own main entry.
list(FILTER SRCTARGET EXCLUDE REGEX "../src/main.cxx")

add_executable(emu-test)

target_sources(emu-test PRIVATE ${SRCTARGET} ${SRCTEST})
target_include_directories(emu-test PRIVATE "../include" ${CATCH2_INCLUDE_DIR})
target_link_libraries(emu-test PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(emu-test)