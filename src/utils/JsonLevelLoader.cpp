#include "utils/JsonLevelLoader.h"

MapData JsonLevelLoader::load(std::string fileName) {
  /*MapData data;
  data.name = "Village";
  data.width = 16;
  data.height = 16;
  data.tileSize = 48;

  data.tiles.resize(data.height,
                    std::vector<TileType>(data.width, TileType::Floor));

  for (int x = 0; x < data.width; ++x) {
    data.tiles[0][x] = TileType::Wall;
    data.tiles[data.height - 1][x] = TileType::Wall;
  }
  for (int y = 0; y < data.height; ++y) {
    data.tiles[y][0] = TileType::Wall;
    data.tiles[y][data.width - 1] = TileType::Wall;
  }

  return data;*/
  MapData data;
  data.name = "Village";
  data.width = 16;
  data.height = 16;
  data.tileSize = 48;

  data.tiles.resize(data.height,
                    std::vector<TileType>(data.width, TileType::Floor));

  int centerX = data.width / 2;
  int centerY = data.height / 2;

  std::vector<std::string> heart = {
      "  ###  ###  ",  " ##### ##### ", "#############",
      " ########### ", "  #########  ", "   #######   ",
      "    #####    ", "     ###     ", "      #      "};

  for (int y = 0; y < heart.size(); ++y) {
    for (int x = 0; x < heart[y].size(); ++x) {
      if (heart[y][x] == '#') {
        int worldX = centerX - 6 + x;
        int worldY = centerY - 5 + y;

        if (worldX >= 1 && worldX < data.width - 1 && worldY >= 1 &&
            worldY < data.height - 1) {
          data.tiles[worldY][worldX] = TileType::Wall;
        }
      }
    }
  }

  return data;
}
