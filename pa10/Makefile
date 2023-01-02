ifeq (Windows_NT, $(OS))
RM_CMD := del /F
EXE = main.exe
else
RM_CMD := rm -vf
EXE = main
endif

# Definition of variables
SRCS = main.cpp dataset.cpp nn.cpp train_test.cpp
OBJS = $(SRCS:.cpp=.o)
CPPFLAGS = -std=c++11 -g -Ofast -Iincludes -Wpedantic

all: $(EXE)

$(EXE): $(OBJS)
	g++ $(CPPFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	g++ $(CPPFLAGS) -c $< -o $@

# For removing the objects/executable files
clean:
	$(RM_CMD) $(OBJS)

# # makedepend can find the .h dependencies automatically
# depend:; makedepend $(SRCS)
