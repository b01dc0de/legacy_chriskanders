#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

struct Shader;
struct ShaderColor;
struct ShaderSingleColor;
struct ShaderTexture;
struct ShaderUI;

struct ShaderManager
{
	ShaderColor* shader_color;
	ShaderSingleColor* shader_singlecolor;
	ShaderTexture* shader_texture;
	ShaderUI* shader_ui;

	static ShaderColor* GetShaderColor() { return Inst()->shader_color; }
	static ShaderSingleColor* GetShaderSingleColor() { return Inst()->shader_singlecolor; }
	static ShaderTexture* GetShaderTexture() { return Inst()->shader_texture; }
	static ShaderUI* GetShaderUI() { return Inst()->shader_ui; }

	static void Init();
	void PrivInit();
	static void Term();
	void PrivTerm();

	static ShaderManager* inst;
	static ShaderManager* Inst();

	~ShaderManager();
};

#endif // SHADERMANAGER_H