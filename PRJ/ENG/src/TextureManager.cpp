#include "ENGCommon.h"

#include "Texture.h"
#include "TextureManager.h"

TextureManager* TextureManager::inst = nullptr;

Texture* TextureManager::Get( CKAString key )
{
	return Inst()->tex_map.Get( key );
}
void TextureManager::Register( CKAString key, const char* filename )
{
	Inst()->tex_map.Add( key, new Texture( filename ) );
	Inst()->keys.Add( key );
}
void TextureManager::Deregister( CKAString key )
{
	delete Inst()->tex_map.Get( key );
	Inst()->tex_map.Remove( key );
	Inst()->keys.RemoveItemFast( key );
}

void TextureManager::Init()
{
	Inst();
}

void TextureManager::Term()
{
	delete inst;
	inst = nullptr;
}

TextureManager* TextureManager::Inst()
{
	if ( inst == nullptr )
	{
		inst = new TextureManager();
	}
	return inst;

}

TextureManager::~TextureManager()
{
	for ( u64 idx = 0; idx < keys.num; idx++ )
	{
		Deregister( keys[idx] );
	}
}

