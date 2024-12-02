#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

struct TextureManager
{
	Map<Texture*> tex_map;
	DynamicArray<CKAString> keys;

	static Texture* Get( CKAString key );
	static void Register( CKAString key, const char* filename );
	static void Deregister( CKAString key );

	static void Init();
	static void Term();

	static TextureManager* inst;
	static TextureManager* Inst();

	~TextureManager();
};

#endif // TEXTUREMANAGER_H
