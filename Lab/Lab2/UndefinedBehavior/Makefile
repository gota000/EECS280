# Makefile

# Compiler
CXX ?= g++

# Compiler flags
CXXFLAGS ?= --std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment
WINDOWS_DEBUG ?= -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG
MACOS_DEBUG ?= -fsanitize=address -fsanitize=undefined -D_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_DEBUG

restaurant.exe: restaurant.cpp Cost.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

restaurant_debug.exe: restaurant.cpp Cost.cpp
# IF using Windows, uncomment below vv
	$(CXX) $(CXXFLAGS) $(WINDOWS_DEBUG) $^ -o $@
# IF using macOS, uncomment below vv
#	$(CXX) $(CXXFLAGS) $(MACOS_DEBUG) $^ -o $@

# Disable built-in Makefile rules
.SUFFIXES:

clean:
	rm -rvf *.exe *.dSYM *.stackdump