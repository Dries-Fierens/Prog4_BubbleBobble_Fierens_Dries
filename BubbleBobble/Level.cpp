#include "Level.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include "Tile.h"
#include "Player.h"

std::vector<std::shared_ptr<dae::GameObject>> Level::CreateLevel(int levelNumber, bool coop)
{
    std::string line;
	std::string filePath = "../Data/Levels/" + std::to_string(levelNumber) + "/Data.txt";
    std::ifstream file(filePath);
	std::vector<std::shared_ptr<dae::GameObject>> level;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            // Remove whitespace
            line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

            if (line.empty() || line[0] == '/' || line[0] == '\n')
                continue;

            size_t pos = line.find('=');
            if (pos == std::string::npos) continue;

            std::string type = line.substr(0, pos);
            std::string args = line.substr(pos + 1);

            if (type == "Tile" || type == "FakeTile" || type == "BigTile" || type == "BigTileInvis") {
                size_t commaPos = args.find(',');
                if (commaPos == std::string::npos) continue;

                float x = std::stof(args.substr(0, commaPos));
                float y = std::stof(args.substr(commaPos + 1));

                bool isBig = (type == "BigTile" || type == "BigTileInvis");
                auto tile = Tile::CreateTile(x, y, levelNumber, isBig);
				level.push_back(tile);
            }
            else if (type == "Player") {
                std::replace(args.begin(), args.end(), ',', ' ');
                std::istringstream iss(args);
                float x, y;
                bool isGreen;
                iss >> x >> y >> std::boolalpha >> isGreen;

                auto player = Player::CreatePlayer(x, y, isGreen, coop);
                level.push_back(player);
            }
            else if (type == "ZenChan") {
                //size_t commaPos = args.find(',');
                //if (commaPos == std::string::npos) continue;

                //float x = std::stof(args.substr(0, commaPos));
                //float y = std::stof(args.substr(commaPos + 1));

                //auto zenChan = ZenChan::CreateEnemy(x, y);
                //std::cout << "ZenChan: (" << x << ", " << y << ")\n";
            }
        }

        file.close();
    }

    return level;
}
