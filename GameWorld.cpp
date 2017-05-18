#include "GameWorld.h"



GameWorld::GameWorld()
{
}


GameWorld::~GameWorld()
{
	D3D::Delete<Terrain*>(terrain);
}

bool GameWorld::Init()
{
	//	directional light
	worldLight = D3D::InitDirectionalLight(&D3DXVECTOR3(0.0f, -1.0f, 0.0f), (D3DXCOLOR*)&D3D::WHITE);
	Device->SetLight(0, &worldLight);
	Device->LightEnable(0, TRUE);

	//	spot light
	D3DLIGHT9 spotLight = D3D::InitSpotLight(&D3DXVECTOR3(0.0f, 100.0f, 10.0f), &D3DXVECTOR3(0.0f, -1.0f, 0.0f), (D3DXCOLOR*)&D3D::WHITE);
	Device->SetLight(1, &spotLight);
	Device->LightEnable(1, TRUE);

	//	point light
	D3DLIGHT9 pointLight = D3D::InitPointLight(&D3DXVECTOR3(0.0f, 2.0f, 10.0f), (D3DXCOLOR*)&D3D::WHITE);
	Device->SetLight(2, &pointLight);
	Device->LightEnable(2, TRUE);

	Device->SetRenderState(D3DRS_LIGHTING, true);

	testMesh.Initialize("models/acr.x");

	Device->SetRenderState(D3DRS_SPECULARENABLE, true);

	skybox.generate();

	terrain = new Terrain("textures/heightMap.raw", 1981, 1981, 10, .005f);
	terrain->genTexture(&D3DXVECTOR3(0.0, -1.0f, 0.0f));
	terrain->loadTexture("textures/terrain.png");

	return true;
}

void GameWorld::Enter()
{
	if (!isInit)
		isInit = Init();

	//	set projection matrix
	D3DXMATRIX P;
	D3DXMatrixPerspectiveFovLH(&P, D3DX_PI / 4, screenWidth / screenHeight, 1.0f, 3000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &P);
}

void GameWorld::Render()
{

	//	set view matrix
	D3DXMATRIX V;
	cam.getViewMatrix(&V);
	Device->SetTransform(D3DTS_VIEW, &V);

	cam._pos.y = terrain->getHeight(cam._pos.x, cam._pos.z) + 25;


	if (Device) {

		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, COLOR_WINDOW, 1.0f, 0);
		Device->BeginScene();

		//	render skybox
		D3DXMATRIX W;
		D3DXMatrixTranslation(&W, cam._pos.x, cam._pos.y, cam._pos.z);
		Device->SetTransform(D3DTS_WORLD, &W);
		skybox.render();

		//	render terrain
		D3DXMATRIX I;
		D3DXMatrixIdentity(&I);
		terrain->draw(&I, false);


		//	render acr
		D3DXMatrixTranslation(&W, 0.0f, 0.0f, 10.0f);
		D3DXMATRIX R;
		D3DXMatrixRotationY(&R, D3DX_PI/2);
		Device->SetTransform(D3DTS_WORLD, &(R*W));
		testMesh.Render();


		Device->EndScene();
		Device->Present(0, 0, 0, 0);
	}
}

void GameWorld::Update(float deltaTime)
{
	if (GetKeyState(VK_UP) & 0x800)
		cam.pitch(-deltaTime * .001);
	if (GetKeyState(VK_DOWN) & 0x800)
		cam.pitch(deltaTime * .001);
	if (GetKeyState(VK_LEFT) & 0x800)
		cam.yaw(-deltaTime * .001);
	if (GetKeyState(VK_RIGHT) & 0x800)
		cam.yaw(deltaTime * .001);
}

void GameWorld::Exit(GameState * nextState)
{
}
