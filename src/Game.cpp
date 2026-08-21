#include "Game.hpp"
#include "Game/Player.hpp"
#include "Map/Map.hpp"
#include "Serializer/Serializer.hpp"

Game::Game() : uid_counter(0), ng(1)
{
    // create player
    // find worldmapyun

    this->p = Player("player", 10, 10);
    this->world_map = WorldMap();
}

void Game::run()
{

    process = std::thread(&Game::process_f, this);
    render = std::thread(&Game::render_f, this);

    process.join();
    render.join();
}

void Game::process_f()
{

    auto tse = std::chrono::steady_clock::now().time_since_epoch();
    uint64_t tmp = 0, last = std::chrono::duration_cast<std::chrono::nanoseconds>(tse).count();

    unsigned int tick_s = 0;
    long double acc_s = 0;

    while (running)
    {
        auto tse = std::chrono::steady_clock::now().time_since_epoch();
        tmp = std::chrono::duration_cast<std::chrono::nanoseconds>(tse).count();
        delta = ((long double)(tmp - last)) / 1'000'000'000.0L;
        last = tmp;
        acc_s += delta;

        if (actual_encouter_map != nullptr && actual_encouter_map->is_active)
        {
            actual_encouter_map->process(delta, process_tick);
        } else {
            world_map.render(delta, process_tick);
        }

        if (acc_s > 1)
        {
            std::cout << "process tick: " << tick_s << std::endl;
            tick_s = 0;
            acc_s = 0;
        }

        tick_s++;
        process_tick++;
    }
}

void Game::render_f()
{
    auto tse = std::chrono::steady_clock::now().time_since_epoch();
    uint64_t tmp = 0, last = std::chrono::duration_cast<std::chrono::nanoseconds>(tse).count();

    unsigned int tick_s = 0;
    long double acc_s = 0;

    while (running)
    {
        auto tse = std::chrono::steady_clock::now().time_since_epoch();
        tmp = std::chrono::duration_cast<std::chrono::nanoseconds>(tse).count();
        delta = ((long double)(tmp - last)) / 1'000'000'000.0L;
        last = tmp;

        acc_s += delta;

        if (actual_encouter_map != nullptr && actual_encouter_map->is_active)
        {
            actual_encouter_map->render(delta, render_tick);
        } else {
            world_map.render(delta, render_tick);
        }

        if (acc_s > 1)
        {
            std::cout << "fps: " << tick_s << std::endl;
            tick_s = 0;
            acc_s = 0;
        }

        tick_s++;
        render_tick++;
    }
}

void Game::load(Serializer &s)
{
    s.load(this->ng);
    s.load(this->uid_counter);
    p.load(s);
    world_map.load_file(s);
}

void Game::save(Serializer &s) const
{
    s.save(this->ng);
    s.save(this->uid_counter);
    p.save(s);
    world_map.save_file(s);
}

void Game::debug_print()
{
    std::cout << "ng: " << ng << std::endl
              << "uid counter: " << uid_counter << std::endl;
    p.debug_print();
    world_map.debug_print();
}