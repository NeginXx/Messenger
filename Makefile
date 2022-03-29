Compiler = clang++

Flags = -std=c++17 -O2 -Wall \
-Wextra -Wpedantic -fsanitize=address

CXX = $(Flags)
LXX = -fsanitize=address

Include = include
Src = src
Bin = bin

Cpp = $(notdir $(wildcard $(Src)/*.cpp))
Headers = $(notdir $(wildcard $(Include)/*.h))
Objects = $(addprefix $(Bin)/, $(Cpp:.cpp=.o))

vpath %.cpp $(Src)
$(Bin)/%.o: %.cpp Makefile
	$(Compiler) -c $< $(CXX) -o $@

out: $(Objects)
	$(Compiler) -o out $(Objects) $(LXX)