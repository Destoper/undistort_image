PROJECT = code
SRC = undistortedCap.cpp test.cpp

LIBS = `pkg-config opencv4 --cflags --libs`


$(PROJECT): $(SRC)
	g++ $(SRC) -o $(PROJECT) $(LIBS) -lstdc++

run: $(PROJECT)
	./$(PROJECT)