macro(YARPROS_ADD_TYPE _type)

    add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/${_type}.h
                       COMMAND cmake ARGS -E copy_if_different ${CMAKE_SOURCE_DIR}/${_type}.msg ${CMAKE_BINARY_DIR}
                       COMMAND yarpros ARGS type ${_type}
                       WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                       DEPENDS ${_type}.msg)
    set_property(SOURCE ${CMAKE_BINARY_DIR}/${_type}.h PROPERTY GENERATED TRUE)

    list(APPEND YARPROS_SOURCES ${CMAKE_BINARY_DIR}/${_type}.h)
endmacro()
