set(CORE_SOURCES installerbackend.cpp installerbackend.h)
add_library(core_backend STATIC ${CORE_SOURCES})
target_include_directories(core_backend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(core_backend PUBLIC Qt6::Core)