#ifndef LEVEL_H
#define LEVEL_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "map.h"
#include "../core/resource_mgr.h"

namespace knights
{
    namespace map
    {
        class Level : sf::NonCopyable
        {
            public:
                Level(std::shared_ptr<knights::res::ResourceMgr>& resource_mgr);
                ~Level();

            private:
                std::shared_ptr<knights::map::Map> _map;
                std::shared_ptr<knights::res::ResourceMgr> _resource_mgr;


        };
    }
}

#endif
