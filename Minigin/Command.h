#pragma once
#include "GameActor.h"
namespace dae
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
	};

	class GameActorCommand : public Command {
		GameActor* m_actor;
	protected:
		GameActor* GetGameActor() const { return m_actor; }
	public:
		GameActorCommand(GameActor* actor) { m_actor = actor; };
		virtual ~GameActorCommand() { delete m_actor; };
	};

	class Move : public GameActorCommand
	{
	public:
		void Execute() override 
		{
			GetGameActor()->Move();
		};
	};

	class Fire : public GameActorCommand {
	public:
		void Execute() override
		{
			GetGameActor()->Fire();
		}
	};
}

