#include "map.h"

namespace ks
{
    Map::Map(
        std::shared_ptr<ks::ResourceMgr> resource_mgr,
        std::shared_ptr<ks::DataLoader> data_loader,
        std::shared_ptr<ks::GameWindow> window,
        std::string map_name)
        : _map_name(map_name),
          _resource_mgr(resource_mgr),
          _data_loader(data_loader),
          _window(window),
          _graph(std::make_unique<ks::Graph>())
    {
        load();
    }

    Map::~Map()
    {
    }

    void Map::load()
    {
        _data_loader->load_map(_map_name);
        json j_map = _data_loader->get_json(_map_name);

        _tiles_cols = j_map["metadata"]["columns"];
        _tiles_rows = j_map["metadata"]["rows"];

        _window->set_map_size(ks::TILE * _tiles_cols, ks::TILE * _tiles_rows);

        std::vector<ks::Spritesheet*> spritesheets;

        // Names of spritesheets used in this map
        json j_sheets = j_map["spritesheets"];

        // Map data (tiles IDs)
        json j_data = j_map["data"];

        // List of layers to draw: layers are drawn from left to right
        json j_layers = j_map["draw_layers"];

        for (const std::string& spritesheet : j_sheets) {
            spritesheets.push_back(&_resource_mgr->get_spritesheet(spritesheet));
        }

        int row = 0;
        int col = 0;

        const int v_per_tile = 4;
        const int dpx = ks::TILE / v_per_tile;

        for (const std::string& layer : j_layers) {
            auto j_layer = j_data[layer];

            for (const auto& tile_info : j_layer) {
                // 0: spritesheet_id, 1: tile_id

                int x = col * ks::TILE;
                int y = row * ks::TILE;

                auto tile = std::make_unique<ks::Tile>(
                    spritesheets[tile_info[0]]->get_new_sprite(tile_info[1]),
                    x, y, tile_info[0], tile_info[1]);

				_tiles.push_back(std::move(tile));

                for (int i = 0; i < v_per_tile; i++) {
                    for (int j = 0; j < v_per_tile; j++) {
                        boost::add_vertex(
                            std::make_shared<ks::Vertex>(
                                x + i * dpx, y + j * dpx), *_graph);
                    }
                }

                col++;

                if (col == _tiles_cols) {
                    col = 0;
                    row++;
                }

                if (row == _tiles_rows)
                    break;
            }
        }
    }

    void Map::update(sf::Time delta)
    {
    }

    void Map::render(
        sf::RenderWindow& window,
        std::vector<std::shared_ptr<ks::Unit> >& units)
    {
        for (auto& tile : _tiles) {
            tile->render(window);
        }

        for (auto& unit : units) {
            unit->render(window);
        }
    }

    void
    Map::_init_map() const
    {

    }
}
