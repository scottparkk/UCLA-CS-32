
bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
	if (sr == er && sc == ec) return true;
	maze[sr][sc] = 'D'; // mark as discovered

	if (maze[sr][sc-1] == '.'&& pathExists(maze, sr, sc -1, er, ec) == true)
		return true;
	if (maze[sr-1][sc] == '.'&& pathExists(maze, sr-1, sc , er, ec) == true)
		return true;
	if (maze[sr][sc+1] == '.'&& pathExists(maze, sr, sc + 1, er, ec) == true)
		return true;
	if (maze[sr+1][sc] == '.'&& pathExists(maze, sr+1, sc, er, ec) == true)
		return true;
	return false;
}

