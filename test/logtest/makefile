#=====================================================
include ./makefile.local
#=====================================================

TARGET	= logtest

FILES	= ./LogTestTask.cpp \
		./LogTest.cpp
		
SRCS	= $(FILES)
OBJS 	= $(SRCS:.cpp=.o)

INCLDIRS	+= -I../../src/common -I../../src/log -I../../src/os
LIBS		+= -L../../lib -lcastella \
			-lpthread

.SUFFIXES : .cpp .o
.cpp.o:
	$(CXX) $(CFLAGS) $(DEFS) $(INCLDIRS) -o $*.o -c $*.cpp 2> err

all : $(TARGET)
	$(CXX) $(BINLDFLAGS) $(TARGET) $(OBJS) $(LIBS)

$(TARGET) : $(OBJS)

clean:
	rm -f *.o
	rm -f $(TARGET)

