
set(prefix "notched_plate_native_neohookean")

foreach (ext "in" "g" "gold.e" "exodiff")
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${prefix}.${ext}
                 ${CMAKE_CURRENT_BINARY_DIR}/${prefix}.${ext} COPYONLY)
endforeach()

set(inputfile "${prefix}.in")

add_test(NAME "${prefix}-serial"
         COMMAND Python::Interpreter ../../run_exodiff_test.py --executable "${nimble_exe}" --cli-flag "" --input-deck "${inputfile}" --num-ranks 1
        )

if (NIMBLE_HAVE_MPI)

  foreach (ext "g.2.0" "g.2.1" "g.4.0" "g.4.1" "g.4.2" "g.4.3")
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${prefix}.${ext}
                   ${CMAKE_CURRENT_BINARY_DIR}/${prefix}.${ext} COPYONLY)
  endforeach()

  foreach (nrank 2 4)
    add_test(NAME "${prefix}-np${nrank}"
             COMMAND Python::Interpreter ../../run_exodiff_test.py --executable "${nimble_exe}" --cli-flag "" --input-deck "${inputfile}" --num-ranks ${nrank}
            )
  endforeach()

endif()

