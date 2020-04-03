#=====================================================
include ./makefile.local
#=====================================================

OUTDIR	= ../lib
TARGET	= libcastella.$(PREFIX_A)

FILES	= ./common/SCEventHandler.cpp \
		./common/SCPThreadTask.cpp \
		./common/SCSelectReactor.cpp \
		./common/SCSocketHandler.cpp \
		./log/SCFileStream.cpp \
		./log/SCLogFormat.cpp \
		./log/SCLogger.cpp \
		./os/SCOS.cpp \
		./os/SCString.cpp \
		./os/SCThread.cpp
		
SRCS	= $(FILES)
OBJS 	= $(SRCS:.cpp=.o)

INCLDIRS	+= -I./common -I./log -I./os

.SUFFIXES : .cpp .o
.cpp.o:
	$(CXX) $(CFLAGS) $(DEFS) $(INCLDIRS) -o $*.o -c $*.cpp 2> err

all : $(TARGET)
	$(AR) $(ARFLAGS) $(TARGET) $(OBJS)
	cp $(TARGET) $(OUTDIR)/.

$(TARGET) : $(OBJS)

clean:
	rm -f */*.o
	rm -f $(TARGET)

