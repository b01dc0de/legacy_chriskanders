#ifndef GFXENTITY_H
#define GFXENTITY_H

struct Shader;
struct ShaderUI;
struct ShaderSingleColor;
struct Mesh;
struct Texture;
struct Image;

struct GFXEntityColor
{
	Shader* shader;
	Mesh* mesh;
	Matrix world;

	void Render();

	GFXEntityColor( Mesh* in_mesh, const Matrix& in_world = Matrix( IDENTITY ) );
	~GFXEntityColor() = default;
};

struct GFXEntitySingleColor
{
	ShaderSingleColor* shader;
	Mesh* mesh;
	Matrix world;
	Vector color;

	void Render();

	GFXEntitySingleColor( Mesh* in_mesh, const Matrix& in_world = Matrix( IDENTITY ) );
	~GFXEntitySingleColor() = default;
};

struct GFXEntityTexture
{
	Shader* shader;
	Texture* texture;
	Mesh* mesh;
	Matrix world;

	void Render();

	GFXEntityTexture( Texture* in_texture, const Matrix& in_world = Matrix( IDENTITY ) );
};

#include "Image.h"

struct GFXEntityUI
{
	ShaderUI* shader;
	Image* image;
	Mesh* mesh;

	float x;
	float y;
	float angle;
	float scale;

	void Render();

	GFXEntityUI( Image* in_image );
};

#endif // GFXENTITY_H