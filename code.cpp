/*
    Name: Mohammad Shoaib Ansari
    Roll Number: BT21CSE063
    Email: as920217.mdshoaibansari@gmail.com
    Course: Artificial Intelligence W24
*/

/* 
    use iterative deepening search to solve the 8-puzzle problem

    step 1: randomly generate a puzzle
    step 2: check if the puzzle is solvable
    step 3: if not, go back to step 1
    step 4: solve the puzzle using iterative deepening search

    goal: 123456780
*/

#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <random>
#include <chrono>
#include <set>
#include <string>

using namespace std;

// Size of the puzzle grid (3x3)
const int N = 3;

// Goal state of the 8-puzzle
vector<vector<int>> goal = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}};

class State
{
public:
    vector<vector<int>> board;  // 2D vector representing the current board
    int space_x, space_y;       // Coordinates of the empty space (0)
    int depth;                  // Depth of the state in the search tree

    // Default constructor: initialize an empty board
    State()
    {
        board = vector<vector<int>>(N, vector<int>(N, 0));
        space_x = 0;
        space_y = 0;
        depth = 0;
    }

    // Constructor with a predefined board configuration
    State(vector<vector<int>> board, int depth = 0) : board(board), depth(depth)
    {
        // Find the position of the empty space (0)
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (board[i][j] == 0)
                {
                    space_x = i;
                    space_y = j;
                    return;
                }
            }
        }
    }

    // Constructor with a given starting board and the position of the space
    State(vector<vector<int>> board, int space_x, int space_y, int depth = 0) : board(board), space_x(space_x), space_y(space_y), depth(depth) {}

    // Randomly generate a puzzle
    void generatePuzzle()
    {
        vector<int> nums(N * N);
        for (int i = 0; i < N * N; i++)
        {
            nums[i] = i;
        }

        // Shuffle the numbers randomly
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(nums.begin(), nums.end(), default_random_engine(seed));

        // Initialize the board with the shuffled numbers
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                board[i][j] = nums[i * N + j];
                if (board[i][j] == 0)
                {
                    space_x = i;
                    space_y = j;
                }
            }
        }
        depth = 0;
    }

    // Check if the puzzle is solvable
    bool isSolvable() const
    {
        vector<int> nums(N * N);
        int k = 0;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                nums[k++] = board[i][j];
            }
        }

        // Count inversions (pairs of numbers out of order)
        int inv_count = 0;
        for (int i = 0; i < N * N; i++)
        {
            for (int j = i + 1; j < N * N; j++)
            {
                if (nums[i] && nums[j] && nums[i] > nums[j])
                {
                    inv_count++;
                }
            }
        }

        // If number of inversions is even, the puzzle is solvable
        return inv_count % 2 == 0;
    }

    // Check if the state is the goal state
    bool isGoal() const
    {
        return board == goal;
    }

    // Generate possible child states by moving the empty space
    vector<State> getChildren() const
    {
        vector<State> children;
        // up, down, left, right
        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++)
        {
            int new_x = space_x + dx[i];
            int new_y = space_y + dy[i];
            if (new_x >= 0 && new_x < N && new_y >= 0 && new_y < N)
            {
                vector<vector<int>> new_board = board;
                swap(new_board[space_x][space_y], new_board[new_x][new_y]);
                children.emplace_back(new_board, new_x, new_y, depth + 1);
            }
        }

        return children;
    }

    // Print the state
    void print() const
    {
        for (const auto &row : board)
        {
            for (int num : row)
            {
                cout << num << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // Get the hash value of the state (used for checking visited states)
    string getHash() const
    {
        string hash = "";
        for (const auto &row : board)
        {
            for (int num : row)
            {
                hash += to_string(num);
            }
        }
        return hash;
    }
};

// Depth-Limited Search implementation
// Searches for the goal state within a specified depth limit
bool DepthLimitedSearch(const State &state, int depthLimit, vector<State> &path, set<string> &visited)
{
    if (state.isGoal())
    {
        path.push_back(state);
        return true;
    }

    if (state.depth >= depthLimit)
    {
        return false;
    }

    visited.insert(state.getHash());

    for (const State &child : state.getChildren())
    {
        if (visited.find(child.getHash()) == visited.end() && DepthLimitedSearch(child, depthLimit, path, visited))
        {
            path.push_back(state);
            return true;
        }
    }

    return false;
}

// Iterative Deepening Search
// Gradually increases search depth until a solution is found
bool IterativeDeepeningSearch(const State &start, vector<State> &solution)
{
    int depth = 0;
    while (true)
    {
        vector<State> path;
        set<string> visited;
        if (DepthLimitedSearch(start, depth, path, visited))
        {
            // Solution found
            solution = move(path);
            reverse(solution.begin(), solution.end());
            return true;
        }
        depth++;
    }

    return false;
}

int main()
{
    // vector<vector<int>> initial_board = {
    //     {1, 2, 3},
    //     {4, 5, 6},
    //     {7, 0, 8}};
    // State start(initial_board);

    State start;
    start.generatePuzzle();

    cout << "Initial State: " << endl;
    while (!start.isSolvable())
    {
        start.print();
        cout << "Unsolvable!" << endl;
        cout << "Regenerating..." << endl;
        start.generatePuzzle();
    }
    start.print();

    vector<State> solution;
    auto start_time = chrono::high_resolution_clock::now();

    if (IterativeDeepeningSearch(start, solution))
    {
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);

        cout << "Solved in " << duration.count() << " ms" << endl;
        cout << "Number of moves: " << solution.size() - 1 << endl;
        cout << "Depth: " << solution.back().depth << endl;

        cout << "Solution: " << endl;
        for (const auto &state : solution)
        {
            state.print();
        }
    }
    else
    {
        cout << "Failed to find a solution!" << endl;
    }

    return 0;
}

// Time Complexity: O(b^d) 
// Space Complexity: O(b*d) 
// where b is the branching factor and d is the depth of the shallowest goal node