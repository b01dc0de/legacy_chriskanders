#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

struct Image;

struct ImageManager
{
	Map<Image*> img_map;
	DynamicArray<CKAString> keys;

	static Image* Get( CKAString key );
	static void Register( CKAString key, Texture* texture, Rect rect );
	static void Deregister( CKAString key );

	static void Init();
	static void Term();

	static ImageManager* inst;
	static ImageManager* Inst();

	~ImageManager();
};

#endif // IMAGEMANAGER