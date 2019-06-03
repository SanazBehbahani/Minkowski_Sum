#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Print 2D vectors coordinate values
void print2DVector(vector<vector<int> > vec)
{
     // Sorting the vector for grading purpose
    sort(vec.begin(), vec.end());
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[0].size(); ++j) {
                cout << vec[i][j] << "  ";
        }
        cout << endl;
    }
}

// Check for duplicate coordinates inside a 2D vector and delete them
vector<vector<int> > delete_duplicate(vector<vector<int> > C)
{
    // Sort the C vector
    sort(C.begin(), C.end());
    // Initialize a non duplicated vector
    vector<vector<int> > Cn;
    for (int i = 0; i < C.size() - 1; i++) {
        // Check if it's a duplicate coordinate
        if (C[i] != C[i + 1]) {
            Cn.push_back(C[i]);
        }
    }
    Cn.push_back(C[C.size() - 1]);
    return Cn;
}

// Compute the Minkowski Sum of two vectors
vector<vector<int> > minkowski_sum(vector<vector<int> > A, vector<vector<int> > B)
{
    vector<vector<int> > C;
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < B.size(); j++) {
            // Compute the current sum
            vector<int> Ci = { A[i][0] + B[j][0], A[i][1] + B[j][1] };
            // Push it to the C vector
            C.push_back(Ci);
        }
    }
    C = delete_duplicate(C);
    return C;
}

// Compute the centroid of a polygon
vector<double> compute_centroid(vector<vector<double> > vec)
{
    vector<double> centroid(2);
    double centroid_x=0, centroid_y=0;
    for (int i = 0; i < vec.size(); i++) {
        centroid_x += vec[i][0];
        centroid_y += vec[i][1];
    }
    centroid[0] = centroid_x / vec.size();
    centroid[1] = centroid_y / vec.size();
    return centroid;
}

// Compute the angle of each point with respect to the centroid and append in a new column
// Resulting vector[xi,yi,anglei]
vector<vector<double> > compute_angle(vector<vector<double> > vec)
{
    vector<double> centroid = compute_centroid(vec);
    double prec = 0.0001;
    for (int i = 0; i < vec.size(); i++) {
        double dy = vec[i][1] - centroid[1];
        double dx = vec[i][0] - centroid[0];
        // If the point is the centroid then delete it from the vector
        if (abs(dx) < prec && abs(dy) < prec) {
            vec.erase(vec.begin() + i);
        }
        else {
            // compute the centroid-point angle
            double theta = (atan2(dy, dx) * 180) / M_PI;
            // append it to the vector in a 3rd column
            vec[i].push_back(theta);
        }
    }
    return vec;
}

// Sort the vector in increasing angle (clockwise) for plotting
vector<vector<double> > sort_vector(vector<vector<double> > vec)
{
    vector<vector<double> > sorted_vec = compute_angle(vec);
    // Change the 0 angle to 90 degrees
    for (int i = 0; i < sorted_vec.size(); i++) {
        if (sorted_vec[i][2] == 0)
            sorted_vec[i][2] = 90.0;
    }
    // Sort with respect to the 3rd column(angles)
    sort(sorted_vec.begin(),
        sorted_vec.end(),
        [](const vector<double>& a, const vector<double>& b) {
            return a[2] < b[2];
        });
    return sorted_vec;
}


int main()
{
    // Define the coordinates of triangle A and B using 2D vectors
    vector<vector<int> > A(3, vector<int>(2));
    A = {{ 1, 0 }, { 0, 1 }, { 0, -1 },};
    vector<vector<int> > B(3, vector<int>(2));
    B = {{ 0, 0 }, { 1, 1 }, { 1, -1 },};
    
    
    // Compute the minkowski sum of triangle A and B
    vector<vector<int> > C;
    C = minkowski_sum(A, B);

    // Print the resulting vector
    print2DVector(C);

    return 0;
}
