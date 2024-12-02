#ifndef GAME_H
#define GAME_H

struct GFXEntityColor;
struct GFXEntityTexture;
struct GFXEntityUI;
struct Tube;

struct Game
{
	GFXEntityColor* gfxcube;
	GFXEntityColor* gfxfloor;
	GFXEntityTexture* gfxrect;
	GFXEntityUI* gfxui;
	Tube* tube;

	void Tick();

	void Init();
	void Term();
};

#endif // GAME_H