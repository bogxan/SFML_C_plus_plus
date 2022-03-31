#include "Scene_Controller.h"
static Scene_Controller* controller;
Scene_Controller* Scene_Controller::getInstance()
{
    if (controller == nullptr) controller = new Scene_Controller();
    return controller;
}