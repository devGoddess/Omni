#include "GameState.h"



GameState::GameState()
{
}


GameState::~GameState()
{
}

void GameState::GameLoop(float deltaTime)
{

	currentState->Render();
	currentState->Update(deltaTime);

}
