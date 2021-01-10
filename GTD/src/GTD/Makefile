
INCLDIR = \
          -I$(PATH)/src/include
LIBDIR = $(PATH)/lib

CC= g++
CXXFLAGS= -fPIC -std=c++11 -g -Wall
LDFLAGS= -shared

BINDIR=$(src\\GTD)
TARGET_NAME = GTD
TARGET_EXT = .so
TARGET=$(BINDIR)\$(TARGET_NAME)$(TARGET_EXT)

OBJECTS = \
          App.o\
          Layer.o\

SOURCES = $(echo *.cpp)
HEADERS = $(echo *.h)
OBJS = $(SOURCES\:\.cpp=\.o)

all: $(TARGET) \: $(OBJS) $(LIBS)
	TEST ALL
#all: $(TARGET) \: $(OBJS) $(LIBS)
#$(CC) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

#clean:
#      rm -f core *~ \#* *.bak $(TARGET) $(OBJS)
