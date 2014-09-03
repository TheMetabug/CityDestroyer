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
	uth::Shader m_shader;
	uth::GameObject* m_player;
	uth::Texture* m_playerTexture;
public: // Every one of these public functions are required.
	ProtoScene();
	~ProtoScene();

	virtual bool Init();
	virtual bool DeInit();

	virtual bool Update(float dt);
	virtual bool Draw();
};

#endif //ProtoScene_HPP