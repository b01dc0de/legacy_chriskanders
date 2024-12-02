#include "CKAShared/src/Common.h"

#include "Sudoku.h"

uint TestFullGrid[SudokuGridLength] =
{
	1, 2, 3, 4, 5, 6, 7, 8, 9,
	4, 5, 6, 7, 8, 9, 1, 2, 3,
	7, 8, 9, 1, 2, 3, 4, 5, 6,
	5, 6, 7, 8, 9, 1, 2, 3, 4,
	8, 9, 1, 2, 3, 4, 5, 6, 7,
	2, 3, 4, 5, 6, 7, 8, 9, 1,
	9, 1, 2, 3, 4, 5, 6, 7, 8,
	6, 7, 8, 9, 1, 2, 3, 4, 5,
	3, 4, 5, 6, 7, 8, 9, 1, 2,
};
uint TestEmptyGrid[SudokuGridLength] =
{
	0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0,
};

uint TestPartialGrid[SudokuGridLength] =
{
	5, 3, 0, 0, 7, 0, 0, 0, 0,
	6, 0, 0, 1, 9, 5, 0, 0, 0,
	0, 9, 8, 0, 0, 0, 0, 6, 0,
	8, 0, 0, 0, 6, 0, 0, 0, 3,
	4, 0, 0, 8, 0, 3, 0, 0, 1,
	7, 0, 0, 0, 2, 0, 0, 0, 6,
	0, 6, 0, 0, 0, 0, 2, 8, 0,
	0, 0, 0, 4, 1, 9, 0, 0, 5,
	0, 0, 0, 0, 8, 0, 0, 7, 9,
};
uint TestPartialGridSolution[SudokuGridLength] =
{
	5, 3, 4, 6, 7, 8, 9, 1, 2,
	6, 7, 2, 1, 9, 5, 3, 4, 8,
	1, 9, 8, 3, 4, 2, 5, 6, 7,
	8, 5, 9, 7, 6, 1, 4, 2, 3,
	4, 2, 6, 8, 5, 3, 7, 9, 1,
	7, 1, 3, 9, 2, 4, 8, 5, 6,
	9, 6, 1, 5, 3, 7, 2, 8, 4,
	2, 8, 7, 4, 1, 9, 6, 3, 5,
	3, 4, 5, 2, 8, 6, 1, 7, 9,
};

bool PosVals::OnlyOnePos()
{
	// TODO: speed up
	uint count = 0;
	for (uint idx = 0; idx < SudokuStride; idx++)
	{
		count += IsPossible(idx) ? 1 : 0;
	}
	return count == 1;
}

uint PosVals::GetPosVal()
{
	CKA_ASSERT(OnlyOnePos());

	uint Result = 0;

	bool bUseSwitch = true;
	if (bUseSwitch)
	{
		switch (pos)
		{
		case 1:
			Result = 1;
		case 2:
			Result = 2;
		case 4:
			Result = 3;
		case 8:
			Result = 4;
		case 16:
			Result = 5;
		case 32:
			Result = 6;
		case 64:
			Result = 7;
		case 128:
			Result = 8;
		case 264:
			Result = 9;
		case 0:
			CKA_ASSERT(false);
		default:
			CKA_ASSERT(false);
		}
	}
	else
	{
		float LogResult = log2f((float)pos);
		uint Val = (uint)LogResult;
		CKA_ASSERT(LogResult == (float)Val);
		return Result;
	}

	CKA_ASSERT(Result != 0);

	return Result;
}

bool PosVals::IsPossible(uint val) // val E [0, 8]
{
	CKA_ASSERT(val < SudokuStride);
	return pos & (1 << val);
}

bool PosVals::IsValid()
{
	return pos != 0;
}

void PosVals::Add(uint val) // val E [0, 8]
{
	CKA_ASSERT(!IsPossible(val));
	pos |= 1 << val;
}

void PosVals::Remove(uint val) // val E [0, 8]
{
	CKA_ASSERT(IsPossible(val));
	pos &= ~(1 << val);
}

void PosVals::Print()
{
	uint dig = pos;
	for (uint idx = 0; idx < SudokuStride; idx++)
	{
		if (dig & 1)
		{
			Outf("%u", idx + 1u);
		}
		else
		{
			Outf("-");
		}

		dig = dig >> 1;
	}
	Outf("\n");
}

PosVals::PosVals()
{
	pos = 0;
	for (uint idx = 0; idx < SudokuStride; idx++)
	{
		pos |= 1 << idx;
	}
}

inline uint& SudokuGrid::GridVal(uint x, uint y)
{
	return grid[y * SudokuStride + x];
}

inline uint& SudokuGrid::GridVal(uint Cell)
{
	return grid[Cell];
}

uint SudokuGrid::GetRow(uint Cell)
{
	CKA_ASSERT(Cell < SudokuGridLength);
	return Cell / SudokuStride;
}

uint SudokuGrid::GetCol(uint Cell)
{
	CKA_ASSERT(Cell < SudokuGridLength);
	return Cell % SudokuStride;
}

uint SudokuGrid::GetBlk(uint Cell)
{
	CKA_ASSERT(Cell < SudokuGridLength);
	return (GetRow(Cell) / SudokuBlkLength * SudokuBlkLength ) + (GetCol(Cell) / SudokuBlkLength);
}

PosVals SudokuGrid::GetPosVals(uint Cell)
{
	PosVals pos_vals;
	for (uint val = 0; val < SudokuStride; val++)
	{
		if (!IsValValid(Cell, val))
		{
			pos_vals.Remove(val);
		}
	}
	return pos_vals;
}

void SudokuGrid::GetPosValsGrid(PosVals* OutGrid)
{
	for (uint i = 0; i < SudokuGridLength; i++)
	{
		OutGrid[i] = GetPosVals(i);
	}
}

uint SudokuGrid::GetRandomFreeCell()
{
	uint rand_cell;
	do
	{
		rand_cell = CKARand::WithinRangeInc(0u, SudokuGridLength);
	} while (GridVal(rand_cell) != 0);

	CKA_ASSERT(GridVal(rand_cell) == 0);
	return rand_cell;
}

uint SudokuGrid::GetRandomPosVal(uint Cell)
{
	CKA_ASSERT(GetPosVals(Cell).IsValid());

	uint rand_pos_val;
	do
	{
		rand_pos_val = CKARand::WithinRangeInc(SudokuMinValue, SudokuMaxValue);
	} while (!GetPosVals(Cell).IsPossible(rand_pos_val));
	// CKA_TODO: Do we want to add 1 here or have that be the caller's responsibility?
	return rand_pos_val + 1;
}

bool SudokuGrid::IsRowValid(uint y)
{
	PosVals ps_x;
	for (uint x = 0; x < SudokuStride; x++)
	{
		uint val = GridVal(x, y);
		if (val != 0)
		{
			val--; // [1, 9] -> [0, 8]
			if (ps_x.IsPossible(val))
			{
				ps_x.Remove(val);
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

bool SudokuGrid::IsColValid(uint x)
{
	PosVals ps_y;
	for (uint y = 0; y < SudokuStride; y++)
	{
		uint val = GridVal(x, y);
		if (val != 0)
		{
			val--; // [1, 9] -> [0, 8]
			if (ps_y.IsPossible(val))
			{
				ps_y.Remove(val);
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

bool SudokuGrid::IsBlkValid(uint b)
{
	PosVals ps_b;
	for (uint i = 0; i < SudokuStride; i++)
	{
		uint val = GridVal((b / 3 * 3) + (i / 3), (b % 3 * 3) + (i % 3));
		if (val != 0)
		{
			val--; // [1, 9] -> [0, 8]
			if (ps_b.IsPossible(val))
			{
				ps_b.Remove(val);
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

bool SudokuGrid::IsValValidRow(uint Cell, uint Val)
{
	CKA_ASSERT(GridVal(Cell) == 0);

	uint RowStart = GetRow(Cell) * SudokuStride;
	for (uint i = 0; i < SudokuStride; i++)
	{
		if (Val == GridVal(RowStart + i))
		{
			return false;
		}
	}

	return true;
}

bool SudokuGrid::IsValValidCol(uint Cell, uint Val)
{
	CKA_ASSERT(GridVal(Cell) == 0);

	uint ColStart = GetCol(Cell);
	for (uint i = 0; i < SudokuStride; i++)
	{
		if (Val == GridVal(ColStart + (i * SudokuStride)))
		{
			return false;
		}
	}

	return true;
}

bool SudokuGrid::IsValValidBlk(uint Cell, uint Val)
{
	CKA_ASSERT(GridVal(Cell) == 0);

	uint BlkNum = GetBlk(Cell);
	uint Row = BlkNum / SudokuBlkLength * SudokuBlkLength;
	uint Col = BlkNum % SudokuBlkLength * SudokuBlkLength;
	uint BlkStart = Row * SudokuStride + Col;
	for (uint i = 0; i < SudokuStride; i++)
	{
		uint CurrCell = BlkStart
			+ (i / SudokuBlkLength * SudokuBlkLength)
			+ (i % SudokuBlkLength);
		if (Val == GridVal(CurrCell))
		{
			return false;
		}
	}

	return true;
}

bool SudokuGrid::IsValid()
{
	for (uint i = 0; i < SudokuStride; i++)
	{
		if (!IsRowValid(i) || !IsColValid(i) || !IsBlkValid(i))
		{
			return false;
		}
	}
	return true;
}

bool SudokuGrid::IsValValid(uint Cell, uint Val)
{
	CKA_ASSERT(GridVal(Cell) == 0);

	return IsValValidRow(Cell, Val)
		&& IsValValidCol(Cell, Val)
		&& IsValValidBlk(Cell, Val);
}

bool SudokuGrid::IsSolved()
{
	bool bEmptyCells = false;
	for (uint i = 0; i < SudokuGridLength; i++)
	{
		if (GridVal(i) == 0)
		{
			bEmptyCells = true;
			break;
		}
	}

	CKA_ASSERT(bEmptyCells || IsValid());
	return !bEmptyCells;
}

void SudokuGrid::Generate()
{
	// TODO: implement
	// Generate 17 random possible values
	for (uint i = 0; i < SudokuGodNumber; i++)
	{
		uint rand_cell = GetRandomFreeCell();
		CKA_ASSERT(GridVal(rand_cell) == 0); // Hasn't tripped yet
		GridVal(rand_cell) = GetRandomPosVal(rand_cell);
	}

	int CellsFilled = 0;
	for (uint i = 0; i < SudokuGridLength; i++)
	{
		if (GridVal(i) != 0)
		{
			CellsFilled++;
		}
	}
	CKA_ASSERT(CellsFilled == SudokuGodNumber);
}

void SudokuGrid::Solve()
{
	// See if there are any PosVals with only one possibility
	//		Yes		Fill them, one by one until they are filled
	//				If we can't fill them all, regress
	//		No		Choose one cell to randomly fill and check again
	// Continue until the grid is filled

	PosVals pos_vals_grid[SudokuGridLength];
	GetPosValsGrid(pos_vals_grid);

	DynamicArray<uint> OnlyOnePosCells;

	bool is_not_solved = true;
	while (is_not_solved)
	{
		// Check for any cells that have only one possible value
		for (uint i = 0; i < SudokuGridLength; i++)
		{
			if (pos_vals_grid[i].OnlyOnePos())
			{
				OnlyOnePosCells.Add(pos_vals_grid[i]);
			}
		}

		// Check if the grid is solved
		is_not_solved = !IsSolved();
	}
	assert(IsValid());
}

void SudokuGrid::SolveHelper()
{

}

void SudokuGrid::Print()
{
	for (uint y = 0; y < SudokuStride; y++)
	{
		for (uint x = 0; x < SudokuStride; x++)
		{
			Outf("%d ", GridVal(x, y));
			if (x == SudokuFirstDiv || x == SudokuSecondDiv)
			{
				Outf("| ");
			}
		}
		if (y == SudokuFirstDiv || y == SudokuSecondDiv)
		{
			Outf("\n----------------------");
		}
		Outf("\n");
	}
	Outf("\n");
}

void SudokuGrid::InitFromPrefab(uint* Prefab, uint PrefabSize)
{
	CKA_ASSERT(sizeof(grid) >= PrefabSize);
	memcpy_s(&grid, sizeof(grid), Prefab, PrefabSize);
}

void SudokuGrid::Test()
{
	struct TestResult
	{
		uint TestNo;
		bool bSucceeded;
	};
	DynamicArray<TestResult> Results;

	// Test with full grid
	InitFromPrefab(TestFullGrid, sizeof(TestFullGrid));
	CKA_ASSERT(IsValid());

	// Test with empty grid
	InitFromPrefab(TestEmptyGrid, sizeof(TestEmptyGrid));

	bool bAllSucceeded = true;
	for (uint TestIdx = 0; TestIdx < Results.num; TestIdx++)
	{
		if (!Results[TestIdx].bSucceeded)
		{
			Outf("Test #%s failed :(\n", TestIdx);
			bAllSucceeded = false;
		}
	}
}

SudokuGrid::SudokuGrid()
{
	for (uint x = 0; x < SudokuStride; x++)
	{
		for (uint y = 0; y < SudokuStride; y++)
		{
			GridVal(x, y) = 0;
		}
	}
}
