# Scientific Visualization

1082 Scientific Visualization HW
* Isosurface
* Volume rendering (slicing method)
* Transfer function design
* Streamline
* Sammon Mapping

## Screenshots

* Isosurface (engine data)
![](https://i.imgur.com/mWxCOit.png)

* Volume Rendering (engine data)
![](https://i.imgur.com/9Kjgnqc.png)

* Volume Rendering (carp data)
![](https://i.imgur.com/RnxZmte.png)

## Library dependency

* GLFW 3.3.2 (https://www.glfw.org/)
* GLAD w/ gl Version 4.3 (https://glad.dav1d.de/)
* ImGui (https://github.com/ocornut/imgui)
* ImPlot (https://github.com/epezent/implot)
* C++17 

## OS dependency

|  | Windows 10 | Ubuntu 18.04 | macOS 10.14 |
| -------- | -------- | -------- | --- |
| Isosurface | O | O | O |
| Volume Rendering | O | O | X |
| Transfer Function | O | O | O |
| Streamline | O | O | O |
| Sammon Mapping | O | O | O |

* Due to the deprecation of OpenGL on macOS, the fragment shader of `slicing method` I wrote with OpenGL 4.3 seems not available on macOS with OpenGL 4.1.

## Usage

First, you will need a `Data/` folder includes `Scalar/` and `Vector/` which contains the volume data and vector feild data respectively.

### Compiler

* g++
* clang++
* mingw (64-bits is recommended)

### Linking setting

If you want to compile manually, you can consider using the linking flags below:

* windows-args `-lglfw3 -lopengl32 -lgdi32`
* linux-args `-lglfw3 -pthread -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -ldl -lXcursor`
* macos-args `-stdlib=libc++ -lglfw -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -framework Carbon`

### Makefile

Or just use GNU make to automatically compile the source codes.

```bash
make
make run
```