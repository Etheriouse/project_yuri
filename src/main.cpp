#include "App.hpp"

#define unused(x) (void)(x)

int main(int argc, char const *argv[])
{
    unused(argc);
    unused(argv);

    App a;
    return a.run(); 
}
