#ifndef CKA_PARSER_H
#define CKA_PARSER_H

#if CKA_COMPILE_OFF
struct CSVEntry
{
	DynamicArray<CKAString> Values;
};

struct ParsedCSVData
{
	bool bFieldsUsed;
	DynamicArray<CKAString> Fields;
	DynamicArray<CSVEntry> Entries;
};

struct CSVParser
{
	static ParsedCSVData* ParseCSVFile(const CKAString& Filename);
};
#endif // CKA_COMPILE_OFF

#endif // CKA_PARSER_H
