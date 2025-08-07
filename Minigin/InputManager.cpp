#include "InputManager.h"
#include <iostream>
#include <sstream>
#include <SDL.h>
#include "Minigin.h"

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			return false;
		}

		// Handle window events
		size_t prevSize = dae::InputManager::m_pKeyboardMap.size();
		for (auto& map : m_pKeyboardMap)
		{
			if (static_cast<unsigned int>(e.key.keysym.sym) == map.first.key)
			{
				if (map.first.type == InputType::OnDown && e.type == SDL_KEYDOWN)
				{
					if (std::ranges::find(m_PressedKeys, map.first.key) != m_PressedKeys.end())
						continue;

					map.second->Execute();
				}
				else if (map.first.type == InputType::OnRelease && e.type == SDL_KEYUP)
				{
					map.second->Execute();
				}

				if (m_pKeyboardMap.size() != prevSize)
				{
					break;
				}
			}
		}
	}

	// Process keyboard inputs
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	for (auto& map : m_pKeyboardMap)
	{
		if (state[SDL_GetScancodeFromKey(static_cast<int>(map.first.key))])
		{
			m_PressedKeys.push_back(map.first.key);

			if (map.first.type == InputType::OnPressed)
			{
				map.second->Execute();
			}
		}
	}


	// Process controller inputs
	for (auto& controller : m_pControllers)
	{
		controller->Update();

		for (auto& map : m_pControllerMap)
		{
			if (map.first.controllerID == controller->GetIndex())
			{
				if ((map.first.type == InputType::OnDown && controller->IsDown(map.first.button)) ||
					(map.first.type == InputType::OnPressed && controller->IsPressed(map.first.button)) ||
					(map.first.type == InputType::OnRelease && controller->IsUp(map.first.button)))
				{
					map.second->Execute();
				}
			}
		}
	}

	return true;
}

void dae::InputManager::AddControllerCommand(std::unique_ptr<Command> pCommand, Controller::ButtonState button, unsigned int controllerId, InputType type)
{
	bool doesControllerExist = false;
	for (const auto& controller : m_pControllers)
	{
		if (controller->GetIndex() == controllerId)
		{
			doesControllerExist = true;
			break;
		}
	}

	if (doesControllerExist == false)
	{
		m_pControllers.push_back(std::make_unique<Controller>(controllerId));
	}

	ControllerInput input{ controllerId, button, type };
	m_pControllerMap.insert(std::pair(input, std::move(pCommand)));
}

void dae::InputManager::AddKeyboardCommand(std::unique_ptr<Command> pCommand, unsigned int keyboardKey, InputType type)
{
	KeyboardInput input{ keyboardKey, type };
	m_pKeyboardMap.insert(std::pair(input, std::move(pCommand)));
}

void dae::InputManager::RemoveInputs()
{
	m_pControllerMap.clear();
	m_pKeyboardMap.clear();
}
