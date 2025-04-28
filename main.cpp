#include "bin/GameController.h"
#include <FL/Fl.H>
#include <ctime>

int main(int argc, char** argv) {
    std::srand(std::time(nullptr)); // ������������� ���������� ��������� �����
    Fl::scheme("gtk+"); // ��������� ����� ����������

    const int width = 800;
    const int height = 600;

    GameController game(width, height);
    game.Run();

    return Fl::run();
}