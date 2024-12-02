#include "ENGCommon.h"

#include "GFXEntity.h"
#include "TextureManager.h"
#include "ImageManager.h"
#include "Tube.h"
#include "PrefabMesh.h"
#include "Game.h"

void Game::Tick()
{
	{ // Update
		gfxui->angle += 0.01f;
		{
			float deadzone = 3000.0f;
			if ( abs( (float)Gamepad::LX ) > deadzone )
			{
				gfxui->x += (float)Gamepad::LX / 10000.0f;
			}
			if ( abs( (float)Gamepad::LY ) > deadzone )
			{
				gfxui->y += (float)Gamepad::LY / 10000.0f;
			}
			if ( abs( (float)Gamepad::RX ) > deadzone &&
				 abs( (float)Gamepad::RY ) > deadzone )
			{
				gfxui->angle = atan2f( (float)-Gamepad::RY / (float)SHRT_MAX,
					Gamepad::RX / (float)SHRT_MAX );
			}
		}
		tube->Update();
	}

	{ // Render
		GFXManager::BegDraw();

		gfxcube->Render();
		gfxfloor->Render();
		gfxrect->Render();
		gfxui->Render();
		tube->Render();

		GFXManager::EndDraw();
	}
}

void Game::Init()
{
	TextureManager::Register( "test_texture", "Textures/test_texture.tga" );
	ImageManager::Register( "test_texture", TextureManager::Get( "test_texture" ), { 0.0f, 0.0f, 1.0f, 1.0f } );

	Matrix gfxcube_world = Matrix( SCALE, 4.0f ) * Matrix( TRANS, 0.0f, 4.0f, 0.0f );
	gfxcube = new GFXEntityColor( PrefabMesh::GetMesh( PrefabType::UNIT_CUBE ), gfxcube_world );

	Matrix gfxfloor_world = Matrix( SCALE, 16.0f );
	gfxfloor = new GFXEntityColor( PrefabMesh::GetMesh( PrefabType::UNIT_FLOOR ), gfxfloor_world );

	Matrix gfxrect_world = Matrix( SCALE, 20.0f ) * Matrix( TRANS, 0.0f, 5.0f, 20.0f );
	gfxrect = new GFXEntityTexture( TextureManager::Get("test_texture"), gfxrect_world );

	gfxui = new GFXEntityUI( ImageManager::Get( "test_texture" ) );

	tube = new Tube();
	tube->Init();
}

void Game::Term()
{
	delete gfxcube;
	delete gfxfloor;
	delete gfxrect;
	delete gfxui;
	tube->Term();
	delete tube;
}
