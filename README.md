# Geometry Processing - As Rigid As Possible Deformation

This is my implementation of As Rigid As possible in [CSC419/CSC2520 Geometry Processing](https://github.com/alecjacobson/geometry-processing-csc2520/).

## Build & Execution
```
git submodule update --init --recursive
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make 
./deformation [path to mesh.obj]
```

- `Space` to toggle whether placing control points or deforming

- `m` to switch deformation method

![](images/knight-deformation.gif)
![](images/bunny-harmonic.gif)
![](images/bunny-biharmonic.gif)
![](images/knight-arap-large-rotation.gif)
![](images/knight-arap-high-vs-low-resolution.gif)