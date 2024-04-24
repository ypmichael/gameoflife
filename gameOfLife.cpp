#include <iostream>
#include <vector>
#include <unistd.h>  // For sleep()

using namespace std;

class GameOfLife {
private:
    int rows, cols;
    vector<vector<int> > grid;

public:
    GameOfLife(int r, int c) : rows(r), cols(c), grid(r, vector<int>(c, 0)) {}

    void setAlive(int x, int y) {
        if (x >= 0 && x < rows && y >= 0 && y < cols) {
            grid[x][y] = 1;
        }
    }

    void initializeGlider(int testp) {
        setAlive(1, (testp+2)%10);
        setAlive(2, (testp+3)%10);
        setAlive(3, (testp+1)%10);
        setAlive(3, (testp+2)%10);
        setAlive(3, (testp+3)%10);
    }

    void printGrid() {
        system("clear");  // Clears the screen for animation
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << (grid[i][j] ? "*" : ".") << " ";
            }
            cout << "\n";
        }
        cout << "\n";
        usleep(200000); // Sleep for 200 milliseconds
    }

    void update() {
        vector<vector<int> > newGrid = grid;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int liveNeighbors = countLiveNeighbors(i, j);
                if (grid[i][j] == 1 && (liveNeighbors < 2 || liveNeighbors > 3)) {
                    newGrid[i][j] = 0;
                } else if (grid[i][j] == 0 && liveNeighbors == 3) {
                    newGrid[i][j] = 1;
                }
            }
        }
        grid = newGrid;
    }

private:
    int countLiveNeighbors(int x, int y) {
        int count = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue;
                int nx = x + i, ny = y + j;
                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                    count += grid[nx][ny];
                }
            }
        }
        return count;
    }
};

int main() {
    GameOfLife game(10, 10);

    for (int test_round=0; test_round<3; test_round++)
    {
	    game.initializeGlider(test_round*3);
	    int generations = 30;
	    for (int i = 0; i < generations; ++i) {
		    game.printGrid();
		    game.update();
	    }
    }

    return 0;
}

