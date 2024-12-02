#include "pseudoku.h"

int main()
{
    grid test_grid;
    test_grid.init_grid();
    printf("Before fill_grid:\n");
    test_grid.print_grid(test_grid);
    printf("After fill_grid:\n");
    test_grid.fill_grid(0);
    test_grid.print_grid(test_grid);
}

int* grid::
get_row_ptr(int r)
{// returns ptr to beg of row r (0-8)
    return &grid[r * 9];
}

int* grid::
get_col_ptr(int c)
{// returns ptr to first cell of col c (0-8)
    return &grid[c];
}

int* grid::
get_box_ptr(int b)
{// returns ptr to first cell of row b (0-8)
    return &grid[(b / 3 * 3 * 9) + (b % 3 * 3)];
}

neighbors* grid::
get_neighbors(int n)
{// returns peers of cell n (0-80)
    neighbors* peers= (neighbors*)malloc(sizeof(neighbors));
    int* row_ptr = get_row_ptr(n / 9);
    int* col_ptr = get_col_ptr(n % 9);
    int* box_ptr = get_box_ptr(n / 27 * 3 + (n % 9) / 3);
    int row[9] = ROW_OF(row_ptr);
    int col[9]= COL_OF(col_ptr);
    int box[9] = BOX_OF(box_ptr);
    int i;
    for (i = 0; i < 9; i++)
    {
	neighbors->row[i] = row[i];
	neighbors->col[i] = col[i];
	neighbors->box[i] = box[i];
    }
    return neighbors;
}

int grid::
is_safe(int n, int v)
{// returns whether or not value v (1-9) in cell n (0-80) is safe
    neighbors* peers= get_neighbors(g, n);
    int i;
    for (i = 0; i < 9; i++)
    {
	if (neighbors->row[i] == v ||
	    neighbors->col[i] == v ||
	    neighbors->box[i] == v)
	{
	    free(neighbors);
	    return (0);
	}
    }
    free(neighbors);
    return (1);
}

possible_vals* grid::
get_pos_vals(int n)
{// returns pos struct containing possible values in cell n (0-80)
    possible_vals* pos_values = (possible_vals*)malloc(sizeof(possible_vals));
    int i, s;
    for (i = 0, s = 0; i < 9; i++)
    {
	if (is_safe(n, i + 1))
	{
	    pos_values->vals[s] = i + 1;
	    s++;
	}  
	
    }
    pos_values->size = s;
    return pos_values;
}

int grid::
fill_grid(int n)
{// fills cells n (0-80) to end of grid
    if (n < 81)
    {
	if (grid[n] != 0)
	{
	    return fill_grid(n + 1);
	}
	else
	{
	    possible_vals *pos_values = get_pos_vals(n);
	    int i;
	    for (i = 0; i < pos_values->size; i++)
	    {
		grid[n] = pos_values->vals[i];
		if (fill_grid(n + 1))
		{
		    free(pos_values);
		    return (1);
		}
		else
		{
		    grid[n] = 0;
		}
	    }
	    free(pos_values);
	    return (0);
	}
    }
    else
    {
	return (1);
    }
}

void grid::
copy_grid(int* new_values)
{// copies values in new_values to grid
    int i;
    for (i = 0; i < 81; i++)
    {
	grid[i] = new_values[i];
    }
}

void grid::
init_grid()
{// initializes grid to test_grid
    int test_grid[81] = {0, 0, 0, 0, 0, 0, 0, 0, 0,
		       0, 0, 0, 0, 0, 0, 0, 0, 0,
		       0, 0, 0, 0, 0, 0, 0, 0, 0,
		       0, 0, 0, 0, 0, 0, 0, 0, 0,
		       0, 0, 0, 0, 0, 0, 0, 0, 0,
		       0, 0, 0, 0, 0, 0, 0, 0, 0,
		       0, 0, 0, 0, 0, 0, 0, 0, 0,
		       0, 0, 0, 0, 0, 0, 0, 0, 0,
		       0, 0, 0, 0, 0, 0, 0, 0, 0};
    copy_grid(grid, test_grid);
}

void grid::
print_grid()
{// prints grid in Sudoku format
    int i;
    for (i = 0; i < 81; i++)
    {
	if (i % 9 == 0 && i != 0)
	    printf("\n");
	if (i % 27 == 0 && i != 0)
	    printf("------+-------+-------\n");
	if (i % 3 == 0 && i % 9 != 0)
	    printf("| %d ", grid[i]);
	else
	    printf("%d ", grid[i]);
    }
    printf("\n");
}
