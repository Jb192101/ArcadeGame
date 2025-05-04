#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>

class MenuView : public Fl_Window {
private:
    Fl_Button* m_newGameBtn;
    Fl_Button* m_aboutBtn;
    Fl_Button* m_exitBtn;

public:
    MenuView(int w, int h, const char* title);
    void setCallbacks(Fl_Callback* newGameCb,
        Fl_Callback* aboutCb,
        Fl_Callback* exitCb,
        void* data);
};