#ifndef TEXTURE_H
#define TEXTURE_H

struct Texture
{
	DXPtr<ID3D11ShaderResourceView> view;
	DXPtr<ID3D11SamplerState> sampler;
	size_t width;
	size_t height;
	
	void SetToContext();

	Texture( const char* filename );
	~Texture() = default;
};

#endif // TEXTURE_H