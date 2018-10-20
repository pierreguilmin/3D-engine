CXX      = clang++
CXXFLAGS = -Weverything -Wno-c++98-compat -Wno-c++11-extensions -Wno-padded -Wno-conversion -Wno-global-constructors -Wno-exit-time-destructors
EXEC     = 3D-engine
LIB      = -lsfml-window -lsfml-graphics -lsfml-system
SRC      = $(shell find src -type f -name '*.cpp')
OBJ      = $(patsubst src/%.cpp, obj/%.o, $(SRC))
DEP      = $(OBJ:.o=.d)


all: print_compilation $(EXEC) open


-include $(DEP)


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


.PHONY: all print_compilation open clean cm
