int isSafe(int board[8][8], int row, int col)
{
    for (int x = 0; x < col; x++)
        if (board[row][x] == 1)
            return 0;
    for (int x = row, y = col; x >= 0 && y >= 0; x--, y--)
        if (board[x][y] == 1)
            return 0;
    for (int x = row, y = col; x < 8 && y >= 0; x++, y--)
        if (board[x][y] == 1)
            return 0;
    return 1;
}
 
int solveNQueens(int board[8][8], int col)
{
    if (col == 8)
        return 1;

    for (int i = 0; i < 8; i++) {
        if (isSafe(board, i, col)) {
            board[i][col] = 1;
            if (solveNQueens(board, col + 1))
                return 1;
            board[i][col] = 0;
        }
    }
    return 0;
}
 
int main()
{
    int board [8][8]; 
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            board[i][j] = 0;
    }

    return solveNQueens(board, 0);
}