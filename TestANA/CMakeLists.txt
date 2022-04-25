set( LLVM_BINARY_DIR ${LLVM_DIR}/llvm-project/build/bin)
configure_lit_site_cfg(
        ${CMAKE_CURRENT_SOURCE_DIR}/lit.site.cfg.py.in
        ${CMAKE_CURRENT_BINARY_DIR}/lit.site.cfg.py
        MAIN_CONFIG
        ${CMAKE_CURRENT_SOURCE_DIR}/lit.cfg.py
)

set(ANA_TEST_DEPENDS
        FileCheck count not lit 
        )

add_lit_testsuite(check-ana "Running the ana regression tests"
        ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS ${ANA_TEST_DEPEND}
        )
set_target_properties(check-ana PROPERTIES FOLDER "Tests")

add_lit_testsuites( ${CMAKE_CURRENT_SOURCE_DIR} DEPENDS ${ANA_TEST_DEPEND})