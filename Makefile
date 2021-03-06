EXECUTABLE := robot.exe
LIBS := gtest pthread
INCLUDES := include
SRCDIR:= src test
CC:=g++
CPPFLAGS := -g -Wall -O3 -std=c++11
CPPFLAGS += $(addprefix -I,$(INCLUDES))

SRCS := $(wildcard $(addsuffix /*.cpp, $(SRCDIR)))
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

.PHONY : all objs clean

all: $(EXECUTABLE)

objs : $(OBJS)

clean :
	rm -f $(OBJS)

$(EXECUTABLE) : $(OBJS)
	$(CC) -o $(EXECUTABLE) $(OBJS) $(addprefix -l,$(LIBS))
