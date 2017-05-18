#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "GameState.h"
#include "Camera.h"
#include "Mesh.h"
#include "Skybox.h"
#include "Terrain.h"
#include "Character.h"

class GameWorld : public GameState
{
public:
	GameWorld();
	~GameWorld();

	bool Init();
	void Enter();
	void Render();
	void Update();
	void Exit(GameState *nextState);

	D3DLIGHT9 worldLight;

	D3DMATERIAL9 testMtrl;
	ID3DXMesh *lightTest = 0;

	Mesh testMesh;

	Camera cam;

	Skybox skybox;
	Terrain *terrain = 0;

	Character knight;


};

#endif