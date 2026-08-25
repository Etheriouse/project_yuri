#include "Global.hpp"
#include "App.hpp"

App *g_app;

void setApp(App *ptr) {
    g_app = ptr;
}