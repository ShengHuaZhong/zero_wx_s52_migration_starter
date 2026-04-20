if(NOT DEFINED ZERO_WX_S57DATA_ROOT)
    message(FATAL_ERROR "ZERO_WX_S57DATA_ROOT was not provided")
endif()

set(required_files
    chartsymbols.xml
    s57attributes.csv
    s57objectclasses.csv
    rastersymbols-day.png
    rastersymbols-dusk.png
    rastersymbols-dark.png
)

set(missing_files)
foreach(required_file IN LISTS required_files)
    if(NOT EXISTS "${ZERO_WX_S57DATA_ROOT}/${required_file}")
        list(APPEND missing_files "${required_file}")
    endif()
endforeach()

if(missing_files)
    list(JOIN missing_files ", " missing_files_text)
    message(FATAL_ERROR "Missing S57 data assets: ${missing_files_text}")
endif()

file(READ "${ZERO_WX_S57DATA_ROOT}/chartsymbols.xml" chartsymbols_xml)

foreach(required_marker IN ITEMS "<line-styles>" "<patterns>" "rastersymbols-day.png" "rastersymbols-dusk.png" "rastersymbols-dark.png")
    string(FIND "${chartsymbols_xml}" "${required_marker}" marker_index)
    if(marker_index EQUAL -1)
        message(FATAL_ERROR "chartsymbols.xml is missing expected marker: ${required_marker}")
    endif()
endforeach()

message(STATUS "Verified required S57 data assets under: ${ZERO_WX_S57DATA_ROOT}")
