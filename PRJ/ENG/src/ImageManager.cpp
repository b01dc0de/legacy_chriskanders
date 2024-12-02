#include "ENGCommon.h"

#include "Image.h"
#include "Texture.h"
#include "ImageManager.h"

ImageManager* ImageManager::inst = nullptr;

Image* ImageManager::Get( CKAString key )
{
	return Inst()->img_map.Get( key );
}

void ImageManager::Register( CKAString key, Texture* texture, Rect rect )
{
	Inst()->img_map.Add( key, new Image( texture, rect ) );
	Inst()->keys.Add( key );
}

void ImageManager::Deregister( CKAString key )
{
	delete Inst()->img_map.Get( key );
	Inst()->img_map.Remove( key );
	Inst()->keys.RemoveItemFast( key );
}

void ImageManager::Init()
{

}
void ImageManager::Term()
{
	delete inst;
	inst = nullptr;
}

ImageManager* ImageManager::Inst()
{
	if ( inst == nullptr )
	{
		inst = new ImageManager();
	}
	return inst;
}

ImageManager::~ImageManager()
{
	for ( u64 idx = 0; idx < keys.num; idx++ )
	{
		Deregister( keys[idx] );
	}
}

