#pragma once
#ifndef ProtoScene_HPP
#define ProtoScene_HPP

#include <UtH/Engine/Scene.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Engine/Sprite.hpp>
#include <UtH/Engine/AnimatedSprite.hpp>
#include <UtH/Core/Shader.hpp>
#include <UtH/Renderer/Camera.hpp>
#include <UtH/Engine/SpriteBatch.hpp>
#include <UtH/Audio/Audio.hpp>

#include <array>

class ProtoScene : public uth::Scene
{
private: // Just place everything else as private.
	uth::Shader		m_shader;
	uth::GameObject m_player;
	uth::GameObject m_bgCity1;
	uth::GameObject m_bgCity2;
	uth::GameObject m_frontCity;
	uth::GameObject m_frontCity2;
	uth::GameObject m_groundTemp;
	uth::GameObject m_skyBg;

	uth::GameObject m_mountain;
	uth::GameObject m_mountain2;
	uth::GameObject m_heli;
	uth::GameObject m_auto;
	uth::GameObject m_aeroplane;
	uth::GameObject m_human;
	uth::GameObject m_tank;
	uth::GameObject m_explode;
	uth::GameObject m_missile;


	//uth::AnimatedSprite m_playerAnimation;
	uth::SpriteBatch m_spriteBatch;

	uth::Audio* m_music;
	uth::Audio* m_stomp;
	uth::SoundDevice* m_soundDevice;

	std::array < uth::Transform, 80 > roadBlocks;

	float roadY;
	void heliMove(float dt);
	void inputLogic(float dt);
	void bgMovement(float dt);
	float normIncrement;
	float missileClock;
	float homingSystem;

	void heliReset();
	void missilePath(float dt);
	pmath::Vec2f mainDir;
	pmath::Vec2f normDir;
	float missileSpeed;
	pmath::Vec2f missileSpawn;
	float normModifier; // close to zero: straight path... else curvy.

	bool isMissile;

	float heliResetClock;
	float heliResetTime;
	float heliTime;
	float heliSpawnX;
	float heliSpawnY;
	float heliWaitClock;
	float shochStartX;
	float shockHeightMatcher;

	bool shock;
	float shockTime;
	float shockSpeed;
	float shockHeight;
	void initShock(float dt);
	float shockLenght;
	float shockRange;
	float shockPrecision;

	float aeroplaneSpeed;
	void aeroplaneMove(float dt);
	float planeResetClock;
	float planeResetTime;
	float planeSpawnX;
	float planeSpawnY;
	void planeReset();

	void carMove(float dt);
	float carSpawnX;
	float carSpawnY;
	void carReset();
	float carWaitTime;
	float carWaitClock;
	bool carAirBorne;
	float carAirSpeed;
	float carRot;

	void tankMove(float dt);
	float tankSpawnX;
	float tankSpawnY;
	void tankReset();
	float tankWaitTime;
	float tankWaitClock;
	float tankSpeed;
	int asd;


	float expX;
	float expY;

	void lerpCamLeft(float dt);
	float lerpSpeed;
	float camLerpX;
	float camLeftMost;
	float camRightMost;
	bool isLerpingRight;
	bool isLerpingLeft;
	bool isLookingRight;
	bool setTempPos;
	pmath::Vec2 tempPos;
	void lerpCamRight(float dt);


	void explodeShake(float dt);
	void explodeSpawn(float,float);
	float explodeTime;
	bool explodeIsOn;

	//Player
	bool m_isPlayerJumping,
		 m_isPlayerCrouching;

	float m_playerJumpSpeed,
		  m_playerGroundLevel,
		  m_playerCrouchTimer;

	void playerJump	 (float dt);
	void playerCrouch(float dt);
	//Buildings
	pmath::Vec2 m_frontCitySpawn;
	pmath::Vec2 m_backCitySpawn;
	pmath::Vec2 m_mountainSpawn;


	//Camera
	void setCameraShake(float time, float amount);
	void shakeCamera(float dt);
	float m_cameraShakeTime, m_cameraShakeAmount;
	bool  m_isCameraShaking;
	uth::Camera* gameCamera;
	//Road
	//std::vector<uth::GameObject*> roadBlocks;
	//uth::Texture 

	float m_humanSpawnX, m_humanSpawnY;
	float m_humanSpeed,
		  m_bgCitySpeed,
		  m_frontCitySpeed,
		  m_mountainSpeed,
		  m_carSpeed,
		  m_planeSpeed,
		  m_heliSpeed;
	std::array < uth::GameObject, 4 > humans;
	
	void humanMove(float dt);

public: // Every one of these public functions are required.
	ProtoScene();
	~ProtoScene();

	virtual bool Init();
	virtual bool DeInit();

	virtual bool Update(float dt);
	virtual bool Draw();
};

#endif //ProtoScene_HPP