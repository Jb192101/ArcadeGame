#include "bin/GameController.h"

#include "bin/MenuController.h"

int main() {
    MenuController menuController;
    menuController.run();
    return Fl::run();
}