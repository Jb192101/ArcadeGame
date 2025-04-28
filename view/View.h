#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>

class View {
public:
    virtual ~View() = default;
    virtual void Draw() = 0;
    virtual void Show() = 0;
    virtual void Hide() = 0;
    virtual Fl_Widget* GetWidget() = 0;
};
