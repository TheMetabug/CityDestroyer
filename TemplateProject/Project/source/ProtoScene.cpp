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

	m_playerGroundLevel = -10;
	m_isPlayerJumping = false;
	m_isPlayerCrouching = false;
	m_playerJumpSpeed = 0;

	// Some shader must be loaded and set window to use it
	m_shader.LoadShader("Shaders/Default.vert", "Shaders/Default.frag");
	m_shader.Use();
	uthEngine.GetWindow().SetShader(&m_shader);

	auto& playerTexture = uthRS.LoadTexture("roar.tga");
	auto& bgCityTexture = uthRS.LoadTexture("background.tga");
	auto& bgFrontCityTexture = uthRS.LoadTexture("frontCity.tga");

	m_player.AddComponent(new Sprite(&playerTexture));
	m_bgCity1.AddComponent(new Sprite(&bgCityTexture));
	m_bgCity2.AddComponent(new Sprite(&bgCityTexture));
	m_frontCity.AddComponent(new Sprite(&bgFrontCityTexture));
	m_frontCity2.AddComponent(new Sprite(&bgFrontCityTexture));

	m_player.transform.SetPosition(umath::vector2(-400, m_playerGroundLevel));
	m_bgCity1.transform.SetPosition(umath::vector2(m_bgCity1.transform.GetSize().x / 2, 0));
	m_bgCity2.transform.SetPosition(umath::vector2(m_bgCity1.transform.GetPosition().x + 
												   m_bgCity1.transform.GetSize().x, 0));


	m_frontCity.transform.SetPosition(umath::vector2(  m_frontCity.transform.GetSize().x / 2, 150));
	m_frontCity2.transform.SetPosition(umath::vector2( m_frontCity.transform.GetPosition().x +
														m_frontCity.transform.GetSize().x, 150));


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

	//BG update things
	bgMovement(dt);

	//Player update things
	m_player.Update(dt);
	if (m_isPlayerJumping && !m_isPlayerCrouching)playerJump(dt);
	if (!m_isPlayerJumping && m_isPlayerCrouching)playerCrouch(dt);
	
	//m_spriteBatch->Update(dt);
	return true; // Update succeeded.
}

// Draw loop. All graphics are drawn during this loop.
bool ProtoScene::Draw()
{
	//Background color, set this first before else
	uthEngine.GetWindow().Clear(0, 0, 0, 1);
	//m_spriteBatch->Draw(uthEngine.GetWindow());
	m_bgCity1	.Draw(uthEngine.GetWindow());
	m_bgCity2	.Draw(uthEngine.GetWindow());
	m_player	.Draw(uthEngine.GetWindow());
	m_frontCity	.Draw(uthEngine.GetWindow());
	m_frontCity2.Draw(uthEngine.GetWindow());

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
		m_player.transform.Move(-100 * dt, 0);
	}
	if (uthInput.Keyboard.IsKeyDown(uth::Keyboard::Right))
	{
		m_player.transform.Move(100 * dt, 0);
	}
	if (uthInput.Keyboard.IsKeyDown(uth::Keyboard::Up) && !m_isPlayerJumping)
	{
		m_isPlayerJumping = true;
		m_playerJumpSpeed = -1000;
	}

}

void ProtoScene::bgMovement(float dt)
{
	m_bgCity1   .transform.Move(-300 * dt, 0);
	m_bgCity2   .transform.Move(-300 * dt, 0);
	m_frontCity .transform.Move(-400 * dt, 0);
	m_frontCity2.transform.Move(-400 * dt, 0);

	if (m_bgCity1.transform.GetPosition().x <= -(m_bgCity1.transform.GetSize().x))
	{
		m_bgCity1.transform.SetPosition(umath::vector2(m_bgCity2.transform.GetPosition().x + (m_bgCity2.transform.GetSize().x), 0));
	}
	if (m_bgCity2.transform.GetPosition().x <= -(m_bgCity2.transform.GetSize().x))
	{
		m_bgCity2.transform.SetPosition(umath::vector2(m_bgCity1.transform.GetPosition().x + (m_bgCity1.transform.GetSize().x), 0));
	}


	///////


	if (m_frontCity.transform.GetPosition().x <= -(m_frontCity.transform.GetSize().x))
	{
		m_frontCity.transform.SetPosition(umath::vector2(m_frontCity2.transform.GetPosition().x + (m_frontCity2.transform.GetSize().x), 150));
	}
	if (m_frontCity2.transform.GetPosition().x <= -(m_frontCity2.transform.GetSize().x))
	{
		m_frontCity2.transform.SetPosition(umath::vector2(m_frontCity.transform.GetPosition().x + (m_frontCity.transform.GetSize().x), 150));
	}


}

void ProtoScene::playerJump(float dt)
{
	m_playerJumpSpeed += 2000*dt;
	auto speed = umath::vector2(0, m_playerJumpSpeed*dt);
	m_player.transform.Move(speed);
	if (m_player.transform.GetPosition().y >= m_playerGroundLevel){ m_isPlayerJumping = false; };
}
void ProtoScene::playerCrouch(float dt)
{

}