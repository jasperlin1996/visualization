#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "IsoSurface.h"
#include "WindowManagement.h"

using namespace std;

int main(){
    IsoSurface iso("./Data/Scalar/engine.inf", "./Data/Scalar/engine.raw", 80);
    // IsoSurface iso("./TestData/TestData.inf", "./TestData/TestData.raw", 3);
    iso.run();

    glm::vec3 data_shape = iso.get_shape();
    data_shape = -data_shape/2.0f;
    data_shape *= iso.get_voxel_size();

    WindowManagement *wm = new WindowManagement();
    if(wm->init(800.0, 600.0, "Iso Surface OuO")){
        cout << "Create window Success.\n";
    }
    Model::normalize(data_shape);

    wm->set_vao_data(iso.get_data()); // transfer vector to array and send to wm
    wm->mainLoop();
}
