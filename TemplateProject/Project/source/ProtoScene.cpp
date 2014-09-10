#include "../include/ProtoScene.hpp"

#include <UtH/Engine/UtHEngine.h>
#include <UtH/Engine/Sprite.hpp>
#include <UtH/Engine/AnimatedSprite.hpp>
#include <UtH/Engine/SpriteBatch.hpp>
#include <UtH/Platform/Input.hpp>
#include <UtH/Platform/Debug.hpp> //WriteLog(...), works like printf.
#include <UtH/Core/Randomizer.hpp>
using namespace uth;

// Main initialisation.
// Automatically called inside SceneManager.
bool ProtoScene::Init()
{

	m_playerGroundLevel	= 250;
	m_isPlayerJumping	= false;
	m_isPlayerCrouching = false;
	m_playerJumpSpeed	= 0;

	m_frontCitySpawn = pmath::Vec2(0, 250);
	m_backCitySpawn  = pmath::Vec2(0, 60);
	m_mountainSpawn  = pmath::Vec2(0, -100);


	m_isCameraShaking = false;

	// Some shader must be loaded and set window to use it

	m_soundDevice = new uth::SoundDevice();

	m_music = new uth::Audio();
	m_music->Load("city_theme.wav");
	m_music->Play();
	m_music->Loop(false);

	heliTime = 0;
	aeroplaneTime = 0;
	m_shader.LoadShader("Shaders/Default.vert", "Shaders/Default.frag");
	m_shader.Use();
	uthEngine.GetWindow().SetShader(&m_shader);

	auto playerTexture		= uthRS.LoadTexture("modzilla.tga");
	auto bgCityTexture		= uthRS.LoadTexture("buildings.png");
	auto autoTexture		= uthRS.LoadTexture("car.tga");
	auto bgFrontCityTexture= uthRS.LoadTexture("lamps.png");
	auto bgMountainTexture = uthRS.LoadTexture("mountain.png");
	auto heliTexture		= uthRS.LoadTexture("heli.tga");
	auto skyTexture = uthRS.LoadTexture("sky.tga");
	auto groundTexture = uthRS.LoadTexture("asphalt.tga");
	auto aeroplaneTexture = uthRS.LoadTexture("aeroplane.tga");
	auto groundBlockTexture = uthRS.LoadTexture("roadblock.tga");
	auto test = uthRS.LoadTexture("donut.png");

	m_spriteBatch.SetTexture(groundBlockTexture);
	unsigned int counter = 0;
	for (auto& i: roadBlocks)
	{
		m_spriteBatch.AddSprite(&i);
		i.SetPosition(pmath::Vec2(-uthEngine.GetWindowResolution().x / 2 + counter * 32 + 16, 250));
		++counter;
	}


	playerTexture->SetSmooth(true);
	m_player.AddComponent(new Sprite(playerTexture));
	m_player.transform.SetOrigin(pmath::Vec2(0, 0.5f));
	m_player.transform.SetScale(pmath::Vec2(0.75f, 0.75f));
	m_bgCity1.AddComponent(new Sprite(bgCityTexture));
	m_bgCity2.AddComponent(new Sprite(bgCityTexture));
	m_frontCity.AddComponent(new Sprite(bgFrontCityTexture));
	m_frontCity2.AddComponent(new Sprite(bgFrontCityTexture));
	m_mountain.AddComponent(new Sprite(bgMountainTexture));
	m_mountain2.AddComponent(new Sprite(bgMountainTexture));
	m_heli.AddComponent(new Sprite(heliTexture));
	m_auto.AddComponent(new Sprite(autoTexture));
	m_human.AddComponent(new Sprite(test));
	m_aeroplane.AddComponent(new Sprite(aeroplaneTexture));
	m_skyBg.AddComponent(new Sprite(skyTexture));
	m_groundTemp.AddComponent(new Sprite(groundTexture));
	

	

	m_heli.transform.SetPosition(pmath::Vec2(600, -500));
	m_auto.transform.SetPosition(pmath::Vec2(1800, 0));
	m_aeroplane.transform.SetPosition(pmath::Vec2(30, -10));

	m_player.transform.SetPosition(pmath::Vec2(-400, m_playerGroundLevel));

	m_bgCity1.transform.SetPosition(pmath::Vec2(0, m_backCitySpawn.y));
	m_bgCity2.transform.SetPosition(pmath::Vec2(m_bgCity1.transform.GetPosition().x + 
												   m_bgCity1.transform.GetSize().x, m_backCitySpawn.y));


	m_frontCity.transform.SetPosition(pmath::Vec2(0, m_frontCitySpawn.y));
	m_frontCity2.transform.SetPosition(pmath::Vec2(m_frontCity.transform.GetPosition().x +
													  m_frontCity.transform.GetSize().x, m_frontCitySpawn.y));

	m_mountain.transform.SetPosition(pmath::Vec2(0, m_mountainSpawn.y));
	m_mountain2.transform.SetPosition(pmath::Vec2(m_mountain.transform.GetPosition().x +
													 m_mountain.transform.GetSize().x, m_mountainSpawn.y));

	//m_spriteBatch->AddSprite(m_player);

	gameCamera = new uth::Camera(pmath::Vec2(0, 0), uthEngine.GetWindowResolution());
	uthEngine.GetWindow().SetCamera(gameCamera);

	m_skyBg.transform.SetPosition(pmath::Vec2(0, 125));
	m_groundTemp.transform.SetPosition(pmath::Vec2(0, 300));

	return true;
}

// Main deinitialisation.
// Automatically called inside SceneManager.
bool ProtoScene::DeInit()
{
	delete m_soundDevice;
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
	gameCamera->Update(dt);
	if (m_isPlayerJumping && !m_isPlayerCrouching)  playerJump(dt);
	if (!m_isPlayerJumping && m_isPlayerCrouching)  playerCrouch(dt);
	if (m_isCameraShaking)  shakeCamera(dt);
	autoMove(dt);
	aeroplaneMove(dt);

	
	m_spriteBatch.Update(dt);
	//m_spriteBatch->Update(dt);
	return true; // Update succeeded.
}

// Draw loop. All graphics are drawn during this loop.
bool ProtoScene::Draw()
{
	//Background color, set this first before else
	uthEngine.GetWindow().Clear(0, 0, 0, 1);
	m_skyBg		.Draw(uthEngine.GetWindow());
	m_mountain  .Draw(uthEngine.GetWindow());
	m_mountain2 .Draw(uthEngine.GetWindow());
	m_groundTemp.Draw(uthEngine.GetWindow());
	m_bgCity1	.Draw(uthEngine.GetWindow());
	m_bgCity2	.Draw(uthEngine.GetWindow());
	m_spriteBatch.Draw(uthEngine.GetWindow());
	m_player	.Draw(uthEngine.GetWindow());
	m_frontCity	.Draw(uthEngine.GetWindow());
	m_frontCity2.Draw(uthEngine.GetWindow());
	m_heli.Draw (uthEngine.GetWindow());
	m_auto.Draw (uthEngine.GetWindow());
	m_aeroplane.Draw(uthEngine.GetWindow());

	return true; // Drawing succeeded.
}

//Default constructor for initialising constant variables.
ProtoScene::ProtoScene() :m_spriteBatch(false)
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
	if (uthInput.Keyboard.IsKeyDown(uth::Keyboard::Up) && !m_isPlayerJumping  && !m_isPlayerCrouching)
	{
		m_isPlayerJumping = true;
		m_playerJumpSpeed = -1000;
	}
	if (uthInput.Keyboard.IsKeyDown(uth::Keyboard::Down) && !m_isPlayerJumping && !m_isPlayerCrouching)
	{
		m_isPlayerCrouching = true;
		m_playerCrouchTimer = 2;
	}

}


void ProtoScene::aeroplaneMove(float dt)
{
	aeroplaneTime += 4*dt;
	m_aeroplane.transform.SetPosition(1500-200*aeroplaneTime,20*aeroplaneTime-550);

}

void ProtoScene::bgMovement(float dt)
{

	m_bgCity1   .transform.Move(-100 * dt, 0);
	m_bgCity2   .transform.Move(-100 * dt, 0);
	m_frontCity .transform.Move(-200 * dt, 0);
	m_frontCity2.transform.Move(-200 * dt, 0);
	m_mountain  .transform.Move(-20 * dt, 0);
	m_mountain2 .transform.Move(-20 * dt, 0);

	heliTime += 3*dt;
	m_heli.transform.Move(10 * sin(heliTime) - 60*dt , 0.7*cos(heliTime / 2));


	if (m_bgCity1.transform.GetPosition().x <= -(m_bgCity1.transform.GetSize().x))
	{
		m_bgCity1.transform.SetPosition(pmath::Vec2(m_bgCity2.transform.GetPosition().x + (m_bgCity2.transform.GetSize().x), m_backCitySpawn.y));
	}
	if (m_bgCity2.transform.GetPosition().x <= -(m_bgCity2.transform.GetSize().x))
	{
		m_bgCity2.transform.SetPosition(pmath::Vec2(m_bgCity1.transform.GetPosition().x + (m_bgCity1.transform.GetSize().x), m_backCitySpawn.y));
	}


	///////


	if (m_frontCity.transform.GetPosition().x <= -(m_frontCity.transform.GetSize().x))
	{
		m_frontCity.transform.SetPosition(pmath::Vec2(m_frontCity2.transform.GetPosition().x + (m_frontCity2.transform.GetSize().x), m_frontCitySpawn.y));
	}
	if (m_frontCity2.transform.GetPosition().x <= -(m_frontCity2.transform.GetSize().x))
	{
		m_frontCity2.transform.SetPosition(pmath::Vec2(m_frontCity.transform.GetPosition().x + (m_frontCity.transform.GetSize().x), m_frontCitySpawn.y));
	}

	//////

	if (m_mountain.transform.GetPosition().x <= -(m_mountain.transform.GetSize().x))
	{
		m_mountain.transform.SetPosition(pmath::Vec2(m_mountain2.transform.GetPosition().x + (m_mountain2.transform.GetSize().x), m_mountainSpawn.y));
	}
	if (m_mountain2.transform.GetPosition().x <= -(m_mountain2.transform.GetSize().x))
	{
		m_mountain2.transform.SetPosition(pmath::Vec2(m_mountain.transform.GetPosition().x + (m_mountain.transform.GetSize().x), m_mountainSpawn.y));
	}

}

void ProtoScene::autoMove(float dt)
{
	m_auto.transform.Move(-600 * dt, 0);
}

void ProtoScene::playerJump(float dt)
{
	m_playerJumpSpeed += 2000*dt;
	auto speed = pmath::Vec2(0, m_playerJumpSpeed*dt);
	m_player.transform.Move(speed);
	if (m_player.transform.GetPosition().y >= m_playerGroundLevel)
	{
		m_isPlayerJumping = false;
		setCameraShake(0.5f, 5);
	};
}

void ProtoScene::playerCrouch(float dt)
{
	m_playerCrouchTimer -= dt;
	setCameraShake(0.1f, m_playerCrouchTimer*4);
	if (m_playerCrouchTimer <= 0)
	{
		m_isPlayerCrouching = false;
		m_isCameraShaking	= false;
	}
}

void ProtoScene::setCameraShake(float time, float amount)
{
		m_cameraShakeTime = time;
		m_cameraShakeAmount = amount;
		m_isCameraShaking = true;
}

void ProtoScene::shakeCamera(float dt)
{
	m_cameraShakeTime -= dt;
	auto pos = pmath::Vec2(Randomizer::GetFloat(-m_cameraShakeAmount, m_cameraShakeAmount),
							  Randomizer::GetFloat(-m_cameraShakeAmount, m_cameraShakeAmount));
	gameCamera->SetPosition(pos);
	if (m_cameraShakeTime < 0)
	{
		m_isCameraShaking = false; 
		gameCamera->SetPosition(pmath::Vec2(0,0));
	}
}

void ProtoScene::humanMove(float dt)
{

}
