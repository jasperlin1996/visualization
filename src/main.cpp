#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

#include "WindowManagement.h"

using namespace std;

int main(){
    WindowManagement *wm = new WindowManagement();
    if(wm->init(1200.0, 900.0, "Scientific Visualization")){
        cout << "Create window Success.\n";
    }

    wm->mainLoop();
}
