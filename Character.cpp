#include "Character.h"



Character::Character()
{
}


Character::~Character()
{
}

bool Character::Initialize(int characterType)
{
	type = characterType;

	//	initialize the model based on the
	//	type of character we want to create
	switch (type) {
	case KNIGHT:
		scale = 5.0f;
		characterMesh.Initialize("models/knight.x");
		thirdPersonCamera.pitch(D3DX_PI / 4);
		break;
	case DRAGON:
		scale = 10.0f;
		characterMesh.Initialize("models/dragon.x");
		break;
	case PRINCESS:
		scale = 5.0f;
		characterMesh.Initialize("models/princess.x");
		break;
	default:
		MessageBox(0, "Character Type Invalid\nSee enum CharacterType in Character.h", "Character Initialization Error", 0);
		return false;
	}


	//	set the scaling matrix
	D3DXMatrixScaling(&S, scale, scale, scale);

	return true;
}

void Character::Render()
{
	//	the position and rotation translation matrix is the inverse of the characters's view matrix
	getViewMatrix(&T);
	D3DXMatrixInverse(&T, NULL, &T);
	P = S*T;
	Device->SetTransform(D3DTS_WORLD, &P);

	characterMesh.Render();

	//	update the bounding box coordinates to match the mesh
	D3DXVec3TransformCoord(&box._min, &characterMesh.min, &P);
	D3DXVec3TransformCoord(&box._max, &characterMesh.max, &P);
}

void Character::Update()
{
	thirdPersonCamera.setPosition(&D3DXVECTOR3(0.0f, _pos.y + 100.0f, _pos.z - 100.0f));

	if (GetAsyncKeyState('W') & 0x8000f)
		walk(timer.DeltaTime()*100.0f);
	if (GetAsyncKeyState('S') & 0x8000f)
		walk(timer.DeltaTime()*100.0f);
	if (GetAsyncKeyState('A') & 0x8000f)
		strafe(timer.DeltaTime()*100.0f);
	if (GetAsyncKeyState('D') & 0x8000f)
		strafe(timer.DeltaTime()*100.0f);
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000f)
		yaw(-timer.DeltaTime()* 10.0f);
	if (GetAsyncKeyState(VK_LEFT) & 0x8000f)
		yaw(timer.DeltaTime() * 10.0f);
}
