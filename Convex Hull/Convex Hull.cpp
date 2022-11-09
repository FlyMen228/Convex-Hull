#include <iostream>
#include <vector>
#include <algorithm>

/*===============================================================================*/

struct Point
{

    int x;
    int y;

public:

    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    Point operator-(Point point)
    {
        return { point.x - this->x, point.y - this->y };
    }

    bool operator>(Point point)
    {
        return this->x * point.y - this->y * point.x;
    }

    bool operator<(Point point) const
    {
        return this->x < point.x || this->x == point.x && this->y < point.y;
    }

};

/*=================================================================================*/

std::vector <Point> grahamAlgorithm(std::vector <Point>& hull);

int findMinPointIndex(std::vector <Point>& hull);

bool crutch(Point& a, Point& b);

/*=================================================================================*/

int main()
{
    Point point1 = Point(0, 0);
    Point point2 = Point(1, 2);
    Point point3 = Point(3, 3);
    Point point4 = Point(-8, -1);
    Point point5 = Point(2, 6);
    Point point6 = Point(-1, 1);

    std::vector <Point> points = { point1, point2, point3, point4, point5, point6 };

    std::vector <Point> hull = grahamAlgorithm(points);

    for (int i = 0; i < hull.size(); ++i)
        std::cout << hull[i].x << " " << hull[i].y << std::endl;
}

std::vector <Point> grahamAlgorithm(std::vector <Point>& points)
{
    int minPointIndex = findMinPointIndex(points);

    std::swap(points[minPointIndex], points[0]);

    sort(points.begin() + 1, points.end(), &crutch);

    std::vector <Point> hull;
    hull.push_back(points[0]);

    for (int i = 1; i < points.size(); ++i)
    {
        while (hull.size() > 1)
        {
            int c = hull.size() - 1;
            if ((hull[c] - hull[c - 1]) > (points[i] - hull[c]) <= 0)
                hull.pop_back();
            else
                break;
        }
        hull.push_back(points[i]);
    }

    return hull;
}

int findMinPointIndex(std::vector <Point>& points)
{
    int minPointIndex = 0;

    for (int i = 0; i < points.size(); ++i)
        if (points[i] < points[minPointIndex])
            minPointIndex = i;
    
    return minPointIndex;
}

bool crutch(Point& a, Point& b)
{
    return a < b;
}