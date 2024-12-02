#ifndef MESH_H
#define MESH_H

struct Vertex
{
	V4 pos;
	float U;
	float V;
	V4 col;
};

struct Triangle
{
	uint p0;
	uint p1;
	uint p2;
};

struct Mesh
{
	bool inited;

	int num_verts;
	int num_prims;

	Vertex* verts;
	Triangle* prims;

	DXPtr<ID3D11Buffer> vertex_buffer;
	DXPtr<ID3D11Buffer> index_buffer;

	void InitBuffers();
	void Render();

	Mesh( int in_num_verts, int in_num_prims );
	Mesh( int in_num_verts, int in_num_prims, Vertex* in_verts, Triangle* in_prims );
	~Mesh();
};

#endif // MESH_H