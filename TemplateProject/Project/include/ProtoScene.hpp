#pragma once
#ifndef ProtoScene_HPP
#define ProtoScene_HPP

#include <UtH/Engine/Scene.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Engine/Sprite.hpp>
#include <UtH/Core/Shader.hpp>
#include <UtH/Renderer/Camera.hpp>

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


	//uth::AnimatedSprite m_playerAnimation;
	//uth::SpriteBatch* m_spriteBatch;

	void inputLogic(float dt);
	void bgMovement(float dt);
	float heliTime;
	void autoMove(float dt);
	//Player
	bool m_isPlayerJumping,
		 m_isPlayerCrouching;

	float m_playerJumpSpeed,
		  m_playerGroundLevel,
		  m_playerCrouchTimer;

	void playerJump	 (float dt);
	void playerCrouch(float dt);
	//Buildings
	umath::vector2 m_frontCitySpawn;
	umath::vector2 m_backCitySpawn;
	umath::vector2 m_mountainSpawn;


	//Camera
	void setCameraShake(float time, float amount);
	void shakeCamera(float dt);
	float m_cameraShakeTime, m_cameraShakeAmount;
	bool  m_isCameraShaking;
	uth::Camera* gameCamera;
	//Road
//	std::vector < GameObject* > roadBlocks;
//	void createRoad();


public: // Every one of these public functions are required.
	ProtoScene();
	~ProtoScene();

	virtual bool Init();
	virtual bool DeInit();

	virtual bool Update(float dt);
	virtual bool Draw();
};

#endif //ProtoScene_HPP