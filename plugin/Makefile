

__start__: obj __lines_for_space__ ../libs/libInterp4Move.so ../libs/libInterp4Set.so ../libs/libInterp4Pause.so  ../libs/libInterp4Rotate.so 
	@echo "  Tworzenie wtyczki zakonczone."
	@echo

obj:
	mkdir obj

CPPFLAGS=-Wall -fPIC -pedantic -std=c++17 -iquote inc -iquote ../inc
LDFLAGS=-Wall -shared

__lines_for_space__:
	@echo
	@echo
	@echo
	@echo
	@echo

../libs/libInterp4Move.so: obj/Interp4Move.o
	g++ ${LDFLAGS} -o ../libs/libInterp4Move.so obj/Interp4Move.o
	@echo
	@echo "  Wtyczka dla polecenia 'Move' zostala utworzona."
	@echo


obj/Interp4Move.o: src/Interp4Move.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Move.hh 
	g++ -c ${CPPFLAGS} -o obj/Interp4Move.o src/Interp4Move.cpp
	

../libs/libInterp4Set.so: obj/Interp4Set.o
	g++ ${LDFLAGS} -o ../libs/libInterp4Set.so obj/Interp4Set.o
	@echo
	@echo "  Wtyczka dla polecenia 'Set' zostala utworzona."
	@echo


obj/Interp4Set.o: src/Interp4Set.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Set.hh 
	g++ -c ${CPPFLAGS} -o obj/Interp4Set.o src/Interp4Set.cpp




../libs/libInterp4Pause.so: obj/Interp4Pause.o
	g++ ${LDFLAGS} -o ../libs/libInterp4Pause.so obj/Interp4Pause.o
	@echo
	@echo "  Wtyczka dla polecenia 'Pasue' zostala utworzona."
	@echo


obj/Interp4Pause.o: src/Interp4Pause.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Pause.hh 
	g++ -c ${CPPFLAGS} -o obj/Interp4Pause.o src/Interp4Pause.cpp



../libs/libInterp4Rotate.so: obj/Interp4Rotate.o
	g++ ${LDFLAGS} -o ../libs/libInterp4Rotate.so obj/Interp4Rotate.o
	@echo
	@echo "  Wtyczka dla polecenia 'Rotate' zostala utworzona."
	@echo


obj/Interp4Rotate.o: src/Interp4Rotate.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Rotate.hh 
	g++ -c ${CPPFLAGS} -o obj/Interp4Rotate.o src/Interp4Rotate.cpp




clean:
	rm -f obj/*

cleanall: clean
	find . -name \*~ -print -exec rm {} \;
