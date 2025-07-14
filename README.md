# Convex Hull Algorithm in C++ (From Scratch)

Implemented as part of TJHSST's Computer Vision class in my junior year of high school. Implemented without any external libraries (including OpenCV) \
\
This repository implements the Convex Hull in C++ entirely from scrath for finding the convex hull of a set of 2D points. The code randomly generates points, finds the convex hull, and traces them out.

## Project Structure

| Name            | Type         | Purpose/Contents                                                                 |
|-----------------|--------------|----------------------------------------------------------------------------------|
| `l041.cpp`      | Source Code  | **Main C++ code:** Generates points, computes the convex hull, and draws output  |
| `l041.exe`      | Binary       | **Windows executable:** Pre-compiled from `l041.cpp`                             |
| `output.ppm`    | Output Image | Main result: shows convex hull and random points (PPM image format)              |
| `points.ppm`    | Output Image | Random points only, visualized (PPM)                                             |
| `lab.jpg`       | Image        | Reference or sample image                                                        |
| `lab.ppm`       | Image        | Example PPM image; comparison/reference                                          |
| `lab2.jpg`      | Image        | Another reference/sample output                                                  |

**Option 2: Command Line**
```sh
g++ l041.cpp -o convexhull
./convexhull
```
- This generates `output.ppm` in the repo folder.

### Viewing Output

- Output files are in the **PPM image format** (Portable PixMap).
- Use any compatible image viewer (e.g. IrfanView, GIMP, or `display` from ImageMagick).
- Convert to PNG or JPG if needed:
  ```sh
  convert output.ppm output.png
  ```

## Algorithm Overview
- **Visualization:** The C++ program draws both the random input points and the calculated convex hull as a colored border.

## Example Files

- **output.ppm**: Result (random points + hull).
- **points.ppm**: Just the points.
- **lab.ppm, lab.jpg, lab2.jpg**: Example/reference outputs for comparison.


**Author:** [nihalcshah](https://github.com/nihalcshah)  
**Contributor:** [cjzulu](https://github.com/cjzulu)
