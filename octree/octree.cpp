#include <iostream>
#include <vector>

// Define the point in 3D space
struct Point {
    int x, y, z;
};

// Define the data for each octant
struct Octant {
    Point top_left, bottom_right;
    Point* point;
    Octant* children[8];
};

// Function to create a new Octant
Octant* newOctant(Point top_left, Point bottom_right) {
    Octant* octant = new Octant();
    octant->top_left = top_left;
    octant->bottom_right = bottom_right;
    octant->point = nullptr;
    for (int i = 0; i < 8; ++i)
        octant->children[i] = nullptr;
    return octant;
}

// Function to check if a point is inside an Octant
bool isPointInsideOctant(Octant* octant, Point* point) {
    return (point->x >= octant->top_left.x && point->x <= octant->bottom_right.x &&
            point->y >= octant->top_left.y && point->y <= octant->bottom_right.y &&
            point->z >= octant->top_left.z && point->z <= octant->bottom_right.z);
}

// Function to insert a point into the Octree
void insert(Octant* octant, Point* point) {
    // Point is not in octant, return
    if (!isPointInsideOctant(octant, point))
        return;

    // If this octant does not contain a point but could contain it
    if (octant->point == nullptr) {
        octant->point = point;
        return;
    }

    // Octant is not at a leaf node
    if (octant->children[0] == nullptr) {
        Point octant_mid = {
            (octant->top_left.x + octant->bottom_right.x) / 2,
            (octant->top_left.y + octant->bottom_right.y) / 2,
            (octant->top_left.z + octant->bottom_right.z) / 2
        };

        // Create 8 children octants
        for (int i = 0; i < 8; ++i) {
            // Compute the top_left and bottom_right points for the new octant
            Point new_top_left = {
                octant->top_left.x + (i & 1) * octant_mid.x,
                octant->top_left.y + ((i & 2) >> 1) * octant_mid.y,
                octant->top_left.z + ((i & 4) >> 2) * octant_mid.z
            };

            Point new_bottom_right = {
                octant_mid.x + (i & 1) * octant->bottom_right.x,
                octant_mid.y + ((i & 2) >> 1) * octant->bottom_right.y,
                octant_mid.z + ((i & 4) >> 2) * octant->bottom_right.z
            };

            octant->children[i] = newOctant(new_top_left, new_bottom_right);
        }
    }

    // Insert the point into the appropriate child octant
    for (int i = 0; i < 8; ++i)
        insert(octant->children[i], point);
}

// Function to search for a point in the Octree
bool search(Octant* octant, Point* point) {
    // Point is not in octant, return false
    if (!isPointInsideOctant(octant, point))
        return false;

    // Point is in octant, but there's no point here
    if (octant->point == nullptr)
        return false;

    // Point found, return true
    if (octant->point->x == point->x && octant->point->y == point->y && octant->point->z == point->z)
        return true;

    // Search in child octants
    for (int i = 0; i < 8; ++i) {
        if (search(octant->children[i], point))
            return true;
    }

    return false;
}

int main() {
    Point top_left = {0, 0, 0};
    Point bottom_right = {100, 100, 100};
    Octant* root = newOctant(top_left, bottom_right);

    Point point1 = {50, 50, 50I apologize for the abrupt cut-off. Here's the missing part of the code:

```cpp
    Point point1 = {50, 50, 50};
    insert(root, &point1);

    Point point2 = {25, 25, 25};
    insert(root, &point2);

    Point search_point = {25, 25, 25};
    if (search(root, &search_point))
        std::cout << "Point found!" << std::endl;
    else
        std::cout << "Point not found." << std::endl;

    return 0;
}
