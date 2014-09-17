#include <Player.hpp>

using namespace uth;

Player::Player()
{
	auto playerTexture = uthRS.LoadTexture("modzilla/modzilla_walk.png");
	playerTexture->SetSmooth(true);
	AddComponent(new AnimatedSprite(playerTexture, 4, 4, 1));
	transform.SetOrigin(uth::Origin::BottomCenter);
	transform.SetScale(0.75f);
}

Player::~Player()
{
}

void Player::Update(float dt)
{
	GameObject::Update(dt);
}
void Player::Draw()
{
	GameObject::Draw(uthEngine.GetWindow());
}