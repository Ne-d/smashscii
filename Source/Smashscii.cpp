#include "Engine/Engine.h"

constexpr short ScreenWidth = 120;
constexpr short ScreenHeight = 40;

int main()
{
	Engine::GetInstance().SetScreenSize(ScreenWidth, ScreenHeight);
	Engine::GetInstance().ShowTitle();
}
