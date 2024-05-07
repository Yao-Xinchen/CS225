/* Your code here! */

#include "maze.h"

#include <algorithm>
#include <queue>
#include <random>

SquareMaze::SquareMaze()
{
    width = 0;
    height = 0;
    cells = DisjointSets();
}

void SquareMaze::makeMaze(const int width, const int height)
{
    if (!cells.empty()) cells = DisjointSets(); // clear existing data
    cells.addelements(width * height);
    this->width = width;
    this->height = height;
    right_walls = vector<bool>(width * height, true); // set all walls to true
    down_walls = vector<bool>(width * height, true); // set all walls to true

    // put all walls into a vector
    std::vector<std::tuple<int, int>> walls;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (i + 1 < width) walls.emplace_back(i, j);
            if (j + 1 < height) walls.emplace_back(i, j);
        }
    }

    // shuffle wall
    shuffle(walls.begin(), walls.end(), std::mt19937(std::random_device()()));

    // remove walls
    // for (const auto& [x, y]: walls)
    for (const auto& wall: walls)
    {
        const auto& x = std::get<0>(wall);
        const auto& y = std::get<1>(wall);
        const auto index = x + y * width;
        // remove wall if it doesn't create a cycle
        if (x + 1 < width && cells.find(index) != cells.find(index + 1))
        {
            setWall(x, y, RIGHT, false);
            cells.setunion(index, index + 1);
        }
        else if (y + 1 < height && cells.find(index) != cells.find(index + width))
        {
            setWall(x, y, DOWN, false);
            cells.setunion(index, index + width);
        }
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const
{
    if (x < 0 || x >= width || y < 0 || y >= height)
    {
        std::cerr << "Invalid coordinates: (" << x << ", " << y << ")" << std::endl;
        return false;
    }

    switch (dir)
    {
    case RIGHT: {
        if (x + 1 == width) return false; // on the right edge
        return !right_walls[x + y * width];
    }
    case DOWN: {
        if (y + 1 == height) return false; // on the bottom edge
        return !down_walls[x + y * width];
    }
    case LEFT: {
        if (x == 0) return false; // on the left edge
        return !right_walls[x - 1 + y * width];
    }
    case UP: {
        if (y == 0) return false; // on the top edge
        return !down_walls[x + (y - 1) * width];
    }
    default:
        std::cerr << "Invalid direction: " << dir << std::endl;
        return false;
    }
}

void SquareMaze::setWall(const int x, const int y, const int dir, const bool exists)
{
    // check if coordinates are valid
    if (x < 0 || x >= width || y < 0 || y >= height)
    {
        std::cerr << "Invalid coordinates: (" << x << ", " << y << ")" << std::endl;
        return;
    }

    // set wall
    switch (dir)
    {
    case RIGHT:
        this->right_walls[x + y * width] = exists;
        break;
    case DOWN:
        this->down_walls[x + y * width] = exists;
        break;
    default:
        std::cerr << "Invalid direction: " << dir << std::endl;
        break;
    }
}

vector<int> SquareMaze::solveMaze() const
{
    static constexpr std::array<int, 4> dx = {1, 0, -1, 0};
    static constexpr std::array<int, 4> dy = {0, 1, 0, -1};

    // Initialize the distance array and the queue
    vector<int> dist(width * height, -1);
    vector<int> prev(width * height, -1);
    queue<int> q;

    // Start from the top-left cell
    dist[0] = 0;
    q.push(0);

    // BFS
    while (!q.empty())
    {
        const int cell = q.front();
        q.pop();

        // For each neighbor
        for (int dir = 0; dir < 4; ++dir)
        {
            const int nx = cell % width + dx[dir];
            const int ny = cell / width + dy[dir];

            // If the neighbor is within the maze and can be traveled to
            if (nx >= 0 && nx < width && ny >= 0 && ny < height && canTravel(cell % width, cell / width, dir))
            {
                int ncell = ny * width + nx;

                // If the neighbor has not been visited yet
                if (dist[ncell] == -1)
                {
                    dist[ncell] = dist[cell] + 1;
                    prev[ncell] = dir;
                    q.push(ncell);
                }
            }
        }
    }

    // Find the farthest cell from the start in the bottom row
    int end = (height - 1) * width;
    for (int i = 0; i < width; ++i)
    {
        if (dist[(height - 1) * width + i] > dist[end])
        {
            end = (height - 1) * width + i;
        }
    }

    // Find the path from the start to the end
    vector<int> path;
    for (int cell = static_cast<int>(end); cell != 0; // Start from the end cell
         cell = (cell / width - dy[prev[cell]]) * width + cell % width - dx[prev[cell]]) // Move to the previous cell
        path.push_back(prev[cell]);

    // Reverse the path to get it from start to end
    reverse(path.begin(), path.end());

    return path;
}

PNG* SquareMaze::drawMaze() const
{
    auto maze = new PNG(width * 10 + 1, height * 10 + 1);

    auto set_black = [&maze](const int x, const int y) {
        maze->getPixel(x, y)->l = 0;
        maze->getPixel(x, y)->a = 1;
        maze->getPixel(x, y)->h = 0;
        maze->getPixel(x, y)->s = 0;
    };

    // Blacken the entire topmost row and leftmost column of pixels
    // except the entrance (1,0) through (9,0)
    for (int x = 10; x < width * 10 + 1; ++x) set_black(x, 0);
    for (int y = 0; y < height * 10 + 1; ++y) set_black(0, y);

    // For each square in the maze
    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            // If the right wall exists, then blacken the pixels
            // with coordinates ((x+1)*10,y*10+k) for k from 0 to 10
            if (right_walls[x + y * width])
            {
                for (int k = 0; k <= 10; ++k) set_black((x + 1) * 10, y * 10 + k);
            }

            // If the bottom wall exists, then blacken the pixels
            // with coordinates (x*10+k, (y+1)*10) for k from 0 to 10
            if (down_walls[x + y * width])
            {
                for (int k = 0; k <= 10; ++k) set_black(x * 10 + k, (y + 1) * 10);
            }
        }
    }

    return maze;
}

PNG* SquareMaze::drawMazeWithSolution() const
{
    // Get the maze without the solution
    auto maze = drawMaze();

    auto set_red = [&maze](const int x, const int y) {
        maze->getPixel(x, y)->l = 0.5;
        maze->getPixel(x, y)->a = 1;
        maze->getPixel(x, y)->h = 0;
        maze->getPixel(x, y)->s = 1;
    };

    auto set_white = [&maze](const int x, const int y) {
        maze->getPixel(x, y)->l = 1;
        maze->getPixel(x, y)->a = 1;
        maze->getPixel(x, y)->h = 0;
        maze->getPixel(x, y)->s = 0;
    };

    // Solve the maze
    auto path = solveMaze();

    // Start at pixel (5,5)
    int x = 5, y = 5;
    for (const auto& dir: path)
    {
        // Each direction in the solution vector corresponds to a trail of 11 red pixels in the given direction
        for (int k = 0; k <= 10; ++k)
        {
            switch (dir)
            {
            case RIGHT:
                set_red(x + k, y);
                break;
            case DOWN:
                set_red(x, y + k);
                break;
            case LEFT:
                set_red(x - k, y);
                break;
            case UP:
                set_red(x, y - k);
                break;
            default:
                std::cerr << "Invalid direction: " << dir << std::endl;
                break;
            }
        }

        // Update the current position
        switch (dir)
        {
        case RIGHT: x += 10;
            break;
        case DOWN: y += 10;
            break;
        case LEFT: x -= 10;
            break;
        case UP: y -= 10;
            break;
        default:
            std::cerr << "Invalid direction: " << dir << std::endl;
            break;
        }
    }

    // Make the exit by undoing the bottom wall of the destination square
    const auto end = max_element(path.begin(), path.end()) - path.begin();
    const auto x_end = x - 5;
    const auto y_end = y + 5;
    for (int k = 1; k <= 9; ++k) set_white(x_end + k, y_end);

    return maze;
}
