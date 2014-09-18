#include <BackGround.hpp>

using namespace uth;

BackGround::BackGround(std::string textureName, float yPos)
{
	auto backgroundTexture = uthRS.LoadTexture(textureName);
	backgroundTexture->SetSmooth(true);
	AddComponent(new Sprite(backgroundTexture));
	transform.SetOrigin(uth::Origin::TopLeft);
	//transform.SetScale(0.75f);
}

BackGround::~BackGround()
{
}

void BackGround::Update(float dt)
{
	GameObject::Update(dt);
}
void BackGround::Draw()
{
	GameObject::Draw(uthEngine.GetWindow());
}