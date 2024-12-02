#pragma once

/*
	MNIST
		FeaturesDict({
			'image': Image(shape=(28, 28, 1), dtype=uint8),
			'label': ClassLabel(shape=(), dtype=int64, num_classes=10),
		})
*/

#if CKA_COMPILE_OFF

/* 
	Hello world of machine learning
	Processes a list of grayscale images of handwritten digits
	Can successfully determine which digit an image contains
*/
struct Digit
{
	static constexpr int32 ImageLength = 28;
	static constexpr int32 ImageSize = ImageLength * ImageLength;
	static constexpr int32 NotSetValue = -1;

	float Image[ImageSize];
	int32 Guess = NotSetValue;
	int32 Answer = NotSetValue;

	void Init();
};

void Digit::Init()
{
	Guess = -1;
	Answer = -1;
	for (int32 i = 0; i < ImageSize; i++)
	{
		Image[i] = 0.0f;
	}
}

#endif // CKA_COMPILE_OFF
