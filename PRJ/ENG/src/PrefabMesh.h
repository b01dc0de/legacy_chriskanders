#ifndef PREFABMESH_H
#define PREFABMESH_H

enum class PrefabType
{
	UNIT_CUBE,
	UNIT_FLOOR,
	RECT,
	SEGMENT,
	MAX
};

struct Mesh;

namespace PrefabMesh
{
	Mesh* GetMesh( PrefabType type );
	void Init();
	void Term();
}

#endif // PREFABMESH_H