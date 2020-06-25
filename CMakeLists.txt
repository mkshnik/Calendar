cmake_minimum_required(VERSION 3.16)
project(Calendar)

set(CMAKE_CXX_STANDARD 17)

 add_executable(
        Calendar src/main.cpp
        src/CApplication.cpp
        src/CApplication.hpp
        src/CStorage.cpp
        src/CCalendar.cpp src/CCalendar.hpp src/CDate.hpp src/CStorage.hpp src/CEvent.hpp src/CTime.hpp src/CSharedEvent.hpp src/CMustDoEvent.hpp src/COptionalEvent.hpp src/CMovableEvent.hpp src/ECalendarTypes.hpp src/CAlarm.cpp src/CAlarm.hpp src/CReminder.hpp src/ETimeWrapper.hpp src/CShowCalendar.hpp src/CScanner.cpp src/CScanner.hpp src/CMovableEvent.cpp src/ECommands.cpp src/ECommands.hpp src/CParticipant.cpp src/CParticipant.hpp src/CSharedEvent.cpp src/CReminder.cpp src/CEvent.cpp src/ETimeWrapper.cpp src/CSaverLoader.cpp src/CSaverLoader.hpp src/ECalendarTypes.cpp src/CShowCalendar.cpp src/CTime.cpp)