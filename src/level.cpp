#include "level.h"

namespace knights
{
    Level::Level(std::shared_ptr<knights::ResourceMgr> resource_mgr)
        : _resource_mgr(resource_mgr)
    {
        load_level_assets();
        init_nations();

        _map = std::make_unique<knights::Map>(
            resource_mgr,
            "test"
            );
    }

    Level::~Level()
    {

    }

    void
    Level::update(sf::Time delta)
    {
        _map->update(delta);
    }

    void
    Level::render(sf::RenderWindow& window)
    {
        _map->render(window);
    }

    void Level::init_nations()
    {
    }

    void Level::load_level_assets() const
    {
        _resource_mgr->load_texture(
            "tiles",
            "assets/images/knights_tiles.png"
            );
    }
}