default: slVector.o slMatrix.o slRotations.o
	ar cr libcommon.a slVector.o slMatrix.o slRotations.o
	ranlib libcommon.a

%.o: %.cpp
	c++ -c -DNDEBUG -O3 -o $@ $< 
