CC          = c++ 

#-----------------------------------------
#Optimization ----------------------------
OPT   =  -Wno-deprecated -g

# on mac use this
#GL_LIB = -framework OpenGL -framework GLUT -framework foundation
# on linux use this
GL_LIB = -lGL -lglut -lGLU

#-----------------------------------------

TARGETS = forwardKinematics viewer

OBJECTS = slVector.o slMatrix.o slRotations.o

#-----------------------------------------

LIBS = $(GL_LIB) 

CCOPTS = $(OPT) $(INCS) 
LDOPTS = $(OPT) $(INCS) $(LIBS) 

#-----------------------------------------
#-----------------------------------------

default: $(TARGETS)


clean:
	/bin/rm -f *.o $(TARGETS)

#-----------------------------------------
#-----------------------------------------

forwardKinematics: $(OBJECTS) forwardKinematics.o
	$(CC) $(OBJECTS) forwardKinematics.o -o forwardKinematics $(LDOPTS)
viewer: $(OBJECTS) viewer.o
	$(CC) $(OBJECTS) viewer.o -o viewer $(LDOPTS)

#-----------------------------------------
#-----------------------------------------

.cpp.o: 
	$(CC) $(CCOPTS) -c $< 

#-----------------------------------------
#-----------------------------------------







