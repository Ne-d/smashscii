#include "Engine/Engine.h"

constexpr short ScreenWidth = 160;
constexpr short ScreenHeight = 50;

int main()
{
	Engine::GetInstance().SetScreenSize(ScreenWidth, ScreenHeight);
	Engine::GetInstance().MainLoop();
}
