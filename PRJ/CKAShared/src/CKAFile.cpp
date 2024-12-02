#include "Common.h"

// CKA_TODO: Is this my practice?
 #include "CKAFile.h"

CKATextFile::CKATextFile(const CKAString& in_filename)
	: filename(in_filename)
	, contents(nullptr)
{
	FILE* text_file = nullptr;
	fopen_s( &text_file, filename.str, "rt" );
	
	if (!text_file)
	{
		return;
	}
	assert(text_file);

	file_size_bytes = GetFileSize(text_file);

	contents.str = new char[(size_t)file_size_bytes];
	fread(contents.str, sizeof(*contents.str), (size_t)file_size_bytes, text_file);
}

long GetFileSize(FILE *in_file)
{
	assert(in_file);

	long cached_file_pos = ftell(in_file);
	long file_size_bytes = 0;
	fseek(in_file, 0, SEEK_END);
	file_size_bytes = ftell(in_file);
	fseek(in_file, cached_file_pos, SEEK_SET);

	return file_size_bytes;
}

