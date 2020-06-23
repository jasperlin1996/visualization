# Scientific Visualization

1082 Scientific Visualization HW
* Isosurface
* Volume rendering (slicing method)
* Transfer function design
* Streamline
* Sammon Mapping

## Library dependency

* GLFW 3.3.2
* GLAD w/ gl Version 4.3
* ImGui
* ImPlot
* C++17

## OS dependency

|  | Windows 10 | Ubuntu 18.04 | macOS 10.14 |
| -------- | -------- | -------- | --- |
| Isosurface | O | O | X |
| Volume Rendering | O | O | O |
| Transfer Function | O | O | O |
| Streamline | O | O | O |
| Sammon Mapping | O | O | O |


* Due to the deprecation of OpenGL on macOS, the fragment shader of `slicing method` I wrote with OpenGL 4.3 seems not available on macOS with OpenGL 4.1.

## Usage

* Makefile

```bash
make
make run
```

* Compile manually
```bash
mkdir -i obj 
```
```bash
g++ -std=c++17 -I./include -Wall -O3 -c -o obj/StreamLine.o src/StreamLine.cpp
g++ -std=c++17 -I./include -Wall -O3 -c -o obj/WindowManagement.o src/WindowManagement.cpp
g++ -std=c++17 -I./include -Wall -O3 -c -o obj/VAO.o src/VAO.cpp
g++ -std=c++17 -I./include -Wall -O3 -c -o obj/IsoSurface.o src/IsoSurface.cpp
g++ -std=c++17 -I./include -Wall -O3 -c -o obj/Volume.o src/Volume.cpp
g++ -std=c++17 -I./include -Wall -O3 -c -o obj/Camera.o src/Camera.cpp
g++ -std=c++17 -I./include -Wall -O3 -c -o obj/SammonMapping.o src/SammonMapping.cpp
g++ -std=c++17 -I./include -Wall -O3 -c -o obj/Transformation.o src/Transformation.cpp
g++ -std=c++17 -I./include -Wall -O3 -c -o obj/Shader.o src/Shader.cpp
g++ -std=c++17 -I./include -Wall -O3 -c -o obj/Model.o src/Model.cpp
g++ -std=c++17 -I./include -Wall -O3 -c -o obj/VolumeRendering.o src/VolumeRendering.cpp
g++ -std=c++17 -I./include -Wall -O3 -c -o obj/Method.o src/Method.cpp
g++ -std=c++17 -I./include -Wall -O3 -c -o obj/main.o src/main.cpp
g++ -std=c++17 -I./include -Wall -O3 -c -o obj/glad.o src/glad/glad.c
g++ -std=c++17 -I./include -Wall -O3 -c -o obj/imgui_draw.o src/imgui/imgui_draw.cpp
g++ -std=c++17 -I./include -Wall -O3 -c -o obj/imgui_widgets.o src/imgui/imgui_widgets.cpp
g++ -std=c++17 -I./include -Wall -O3 -c -o obj/imgui_impl_opengl3.o src/imgui/imgui_impl_opengl3.cpp
g++ -std=c++17 -I./include -Wall -O3 -c -o obj/imgui.o src/imgui/imgui.cpp
g++ -std=c++17 -I./include -Wall -O3 -c -o obj/imgui_demo.o src/imgui/imgui_demo.cpp
g++ -std=c++17 -I./include -Wall -O3 -c -o obj/imgui_impl_glfw.o src/imgui/imgui_impl_glfw.cpp
g++ -std=c++17 -I./include -Wall -O3 -c -o obj/implot.o src/implot/implot.cpp
g++ -std=c++17 -I./include -Wall -O3 -c -o obj/implot_demo.o src/implot/implot_demo.cpp
g++ -std=c++17 -I./include -Wall -O3 -o main obj/StreamLine.o obj/WindowManagement.o obj/VAO.o obj/IsoSurface.o obj/Volume.o obj/Camera.o obj/SammonMapping.o obj/Transformation.o obj/Shader.o obj/Model.o obj/VolumeRendering.o obj/Method.o obj/main.o obj/glad.o obj/imgui_draw.o obj/imgui_widgets.o obj/imgui_impl_opengl3.o obj/imgui.o obj/imgui_demo.o obj/imgui_impl_glfw.o obj/implot.o obj/implot_demo.o -L./lib -lglfw3 -lopengl32 -lgdi32
```
