#include "ENGCommon.h"

#include "ShaderManager.h"
#include "Shader.h"

ShaderManager* ShaderManager::inst = nullptr;

void ShaderManager::Init()
{
	Inst()->PrivInit();
}
void ShaderManager::PrivInit()
{
	shader_color = new ShaderColor();
	shader_singlecolor = new ShaderSingleColor();
	shader_texture = new ShaderTexture();
	shader_ui = new ShaderUI();
}

void ShaderManager::Term()
{
	Inst()->PrivTerm();
}
void ShaderManager::PrivTerm()
{
	delete inst;
	inst = nullptr;
}

ShaderManager* ShaderManager::Inst()
{
	if ( inst == nullptr )
	{
		inst = new ShaderManager();
	}
	return inst;
}

ShaderManager::~ShaderManager()
{
	delete shader_color;
	delete shader_singlecolor;
	delete shader_texture;
	delete shader_ui;
}
