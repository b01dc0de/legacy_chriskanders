#include "ENGCommon.h"

#include "GFXEntity.h"
#include "Mesh.h"
#include "PrefabMesh.h"
#include "Tube.h"

void Tube::Update()
{
	if ( segments[curr_one]->world.row_3.z > max_dist )
	{
		Matrix& prev_one = segments[( curr_one + 1 ) % num_segments]->world;
		segments[curr_one]->world =
			Matrix( SCALE, 16.0f, 9.0f, thickness ) *
			Matrix( TRANS, prev_one.row_3.x, prev_one.row_3.y, offset_z );
		curr_one = (curr_one - 1) % num_segments;
	}
	for ( size_t idx = 0; idx < segments.num; idx++ )
	{
		segments[idx]->world.row_3.z += speed * Clock::Delta();
	}
}

void Tube::Render()
{
	for ( size_t idx = 0; idx < segments.num; idx++ )
	{
		segments[idx]->Render();
	}
}

void Tube::Init()
{
	num_segments = 500;
	thickness = 2.5f;
	offset_z = 25.0f;
	max_dist = (float)num_segments * thickness + offset_z;
	curr_one = size_t(num_segments - 1);
	speed = 10.00f;
	Vector black( 0.0f, 0.0f, 0.0f );
	Vector white( 1.0f, 1.0f, 1.0f );
	for ( int idx = 0; idx < num_segments; idx++ )
	{
		Matrix segmentworld = Matrix( SCALE, 16.0f, 9.0f, thickness ) * Matrix( TRANS, 0.0f, 0.0f, (float)idx*thickness + offset_z );
		GFXEntitySingleColor* gfxsegment = new GFXEntitySingleColor( PrefabMesh::GetMesh( PrefabType::SEGMENT ), segmentworld );
		gfxsegment->color = idx % 2 == 0 ? black : white;
		segments.Add( gfxsegment );
	}
}

void Tube::Term()
{
	segments.DeleteAll();
}
