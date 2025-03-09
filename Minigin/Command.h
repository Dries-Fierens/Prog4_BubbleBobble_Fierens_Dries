#pragma once
#include "GameActor.h"
namespace dae
{
	class Command
	{
	public:
		virtual ~Command() {}
		virtual void Execute(GameActor& actor) = 0;
	};

	class FireCommand : public Command
	{
	public:
		virtual void Execute(GameActor& actor) { actor.Fire(); }
	};

	class LeftCommand : public Command
	{
	public:
		virtual void Execute(GameActor& actor) { actor.MoveLeft(); }
	};

	class RightCommand : public Command
	{
	public:
		virtual void Execute(GameActor& actor) { actor.MoveRight(); }
	};

	class UpCommand : public Command
	{
	public:
		virtual void Execute(GameActor& actor) { actor.MoveUp(); }
	};

	class DownCommand : public Command
	{
	public:
		virtual void Execute(GameActor& actor) { actor.MoveDown(); }
	};
}

