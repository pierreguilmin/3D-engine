CXX      = clang++
CXXFLAGS = -Weverything -Wno-c++11-extensions -Wno-padded -Wno-c++98-compat -Wno-float-conversion -Wno-conversion -std=c++11
EXEC     = 3D-engine
LIB      = -lsfml-window -lsfml-graphics -lsfml-system
SRC      = $(wildcard src/*.cpp)
OBJ      = $(patsubst src/%.cpp,obj/%.o,$(SRC))
DEP      = $(OBJ:.o=.d)


all: print_compilation $(EXEC) open


-include $(DEP)


print_compilation:
	@printf '→ compilation...\n'


$(EXEC): $(OBJ)
	$(CXX) $^ -o $(EXEC) $(LIB)


obj/%.o : src/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@


open:
	@printf '\n→ launch $(EXEC)...\n'
	@./$(EXEC)


clean:
	@printf '→ clean...'
	rm -f obj/*.o
	rm -f obj/*.d
	rm -f $(EXEC)


.PHONY: all clean
