if(NOT DEFINED ZERO_WX_EMPTY_SMOKE_STAMP)
    message(FATAL_ERROR "ZERO_WX_EMPTY_SMOKE_STAMP was not provided")
endif()

if(NOT EXISTS "${ZERO_WX_EMPTY_SMOKE_STAMP}")
    message(FATAL_ERROR "Empty smoke stamp not found: ${ZERO_WX_EMPTY_SMOKE_STAMP}")
endif()

message(STATUS "Verified empty smoke stamp: ${ZERO_WX_EMPTY_SMOKE_STAMP}")
