OBJ=obj
CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++17 -g
execute=./kuvshmyk

all: compile doc

compile: dirs $(execute)
.PHONY: doc
doc :
		doxygen examples/doc-tmp
		mv doc/html/* doc

$(execute): obj/main.o obj/CAlarm.o obj/CAplication.o obj/CTime.o obj/CCalendar.o obj/CEvent.o obj/CSharedEvent.o obj/CStorage.o obj/CSaverLoader.o obj/CMovableEvent.o obj/CParticipant.o obj/CReminder.o obj/CScanner.o obj/ECommands.o obj/ECalendarTypes.o obj/CShowCalendar.o obj/ETimeWrapper.o
	$(CXX) $(CXXFLAGS) -o $@ $^
dirs:
	mkdir $(OBJ)

obj/CAlarm.o: src/CAlarm.cpp
	$(CXX) -c -o obj/CAlarm.o $^
obj/CEvent.o: src/CEvent.cpp
	$(CXX) -c -o obj/CEvent.o $^
obj/CAplication.o: src/CApplication.cpp
	$(CXX) -c -o obj/CAplication.o $^
obj/CCalendar.o: src/CCalendar.cpp
	$(CXX) -c -o obj/CCalendar.o $^
obj/CMovableEvent.o: src/CMovableEvent.cpp
	$(CXX) -c -o obj/CMovableEvent.o $^
obj/ECalendarTypes.o: src/ECalendarTypes.cpp
	$(CXX) -c -o obj/ECalendarTypes.o $^
obj/CShowCalendar.o: src/CShowCalendar.cpp
	$(CXX) -c -o obj/CShowCalendar.o $^
obj/CParticipant.o: src/CParticipant.cpp
	$(CXX) -c -o obj/CParticipant.o $^
obj/CReminder.o : src/CReminder.cpp
	$(CXX) -c -o obj/CReminder.o $^
obj/CSaverLoader.o : src/CSaverLoader.cpp
	$(CXX) -c -o obj/CSaverLoader.o $^
obj/CSharedEvent.o : src/CSharedEvent.cpp
	$(CXX) -c -o obj/CSharedEvent.o $^
obj/CScanner.o: src/CScanner.cpp
	$(CXX) -c -o obj/CScanner.o $^
obj/ETimeWrapper.o: src/ETimeWrapper.cpp
	$(CXX) -c -o obj/ETimeWrapper.o $^
obj/CStorage.o: src/CStorage.cpp
	$(CXX) -c -o obj/CStorage.o $^
obj/CTime.o: src/CTime.cpp
	$(CXX) -c -o obj/CTime.o $^
obj/ECommands.o: src/ECommands.cpp
	$(CXX) -c -o obj/ECommands.o $^
obj/main.o: src/main.cpp
		$(CXX) -c -o obj/main.o $^


run:
	$(execute)

clean:
	rm -r $(OBJ) doc/* kuvshmyk


