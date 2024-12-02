#include "Common.h"

#include "CKAParser.h"

#if CKA_COMPILE_OFF
ParsedCSVData* ParseCSVFile(const CKAString& Filename)
{
	CKATextFile csv_file(Filename);
	return nullptr;
}
#endif // CKA_COMPILE_OFF
