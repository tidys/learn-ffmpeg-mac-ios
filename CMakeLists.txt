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
# set(arch arm64)
set(arch x86_64)
set(CMAKE_OSX_ARCHITECTURES ${arch})
project(${app})
set(lib_dir ${CMAKE_CURRENT_LIST_DIR}/ffmpeg/include)
file(GLOB_RECURSE ffmpeg_src ${lib_dir}/*.h )
set(proj_src ${ffmpeg_src} ./src/main.cpp)
add_executable(${app} ${proj_src})

source_group(TREE ./ FILES ${proj_src})

include_directories(${lib_dir})
set(lib_arch ${CMAKE_CURRENT_LIST_DIR}/ffmpeg/${arch})
# link_directories(${lib_arch})
# link_libraries(libavcodec libavfilter libavformat libavutil libswscale)
foreach(lib libavcodec libavfilter libavformat libavutil libswscale)
    target_link_libraries(${app} ${lib_arch}/${lib}.a)
endforeach()

foreach(source ${proj_src})
    # targetMembership 仅对cpp有效
    set_source_files_properties(${source} PROPERTIES 
        XCODE_FILE_ATTRIBUTES "TargetMembership(${app})"
    )
    
endforeach()
