CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )
PROJECT( cppcore )
SET ( CPPCORE_VERSION_MAJOR 0 )
SET ( CPPCORE_VERSION_MINOR 1 )
SET ( CPPCORE_VERSION_PATCH 0 )
SET ( CPPCORE_VERSION ${CPPCORE_VERSION_MAJOR}.${CPPCORE_VERSION_MINOR}.${CPPCORE_VERSION_PATCH} )
SET ( PROJECT_VERSION "${CPPCORE_VERSION}" )

if( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )
    option(gtest_disable_pthreads "Disable uses of pthreads in gtest." ON)
endif()

add_definitions( -DCPPCORE_BUILD )
add_definitions( -D_VARIADIC_MAX=10 )

INCLUDE_DIRECTORIES(
	../
	../include/
    ../contrib/gtest-1.7.0/include
    ../contrib/gtest-1.7.0/
)

link_directories(
	../
)

SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/../lib )
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/../lib )
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/../bin )

if( WIN32 AND NOT CYGWIN )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc" )  # Force to always compile with W4
  if( CMAKE_CXX_FLAGS MATCHES "/W[0-4]" )
    string( REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" )
  else()
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4" )
  endif()
elseif( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -std=c++0x")
endif()

SET ( cppcore_src
	../code/cppcore.cpp
    ../include/cppcore/CPPCoreCommon.h
)

SET ( cppcore_common_src
	../include/cppcore/Common/Variant.h
    ../include/cppcore/Common/CString.h
    ../include/cppcore/Common/TStringBase.h
    ../code/Common/CString.cpp
)

SET ( cppcore_container_src
    ../include/cppcore/Container/TArray.h
    ../include/cppcore/Container/TList.h
)
 
SOURCE_GROUP( code            FILES ${cppcore_src} )
SOURCE_GROUP( code\\common    FILES ${cppcore_common_src} )
SOURCE_GROUP( code\\container FILES ${cppcore_container_src} )

ADD_LIBRARY( cppcore SHARED
    ${cppcore_container_src}
    ${cppcore_common_src}
	${cppcore_src}
)

SET( cppcore_common_test_src
	../test/common/StringTest.cpp
    ../test/common/VariantTest.cpp
)

SET( cppcore_container_test_src
    ../test/container/TArrayTest.cpp
    ../test/container/TListTest.cpp
)

SET ( GTEST_PATH ../contrib/gtest-1.7.0 )

SET ( gtest_src
    ${GTEST_PATH}/src/gtest-death-test.cc
    ${GTEST_PATH}/src/gtest-filepath.cc
    ${GTEST_PATH}/src/gtest-internal-inl.h
    ${GTEST_PATH}/src/gtest-port.cc
    ${GTEST_PATH}/src/gtest-printers.cc
    ${GTEST_PATH}/src/gtest-test-part.cc
    ${GTEST_PATH}/src/gtest-typed-test.cc
    ${GTEST_PATH}/src/gtest.cc
    ${GTEST_PATH}/src/gtest_main.cc
)

SOURCE_GROUP( code\\common    FILES ${cppcore_common_test_src} )
SOURCE_GROUP( code\\container FILES ${cppcore_container_test_src} )
SOURCE_GROUP( contrib\\gtest  FILES ${gtest_src} )

ADD_EXECUTABLE( cppcore_test
    ${gtest_src}
    ${cppcore_common_test_src}
    ${cppcore_container_test_src}
)

target_link_libraries( cppcore_test cppcore )
