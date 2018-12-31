CXX      = clang++
CXXFLAGS = -std=c++11 -Weverything -Wno-c++98-compat -Wno-padded -Wno-conversion -Wno-global-constructors -Wno-exit-time-destructors
EXEC     = 3D-engine
LIB      = -lsfml-window -lsfml-graphics -lsfml-system
SRC      = $(shell find src -type f -name '*.cpp')
OBJ      = $(patsubst src/%.cpp, obj/%.o, $(SRC))
DEP      = $(OBJ:.o=.d)


-include $(DEP)


all: print_compilation $(EXEC) open


compile: print_compilation $(EXEC)


print_compilation:
	@printf '\n→ compilation...\n'


$(EXEC): $(OBJ)
	$(CXX) $^ -o $(EXEC) $(LIB)


obj/%.o : src/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@


open:
	@printf '\n→ launch $(EXEC)...\n'
	@./$(EXEC)


clean:
	@printf '\n→ clean...\n'
	rm -f $(OBJ)
	rm -f $(DEP)
	rm -f $(EXEC)


cm: clean all 


.PHONY: all compile print_compilation open clean cm
