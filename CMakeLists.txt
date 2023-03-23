cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_SYSTEM_NAME iOS)
set(CMAKE_OSX_DEPLOYMENT_TARGET "11.0" CACHE STRING "Minimum OS X deployment version")

set(CMAKE_XCODE_ATTRIBUTE_SDKROOT iphoneos)
set(CMAKE_XCODE_ATTRIBUTE_SUPPORTED_PLATFORMS "iphonesimulator iphoneos")
set(CMAKE_XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH "YES")
set(CMAKE_IOS_INSTALL_COMBINED YES)
set(CMAKE_XCODE_ATTRIBUTE_ENABLE_BITCODE "YES")
set(CMAKE_XCODE_ATTRIBUTE_BITCODE_GENERATION_MODE bitcode)

set(app "learn-ffmpeg-mac-ios")
set(arch arm64)
# set(arch x86_64)
set(CMAKE_OSX_ARCHITECTURES ${arch})
project(${app})
set(lib_dir ${CMAKE_CURRENT_LIST_DIR}/ffmpeg/include)
file(GLOB_RECURSE ffmpeg_src ${lib_dir}/*.h )
set(proj_src ${ffmpeg_src} ./src/main.cpp)
add_executable(${app} ${proj_src})

source_group(TREE ./ FILES ${proj_src})

include_directories(${lib_dir})
set(lib_arch ${CMAKE_CURRENT_LIST_DIR}/ffmpeg/${arch})
set(ffmpeg_libs libavcodec libavfilter libavformat libavutil libswscale libswresample)
# link_directories(${lib_arch})
# link_libraries(${ffmpeg_libs})
foreach(lib ${ffmpeg_libs}) 
    target_link_libraries(${app}   ${lib_arch}/${lib}.a)
endforeach()

# fix: "_compress", referenced from:      _encode_strip in libavcodec.a(tiffenc.o)
# TIFF（Tagged Image File Format）库是一个用于处理图像文件的开放源代码软件库。它支持许多不同的压缩算法和颜色空间，并且可以读取和写入多种格式的图像文件。
# 安装: brew install libtiff
# http://download.osgeo.org/libtiff/

# set(CMAKE_PREFIX_PATH "/usr/local")
# set(TIFF_LIBRARY "/usr/local/lib/libtiff.a")
# set(TIFF_INCLUDE_DIR "/usr/local/include")
# find_package(TIFF REQUIRED)
# if(NOT TIFF_FOUND)
#     message(FATAL_ERROR "need tiff")
# endif()
# message(STATUS "tiff include dirs: ${TIFF_INCLUDE_DIRS}")
# message(STATUS "tiff libraries: ${TIFF_LIBRARIES}")
# target_link_libraries(${app} PRIVATE TIFF::TIFF)

# foreach(package Iconv ZLIB BZip2)
#     find_package(${package} REQUIRED)
#     if(NOT ${package}_FOUND)
#         message(FATAL_ERROR "need ${package}")
#     endif()
#     message(STATUS "[${package}] include dirs: ${${package}_INCLUDE_DIRS}")
#     message(STATUS "[${package}] libraries: ${${package}_LIBRARIES}")
#     target_link_libraries(${app} PRIVATE ${${package}_LIBRARIES})
# endforeach()


# fix: _vtenc_send_frame in libavcodec.a(videotoolboxenc.o)
foreach(framework CoreVideo CoreAudio VideoToolbox AudioToolbox CoreMedia Security CoreFoundation bz2 z iconv)
    find_library(result NAMES ${framework} NO_CACHE REQUIRED) 
    if(NOT result)
        message(FATAL_ERROR "need ${framework}")
    endif()
    message(STATUS "${framework}: ${result}")
    target_link_libraries(${app}   ${result})
    unset(result)
endforeach()

# fix: _flashsv_decode_frame in libavcodec.a(flashsv.o)
# fix: vtenc_create_encoder in libavcodec.a(videotoolboxenc.o)
# fix: _flashsv2_encode_frame in libavcodec.a(flashsv2enc.o)
# fix: _matroska_decode_buffer in libavformat.a(matroskadec.o)


foreach(source ${proj_src})
    # targetMembership 仅对cpp有效
    set_source_files_properties(${source} PROPERTIES 
        XCODE_FILE_ATTRIBUTES "TargetMembership(${app})"
    )
endforeach()
