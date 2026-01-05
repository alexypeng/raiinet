CXX = g++-14 -std=c++20 -fmodules-ts
CXXFLAGS = -Wall -g
HEADERFLAGS = -c -x c++-system-header
HEADERS = algorithm cstdlib fstream iostream map memory sstream string vector
SOURCES = enums.cc posn.cc posn-impl.cc link.cc link-impl.cc \
		square.cc square-impl.cc abilityresult.cc abilityresult-impl.cc ability.cc ability-impl.cc \
		moveresult.cc linkboost.cc linkboost-impl.cc \
		polarize.cc polarize-impl.cc scan.cc scan-impl.cc \
		firewall.cc firewall-impl.cc barrier.cc barrier-impl.cc \
		diagonal.cc diagonal-impl.cc swap.cc swap-impl.cc  download.cc download-impl.cc\
		board.cc board-impl.cc player.cc player-impl.cc iobserver.cc isubject.cc \
		isubject-impl.cc game.cc game-impl.cc textdisplay.cc \
		textdisplay-impl.cc window.cc window-impl.cc graphic-display.cc \
		graphic-display-impl.cc main.cc
OBJECTS = $(SOURCES:.cc=.o)
EXEC = RAIInet

all: $(EXEC)

$(EXEC): headers $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC) -lX11

.PHONY: headers
headers:
	$(CXX) $(HEADERFLAGS) $(HEADERS)

%.o: %.cc headers
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(EXEC) $(OBJECTS)
	rm -rf gcm.cache
