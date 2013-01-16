#makefile model
RM=rm
CC=g++
MKDIR=mkdir

DIR_OBJ=obj
DIR_BIN=bin
#UE_Dll.o UE_SocketD.o UE_DealMail.o UE_Comm.o main.o
SOURCE=$(wildcard *.cpp)
OBJ=$(patsubst %.cpp,%.o,$(SOURCE))
#CFLAGS+=-DLINUXCODE
#USBCMD:=$(CC) -Dmacro=LINUXCODE -DLINUXCODE -c
USBCMD:=$(CC) $(CFLAGS) -c

DIRS=$(DIR_OBJ) $(DIR_BIN)
TAGGET=main




ALL:$(DIRS) $(TAGGET)
$(DIRS):
	$(MKDIR) $@
#	ECHO $(VPATH)
$(TAGGET):$(OBJ)
	$(CC) -WALL -g -o $(DIR_BIN)/main  $(DIR_OBJ)/*.o -L./lib/ -lpublic
main.o:
	$(USBCMD) -g main.cpp -o $(DIR_OBJ)/main.o




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


