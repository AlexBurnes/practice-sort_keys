
macro(out_of_source_dir msg)
    string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" in_source)
    get_filename_component(PARENTDIR ${CMAKE_SOURCE_DIR} PATH)
    string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${PARENTDIR}" in_source_sub_dir)
    if(in_source OR in_source_sub_dir)
        lf("${msg}")
    endif(in_source OR in_source_sub_dir)
endmacro(out_of_source_dir)
