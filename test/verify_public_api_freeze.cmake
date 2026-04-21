if(NOT DEFINED ZERO_WX_SOURCE_ROOT)
    message(FATAL_ERROR "ZERO_WX_SOURCE_ROOT was not provided")
endif()

if(NOT DEFINED ZERO_WX_PUBLIC_API_MANIFEST)
    message(FATAL_ERROR "ZERO_WX_PUBLIC_API_MANIFEST was not provided")
endif()

if(NOT EXISTS "${ZERO_WX_PUBLIC_API_MANIFEST}")
    message(FATAL_ERROR "Public API manifest not found: ${ZERO_WX_PUBLIC_API_MANIFEST}")
endif()

file(READ "${ZERO_WX_PUBLIC_API_MANIFEST}" manifest_text)
string(REPLACE "\r\n" "\n" manifest_text "${manifest_text}")
string(REPLACE "\r" "\n" manifest_text "${manifest_text}")
string(REGEX REPLACE "\n+$" "" manifest_text "${manifest_text}")
string(REPLACE "\n" ";" manifest_entries "${manifest_text}")

set(manifest_headers)
foreach(manifest_entry IN LISTS manifest_entries)
    string(STRIP "${manifest_entry}" manifest_entry_stripped)
    if(NOT manifest_entry_stripped STREQUAL "")
        list(APPEND manifest_headers "${manifest_entry_stripped}")
    endif()
endforeach()
list(REMOVE_DUPLICATES manifest_headers)
list(SORT manifest_headers)

set(actual_headers)
foreach(pattern IN ITEMS
    "${ZERO_WX_SOURCE_ROOT}/include/marine_chart/*.h"
    "${ZERO_WX_SOURCE_ROOT}/include/marine_chart/*.hpp"
    "${ZERO_WX_SOURCE_ROOT}/include/marine_chart/*.hh"
)
    file(GLOB_RECURSE matched_headers LIST_DIRECTORIES false "${pattern}")
    list(APPEND actual_headers ${matched_headers})
endforeach()

set(actual_header_relpaths)
foreach(actual_header IN LISTS actual_headers)
    file(RELATIVE_PATH actual_header_relpath "${ZERO_WX_SOURCE_ROOT}" "${actual_header}")
    string(REPLACE "\\" "/" actual_header_relpath "${actual_header_relpath}")
    list(APPEND actual_header_relpaths "${actual_header_relpath}")
endforeach()

list(REMOVE_DUPLICATES actual_header_relpaths)
list(SORT actual_header_relpaths)

if(NOT manifest_headers STREQUAL actual_header_relpaths)
    set(missing_headers)
    foreach(manifest_header IN LISTS manifest_headers)
        list(FIND actual_header_relpaths "${manifest_header}" actual_index)
        if(actual_index EQUAL -1)
            list(APPEND missing_headers "${manifest_header}")
        endif()
    endforeach()

    set(untracked_headers)
    foreach(actual_header_relpath IN LISTS actual_header_relpaths)
        list(FIND manifest_headers "${actual_header_relpath}" manifest_index)
        if(manifest_index EQUAL -1)
            list(APPEND untracked_headers "${actual_header_relpath}")
        endif()
    endforeach()

    message(FATAL_ERROR
        "Public API header set diverged from manifest.\n"
        "Missing from source: ${missing_headers}\n"
        "Missing from manifest: ${untracked_headers}")
endif()

set(forbidden_public_header_markers
    "wx/"
    "wxString"
    "wxColour"
    "wxBitmap"
    "wxWindow"
)

set(forbidden_non_host_qt_markers
    "QWidget"
    "QWindow"
    "QString"
    "QImage"
    "QColor"
    "QRhi"
    "QObject"
    "#include <Q"
)

foreach(public_header_relpath IN LISTS actual_header_relpaths)
    set(public_header_path "${ZERO_WX_SOURCE_ROOT}/${public_header_relpath}")
    file(READ "${public_header_path}" public_header_text)
    foreach(forbidden_marker IN LISTS forbidden_public_header_markers)
        string(FIND "${public_header_text}" "${forbidden_marker}" marker_index)
        if(NOT marker_index EQUAL -1)
            message(FATAL_ERROR
                "Forbidden marker '${forbidden_marker}' found in public header: ${public_header_path}")
        endif()
    endforeach()

    if(NOT public_header_relpath MATCHES "^include/marine_chart/chart_qt_host/")
        foreach(forbidden_qt_marker IN LISTS forbidden_non_host_qt_markers)
            string(FIND "${public_header_text}" "${forbidden_qt_marker}" marker_index)
            if(NOT marker_index EQUAL -1)
                message(FATAL_ERROR
                    "Forbidden Qt marker '${forbidden_qt_marker}' found in non-host public header: ${public_header_path}")
            endif()
        endforeach()
    endif()
endforeach()

message(STATUS "Verified public API freeze manifest and host-type boundaries")
