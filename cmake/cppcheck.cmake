find_program(CPPCHECK NAMES cppcheck)
message("CMAKE_CXX_CPPCHECK=${CMAKE_CXX_CPPCHECK}")
if (NOT (CPPCHECK MATCHES "NOTFOUND"))
    set(
        CMAKE_CXX_CPPCHECK 
            "${CPPCHECK}"
            "--enable=all"
            "--suppressions-list=${PROJECT_SOURCE_DIR}/cppcheck_suppress.txt"
            "--include=${PROJECT_SOURCE_DIR}/cppcheck_include.txt"
            "--error-exitcode=1"
            "-rp=${PROJECT_SOURCE_DIR}"
    )
endif()