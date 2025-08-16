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
#include "InputManager.h"
#include "SkipLevelCommand.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "ZenChan.h"
#include "Maita.h"

std::vector<std::shared_ptr<dae::GameObject>> Level::Create(int levelNumber)
{
    std::string line;
	std::string filePath = "../Data/Levels/" + std::to_string(levelNumber) + "/Data.txt";
    std::ifstream file(filePath);
	std::vector<std::shared_ptr<dae::GameObject>> level;
    int playerCount = 0;

    auto fontPang = dae::ResourceManager::GetInstance().LoadFont("../Data/Fonts/Pang.ttf", 20);
    glm::vec2 windowSize = dae::Renderer::GetInstance().GetWindowSize();

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
                auto tile = Tile::Create(x, y, levelNumber, isBig);
				level.push_back(tile);
            }
            else if (type == "Player") {

                if (GameManager::GetInstance().GetGameState() == GameManager::GameState::Singleplayer && playerCount >= 1)
                    continue;

                std::replace(args.begin(), args.end(), ',', ' ');
                std::istringstream iss(args);
                float x, y;
                bool isGreen;
                iss >> x >> y >> std::boolalpha >> isGreen;

                auto player = Player::Create(x, y, isGreen);
                level.push_back(player);

                auto lives = std::make_shared<dae::GameObject>();
                auto livesText = std::make_shared<dae::TextComponent>("LIVES: ", fontPang, lives.get());
                livesText->Update();

                lives->AddComponent(livesText);

                float offsetY = 40.0f;
                if (playerCount == 0) 
                {
                    lives->SetLocalPosition(10.0f, windowSize.y - offsetY);
                }
                else 
                {
                    float livesWidth = livesText->GetSize().x;
                    lives->SetLocalPosition(windowSize.x - livesWidth - 10.0f, windowSize.y - offsetY);
                }

                level.push_back(lives);
                ++playerCount;
            }
            else if (type == "ZenChan") {
                size_t commaPos = args.find(',');
                if (commaPos == std::string::npos) continue;

                float x = std::stof(args.substr(0, commaPos));
                float y = std::stof(args.substr(commaPos + 1));

                auto zenChan = ZenChan::Create(x, y);
				level.push_back(zenChan);
            }
            else if (type == "Maita") {
                size_t commaPos = args.find(',');
                if (commaPos == std::string::npos) continue;

                float x = std::stof(args.substr(0, commaPos));
                float y = std::stof(args.substr(commaPos + 1));

                auto maita = Maita::Create(x, y);
				level.push_back(maita);
            }
        }

        file.close();
    }

    dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<SkipLevelCommand>(), SDLK_F1, dae::InputManager::InputType::OnDown);

    return level;
}
