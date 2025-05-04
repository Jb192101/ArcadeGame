#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>

class MenuView : public Fl_Window {
private:
    Fl_Button* newGameBtn;
    Fl_Button* aboutBtn;
    Fl_Button* exitBtn;

public:
    MenuView(int w, int h, const char* title);
    void setCallbacks(Fl_Callback* newGameCb,
        Fl_Callback* aboutCb,
        Fl_Callback* exitCb,
        void* data);
};