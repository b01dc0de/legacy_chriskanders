#ifndef SHADER_H
#define SHADER_H

struct Shader
{
	DXPtr<ID3D11VertexShader> vertex_shader;
	DXPtr<ID3D11PixelShader> pixel_shader;
	DXPtr<ID3D11InputLayout> input_layout;

	DXPtr<ID3D11Buffer> w_buffer;
	DXPtr<ID3D11Buffer> vp_buffer;

	static HRESULT CompileShader( const WCHAR* file_name, const char* entry_point, const char* shader_model, ID3DBlob **blob_out );
	void CreateInputLayout( D3D11_INPUT_ELEMENT_DESC layout[], UINT num_elements, DXPtr<ID3DBlob>& vs_blob );
	void CreateWVPBuffers();

	virtual void SetToContext();
	void UpdateViewProj( ViewProj* viewproj );
	void UpdateWorld( Matrix* world );

	Shader( const WCHAR* filename );
	Shader( const Shader& ) = delete;
	Shader& operator=( const Shader& ) = delete;
	virtual ~Shader() = default;
};

struct ShaderColor : Shader
{
	ShaderColor();
};

struct ShaderSingleColor : Shader
{
	DXPtr<ID3D11Buffer> color_buffer;

	virtual void SetToContext() override;
	void UpdateColor( Vector* color );

	ShaderSingleColor();
};

struct Texture;

struct ShaderTexture : Shader
{
	virtual void SetToContext() override;

	ShaderTexture();
	~ShaderTexture() = default;
};

struct Rect;

struct ShaderUI : Shader
{
	DXPtr<ID3D11Buffer> rect_buffer;

	virtual void SetToContext() override;
	void UpdateRect( Rect* rect );
	
	ShaderUI();
	~ShaderUI() = default;
};

#endif // SHADER_H
