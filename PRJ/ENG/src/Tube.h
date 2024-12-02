#ifndef TUBE_H
#define TUBE_H

struct Tube
{
	DynamicArray<GFXEntitySingleColor*> segments;
	int num_segments;
	size_t curr_one;
	float thickness;
	float offset_z;
	float max_dist;
	float speed;


	void Update();
	void Render();

	void Init();
	void Term();

	virtual ~Tube() = default;
};

#endif // TUBE_H