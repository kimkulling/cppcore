CMAKE_MINIMUM_REQUIRED( VERSION 3.10 )
PROJECT( cppcore )
SET ( CPPCORE_VERSION_MAJOR 0 )
SET ( CPPCORE_VERSION_MINOR 1 )
SET ( CPPCORE_VERSION_PATCH 0 )
SET ( CPPCORE_VERSION ${CPPCORE_VERSION_MAJOR}.${CPPCORE_VERSION_MINOR}.${CPPCORE_VERSION_PATCH} )
SET ( PROJECT_VERSION "${CPPCORE_VERSION}" )

if( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )
    find_package(Threads)
endif()

set(CMAKE_CXX_STANDARD 14)
option( CPPCORE_BUILD_UNITTESTS 
    "Build unit tests."
     ON 
)
option( CPPCORE_ASAN
    "Enable AddressSanitizer."
    OFF
)
option( CPPCORE_UBSAN
    "Enable Undefined Behavior sanitizer."
    OFF
)

add_definitions( -DCPPCORE_BUILD )
add_definitions( -D_VARIADIC_MAX=10 )
add_definitions( -D_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING=1)

INCLUDE_DIRECTORIES( BEFORE
    include/
    contrib/googletest-1.10.0/gtest/include
    contrib/googletest-1.10.0/gtest
)

link_directories(
    ${CMAKE_HOME_DIRECTORY}/
)

SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib )
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib )
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin )

if( WIN32 AND NOT CYGWIN )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc" )  # Force to always compile with W4
  if( CMAKE_CXX_FLAGS MATCHES "/W[0-4]" )
    string( REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" )
  else()
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4" )
  endif()
elseif( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -g -pedantic -std=c++0x")
elseif ( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -g -pedantic -std=c++11")
endif()

IF (ASSIMP_ASAN)
  MESSAGE(STATUS "AddressSanitizer enabled")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
ENDIF()

IF (ASSIMP_UBSAN)
  MESSAGE(STATUS "Undefined Behavior sanitizer enabled")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined -fno-sanitize-recover=all")
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=undefined -fno-sanitize-recover=all")
ENDIF()

SET ( cppcore_src
    code/cppcore.cpp
    include/cppcore/CPPCoreCommon.h
)

SET ( cppcore_common_src
    include/cppcore/Common/Hash.h
    include/cppcore/Common/TStringBase.h
    include/cppcore/Common/TSharedPtr.h
    include/cppcore/Common/Variant.h
    include/cppcore/Common/TBitField.h
    include/cppcore/Common/TOptional.h
)

SET( cppcore_random_src
    include/cppcore/Random/RandomGenerator.h
    code/Random/RandomGenerator.cpp
)

SET ( cppcore_container_src
    include/cppcore/Container/THashMap.h
    include/cppcore/Container/TArray.h
    include/cppcore/Container/TStaticArray.h
    include/cppcore/Container/TList.h
    include/cppcore/Container/TQueue.h
    include/cppcore/Container/TStaticArray.h
)
 
 SET ( cppcore_memory_src
    include/cppcore/Memory/MemUtils.h
    include/cppcore/Memory/TDefaultAllocator.h
    include/cppcore/Memory/TStackAllocator.h
    include/cppcore/Memory/TPoolAllocator.h
    code/Memory/MemUtils.cpp
 )

 SET( cppcore_io_src 
    include/cppcore/IO/FileSystem.h
 )

SOURCE_GROUP( code            FILES ${cppcore_src} )
SOURCE_GROUP( code\\common    FILES ${cppcore_common_src} )
SOURCE_GROUP( code\\container FILES ${cppcore_container_src} )
SOURCE_GROUP( code\\IO        FILES ${cppcore_io_src} )
SOURCE_GROUP( code\\memory    FILES ${cppcore_memory_src} )
SOURCE_GROUP( code\\random    FILES ${cppcore_random_src} )

ADD_LIBRARY( cppcore SHARED
    ${cppcore_container_src}
    ${cppcore_common_src}
    ${cppcore_memory_src}
    ${cppcore_random_src}
    ${cppcore_io_src}
    ${cppcore_src}
    README.md
)


IF( CPPCORE_BUILD_UNITTESTS )
    SET( cppcore_test_src  
        test/CPPCoreCommonTest.cpp 
    )

    SET( cppcore_common_test_src
        test/common/HashTest.cpp
        test/common/VariantTest.cpp
        test/common/TBitFieldTest.cpp
        test/common/TOptionalTest.cpp
        test/common/TSharedPtrTest.cpp
    )

    SET( cppcore_container_test_src
        test/container/TArrayTest.cpp
        test/container/THashMapTest.cpp
        test/container/TListTest.cpp
        test/container/TQueueTest.cpp
        test/container/TStaticArrayTest.cpp
    )

    SET( cppcore_memory_test_src
        test/memory/TStackAllocatorTest.cpp
        test/memory/TPoolAllocatorTest.cpp
    )

    SET( cppcore_random_test_src
        test/Random/RandomGeneratorTest.cpp
    )
	
    SET ( GTEST_PATH ../contrib/googletest-1.10.0 )

    SOURCE_GROUP( code            FILES ${cppcore_test_src} )
    SOURCE_GROUP( code\\common    FILES ${cppcore_common_test_src} )
    SOURCE_GROUP( code\\container FILES ${cppcore_container_test_src} )
    SOURCE_GROUP( code\\memory    FILES ${cppcore_memory_test_src} ) 
    SOURCE_GROUP( code\\random    FILES ${cppcore_random_test_src} )
    
    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    SET(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    ADD_SUBDIRECTORY( contrib/googletest-1.10.x/ )
    ADD_EXECUTABLE( cppcore_unittest
        ${cppcore_test_src}
        ${cppcore_common_test_src}
        ${cppcore_memory_test_src}
        ${cppcore_random_test_src}
        ${cppcore_container_test_src}
    )

    IF( WIN32 )
        SET( platform_libs )
    ELSE( WIN32 )
        SET( platform_libs pthread )
    ENDIF( WIN32 )
    target_link_libraries( cppcore_unittest cppcore ${CMAKE_THREAD_LIBS_INIT} gtest_main ${platform_libs} )
ENDIF()
