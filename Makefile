windows-args = -lglfw3 -lopengl32 -lgdi32
linux-args   = -lglfw3 -pthread -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -ldl -lXcursor
IMGUI_SOURCE_FILES = src/imgui/imgui.cpp src/imgui/imgui_draw.cpp src/imgui/imgui_widgets.cpp src/imgui/imgui_impl_glfw.cpp src/imgui/imgui_impl_opengl3.cpp
GLAD_SOURCE_FILES = src/glad/*.c


OBJ_DIR = obj
LIB_DIR = lib


SOURCES = $(wildcard src/*.cpp)
SOURCES += $(wildcard src/glad/*.c)
SOURCES += $(wildcard src/imgui/*.cpp)


OBJS    = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(notdir $(SOURCES)))))
LIBS    = -L./lib
CXXFLAGS= -std=c++17 -I./include


mkdir = 
rm = 


ifeq ($(OS),Windows_NT)
	CCFLAGS = $(windows-args)

	mkdir = if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)

	rm = del /S /Q *.exe *.out imgui.ini & rmdir /S /Q $(OBJ_DIR)
else ifeq ($(findstring Microsoft, $(shell uname -a)), Microsoft)
	CXX = cmd.exe /c g++
	EXE = main.exe

	LIBS += $(windows-args)

	mkdir = mkdir -p $(OBJ_DIR)
    
	rm = rm *.exe *.out imgui.ini
	rm = rm -rf $(OBJ_DIR)
else
	CXX = g++
	EXE = main

	LIBS += $(linux-args)

	mkdir = mkdir -p $(OBJ_DIR)

	rm = rm *.exe *.out imgui.ini
	rm = rm -rf $(OBJ_DIR)
endif


$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: src/glad/%.c
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: src/imgui/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


default: create_dir $(EXE) exe
	@echo Compile and Execute Success

create_dir:
	$(call mkdir)

linux:
	$(CXX) $(CXXFLAGS) -std=c++17 $(SOURCES) $(IMGUI_SOURCE_FILES) $(GLAD_SOURCE_FILES) -o $(EXE) $(linux-args)
	./main

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

exe:
	./$(EXE)

histogram:
	cmd.exe /c g++ -DHISTOGRAM main.cpp IsoSurface.cpp Volume.cpp WindowManagement.cpp Model.cpp Camera.cpp VAO.cpp Shader.cpp glad/glad.c -o main.exe $(CCFLAGS)
	./main.exe
	cmd.exe /c python histogram.py

clean:
	$(call rm)
