/**
 * sudo apt-get install libgtkmm-3.0-dev
 */


#include "app.h"

#include <iostream>

//#include <
using namespace std;

void HelloWin::on_button_clicked()
{
    cout << "button clicked" << endl;
}

void HelloWin::show_app()
{
    int argc = 0;
    char ** argv = NULL;
    Glib::RefPtr<Gtk::Application> app =
                Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

    Gtk::Button btn1, btn2;
    Gtk::Box box1;

    HelloWin window;
    window.set_default_size(640, 480);

    window.add(box1);

    btn1.add_pixlabel("info.xpm", "开始");
    btn1.set_border_width(10);
    btn1.signal_clicked().connect(
            sigc::mem_fun(window, &HelloWin::on_button_clicked));

    box1.pack_start(btn1);

    btn1.show();
    box1.show();

    app->run(window);
}

