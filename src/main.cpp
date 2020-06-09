#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
// #include "IsoSurface.h"
#include "temp_WindowManagement.h"

using namespace std;

int main(){
    WindowManagement *wm = new WindowManagement();
    if(wm->init(800.0, 600.0, "Iso Surface OuO")){
        cout << "Create window Success.\n";
    }

    wm->mainLoop();
}
