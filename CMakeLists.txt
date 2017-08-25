cmake_minimum_required(VERSION 3.6)
project(tutorial1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

INCLUDE_DIRECTORIES(

        /usr/local/include/ns3-dev
        /usr/local/include/ns3-dev/ns3/ndnSIM/NFD/daemon/
        /usr/local/include/ns3-dev/ns3/ndnSIM/ndn-cxx
)
set(SOURCE_FILES
        extensions/AdhocScenario.cpp
    extensions/AdhocScenario.hpp
    scenarios/ndn-simple-wifi.cpp extensions/strategies/BroadCastStrategy.cpp extensions/strategies/BroadCastStrategy.h)

add_executable(tutorial1 ${SOURCE_FILES})