#include "../include/ProtoScene.hpp"

#include <UtH/Engine/UtHEngine.h>
#include <UtH/Engine/Sprite.hpp>
#include <UtH/Engine/AnimatedSprite.hpp>
#include <UtH/Platform/Debug.hpp> //WriteLog(...), works like printf.

using namespace uth;

// Main initialisation.
// Automatically called inside SceneManager.
bool ProtoScene::Init()
{
	// Some shader must be loaded and set window to use it
	m_shader.LoadShader("Shaders/Default.vert", "Shaders/Default.frag");
	m_shader.Use();
	uthEngine.GetWindow().SetShader(&m_shader);

	m_playerTexture = new Texture();
	m_playerTexture->LoadFromFile("roar.tga");

	m_player = new GameObject();
	m_player->AddComponent(new AnimatedSprite(m_playerTexture,2,umath::vector2(256,512),15));

	return true;
}

// Main deinitialisation.
// Automatically called inside SceneManager.
bool ProtoScene::DeInit()
{
	return true;
}

// Update loop. Gone trought once per frame.
bool ProtoScene::Update(float dt)
{
	return true; // Update succeeded.
}

// Draw loop. All graphics are drawn during this loop.
bool ProtoScene::Draw()
{
	//Background color, set this first before else
	uthEngine.GetWindow().Clear(0.3f, 0.4f, 0, 1);
	//m_player->Draw(uthEngine.GetWindow());


	return true; // Drawing succeeded.
}

//Default constructor for initialising constant variables.
ProtoScene::ProtoScene()
{

}
//Default deconstrutor.
ProtoScene::~ProtoScene()
{

}