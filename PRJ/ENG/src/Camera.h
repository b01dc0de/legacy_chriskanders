#ifndef CAMERA_H
#define CAMERA_H

struct ViewProj
{
	Matrix view;
	Matrix proj;
};

struct Camera
{
	ViewProj viewproj;
};

struct Camera2D : Camera
{
	float width;
	float height;
	float depth;

	void Orthographic( float in_width, float in_height, float in_depth = 1.0f );
	Camera2D( float in_width, float in_height, float in_depth );
};

struct Camera3D : Camera
{
	Vector up;
	Vector dir;
	Vector right;
	Vector pos;
	Vector look_at;

	float fov_y;
	float aspect_ratio;
	float near_dist;
	float far_dist;

	Matrix ndc_convert;

	void UpdateViewProj();
	void OrientAndPos( const Vector& in_look_at, const Vector& in_pos, const Vector& absolute_up = Vector( 0.0f, 1.0f, 0.0f ) );
	Camera3D( long width, long height, const Vector& in_look_at, const Vector& in_pos, const Vector& absolute_up = Vector( 0.0f, 1.0f, 0.0f ) );
};

enum CameraType
{
	CameraType_God = 0,
	CameraType_FirstPerson = 1,
	CameraType_Mouse = 2,
	CameraType_UI = 3,
	CameraType_MAX = 4,
};

struct CameraControl
{
	virtual ViewProj* GetViewProj() = 0;
	virtual void ProcessInput() = 0;
	virtual ~CameraControl() {}
};

extern CameraControl* cam_ctrls[];
extern CameraType curr_cam;

struct GodCamera : CameraControl
{
	Camera3D camera3D;

	virtual void ProcessInput() override;
	virtual ViewProj* GetViewProj() override { return &camera3D.viewproj; }

	GodCamera( long width, long height, const Vector& in_look_at, const Vector& in_pos, const Vector& absolute_up = Vector( 0.0f, 1.0f, 0.0f, 0.0f ) )
		: camera3D( width, height, in_look_at, in_pos, absolute_up )
	{}
};

struct FirstPersonCamera : CameraControl
{
	Camera3D camera3D;

	virtual void ProcessInput() override;
	virtual ViewProj* GetViewProj() override { return &camera3D.viewproj; }

	FirstPersonCamera( long width, long height, const Vector& in_look_at, const Vector& in_pos, const Vector& absolute_up = Vector( 0.0f, 1.0f, 0.0f, 0.0f ) )
		: camera3D( width, height, in_look_at, in_pos, absolute_up )
	{}
};

struct MouseCamera : CameraControl
{
	Camera3D camera3D;

	virtual void ProcessInput() override;
	virtual ViewProj* GetViewProj() override { return &camera3D.viewproj; }

	MouseCamera( long width, long height, const Vector& in_look_at, const Vector& in_pos, const Vector& absolute_up = Vector( 0.0f, 1.0f, 0.0f, 0.0f ) )
		: camera3D( width, height, in_look_at, in_pos, absolute_up )
	{}
};

struct UICamera : CameraControl
{
	Camera2D camera2D;

	virtual void ProcessInput() override;
	virtual ViewProj* GetViewProj() override { return &camera2D.viewproj; }

	UICamera( float width, float height, float depth )
		: camera2D( width, height, depth )
	{}
};

#endif // CAMERA_H