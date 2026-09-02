#include "App.hpp"

#define unused(x) (void)(x)

int main(int argc, char const *argv[])
{
    unused(argc);
    unused(argv);

    // Serializer::Writer w("app.settings");
    // uint32_t wd = 1600, h = 900;
    // std::string s = "Random Rogue Lite Yuri";

    // w.write(wd);
    // w.write(h);
    // w.write(s);
    // return 0;
    return App::create().run(); 
}
