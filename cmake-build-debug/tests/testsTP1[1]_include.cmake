if(EXISTS "C:/Users/charl/CLionProjects/TP1/cmake-build-debug/tests/testsTP1[1]_tests.cmake")
  include("C:/Users/charl/CLionProjects/TP1/cmake-build-debug/tests/testsTP1[1]_tests.cmake")
else()
  add_test(testsTP1_NOT_BUILT testsTP1_NOT_BUILT)
endif()