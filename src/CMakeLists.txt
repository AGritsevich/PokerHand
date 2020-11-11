cmake_minimum_required (VERSION 3.8)

set(HEADERS
    ${CMAKE_SOURCE_DIR}/src/include/
)

set(SRC 
    ${CMAKE_SOURCE_DIR}/src/Poker.cpp
    ${CMAKE_SOURCE_DIR}/src/Deck.cpp
    ${CMAKE_SOURCE_DIR}/src/Log.cpp
    ${CMAKE_SOURCE_DIR}/src/PockerHand.cpp
#	${CMAKE_SOURCE_DIR}/src/trade/trade.cc
)

add_executable(${APP_NAME} ${SRC})

set(BIN_DIR ${CMAKE_SOURCE_DIR}/build/bin/)

target_compile_features(${APP_NAME} PUBLIC cxx_std_14)

set_target_properties( ${APP_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR} )

target_include_directories(${APP_NAME} PUBLIC ${HEADERS})

