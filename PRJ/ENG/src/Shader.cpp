#include "ENGCommon.h"

#include "Engine.h"
#include "Texture.h"
#include "Shader.h"

HRESULT Shader::CompileShader( const WCHAR* file_name, const char* entry_point, const char* shader_model, ID3DBlob **blob_out )
{
	HRESULT result = S_OK;

	DWORD shader_flags = D3DCOMPILE_ENABLE_STRICTNESS;

#ifdef _DEBUG
	shader_flags |= D3DCOMPILE_DEBUG;
	shader_flags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif // _DEBUG

	DXPtr<ID3DBlob> error_blob = nullptr;
	result = D3DCompileFromFile
	(
		file_name,
		nullptr,
		nullptr,
		(LPCSTR)entry_point,
		(LPCSTR)shader_model,
		shader_flags,
		0,
		blob_out,
		&error_blob
	);

	if ( FAILED( result ) )
	{
		if ( error_blob )
		{
			OutputDebugString( (const char *)error_blob->GetBufferPointer() );
		}
	}

	return result;
};

void Shader::CreateInputLayout( D3D11_INPUT_ELEMENT_DESC layout[], UINT num_elements, DXPtr<ID3DBlob>& vs_blob )
{
	Verify( global_device->CreateInputLayout( layout, num_elements, vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), &input_layout ) );
}

void Shader::CreateWVPBuffers()
{
	D3D11_BUFFER_DESC buffer_desc = {};
	// viewprof cbuffer prep
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.ByteWidth = sizeof( ViewProj );
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	Verify( global_device->CreateBuffer( &buffer_desc, nullptr, &vp_buffer ) );
	buffer_desc = {};
	// world cbuffer prep
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.ByteWidth = sizeof( Matrix );
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	Verify( global_device->CreateBuffer( &buffer_desc, nullptr, &w_buffer ) );
}

void Shader::SetToContext()
{
	global_context->VSSetShader( vertex_shader, nullptr, 0 );
	global_context->PSSetShader( pixel_shader, nullptr, 0 );
	global_context->IASetInputLayout( input_layout );
	global_context->VSSetConstantBuffers( 0, 1, &vp_buffer );
	global_context->VSSetConstantBuffers( 1, 1, &w_buffer );
}

void Shader::UpdateViewProj( ViewProj* viewproj )
{
	global_context->UpdateSubresource( vp_buffer, 0, nullptr, viewproj, 0, 0 );
}

void Shader::UpdateWorld( Matrix* world )
{
	global_context->UpdateSubresource( w_buffer, 0, nullptr, world, 0, 0 );
}

Shader::Shader( const WCHAR* filename )
{
	DXPtr<ID3DBlob> vs_blob;
	DXPtr<ID3DBlob> ps_blob;

	Verify( CompileShader( filename, "VSMain", "vs_4_0", &vs_blob ) );
	Verify( global_device->CreateVertexShader( vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), nullptr, &vertex_shader ) );

	Verify( CompileShader( filename, "PSMain", "ps_4_0", &ps_blob ) );
	Verify( global_device->CreatePixelShader( ps_blob->GetBufferPointer(), ps_blob->GetBufferSize(), nullptr, &pixel_shader ) );

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT num_elements = ArraySize( layout );
	CreateInputLayout( layout, num_elements, vs_blob );

	CreateWVPBuffers();
}

ShaderColor::ShaderColor()
	: Shader( L"Shaders/ShaderColor.hlsl" )
{
}

void ShaderSingleColor::SetToContext()
{
	Shader::SetToContext();
	global_context->VSSetConstantBuffers( 2, 1, &color_buffer );
}

void ShaderSingleColor::UpdateColor( Vector* color )
{
	global_context->UpdateSubresource( color_buffer, 0, nullptr, color, 0, 0 );
}

ShaderSingleColor::ShaderSingleColor()
	: Shader(L"Shaders/ShaderSingleColor.hlsl")
{
	D3D11_BUFFER_DESC buffer_desc = {};
	// viewprof cbuffer prep
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.ByteWidth = sizeof( Vector );
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	Verify( global_device->CreateBuffer( &buffer_desc, nullptr, &color_buffer ) );
}

void ShaderTexture::SetToContext()
{
	Shader::SetToContext();
}

ShaderTexture::ShaderTexture()
	: Shader( L"Shaders/ShaderTexture.hlsl" )
{
}

void ShaderUI::SetToContext()
{
	Shader::SetToContext();
	global_context->VSSetConstantBuffers( 2, 1, &rect_buffer );
}

void ShaderUI::UpdateRect( Rect* rect )
{
	global_context->UpdateSubresource( rect_buffer, 0, nullptr, rect, 0, 0 );
}
	
ShaderUI::ShaderUI()
	: Shader(L"Shaders/ShaderUI.hlsl")
{

	D3D11_BUFFER_DESC buffer_desc = {};
	// viewprof cbuffer prep
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.ByteWidth = sizeof( Vector );
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	Verify( global_device->CreateBuffer( &buffer_desc, nullptr, &rect_buffer ) );
}
