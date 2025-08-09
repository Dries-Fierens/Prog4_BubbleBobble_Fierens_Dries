#include "SkipLevelCommand.h"
#include "GameManager.h"

void SkipLevelCommand::Execute()
{
	GameManager::GetInstance().SkipLevel();
}
