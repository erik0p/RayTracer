CXX=g++

CXXFLAGS=-Wall -g

ifeq ($(OS),Windows_NT)
	RM = del /Q
else
	RM = rm -f
endif

Render: Render.o SceneReader.o Sphere.o Point3.o Vector3.o Color.o
	$(CXX) $(CXXFLAGS) Render.o SceneReader.o Sphere.o Point3.o Vector3.o Color.o -o Render

Render.o: Render.cpp SceneReader.o SceneReader.h
	$(CXX) $(CXXFLAGS) -c Render.cpp

SceneReader.o: SceneReader.cpp SceneReader.h Vector3.o Color.o Sphere.o Point3.o
	$(CXX) $(CXXFLAGS) -c SceneReader.cpp

Sphere.o: Sphere.cpp Sphere.h Point3.o
	$(CXX) $(CXXFLAGS) -c Sphere.cpp

Point3.o: Point3.cpp Point3.h
	$(CXX) $(CXXFLAGS) -c Point3.cpp

Vector3.o: Vector3.cpp Vector3.h
	$(CXX) $(CXXFLAGS) -c Vector3.cpp

Color.o: Color.cpp Color.h
	$(CXX) $(CXXFLAGS) -c Color.cpp

clean:
	$(RM) *.o *.exe
