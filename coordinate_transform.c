#include <stdio.h>
#include <string.h>

typedef struct {
    double x;
    double y;
    double lon;
    double lat;
} Point;

/*
 Solves a 3x3 linear system using Gaussian elimination.
 A * result = B
*/
int solve_linear_system(double A[3][3], double B[3], double result[3]) {
    double M[3][3];
    double R[3];

    memcpy(M, A, sizeof(M));
    memcpy(R, B, sizeof(R));

    for (int i = 0; i < 3; i++) {
        double pivot = M[i][i];
        if (pivot == 0.0) {
            return -1;
        }

        for (int j = 0; j < 3; j++) {
            M[i][j] /= pivot;
        }
        R[i] /= pivot;

        for (int k = i + 1; k < 3; k++) {
            double factor = M[k][i];
            for (int j = 0; j < 3; j++) {
                M[k][j] -= factor * M[i][j];
            }
            R[k] -= factor * R[i];
        }
    }

    for (int i = 2; i >= 0; i--) {
        result[i] = R[i];
        for (int j = i + 1; j < 3; j++) {
            result[i] -= M[i][j] * result[j];
        }
    }

    return 0;
}

/*
 Computes affine transformation coefficients from local (x,y)
 to global (lon,lat) coordinates using least squares.
*/
void compute_affine_coeffs(
    Point pts[4],
    double *a11, double *a12, double *b1,
    double *a21, double *a22, double *b2
) {
    double A[3][3] = {0};
    double B_lon[3] = {0};
    double B_lat[3] = {0};

    for (int i = 0; i < 4; i++) {
        double x = pts[i].x;
        double y = pts[i].y;

        A[0][0] += x * x;
        A[0][1] += x * y;
        A[0][2] += x;
        A[1][1] += y * y;
        A[1][2] += y;
        A[2][2] += 1.0;

        B_lon[0] += x * pts[i].lon;
        B_lon[1] += y * pts[i].lon;
        B_lon[2] += pts[i].lon;

        B_lat[0] += x * pts[i].lat;
        B_lat[1] += y * pts[i].lat;
        B_lat[2] += pts[i].lat;
    }

    A[1][0] = A[0][1];
    A[2][0] = A[0][2];
    A[2][1] = A[1][2];

    double lon_coeffs[3];
    double lat_coeffs[3];

    solve_linear_system(A, B_lon, lon_coeffs);
    solve_linear_system(A, B_lat, lat_coeffs);

    *a11 = lon_coeffs[0];
    *a12 = lon_coeffs[1];
    *b1  = lon_coeffs[2];

    *a21 = lat_coeffs[0];
    *a22 = lat_coeffs[1];
    *b2  = lat_coeffs[2];
}

int main() {
    Point pts[4] = {
        {155.975164, 764.0, 33.514767, 44.619784},
        {916.024836, 764.0, 33.514149, 44.619707},
        {916.024836, 0.0,   33.514040, 44.620150},
        {155.975164, 0.0,   33.514658, 44.620228}
    };

    double a11, a12, b1;
    double a21, a22, b2;

    compute_affine_coeffs(pts, &a11, &a12, &b1, &a21, &a22, &b2);

    printf("Affine transform coefficients:\n");
    printf("lon = %.10e * x + %.10e * y + %.10f\n", a11, a12, b1);
    printf("lat = %.10e * x + %.10e * y + %.10f\n", a21, a22, b2);

    return 0;
}
