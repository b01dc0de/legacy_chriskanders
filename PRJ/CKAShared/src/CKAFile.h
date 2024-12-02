#ifndef CKAFILE_H
#define CKAFILE_H

struct CKATextFile
{
	long file_size_bytes;
	CKAString filename;
	CKAString contents;
	bool bValid;

	CKATextFile(const CKAString& in_filename);
};

long GetFileSize(FILE* in_file);

#endif // CKAFILE_H
