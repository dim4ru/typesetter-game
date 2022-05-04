cmake_minimum_required(VERSION 3.22)
project(typesetter)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(typesetter)

add_executable(typesetter
        typesetter/main.c
        typesetter.xcodeproj/project.xcworkspace/xcshareddata/IDEWorkspaceChecks.plist
        typesetter.xcodeproj/project.xcworkspace/xcuserdata/dmitry.xcuserdatad/UserInterfaceState.xcuserstate
        typesetter.xcodeproj/project.xcworkspace/contents.xcworkspacedata
        typesetter.xcodeproj/xcuserdata/dmitry.xcuserdatad/xcdebugger/Breakpoints_v2.xcbkptlist
        typesetter.xcodeproj/xcuserdata/dmitry.xcuserdatad/xcschemes/xcschememanagement.plist
        typesetter.xcodeproj/project.pbxproj
        "versions/Архив/Подсчет символов в файле"
        versions/1.0.1
        versions/1.0.2
        versions/1.1
        "versions/1.4 comments"
        "versions/1.4 safe"
        versions/1.4debug
        "#include <stdio.h>"
        english.txt
        russian.txt
        russian0.txt)
