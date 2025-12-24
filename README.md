# coordinate-transform-c

C implementation of an affine coordinate transformation used to convert
local coordinates (x, y) into global geographic coordinates (lon, lat).

## Project Goal
This project demonstrates how coordinate transformation algorithms used in
navigation systems can be implemented in C.

The affine transformation parameters are computed using the least squares
method based on a set of reference points.

## Model
lon = a11 * x + a12 * y + b1  
lat = a21 * x + a22 * y + b2

## Technologies
- C
- Linear algebra
- Least squares method
- Gaussian elimination

## Functionality
- Computes affine transformation coefficients from reference points
- Converts local coordinates to global geographic coordinates
- Solves linear systems using Gaussian elimination
- Suitable for navigation and positioning tasks

## Example Use Case
This project can be used in navigation systems to convert local motion
coordinates of a vehicle into global geographic coordinates using an
affine transformation model.

## Disclaimer
This project is intended for educational and research purposes only.
The author is not responsible for any misuse of the provided code.
