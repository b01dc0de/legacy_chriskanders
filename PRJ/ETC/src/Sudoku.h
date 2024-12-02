#ifndef SUDOKU_H
#define SUDOKU_H

extern constexpr uint SudokuStride = 9u;
extern constexpr uint SudokuBlkLength = 3u; // CKA_TODO: Generalize this, not sure how to do that while still being a constexpr
extern constexpr uint SudokuGridLength = SudokuStride * SudokuStride;
static_assert((SudokuBlkLength * SudokuBlkLength) == SudokuStride, "Only support square numbers for SudokuStride right now :(");
static_assert(SudokuStride == 9u, "We only support 9x9 grids right now");
extern constexpr uint SudokuFirstDiv = SudokuBlkLength - 1;
extern constexpr uint SudokuSecondDiv = (SudokuBlkLength * 2) - 1;

extern constexpr uint SudokuMinValue = 0u;
extern constexpr uint SudokuMaxValue = SudokuStride - 1;

extern constexpr uint SudokuGodNumber = 17;
static_assert(SudokuStride <= sizeof(SudokuStride) * 8, "Type for SudokuStride is not big enough");

/*	EXAMPLE FINISHED GRID
		1, 2, 3, | 4, 5, 6, | 7, 8, 9,
		4, 5, 6, | 7, 8, 9, | 1, 2, 3,
		7, 8, 9, | 1, 2, 3, | 4, 5, 6,
		---------+----------+--------
		5, 6, 7, | 8, 9, 1, | 2, 3, 4,
		8, 9, 1, | 2, 3, 4, | 5, 6, 7,
		2, 3, 4, | 5, 6, 7, | 8, 9, 1,
		---------+----------+--------
		9, 1, 2, | 3, 4, 5, | 6, 7, 8,
		6, 7, 8, | 9, 1, 2, | 3, 4, 5,
		3, 4, 5, | 6, 7, 8, | 9, 1, 2,
*/
/*	CELL IDS
		 0,  1,  2, |  3,  4,  5, |  6,  7,  8,
		 9, 10, 11, | 12, 13, 14, | 15, 16, 17,
		18, 19, 20, | 21, 22, 23, | 24, 25, 26,
		------------+-------------+-----------
		27, 28, 29, | 30, 31, 32, | 33, 34, 35,
		36, 37, 38, | 39, 40, 41, | 42, 43, 44,
		45, 46, 47, | 48, 49, 50, | 51, 52, 53,
		------------+-------------+-----------
		54, 55, 56, | 57, 58, 59, | 60, 61, 62,
		63, 64, 65, | 66, 67, 68, | 69, 70, 71,
		72, 73, 74, | 75, 76, 77, | 78, 79, 80,
*/

extern uint TestFullGrid[SudokuGridLength];
extern uint TestEmptyGrid[SudokuGridLength];

struct PosVals
{
	uint pos;

	bool OnlyOnePos();
	uint GetPosVal();
	bool IsPossible(uint val); // val E [0, 8]
	bool IsValid();
	void Add(uint val); // val E [0, 8]
	void Remove(uint val); // val E [0, 8]

	void Print();

	PosVals();

	operator uint()
	{
		CKA_ASSERT(OnlyOnePos());
		return GetPosVal();
	}
};

struct SudokuGrid
{
	uint grid[SudokuGridLength];

	inline uint& GridVal(uint x, uint y);
	inline uint& GridVal(uint Cell);

	uint GetRow(uint Cell);
	uint GetCol(uint Cell);
	uint GetBlk(uint Cell);

	PosVals GetPosVals(uint Cell);
	void GetPosValsGrid(PosVals* OutGrid);

	uint GetRandomFreeCell();
	uint GetRandomPosVal(uint Cell);

	bool IsRowValid(uint y);
	bool IsColValid(uint x);
	bool IsBlkValid(uint b);

	bool IsValValidRow(uint Cell, uint Val);
	bool IsValValidCol(uint Cell, uint Val);
	bool IsValValidBlk(uint Cell, uint Val);

	bool IsValid();
	bool IsValValid(uint Cell, uint Val);

	bool IsSolved();

	void Generate();
	void Solve();
	void SolveHelper();

	void Print();

	void InitFromPrefab(uint* Prefab, uint PrefabSize);
	void Test();

	SudokuGrid();
};

#endif // SUDOKU_H