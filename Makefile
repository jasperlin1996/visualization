args=-lglfw3 -lopengl32 -lgdi32

default:
	cmd.exe /c g++ main.cpp IsoSurface.cpp Volume.cpp WindowManagement.cpp Model.cpp Camera.cpp VAO.cpp Shader.cpp glad/glad.c -o main.exe $(args)
	./main.exe

histogram:
	cmd.exe /c g++ -DHISTOGRAM main.cpp IsoSurface.cpp Volume.cpp WindowManagement.cpp Model.cpp Camera.cpp VAO.cpp Shader.cpp glad/glad.c -o main.exe $(args)
	./main.exe
	cmd.exe /c python historgram.py
iso:
	cmd.exe /c g++ testIsoSurface.cpp IsoSurface.cpp Volume.cpp -Wall -o iso.exe
	./iso.exe

testVolume:
	cmd.exe /c g++ testVolume.cpp Volume.cpp -Wall -o testVolume.exe
	./testVolume.exe

test2vao:
	cmd.exe /c g++ test2vao.cpp glad/glad.c -o test2vao.exe $(args)
	./test2vao.exe
