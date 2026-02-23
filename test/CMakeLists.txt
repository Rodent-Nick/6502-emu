find_package(Catch2 3 REQUIRED)

add_executable(emu-test)

target_sources(emu-test PRIVATE ${SRC} "main.cxx")
target_include_directories(emu-test PRIVATE "../include" ${CATCH2_INCLUDE_DIR})
target_link_libraries(emu-test PRIVATE Catch2::Catch2WithMain)