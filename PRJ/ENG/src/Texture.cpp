#include "ENGCommon.h"

DISABLE_WARNING_PUSH()
DISABLE_WARNING( 4365 )
DISABLE_WARNING( 4668 )
#include "lib/DXTex/include/DirectXTex.h"
DISABLE_WARNING_POP()
#include "Texture.h"

void Texture::SetToContext()
{
	UINT texture_slot = 0;
	UINT sampler_slot = 0;
	global_context->PSSetShaderResources( texture_slot, 1, &view );
	global_context->PSSetSamplers( sampler_slot, 1, &sampler );
}

Texture::Texture( const char* filename )
{
	D3D11_FILTER filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	UINT isotropic_level = 4;

	DirectX::ScratchImage scratch_img;

	{ // Load texture
		size_t len = strlen( filename );
		wchar_t* wfilename = new wchar_t[len + 1];
		for ( size_t i = 0; i < len; i++ )
		{
			wfilename[i] = (wchar_t)filename[i];
		}
		wfilename[len] = '\0';

		Verify( DirectX::LoadFromTGAFile( wfilename, nullptr, scratch_img ) );

		delete[] wfilename;
	}

	const DirectX::TexMetadata& img_meta = scratch_img.GetMetadata();
	width = img_meta.width;
	height = img_meta.height;
	Verify( DirectX::CreateShaderResourceView
	(
		global_device,
		scratch_img.GetImage(0, 0, 0),
		scratch_img.GetImageCount(),
		scratch_img.GetMetadata(),
		&view
	) );

	D3D11_SAMPLER_DESC sampler_desc = {};
	sampler_desc.Filter = filter;
	sampler_desc.MaxAnisotropy = isotropic_level;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampler_desc.MinLOD = 0;
	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;
	Verify( global_device->CreateSamplerState( &sampler_desc, &sampler ) );
}