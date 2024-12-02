#include "ENGCommon.h"

#include "ENG_Win32.h"
/* Included by ENGCommon.h */

void Camera2D::Orthographic( float in_width, float in_height, float in_depth )
{
	width = in_width;
	height = in_height;
	depth = in_depth;

	viewproj.view.Identity();
	viewproj.proj.Identity();

	viewproj.proj.row_0.x = +2.0f / width;
	viewproj.proj.row_1.y = +2.0f / height;
	viewproj.view.row_2.z = -2.0f / depth;
}

Camera2D::Camera2D( float in_width, float in_height, float in_depth )
{
	Orthographic( in_width, in_height, in_depth );
}

void Camera3D::UpdateViewProj()
{
	float d = 1 / tanf( fov_y / 2.0f );

	viewproj.proj.row_0 = { 0.0f, 0.0f, 0.0f, 0.0f };
	viewproj.proj.row_1 = { 0.0f, 0.0f, 0.0f, 0.0f };
	viewproj.proj.row_2 = { 0.0f, 0.0f, 0.0f, 0.0f };
	viewproj.proj.row_3 = { 0.0f, 0.0f, 0.0f, 0.0f };
	viewproj.proj.row_0.x = d / aspect_ratio;
	viewproj.proj.row_1.y = d;
	viewproj.proj.row_2.z = -( far_dist + near_dist ) / ( far_dist - near_dist );
	viewproj.proj.row_2.w = -1.0f;
	viewproj.proj.row_3.z = ( -2.0f * far_dist * near_dist ) / ( far_dist - near_dist );

	viewproj.proj *= ndc_convert;

	viewproj.view.row_0 = { right.x, up.x, dir.x, 0.0f };
	viewproj.view.row_1 = { right.y, up.y, dir.y, 0.0f };
	viewproj.view.row_2 = { right.z, up.z, dir.z, 0.0f };

	viewproj.view.row_3.x = -Dot( pos, right );
	viewproj.view.row_3.y = -Dot( pos, up );
	viewproj.view.row_3.z = -Dot( pos, dir );
	viewproj.view.row_3.w = 1.0f;
}

void Camera3D::OrientAndPos( const Vector& in_look_at, const Vector& in_pos, const Vector& absolute_up )
{
	look_at = in_look_at;
	pos = in_pos;

	dir = -( look_at - pos );
	dir.Norm();

	right = Cross( absolute_up, dir );
	right.Norm();

	up = Cross( dir, right );
	up.Norm();

	UpdateViewProj();
}

Camera3D::Camera3D( long width, long height, const Vector& in_look_at, const Vector& in_pos, const Vector& absolute_up )
	: fov_y( 45.0f )
	, aspect_ratio( (float)width / (float)height )
	, near_dist( 1.0f )
	, far_dist( 1000.0f )
	, ndc_convert( Mult( Matrix( TRANS, Vector( 0.0f, 0.0f, 1.0f, 1.0f ) ), Matrix( SCALE, 1.0f, 1.0f, 0.5f ) ) )
{
	OrientAndPos( in_look_at, in_pos, absolute_up );
}

CameraControl* cam_ctrls[CameraType_MAX];
CameraType curr_cam = CameraType_God;

void GodCamera::ProcessInput()
{
	static const float _cam_speed = 12.0f;
	static const float _rot_speed = 2.5f;
	static const Vector y_axis( 0.0f, 1.0f, 0.0f, 0.0f );

	const float adj_cam_speed = _cam_speed * Clock::Delta();
	const float adj_rot_speed = _rot_speed * Clock::Delta();

	Matrix rot( ROT_ORIENT, camera3D.look_at - camera3D.pos, y_axis );

	Vector diff_pos( 0.0f, 0.0f, 0.0f, 0.0f );

	if ( Keyboard::GetKeyState( KEY_W ) )
	{
		diff_pos += rot.row_2 * adj_cam_speed;
	}
	if ( Keyboard::GetKeyState( KEY_S ) )
	{
		diff_pos += rot.row_2 * -adj_cam_speed;
	}

	if ( Keyboard::GetKeyState( KEY_A ) )
	{
		diff_pos += rot.row_0 * adj_cam_speed;
	}
	if ( Keyboard::GetKeyState( KEY_D ) )
	{
		diff_pos += rot.row_0 * -adj_cam_speed;
	}

	if ( Keyboard::GetKeyState( KEY_Q ) )
	{
		diff_pos += y_axis * adj_cam_speed;
	}
	if ( Keyboard::GetKeyState( KEY_E ) )
	{
		diff_pos += y_axis * -adj_cam_speed;
	}

	if ( Keyboard::GetKeyState( KEY_LEFT ) )
	{
		rot *= Matrix( ROT_Y, -adj_rot_speed );
	}
	if ( Keyboard::GetKeyState( KEY_RIGHT ) )
	{
		rot *= Matrix( ROT_Y, adj_rot_speed );
	}

	if ( Keyboard::GetKeyState( KEY_UP ) )
	{
		rot *= Matrix( ROT_AXIS, rot.row_0, -adj_rot_speed );
	}
	if ( Keyboard::GetKeyState( KEY_DOWN ) )
	{
		rot *= Matrix( ROT_AXIS, rot.row_0, adj_rot_speed );
	}

	if ( Keyboard::GetKeyState( KEY_0 ) )
	{
		rot.Rot( ROT_ORIENT, camera3D.look_at - camera3D.pos, Vector( 0.0f, 1.0f, 0.0f, 0.0f ) );
	}

	if ( diff_pos.Length() > FLT_EPSILON )
	{
		diff_pos.Norm();
	}
	diff_pos *= adj_cam_speed;

	camera3D.pos += diff_pos;

	Vector new_look_at = camera3D.pos + rot.row_2;
	Vector new_up_rot = rot.row_1;
	camera3D.OrientAndPos( new_look_at, camera3D.pos, new_up_rot );
}

void FirstPersonCamera::ProcessInput()
{
	static const float _cam_speed = 12.0f;
	static const float _rot_speed = 1.0f;
	static const Vector y_axis( 0.0f, 1.0f, 0.0f, 0.0f );

	const float adj_cam_speed = _cam_speed * Clock::Delta();
	const float adj_rot_speed = _rot_speed * Clock::Delta();

	Matrix rot( ROT_ORIENT, camera3D.look_at - camera3D.pos, y_axis );

	Vector forward( rot.row_2.x, 0.0f, rot.row_2.z );
	Vector left = Cross( y_axis, forward );

	Vector diff_pos( 0.0f, 0.0f, 0.0f, 0.0f );

	if ( Keyboard::GetKeyState( KEY_W ) )
	{
		diff_pos += forward * adj_cam_speed;
	}
	if ( Keyboard::GetKeyState( KEY_S ) )
	{
		diff_pos += forward * -adj_cam_speed;
	}

	if ( Keyboard::GetKeyState( KEY_A ) )
	{
		diff_pos += left * adj_cam_speed;
	}
	if ( Keyboard::GetKeyState( KEY_D ) )
	{
		diff_pos += left * -adj_cam_speed;
	}

	if ( CurrActive && !Mouse::SetPos && ( Mouse::DeltaX || Mouse::DeltaY ) )
	{
		if ( Mouse::DeltaX != 0 )
		{
			rot *= Matrix( ROT_Y, adj_rot_speed*(float)Mouse::DeltaX );
		}
		if ( Mouse::DeltaY != 0 )
		{
			rot *= Matrix( ROT_AXIS, rot.row_0, adj_rot_speed*(float)Mouse::DeltaY );
		}
	}

	if ( diff_pos.Length() > FLT_EPSILON )
	{
		diff_pos.Norm();
	}
	diff_pos *= adj_cam_speed;

	camera3D.pos += diff_pos;

	Vector new_look_at = camera3D.pos + rot.row_2;
	Vector new_up_rot = rot.row_1;
	camera3D.OrientAndPos( new_look_at, camera3D.pos, new_up_rot );
}

void MouseCamera::ProcessInput()
{
	static const float CircleDiameter = 200.0f;
	static const float CircleDiameterSqrt = sqrtf( CircleDiameter );
	static const float ClampYTop = PI / 3.0f;
	static const float ClampYBottom = -PI / 3.0f;
	static const float CameraSpeed = 0.01f;

	static float XZAngle = 0;
	static float YAngle = ClampYTop;

	static const Vector new_look_at = Vector( 0.0f, 5.0f, 0.0f );
	static const Vector new_up_rot = Vector( 0.0f, 1.0f, 0.0f );

	if ( CurrActive && !Mouse::SetPos && ( Mouse::DeltaX || Mouse::DeltaY ) )
	{
		if ( Mouse::DeltaX != 0 )
		{
			XZAngle += (float)Mouse::DeltaX * CameraSpeed;
		}
		if ( Mouse::DeltaY != 0 )
		{
			YAngle = Clamp( YAngle + ( (float)Mouse::DeltaY*CameraSpeed ), ClampYBottom, ClampYTop );
		}

		Vector new_pos = Vector( sinf( XZAngle )*CircleDiameterSqrt, sinf( YAngle )*CircleDiameterSqrt, -cosf( XZAngle )*CircleDiameterSqrt ); // Position on circle

		camera3D.OrientAndPos( new_look_at, new_pos, new_up_rot );
	}
}

void UICamera::ProcessInput()
{

}

