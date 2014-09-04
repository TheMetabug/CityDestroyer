#pragma once
#ifndef ProtoScene_HPP
#define ProtoScene_HPP

#include <UtH/Engine/Scene.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Engine/Sprite.hpp>
#include <UtH/Core/Shader.hpp>

class ProtoScene : public uth::Scene
{
private: // Just place everything else as private.
	uth::Shader		m_shader;
	uth::GameObject m_player;
	uth::GameObject m_bgCity1;
	uth::GameObject m_bgCity2;
	uth::GameObject m_frontCity;
	uth::GameObject m_frontCity2;

	uth::GameObject m_mountain;
	uth::GameObject m_mountain2;
	uth::GameObject m_heli;

	//uth::AnimatedSprite m_playerAnimation;
	//uth::SpriteBatch* m_spriteBatch;

	void inputLogic(float dt);
	void bgMovement(float dt);
	float heliTime;

	bool m_isPlayerJumping, m_isPlayerCrouching;

	float m_playerJumpSpeed, m_playerGroundLevel;

	void playerJump	 (float dt);
	void playerCrouch(float dt);


public: // Every one of these public functions are required.
	ProtoScene();
	~ProtoScene();

	virtual bool Init();
	virtual bool DeInit();

	virtual bool Update(float dt);
	virtual bool Draw();
};

#endif //ProtoScene_HPP