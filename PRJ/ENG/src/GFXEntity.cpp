#include "ENGCommon.h"

#include "Shader.h"
#include "Mesh.h"
#include "PrefabMesh.h"
#include "GFXEntity.h"
#include "Texture.h"
#include "ShaderManager.h"

void GFXEntityColor::Render()
{
	shader->SetToContext();
	shader->UpdateViewProj( cam_ctrls[curr_cam]->GetViewProj() );
	shader->UpdateWorld( &world );
	mesh->Render();
}

GFXEntityColor::GFXEntityColor( Mesh* in_mesh, const Matrix& in_world )
{
	shader = ShaderManager::GetShaderColor();
	mesh = in_mesh;
	world = in_world;
}

void GFXEntitySingleColor::Render()
{
	shader->SetToContext();
	shader->UpdateViewProj( cam_ctrls[curr_cam]->GetViewProj() );
	shader->UpdateWorld( &world );
	shader->UpdateColor( &color );
	mesh->Render();
}

GFXEntitySingleColor::GFXEntitySingleColor( Mesh* in_mesh, const Matrix& in_world )
{
	shader = ShaderManager::GetShaderSingleColor();
	mesh = in_mesh;
	world = in_world;
	color = Vector();
}

void GFXEntityTexture::Render()
{
	shader->SetToContext();
	shader->UpdateViewProj( cam_ctrls[curr_cam]->GetViewProj() );
	shader->UpdateWorld( &world );
	texture->SetToContext();
	mesh->Render();
}

GFXEntityTexture::GFXEntityTexture( Texture* in_texture, const Matrix& in_world )
{
	shader = ShaderManager::GetShaderTexture();
	texture = in_texture;
	mesh = PrefabMesh::GetMesh( PrefabType::RECT );
	world = in_world;
}

void GFXEntityUI::Render()
{
	Matrix trans_mat( TRANS, x, y, 0.0f );
	Matrix rot_mat( ROT_Z, angle );
	Matrix scale_mat( SCALE, scale*(float)image->texture->width, scale*(float)image->texture->height, 1.0f );
	Matrix world = Mult( scale_mat, rot_mat, trans_mat );

	shader->SetToContext();
	shader->UpdateViewProj( cam_ctrls[CameraType_UI]->GetViewProj() );
	shader->UpdateWorld( &world );
	shader->UpdateRect( &image->rect );
	image->texture->SetToContext();
	mesh->Render();
}

GFXEntityUI::GFXEntityUI( Image* in_image )
{
	shader = ShaderManager::GetShaderUI();
	mesh = PrefabMesh::GetMesh( PrefabType::RECT );
	image = in_image;

	x = 100.0f;
	y = -100.0f;
	angle = 0.0f;
	scale = 0.25f;
}
