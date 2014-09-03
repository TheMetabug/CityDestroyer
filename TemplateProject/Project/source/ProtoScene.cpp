#include "../include/ProtoScene.hpp"

#include <UtH/Engine/UtHEngine.h>
#include <UtH/Engine/Sprite.hpp>
#include <UtH/Engine/AnimatedSprite.hpp>
#include <UtH/Engine/SpriteBatch.hpp>
#include <UtH/Platform/Input.hpp>
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
	m_bgCityTexture = new Texture();
	m_bgCityTexture->LoadFromFile("background.tga");

	m_player = new GameObject();
	m_bgCity1 = new GameObject();
	m_bgCity2 = new GameObject();

	m_player->AddComponent(new Sprite(m_playerTexture));
	m_bgCity1->AddComponent(new Sprite(m_bgCityTexture));
	m_bgCity2->AddComponent(new Sprite(m_bgCityTexture));

	m_player->transform.SetPosition(umath::vector2(-400, 0));
	m_bgCity1->transform.SetPosition(umath::vector2(m_bgCity1->transform.GetSize().x / 2, 0));
	m_bgCity2->transform.SetPosition(umath::vector2(m_bgCity1->transform.GetPosition().x + 
													m_bgCity1->transform.GetSize().x/2, 0));
	//m_spriteBatch->AddSprite(m_player);

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
	inputLogic(dt);
	bgMovement(dt);
	m_player->Update(dt);
	//m_spriteBatch->Update(dt);
	return true; // Update succeeded.
}

// Draw loop. All graphics are drawn during this loop.
bool ProtoScene::Draw()
{
	//Background color, set this first before else
	uthEngine.GetWindow().Clear(0, 0, 0, 1);
	//m_spriteBatch->Draw(uthEngine.GetWindow());
	m_bgCity1->Draw(uthEngine.GetWindow());
	m_bgCity2->Draw(uthEngine.GetWindow());
	m_player->Draw(uthEngine.GetWindow());


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

void ProtoScene::inputLogic(float dt)
{
	if (uthInput.Keyboard.IsKeyDown(uth::Keyboard::Left))
	{
		m_player->transform.Move(-100 * dt, 0);
	}
	else if (uthInput.Keyboard.IsKeyDown(uth::Keyboard::Right))
	{
		m_player->transform.Move(100 * dt, 0);
	}
}

void ProtoScene::bgMovement(float dt)
{
	m_bgCity1->transform.Move(-300 * dt, 0);
	m_bgCity2->transform.Move(-300 * dt, 0);

	if (m_bgCity1->transform.GetPosition().x <= -(m_bgCity1->transform.GetSize().x))
	{
		m_bgCity1->transform.SetPosition(umath::vector2(m_bgCity2->transform.GetPosition().x + (m_bgCity2->transform.GetSize().x), 0));
	}
	if (m_bgCity2->transform.GetPosition().x <= -(m_bgCity2->transform.GetSize().x))
	{
		m_bgCity2->transform.SetPosition(umath::vector2(m_bgCity1->transform.GetPosition().x + (m_bgCity1->transform.GetSize().x), 0));
	}

}