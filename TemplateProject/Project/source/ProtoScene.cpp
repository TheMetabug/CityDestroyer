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
	Randomizer::SetSeed();
	m_playerGroundLevel = 250;
	m_isPlayerJumping = false;
	m_isPlayerCrouching = false;
	m_playerJumpSpeed = 0;

	m_frontCitySpawn = pmath::Vec2(0, 300);
	m_backCitySpawn = pmath::Vec2(0, 60);
	m_mountainSpawn = pmath::Vec2(0, -100);
	planeResetClock = 0;
	planeResetTime = 0;
	planeSpawnX = 1500;
	planeSpawnY = -250;

	carSpawnX = 1100;
	carSpawnY = 200;
	carWaitClock = 0;
	carAirBorne = 0;
	carAirSpeed = 1000;

	heliSpawnX = 1000;
	heliSpawnY = -200;
	heliResetTime = 30;
	heliResetClock = 0;

	m_humanSpawnX = uthEngine.GetWindowResolution().x + 100;
	m_humanSpawnY = 200;


	m_humanSpeed = 200;
	m_bgCitySpeed = 100;
	m_frontCitySpeed = 250;
	m_mountainSpeed = 20;
	m_carSpeed = 150;
	m_planeSpeed = 400;
	
	shockSpeed = 600;
	shockTime = 0;
	shockHeight = 0.1;
	shockRange = 1400;
	roadY = 320;
	shockLenght = 128;
	shock = 0;
	shochStartX = 450;
	shockHeightMatcher = 150;
	shockPrecision = 100;

	m_heliSpeed = 50;
	tankSpawnX = 1300;
	tankSpawnY = 200;
	tankWaitClock = 0;
	tankWaitTime = 0;
	tankSpeed = 150;
	asd = 0;


	m_isCameraShaking = false;

	// Some shader must be loaded and set window to use it

	m_soundDevice = new uth::SoundDevice();

	m_music = new uth::Audio();
	m_music->Load("city_theme.wav");
	m_music->Play();
	m_music->Loop(true);

	m_stomp = new uth::Audio();
	m_stomp->Load("impact_temporary.wav");

	heliTime = 0;
	aeroplaneSpeed = 0;
	m_shader.LoadShader("Shaders/Default.vert", "Shaders/Default.frag");
	m_shader.Use();
	uthEngine.GetWindow().SetShader(&m_shader);

	auto playerTexture = uthRS.LoadTexture("modzilla_ANIM.png");
	auto bgCityTexture = uthRS.LoadTexture("buildings.png");
	auto autoTexture = uthRS.LoadTexture("car.png");
	auto bgFrontCityTexture = uthRS.LoadTexture("lamps.png");
	auto bgMountainTexture = uthRS.LoadTexture("mountain.png");
	auto heliTexture = uthRS.LoadTexture("copter.png");
	auto skyTexture = uthRS.LoadTexture("sky.tga");
	auto groundTexture = uthRS.LoadTexture("asphalt.png");
	auto aeroplaneTexture = uthRS.LoadTexture("aeroplane.png");
	auto groundBlockTexture = uthRS.LoadTexture("roadblock.tga");
	auto humanRunTexture = uthRS.LoadTexture("man_run_ANIM.png");
	auto tankTexture = uthRS.LoadTexture("tank.tga");
	auto test = uthRS.LoadTexture("donut.png");

	m_spriteBatch.SetTexture(groundBlockTexture);
	unsigned int counter = 0;
	for (auto& i : roadBlocks)
	{
		m_spriteBatch.AddSprite(&i);
		i.SetPosition(pmath::Vec2(-uthEngine.GetWindowResolution().x / 2 + counter * 15.9 + 8, roadY));
		++counter;
	}

	playerTexture->SetSmooth(true);
	m_player.AddComponent(new AnimatedSprite(playerTexture,4,4,1));
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
	//m_human.AddComponent(new Sprite(test));
	m_aeroplane.AddComponent(new Sprite(aeroplaneTexture));
	m_aeroplane.transform.SetSize(m_aeroplane.transform.GetSize().x / 2, m_aeroplane.transform.GetSize().y / 2);
	m_skyBg.AddComponent(new Sprite(skyTexture));
	m_groundTemp.AddComponent(new Sprite(groundTexture));
	m_tank.AddComponent(new Sprite(tankTexture));

	

	m_heli.transform.SetPosition(pmat	shochStartX = m_player.transform.GetPosition().x;h::Vec2(heliSpawnX, heliSpawnY));
	m_auto.transform.SetPosition(pmath::Vec2(carSpawnX, carSpawnY));
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
	unsigned int humanCount = 0;
	for (auto& i : humans)
	{
		//i.SetPosition(pmath::Vec2(uthEngine.GetWindowResolution().x / 2 + counter * Randomizer::GetInt(15, 50) , 200));
		i.AddComponent(new AnimatedSprite(humanRunTexture, 2, 2, 1, 20));
		i.transform.SetSize(i.transform.GetSize().x / 2, i.transform.GetSize().y / 2);
		i.transform.SetPosition(pmath::Vec2(uthEngine.GetWindowResolution().x / 2 + counter * Randomizer::GetInt(10,90), 200 + Randomizer::GetInt(-20,20)));
		++humanCount;
	}

	gameCamera = new uth::Camera(pmath::Vec2(0, 0), uthEngine.GetWindowResolution());
	uthEngine.GetWindow().SetCamera(gameCamera);

	m_skyBg.transform.SetPosition(pmath::Vec2(0, 125));
	m_groundTemp.transform.SetPosition(pmath::Vec2(0, 300));

	m_tank.transform.SetPosition(pmath::Vec2(tankSpawnX, tankSpawnY));
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
	carMove(dt);
	aeroplaneMove(dt);
	heliMove(dt);
	humanMove(dt);
	tankMove(dt);
	shochStartX = -m_player.transform.GetPosition().x;

	if (shock)
	{
		initShock(dt);
	}
	for (auto& i : humans)
	{
		i.Update(dt);
	}

	m_spriteBatch.Update(dt);

	if ((std::abs(m_auto.transform.GetPosition().x - shockTime * shockSpeed + shochStartX -0.5 * shockLenght) <= 10) && shock)
	{
		carAirBorne = 1;
		std::cout << carAirBorne << std::endl;
	}

	if (carAirBorne)
	{
		m_auto.transform.SetPosition(pmath::Vec2f(m_auto.transform.GetPosition().x, m_auto.transform.GetPosition().y - carAirSpeed * dt));
	}

	if (carAirBorne && m_auto.transform.GetPosition().y <= -400)
	{
		carAirBorne = 0;
		std::cout << carAirBorne << std::endl;
		m_auto.transform.SetPosition(carSpawnX,carSpawnY);
	}


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
	m_auto.Draw (uthEngine.GetWindow());
	m_heli.Draw (uthEngine.GetWindow());
	m_aeroplane.Draw(uthEngine.GetWindow());
	m_tank.Draw(uthEngine.GetWindow());
	for (auto& i : humans)
	{
		i.Draw(uthEngine.GetWindow());
	}
	m_frontCity	.Draw(uthEngine.GetWindow());
	m_frontCity2.Draw(uthEngine.GetWindow());

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
		m_stomp->Play();
		m_stomp->SetPitch(50);
		shock = 1;
	}

}




void ProtoScene::initShock(float dt)
{
//	std::cout << "shock" << std::endl;
		for (int i = 0; i < roadBlocks.size(); i++)
		{
	

			if (shockLenght < std::abs(shockSpeed*shockTime - shochStartX - roadBlocks[i].GetPosition().x))
			{
				roadBlocks[i].SetPosition(roadBlocks[i].GetPosition().x, roadY);
			}
			else
			{
				roadBlocks[i].SetPosition(roadBlocks[i].GetPosition().x, roadY - shockHeight + std::pow((shockSpeed*shockTime - shochStartX) - roadBlocks[i].GetPosition().x, 2) / 100 - shockHeightMatcher);
			}

		}



		shockTime += dt;

		if (shockTime*shockSpeed >= shockRange)
		{
			shock = 0;
			shockTime = 0;
		}
}



void ProtoScene::aeroplaneMove(float dt)
{
	aeroplaneSpeed += 4*dt;
	m_aeroplane.transform.SetPosition(planeSpawnX-200*aeroplaneSpeed,20*aeroplaneSpeed+planeSpawnY);

	if (planeResetClock >= planeResetTime)
	{
		planeReset();
		planeResetTime = Randomizer::GetFloat(3, 10);
	}
	planeResetClock +=dt;

}

void ProtoScene::heliMove(float dt)
{
	heliTime += 3 * dt;
	m_heli.transform.Move( - 60 * dt, 0 );
	m_heli.transform.SetOrigin(pmath::Vec2(sin(heliTime), 0.7*cos(heliTime / 2)));


	if (heliResetClock >= heliResetTime)
	{
		heliReset();
		heliResetTime = Randomizer::GetFloat(30, 60);
	}
	heliResetClock += dt;

}

void ProtoScene::bgMovement(float dt)
{

	m_bgCity1.transform.Move(-m_bgCitySpeed * dt, 0);
	m_bgCity2.transform.Move(-m_bgCitySpeed * dt, 0);
	m_frontCity.transform.Move(-m_frontCitySpeed * dt, 0);
	m_frontCity2.transform.Move(-m_frontCitySpeed * dt, 0);
	m_mountain.transform.Move(-m_mountainSpeed * dt, 0);
	m_mountain2.transform.Move(-m_mountainSpeed * dt, 0);



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

void ProtoScene::planeReset()
{
	aeroplaneSpeed = 0;
	m_aeroplane.transform.SetPosition(planeSpawnX, planeSpawnY);
	planeResetClock = 0;
}

void ProtoScene::heliReset()
{
	heliTime = 0;
	m_heli.transform.SetPosition(heliSpawnX, heliSpawnY);
	heliResetClock = 0;
}

void ProtoScene::carMove(float dt)
{
	if (!carAirBorne)
	{
		m_auto.transform.Move(-900 * dt, 0);

		if (m_auto.transform.GetPosition().x <= -900)
		{
			carWaitClock += dt;

			if (carWaitClock >= carWaitTime)
			{
				m_auto.transform.SetPosition(carSpawnX, carSpawnY);
				carWaitClock = 0;
				carWaitTime = Randomizer::GetFloat(0, 8);
			}

		}
	}
}

void ProtoScene::tankMove(float dt)
{
	m_tank.transform.Move(-tankSpeed * dt, 0);

	if (m_tank.transform.GetPosition().x <= -900)
	{
		tankWaitClock += dt;
		if (tankWaitClock >= carWaitTime)
		{
			m_tank.transform.SetPosition(tankSpawnX, tankSpawnY);
			tankWaitClock = 0;
			tankWaitTime = Randomizer::GetFloat(10, 25);
		}

	}

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
		m_stomp->Play();
		m_stomp->SetPitch(70);
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
	for (auto& i : humans)
	{
		i.transform.Move(-m_humanSpeed * dt, 0);
		if (i.transform.GetPosition().x < -uthEngine.GetWindowResolution().x / 2)
		{
			i.transform.SetPosition(Randomizer::GetFloat(30, 600) + m_humanSpawnX, m_humanSpawnY);
		}
	}
}
