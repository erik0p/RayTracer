CXX=g++

CXXFLAGS=-Wall -g

ifeq ($(OS),Windows_NT)
	RM = del /Q
else
	RM = rm -f
endif

raytracer1a: Render.o Scene.o Sphere.o Ray.o Vector3.o Color.o Object.o
	$(CXX) $(CXXFLAGS) Render.o Scene.o Sphere.o Object.o Ray.o Vector3.o Color.o -o raytracer1a

Render.o: Render.cpp Scene.o Ray.o Vector3.o
	$(CXX) $(CXXFLAGS) -c Render.cpp

Scene.o: Scene.cpp Scene.h Ray.o Vector3.o Color.o Sphere.o
	$(CXX) $(CXXFLAGS) -c Scene.cpp

Sphere.o: Sphere.cpp Sphere.h Vector3.o Object.o
	$(CXX) $(CXXFLAGS) -c Sphere.cpp

Object.o: Object.cpp Object.h
	$(CXX) $(CXXFLAGS) -c Object.cpp

# Point3.o: Point3.cpp Point3.h
# 	$(CXX) $(CXXFLAGS) -c Point3.cpp

Ray.o: Ray.cpp Ray.h Vector3.o
	$(CXX) $(CXXFLAGS) -c Ray.cpp

Vector3.o: Vector3.cpp Vector3.h
	$(CXX) $(CXXFLAGS) -c Vector3.cpp

Color.o: Color.cpp Color.h
	$(CXX) $(CXXFLAGS) -c Color.cpp

clean:
	$(RM) *.o *.exe
