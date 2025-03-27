if ("${CMAKE_CXX_CPPCHECK}" STREQUAL "")
    find_program(CPPCHECK NAMES cppcheck)
    if (NOT (CPPCHECK MATCHES "NOTFOUND"))
        set(CMAKE_CXX_CPPCHECK "${CPPCHECK}")
    endif()
endif()
message("CMAKE_CXX_CPPCHECK=${CMAKE_CXX_CPPCHECK}")
if (NOT ("${CMAKE_CXX_CPPCHECK}" STREQUAL ""))
    message("run static code analisys tool ${CMAKE_CXX_CPPCHECK}")
    set(
        CMAKE_CXX_CPPCHECK 
            "${CMAKE_CXX_CPPCHECK}"
            "--enable=all"
            "--suppressions-list=${PROJECT_SOURCE_DIR}/cppcheck_suppress.txt"
            "--include=${PROJECT_SOURCE_DIR}/cppcheck_include.txt"
            "--error-exitcode=1"
            "--check-level=exhaustive"
            "-rp=${PROJECT_SOURCE_DIR}"
    )
endif()