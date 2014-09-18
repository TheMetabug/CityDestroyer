//#include "Heli.h"
//
//Heli::Heli()
//{
//}
//
//
//Heli::~Heli()
//{
//}
//
//
//void Heli::lerp(pmath::Vec2f targ, float dt)
//{
//	pmath::Vec2f dir = (targPos - curPos).normalize();
//	curPos += speed * dt * dir;
//}
//
//void Heli::navigate(pmath::Vec2f targ, float dt)
//{
//	TargPos = targ;
//	lerp(targ, dt);
//}
//
//void Heli::Hover(float dt)
//{
//	heliTime += 3 * dt;
//	m_heli.transform.SetPosition(heliCurPos + pmath::Vec2f(sin(heliTime), cos(heliTime / 2)));
//
//	if (heliResetClock >= heliResetTime)
//	{
//		heliReset();
//		heliResetTime = Randomizer::GetFloat(30, 60);
//		heliResetClock += dt;
//	}
//
//
//}