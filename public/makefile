#sample USB_Mail project makefile
RM=rm
CC=g++
MKDIR=mkdir

DIR_OBJ=obj
DIR_BIN=bin

SOURCE=$(wildcard *.cpp)
OBJ=$(patsubst %.cpp,%.o,$(SOURCE))
#CFLAGS+=-DLINUXCODE
#USBCMD:=$(CC) -Dmacro=LINUXCODE -DLINUXCODE -c
USBCMD:=$(CC) $(CFLAGS) -c

DIRS=$(DIR_OBJ) $(DIR_BIN)
TAGGET=libpublic




ALL:$(DIRS) $(TAGGET)
$(DIRS):
	$(MKDIR) $@
#	ECHO $(VPATH)
$(TAGGET):$(OBJ)
	ar -rc ../lib/libpublic.a $(DIR_OBJ)/*.o
MMTrace.o:
	$(USBCMD) -g MMTrace.cpp -o $(DIR_OBJ)/MMTrace.o
XYLogFile.o:
	$(USBCMD) -g XYLogFile.cpp -o $(DIR_OBJ)/XYLogFile.o
XYPublic.o:
	$(USBCMD) -g XYPublic.cpp -o $(DIR_OBJ)/XYPublic.o
XYString.o:
	$(USBCMD) -g XYString.cpp -o $(DIR_OBJ)/XYString.o
XYDateTime.o:
	$(USBCMD) -g XYDateTime.cpp -o $(DIR_OBJ)/XYDateTime.o
XYFile.o:
	$(USBCMD) -g XYFile.cpp -o $(DIR_OBJ)/XYFile.o
#XYError.o:
#	$(USBCMD) -g XYError.cpp -o $(DIR_OBJ)/XYError.o
XYObject.o:
	$(USBCMD) -g XYObject.cpp  -o $(DIR_OBJ)/XYObject.o





#SRCS=$(wildcard *.cpp)
#OBJS:=$(addprefix,$(DIR_OBJS)/,$(OBJS))
#TAGGET:=$(addprefix,$(DIR_BIN)/,$(TAGGET))

#$(TAGGET):$(OBJS)
#	$(CC) -o $(DIR_BIN)/$(TAGGET) -ldl $(OBJS)
#$(DIRS):
#	$(MKDIR) $@
#$(DIR_OBJ)/%.o:$(SOURCE)
#	$(CC) -Dmacro=LINUXCODE -DLINUXCODE -c $^ -o $@


clean:
	\$(RM) *.o $(TAGGET) $(DIRS) -fr


