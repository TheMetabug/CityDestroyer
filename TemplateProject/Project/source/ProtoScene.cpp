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
	m_player.transform.SetPosition(pmath::Vec2f(0, m_playerGroundLevel));
	m_isPlayerJumping = false;
	m_isPlayerCrouching = false;
	m_playerJumpSpeed = 0;

	m_frontCitySpawn = pmath::Vec2(0, 300);
	m_backCitySpawn = pmath::Vec2(0, 60);
	m_mountainSpawn = pmath::Vec2(0, -100);
	planeResetClock = 0;
	planeResetTime = 0;
	planeSpawnX = 4500;
	planeSpawnY = -450;

	carSpawnX = 1100;
	carSpawnY = 200;
	carWaitClock = 0;
	carAirBorne = false;
	carAirSpeed = 1000;

	heliCurPos = pmath::Vec2f(200, -200);
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

	missileSpeed = 500;
	normModifier = 0.25;
	isMissile = 0;
	normIncrement = 0;
	
	shockSpeed = 900;
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
	missileClock = 0;


	camLerpX = 0;
	lerpSpeed = 4;
	camLeftMost = -400;
	camRightMost = 400;
	isLerpingRight = false;
	isLerpingLeft = false;

	m_isCameraShaking = false;
	setTempPos = true;
	explodeIsOn = false;

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

	auto playerTexture = uthRS.LoadTexture("modzilla/modzilla_walk.png");
	auto bgCityTexture = uthRS.LoadTexture("buildings.png");
	auto autoTexture = uthRS.LoadTexture("vehicles/car1.png");
	auto bgFrontCityTexture = uthRS.LoadTexture("lamps.png");
	auto bgMountainTexture = uthRS.LoadTexture("mountain.png");
	auto heliTexture = uthRS.LoadTexture("vehicles/fighter_copter.png");
	auto skyTexture = uthRS.LoadTexture("sky.tga");
	auto groundTexture = uthRS.LoadTexture("asphalt.png");
	auto aeroplaneTexture = uthRS.LoadTexture("vehicles/fighter_plane.png");
	auto groundBlockTexture = uthRS.LoadTexture("asphalt_block.png");
	auto humanRunTexture = uthRS.LoadTexture("man_run_ANIM.png");
	auto tankTexture = uthRS.LoadTexture("vehicles/tank.png");
	auto test = uthRS.LoadTexture("donut.png");
	auto missileTexture = uthRS.LoadTexture("missile.png");

	auto explodeTexture = uthRS.LoadTexture("explosion.png");

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
	m_aeroplane.AddComponent(new Sprite(aeroplaneTexture));
	m_aeroplane.transform.SetSize(m_aeroplane.transform.GetSize().x / 2, m_aeroplane.transform.GetSize().y / 2);
	m_skyBg.AddComponent(new Sprite(skyTexture));
	m_skyBg.transform.SetSize(m_skyBg.transform.GetSize().x*2, m_skyBg.transform.GetSize().y);
	m_groundTemp.AddComponent(new Sprite(groundTexture));
	m_tank.AddComponent(new Sprite(tankTexture));
	m_explode.AddComponent(new Sprite(explodeTexture));
	
	m_missile.AddComponent(new Sprite(missileTexture));

	m_heli.transform.SetPosition(pmath::Vec2(heliSpawnX, heliSpawnY));
	m_auto.transform.SetPosition(pmath::Vec2(carSpawnX, carSpawnY));
	m_aeroplane.transform.SetPosition(pmath::Vec2(30, -10));


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
	m_explode.transform.SetPosition(pmath::Vec2(1500, 1500));
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

	if (explodeIsOn)
	{ 
		explodeShake(dt);
	}

	if (m_auto.transform.GetPosition().x - shockSpeed*shockTime + shochStartX <= 0.5*shockLenght && shock)
	{
		carAirBorne = 1;
	}

	if (carAirBorne)
	{
		m_auto.transform.SetPosition(pmath::Vec2f(m_auto.transform.GetPosition().x, m_auto.transform.GetPosition().y - carAirSpeed * dt));
		m_auto.transform.Rotate(dt * 900);
	}

	if (carAirBorne && m_auto.transform.GetPosition().y <= -400)
	{
		carAirBorne = 0;
		std::cout << carAirBorne << std::endl;
		m_auto.transform.SetPosition(carSpawnX,carSpawnY);
		m_auto.transform.SetRotation(0);
	}


	if (std::abs(m_auto.transform.GetPosition().x - m_heli.transform.GetPosition().x ) <= 10 && std::abs(m_auto.transform.GetPosition().y - m_heli.transform.GetPosition().y ) <= 10)
	{
		expX = m_heli.transform.GetPosition().x;
		expY = m_heli.transform.GetPosition().y;
		explodeSpawn(expX,expY);

		m_heli.transform.position.x = heliSpawnX;
		m_heli.transform.position.y = heliSpawnY;

	}

	if (isLerpingLeft)
	{
		isLerpingRight = false;
		lerpCamLeft(dt);
	}


	if (isLerpingRight)
	{
		isLerpingLeft = false;
		lerpCamRight(dt);
	}


	if (isMissile)
	{
		missilePath(dt);
	}


	return true; // Update succeeded.

}

void ProtoScene::missilePath(float dt)
{
	if (isMissile)
	{
		

		homingSystem = sin((-m_player.transform.GetPosition() + m_missile.transform.GetPosition()).dot(mainDir));

		m_missile.transform.SetPosition(pmath::Vec2f(missileSpawn - missileSpeed * missileClock * (mainDir + normModifier*sin(3*missileClock)*sin(missileClock*5)/2 * normDir)));
		missileClock += dt;

		if ((m_missile.transform.GetPosition() - m_player.transform.GetPosition()).length() <= 30 || missileClock >= 3)
		{
			m_missile.transform.SetPosition(m_heli.transform.GetPosition());
			explodeSpawn(m_player.transform.GetPosition().x, m_player.transform.GetPosition().y);
			missileClock = 0;
			isMissile = 0;
		}
	}
}



void ProtoScene::lerpCamLeft(float dt)
{
	if (gameCamera->GetPosition().x > camLeftMost && isLerpingLeft)

	{
		isLookingRight = false;
		camLerpX += camLeftMost * lerpSpeed* dt;
		gameCamera->SetPosition(pmath::Vec2(camLerpX, gameCamera->GetPosition().y));
	}
	if (gameCamera->GetPosition().x <= camLeftMost && isLerpingLeft)
	{
		gameCamera->SetPosition(pmath::Vec2(camLeftMost, gameCamera->GetPosition().y));
		isLerpingLeft = false;	
		m_player.transform.SetScale(-abs(m_player.transform.GetScale().x), m_player.transform.GetScale().y);
		/*m_player.GetComponent<AnimatedSprite>("AnimatedSprite")->SetColor(Randomizer::GetFloat(0, 1),
			Randomizer::GetFloat(0, 1),
			Randomizer::GetFloat(0, 1),
			1);*/
	}

}

void ProtoScene::lerpCamRight(float dt)
{
	if (camLerpX < camRightMost  && isLerpingRight)

	{
		isLookingRight = true;
		camLerpX -= camLeftMost * lerpSpeed* dt;
		gameCamera->SetPosition(pmath::Vec2(camLerpX, gameCamera->GetPosition().y));
	}

	if (gameCamera->GetPosition().x >= camRightMost && isLerpingRight)
	{
		gameCamera->SetPosition(pmath::Vec2(camRightMost, gameCamera->GetPosition().y));
		isLerpingRight = false;
		m_player.transform.SetScale(abs(m_player.transform.GetScale().x), m_player.transform.GetScale().y);
		/*m_player.GetComponent<AnimatedSprite>("AnimatedSprite")->SetColor(Randomizer::GetFloat(0, 1),
			Randomizer::GetFloat(0, 1),
			Randomizer::GetFloat(0, 1),
			1);*/
	}
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
	m_missile.Draw(uthEngine.GetWindow());
	for (auto& i : humans)
	{
		i.Draw(uthEngine.GetWindow());
	}
	m_frontCity	.Draw(uthEngine.GetWindow());
	m_frontCity2.Draw(uthEngine.GetWindow());
	m_explode.Draw(uthEngine.GetWindow());
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
		isLerpingLeft = true;
	}
	if (uthInput.Keyboard.IsKeyDown(uth::Keyboard::Right))
	{
		isLerpingRight = true;;

	}
	if (uthInput.Keyboard.IsKeyDown(uth::Keyboard::Up) && !m_isPlayerJumping  && !m_isPlayerCrouching)
	{
		m_isPlayerJumping = true;
		m_playerJumpSpeed = -1000;
	}

	if (uthInput.Keyboard.IsKeyDown(uth::Keyboard::Q))
	{
		missileSpawn = m_heli.transform.GetPosition();
		mainDir = ((-m_player.transform.GetPosition() + missileSpawn).normalize());
		normDir = pmath::Vec2f(mainDir.y, -mainDir.x);
		m_missile.transform.SetPosition(missileSpawn);
		isMissile = true;
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

	if (m_aeroplane.transform.GetPosition().x <= m_player.transform.GetPosition().x + 100)
	{
		planeReset();
		planeResetTime = Randomizer::GetFloat(3, 10);
	}
	planeResetClock +=dt;

}



void ProtoScene::navigate(pmath::Vec2f targ, float dt)
{
	heliTargPos = targ;
	heliLerp(targ, dt);
}

void ProtoScene::heliLerp(pmath::Vec2f targ,float dt)
{
	pmath::Vec2f heliDir = (heliTargPos - heliCurPos).normalize();
	heliCurPos += heliSpeed * heliDir;
}

void ProtoScene::heliHover(float dt)
{
	heliTime += 3 * dt;
	m_heli.transform.SetPosition(heliCurPos + pmath::Vec2f(sin(heliTime), cos(heliTime/2)));

	if (heliResetClock >= heliResetTime)
	{
		heliReset();
		heliResetTime = Randomizer::GetFloat(30, 60);
		heliResetClock += dt;
	}


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
	explodeSpawn(m_aeroplane.transform.GetPosition().x, m_aeroplane.transform.GetPosition().y);
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
		m_auto.transform.Move(-m_carSpeed * dt, 0);

		if (m_auto.transform.GetPosition().x <= -m_carSpeed)
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

		if (m_cameraShakeTime <= 0.f)
		{
			m_isCameraShaking = false;
			if (isLookingRight)
			{
				gameCamera->SetPosition(pmath::Vec2(camRightMost, 0));
			}
			else
			{
				gameCamera->SetPosition(pmath::Vec2(camLeftMost, 0));
			}
			gameCamera->SetRotation(0);
		}
		gameCamera->SetRotation(0);
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

	if (setTempPos)
	{
		tempPos.x = gameCamera->GetPosition().x;
		tempPos.y = gameCamera->GetPosition().y;
		setTempPos = false;
	}
	else
	{
		auto pos = pmath::Vec2(Randomizer::GetFloat(tempPos.x - m_cameraShakeAmount, tempPos.x + m_cameraShakeAmount),
			Randomizer::GetFloat(tempPos.y + m_cameraShakeAmount, tempPos.y - m_cameraShakeAmount));
		gameCamera->SetPosition(pos);
		gameCamera->SetRotation(Randomizer::GetFloat(-0.6, 0.6));
	}


	if (m_cameraShakeTime <= 0.f)
	{
		m_isCameraShaking = false; 
		if (isLookingRight)
		{
			gameCamera->SetPosition(pmath::Vec2(camRightMost, 0));
		}
		else
		{
			gameCamera->SetPosition(pmath::Vec2(camLeftMost, 0));
		}
		gameCamera->SetRotation(0);
		setTempPos = true;
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

void ProtoScene::explodeSpawn(float x, float y)
{
	m_explode.transform.SetPosition(x, y);
	explodeTime = 0.5;
	explodeIsOn = true;
}

void ProtoScene::explodeShake(float dt)
{
	explodeTime -= dt;
	if (explodeTime >= 0)
	{
		m_explode.transform.SetPosition(m_explode.transform.GetPosition().x + Randomizer::GetFloat(-3, 3),
			m_explode.transform.GetPosition().y + Randomizer::GetFloat(-3, 3));
		m_explode.transform.SetScale(Randomizer::GetFloat(explodeTime*2, explodeTime*4));
		m_explode.transform.Rotate(explodeTime);
	}
	else
	{
		explodeIsOn = false;
		m_explode.transform.SetPosition(1500,1500);
	}
}
