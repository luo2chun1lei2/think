#include <gtkmm.h>

int main(int argc, char * argv[])
{
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "example.view");
    Gtk::Window win;
    win.set_default_size(200, 200);

    return app->run(win);
}
