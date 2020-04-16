windows-args = -lglfw3 -lopengl32 -lgdi32
linux-args   = -lglfw3 -pthread -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -ldl -lXcursor
IMGUI_CPP_FILES = imgui/imgui.cpp imgui/imgui_draw.cpp imgui/imgui_widgets.cpp imgui/imgui_impl_glfw.cpp imgui/imgui_impl_opengl3.cpp

ifeq ($(OS),Windows_NT)
	CCFLAGS = $(windows-args)
else
	CCFLAGS = $(linux-args)
endif

default:
	cmd.exe /c g++ -std=c++17 main.cpp IsoSurface.cpp Volume.cpp WindowManagement.cpp Model.cpp Camera.cpp VAO.cpp Shader.cpp glad/glad.c -o main.exe $(windows-args)
	./main.exe

linux:
	g++ main.cpp IsoSurface.cpp Volume.cpp WindowManagement.cpp Model.cpp Camera.cpp VAO.cpp Shader.cpp glad/glad.c -o main $(linux-args)
	./main

histogram:
	cmd.exe /c g++ -DHISTOGRAM main.cpp IsoSurface.cpp Volume.cpp WindowManagement.cpp Model.cpp Camera.cpp VAO.cpp Shader.cpp glad/glad.c -o main.exe $(CCFLAGS)
	./main.exe
	cmd.exe /c python histogram.py
iso:
	cmd.exe /c g++ testIsoSurface.cpp IsoSurface.cpp Volume.cpp -Wall -o iso.exe
	./iso.exe

testVolume:
	cmd.exe /c g++ testVolume.cpp Volume.cpp -Wall -o testVolume.exe
	./testVolume.exe

test2vao:
	cmd.exe /c g++ test2vao.cpp glad/glad.c -o test2vao.exe $(CCFLAGS)
	./test2vao.exe
