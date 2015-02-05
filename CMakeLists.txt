#include_directories(${CMAKE_SRC_DIR}../node/)
#include_directories(${CMAKE_SRC_DIR}../node/src)

#include_directories( SYSTEM "${ANDROID_SYSROOT}/usr/include" ${ANDROID_STL_INCLUDE_DIRS} )
include_directories(SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/../node/src")
include_directories(SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/../node/deps/v8/include")
include_directories(SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/../node/deps/uv/include")

message(STATUS "cmake src dir is:")
message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "${CMAKE_CURRENT_SOURCE_DIR}/../node/src")
add_executable(app src/nodecompute.cc src/ocl.cpp)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -ffunction-sections -fdata-sections -fpermissive -Wignored-qualifiers")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -ffunction-sections -fdata-sections -fpermissive -Wignored-qualifiers")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -I../../node/src -DDEBUG -D_DEBUG -g -O0")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -I../../node/src -DDEBUG -D_DEBUG -g -O0 ")


if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(LINUX True)
endif()

if(TARGET_ARCH STREQUAL "ia32")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -m32")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -m32 ")
  endif()
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m32")
  set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -m32")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -m32")

           # 'cflags': [ '-m32' ],
            #'ldflags': [ '-m32' ],
endif()

if (TARGET_ARCH STREQUAL "x64")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64")
  if (CMAKE_BUILD_TYPE EQAUL "Debug")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -m64")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -m64 ")
  endif()
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m64")
  set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -m64")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -m64")
endif()

if (UNIX AND NOT APPLE) # Linux, freebsd, solaris. But not mac or win
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-omit-frame-pointer -pthread -Wall -Wextra -Wno-unused-parameter -fno-rtti', '-fno-exceptions'")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread -rdynamic")
endif()

set(BUILDING_NODE_EXTENSION True)

#[ 'OS=="freebsd" or OS=="openbsd" or OS=="solaris" or (OS=="linux" and target_arch!="ia32")', {

if (UNIX OR LINUX)
  if (NOT TARGET_ARCH  EQUAL "ia32")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -fPIC")
  endif()
endif()






#if ggc version >= 40
# set cflags  -fno-tree-vrp'  # Work around compiler bug.
#endif
#if ggc version <=44 
# set cflags '-fno-tree-sink'  # Work around compiler bug.
#endif

#   argv.push('-I', addon_gypi)
#   argv.push('-I', common_gypi)
#   argv.push('-Dlibrary=shared_library')
#   argv.push('-Dvisibility=default')
#   argv.push('-Dnode_root_dir=' + nodeDir)
#   argv.push('-Dmodule_root_dir=' + process.cwd())
#   argv.push('--depth=.')
#   argv.push('--no-parallel')


