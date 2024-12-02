#include "ENGCommon.h"

#include "Mesh.h"

Mesh* unit_cube = nullptr;
Mesh* unit_floor = nullptr;

void Mesh::InitBuffers()
{
	inited = true;
	D3D11_BUFFER_DESC buffer_desc = {};
	D3D11_SUBRESOURCE_DATA init_data = {};
	// vertex_buffer
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.ByteWidth = sizeof( Vertex ) * num_verts;
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	init_data.pSysMem = verts;
	Verify( global_device->CreateBuffer( &buffer_desc, &init_data, &vertex_buffer ) );

	// index buffer
	buffer_desc = {};
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.ByteWidth = sizeof( Triangle ) * num_prims;
	buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	init_data.pSysMem = prims;
	Verify( global_device->CreateBuffer( &buffer_desc, &init_data, &index_buffer ) );
}

void Mesh::Render()
{
	assert( inited );
	uint stride = sizeof( Vertex );
	uint offset = 0;
	global_context->IASetVertexBuffers( 0, 1, &vertex_buffer, &stride, &offset );
	global_context->IASetIndexBuffer( index_buffer, DXGI_FORMAT_R32_UINT, 0 );
	global_context->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	global_context->DrawIndexed( (UINT)num_prims * 3, 0u, 0u );
}

Mesh::Mesh( int in_num_verts, int in_num_prims )
	: inited( false )
	, num_verts(in_num_verts)
	, num_prims(in_num_prims)
	, verts(new Vertex[(size_t)in_num_verts])
	, prims(new Triangle[(size_t)in_num_prims])
{
}

Mesh::Mesh( int in_num_verts, int in_num_prims, Vertex* in_verts, Triangle* in_prims )
	: inited( false )
	, num_verts( in_num_verts )
	, num_prims( in_num_prims )
	, verts( in_verts )
	, prims( in_prims)
{
	InitBuffers();
}

Mesh::~Mesh()
{
	delete[] verts;
	delete[] prims;
}
