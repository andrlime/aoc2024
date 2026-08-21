file(GLOB junelib_SOURCES "${CMAKE_CURRENT_LIST_DIR}/*.cc")

add_library(junelib STATIC ${junelib_SOURCES})
target_include_directories(junelib PUBLIC ${CMAKE_SOURCE_DIR})
target_compile_features(junelib PUBLIC cxx_std_${CMAKE_CXX_STANDARD})
