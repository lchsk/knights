#include <iostream>

#include "game.h"

namespace knights
{
    Game::Game()
    {
        _w = 800;
        _h = 600;

        _resource_mgr = std::shared_ptr<knights::res::ResourceMgr>(
            new knights::res::ResourceMgr()
        );

        _current_level = std::unique_ptr<knights::map::Level>(
            new knights::map::Level(_resource_mgr)
        );

        _window = std::unique_ptr<sf::RenderWindow>(
            new sf::RenderWindow(sf::VideoMode(_w, _h), "knights")
        );

        _view = std::unique_ptr<sf::View>(
            new sf::View(sf::FloatRect(0, 0, _w, _h))
        );

        _window->setView(*_view);

        _resource_mgr->load_texture(
            "archer",
            "assets/images/knights_archer_bow.png"
        );

        _sp.setTexture(_resource_mgr->get_texture("archer"));
    }

    Game::~Game()
    {
    }

    void Game::run()
    {
        sf::Clock clock;
        sf::Time since_last_update;
        sf::Time per_frame = sf::seconds(1.0f / 60.0f);

        while (_window->isOpen()) {
            bool repaint = false;

            sf::Time delta = clock.restart();
            since_last_update += delta;

            if (since_last_update > per_frame) {
                handle_events();

                since_last_update -= per_frame;
                repaint = true;

                update(since_last_update);
            }

            if (repaint)
                render();
        }
    }

    void Game::update(sf::Time delta)
    {
        _window->setView(*_view);
    }

    void Game::render()
    {
        _window->clear();
        _window->draw(_sp);

        _window->display();
    }

    void Game::handle_events()
    {
        sf::Event event;

        while(_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window->close();
            else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape)
                _window->close();
        }
    }
}
