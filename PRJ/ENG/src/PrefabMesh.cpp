#include "ENGCommon.h"

#include "Mesh.h"
#include "PrefabMesh.h"

namespace PrefabMesh
{
	Mesh* unit_cube;
	Mesh* unit_floor;
	Mesh* rect;
	Mesh* segment;
}

Mesh* PrefabMesh::GetMesh( PrefabType type )
{
	Mesh* mesh = nullptr;
	switch ( type )
	{
		case PrefabType::UNIT_CUBE:
		{
			mesh = unit_cube;
		} break;
		case PrefabType::UNIT_FLOOR:
		{
			mesh = unit_floor;
		} break;
		case PrefabType::RECT:
		{
			mesh = rect;
		} break;
		case PrefabType::SEGMENT:
		{
			mesh = segment;
		} break;
		case PrefabType::MAX:
		default:
		{
			assert( 0 );
		} break;
	}
	return mesh;
}
void PrefabMesh::Init()
{
	{ // UNIT_CUBE
		int num_verts = 24;
		int num_prims = 12;

		Vertex* verts = new Vertex[(size_t)num_verts];
		Triangle* prims = new Triangle[(size_t)num_prims];

		// Setting up per-face
		// Forward
		uint v_ind = 0;
		uint t_ind = 0;
		verts[v_ind + 0] = { Vector{ 0.5f, 0.5f, 0.5f }, 1.0f, 0.0f, GetRandomColor() };
		verts[v_ind + 1] = { Vector{ -0.5f, 0.5f, 0.5f }, 0.0f, 0.0f, GetRandomColor() };
		verts[v_ind + 2] = { Vector{ -0.5f, -0.5f, 0.5f }, 0.0f, 1.0f, GetRandomColor() };
		verts[v_ind + 3] = { Vector{ 0.5f, -0.5f, 0.5f }, 1.0f, 1.0f, GetRandomColor() };
		prims[t_ind + 0] = { v_ind, v_ind + 1, v_ind + 2 };
		prims[t_ind + 1] = { v_ind, v_ind + 2, v_ind + 3 };

		// Back
		v_ind += 4;
		t_ind += 2;
		verts[v_ind + 0] = { Vector( 0.5f, 0.5f, -0.5f ), 0.0f, 0.0f, GetRandomColor() };
		verts[v_ind + 1] = { Vector( -0.5f, 0.5f, -0.5f ), 1.0f, 0.0f, GetRandomColor() };
		verts[v_ind + 2] = { Vector( -0.5f, -0.5f, -0.5f ), 1.0f, 1.0f, GetRandomColor() };
		verts[v_ind + 3] = { Vector( 0.5f, -0.5f, -0.5f ), 0.0f, 1.0f, GetRandomColor() };
		prims[t_ind + 0] = { v_ind + 2, v_ind + 1, v_ind };
		prims[t_ind + 1] = { v_ind + 3, v_ind + 2, v_ind };

		// Left
		v_ind += 4;
		t_ind += 2;
		verts[v_ind + 0] = { Vector( 0.5f, 0.5f, -0.5f ), 1.0f, 0.0f, GetRandomColor() };
		verts[v_ind + 1] = { Vector( 0.5f, 0.5f, 0.5f ), 0.0f, 0.0f, GetRandomColor() };
		verts[v_ind + 2] = { Vector( 0.5f, -0.5f, 0.5f ), 0.0f, 1.0f, GetRandomColor() };
		verts[v_ind + 3] = { Vector( 0.5f, -0.5f, -0.5f ), 1.0f, 1.0f, GetRandomColor() };
		prims[t_ind + 0] = { v_ind, v_ind + 1, v_ind + 2 };
		prims[t_ind + 1] = { v_ind, v_ind + 2, v_ind + 3 };

		// Right
		v_ind += 4;
		t_ind += 2;
		verts[v_ind + 0] = { Vector( -0.5f, 0.5f, 0.5f ), 1.0f, 0.0f, GetRandomColor() };
		verts[v_ind + 1] = { Vector( -0.5f, 0.5f, -0.5f ), 0.0f, 0.0f, GetRandomColor() };
		verts[v_ind + 2] = { Vector( -0.5f, -0.5f, -0.5f ), 0.0f, 1.0f, GetRandomColor() };
		verts[v_ind + 3] = { Vector( -0.5f, -0.5f, 0.5f ), 1.0f, 1.0f, GetRandomColor() };
		prims[t_ind + 0] = { v_ind, v_ind + 1, v_ind + 2 };
		prims[t_ind + 1] = { v_ind, v_ind + 2, v_ind + 3 };

		// Top
		v_ind += 4;
		t_ind += 2;
		verts[v_ind + 0] = { Vector( 0.5f, 0.5f, -0.5f ), 1.0f, 0.0f, GetRandomColor() };
		verts[v_ind + 1] = { Vector( -0.5f, 0.5f, -0.5f ), 0.0f, 0.0f, GetRandomColor() };
		verts[v_ind + 2] = { Vector( -0.5f, 0.5f, 0.5f ), 0.0f, 1.0f, GetRandomColor() };
		verts[v_ind + 3] = { Vector( 0.5f, 0.5f, 0.5f ), 1.0f, 1.0f, GetRandomColor() };
		prims[t_ind + 0] = { v_ind, v_ind + 1, v_ind + 2 };
		prims[t_ind + 1] = { v_ind, v_ind + 2, v_ind + 3 };

		// Bottom
		v_ind += 4;
		t_ind += 2;
		verts[v_ind + 0] = { Vector( 0.5f, -0.5f, 0.5f ), 1.0f, 0.0f, GetRandomColor() };
		verts[v_ind + 1] = { Vector( -0.5f, -0.5f, 0.5f ), 0.0f, 0.0f, GetRandomColor() };
		verts[v_ind + 2] = { Vector( -0.5f, -0.5f, -0.5f ), 0.0f, 1.0f, GetRandomColor() };
		verts[v_ind + 3] = { Vector( 0.5f, -0.5f, -0.5f ), 1.0f, 1.0f, GetRandomColor() };
		prims[t_ind + 0] = { v_ind, v_ind + 1, v_ind + 2 };
		prims[t_ind + 1] = { v_ind, v_ind + 2, v_ind + 3 };

		unit_cube = new Mesh( num_verts, num_prims, verts, prims );
	}

	{ // UNIT_FLOOR
		int num_verts = 4;
		int num_prims = 4;

		Vertex* verts = new Vertex[(size_t)num_verts];
		Triangle* prims = new Triangle[(size_t)num_prims];

		verts[0] = { Vector( 1.0f, 0.0f, -1.0f ), 0.0f, 1.0f, GetRandomColor() };
		verts[1] = { Vector( -1.0f, 0.0f, -1.0f ), 1.0f, 1.0f, GetRandomColor() };
		verts[2] = { Vector( -1.0f, 0.0f, 1.0f ), 1.0f, 0.0f, GetRandomColor() };
		verts[3] = { Vector( 1.0f, 0.0f, 1.0f ), 0.0f, 0.0f, GetRandomColor() };

		prims[0] = { 0, 1, 2 };
		prims[1] = { 0, 2, 3 };
		prims[2] = { 0, 2, 1 };
		prims[3] = { 0, 3, 2 };

		unit_floor = new Mesh( num_verts, num_prims, verts, prims );
	}

	{ // RECT
		int num_verts = 4;
		int num_prims = 4;

		Vertex* verts = new Vertex[(size_t)num_verts];
		Triangle* prims = new Triangle[(size_t)num_verts];

		verts[0] = { Vector( +0.5f, +0.5f, 0.0f ), 0.0f, 0.0f, GetRandomColor() };
		verts[1] = { Vector( -0.5f, +0.5f, 0.0f ), 1.0f, 0.0f, GetRandomColor() };
		verts[2] = { Vector( +0.5f, -0.5f, 0.0f ), 0.0f, 1.0f, GetRandomColor() };
		verts[3] = { Vector( -0.5f, -0.5f, 0.0f ), 1.0f, 1.0f, GetRandomColor() };

		prims[0] = { 0, 2, 3 };
		prims[1] = { 0, 3, 1 };
		prims[2] = { 0, 3, 2 };
		prims[3] = { 0, 1, 3 };
		
		rect = new Mesh( num_verts, num_prims, verts, prims );
	}

	{ // SEGMENT
		int num_verts = 16;
		int num_prims = 16;

		Vertex* verts = new Vertex[(size_t)num_verts];
		Triangle* prims = new Triangle[(size_t)num_prims];

		// Setting up per-face

		// Left
		uint v_ind = 0;
		uint t_ind = 0;
		verts[v_ind + 0] = { Vector( 0.5f, 0.5f, -0.5f ), 1.0f, 0.0f, GetRandomColor() };
		verts[v_ind + 1] = { Vector( 0.5f, 0.5f, 0.5f ), 0.0f, 0.0f, GetRandomColor() };
		verts[v_ind + 2] = { Vector( 0.5f, -0.5f, 0.5f ), 0.0f, 1.0f, GetRandomColor() };
		verts[v_ind + 3] = { Vector( 0.5f, -0.5f, -0.5f ), 1.0f, 1.0f, GetRandomColor() };
		prims[t_ind + 0] = { v_ind, v_ind + 1, v_ind + 2 };
		prims[t_ind + 1] = { v_ind, v_ind + 2, v_ind + 3 };
		prims[t_ind + 2] = { v_ind, v_ind + 2, v_ind + 1 };
		prims[t_ind + 3] = { v_ind, v_ind + 3, v_ind + 2 };

		// Right
		v_ind += 4;
		t_ind += 4;
		verts[v_ind + 0] = { Vector( -0.5f, 0.5f, 0.5f ), 1.0f, 0.0f, GetRandomColor() };
		verts[v_ind + 1] = { Vector( -0.5f, 0.5f, -0.5f ), 0.0f, 0.0f, GetRandomColor() };
		verts[v_ind + 2] = { Vector( -0.5f, -0.5f, -0.5f ), 0.0f, 1.0f, GetRandomColor() };
		verts[v_ind + 3] = { Vector( -0.5f, -0.5f, 0.5f ), 1.0f, 1.0f, GetRandomColor() };
		prims[t_ind + 0] = { v_ind, v_ind + 1, v_ind + 2 };
		prims[t_ind + 1] = { v_ind, v_ind + 2, v_ind + 3 };
		prims[t_ind + 2] = { v_ind, v_ind + 2, v_ind + 1 };
		prims[t_ind + 3] = { v_ind, v_ind + 3, v_ind + 2 };

		// Top
		v_ind += 4;
		t_ind += 4;
		verts[v_ind + 0] = { Vector( 0.5f, 0.5f, -0.5f ), 1.0f, 0.0f, GetRandomColor() };
		verts[v_ind + 1] = { Vector( -0.5f, 0.5f, -0.5f ), 0.0f, 0.0f, GetRandomColor() };
		verts[v_ind + 2] = { Vector( -0.5f, 0.5f, 0.5f ), 0.0f, 1.0f, GetRandomColor() };
		verts[v_ind + 3] = { Vector( 0.5f, 0.5f, 0.5f ), 1.0f, 1.0f, GetRandomColor() };
		prims[t_ind + 0] = { v_ind, v_ind + 1, v_ind + 2 };
		prims[t_ind + 1] = { v_ind, v_ind + 2, v_ind + 3 };
		prims[t_ind + 2] = { v_ind, v_ind + 2, v_ind + 1 };
		prims[t_ind + 3] = { v_ind, v_ind + 3, v_ind + 2 };

		// Bottom
		v_ind += 4;
		t_ind += 4;
		verts[v_ind + 0] = { Vector( 0.5f, -0.5f, 0.5f ), 1.0f, 0.0f, GetRandomColor() };
		verts[v_ind + 1] = { Vector( -0.5f, -0.5f, 0.5f ), 0.0f, 0.0f, GetRandomColor() };
		verts[v_ind + 2] = { Vector( -0.5f, -0.5f, -0.5f ), 0.0f, 1.0f, GetRandomColor() };
		verts[v_ind + 3] = { Vector( 0.5f, -0.5f, -0.5f ), 1.0f, 1.0f, GetRandomColor() };
		prims[t_ind + 0] = { v_ind, v_ind + 1, v_ind + 2 };
		prims[t_ind + 1] = { v_ind, v_ind + 2, v_ind + 3 };
		prims[t_ind + 2] = { v_ind, v_ind + 2, v_ind + 1 };
		prims[t_ind + 3] = { v_ind, v_ind + 3, v_ind + 2 };

		segment = new Mesh( num_verts, num_prims, verts, prims );
	}
}
void PrefabMesh::Term()
{
	delete unit_cube;
	delete unit_floor;
	delete rect;
	delete segment;
}
