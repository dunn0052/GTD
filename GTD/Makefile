
INCLDIR = \
          -I$(PATH)/src/include
LIBDIR = $(PATH)/lib

CC= g++
#CXXFLAGS= -fPIC -std=c++11 -g -Wall
CXXFLAGS= -std=c++11 -g -Wall
LDFLAGS= -shared

BINDIR=
TARGET_NAME = GTD
TARGET_EXT = .so
TARGET=$(BINDIR)\$(TARGET_NAME)$(TARGET_EXT)

SOURCES = $(echo *.cpp)
HEADERS = $(echo *.h)
OBJS = $(SOURCES\:\.cpp=\.o)

all: $(TARGET) \: $(OBJS) $(LIBS)
#all: $(TARGET) \: $(OBJS) $(LIBS)
#$(CC) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

#clean:
#      rm -f core *~ \#* *.bak $(TARGET) $(OBJS)
