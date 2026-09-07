# donut.c

A spinning 3D terminal donut. Built in C with some basic 3D math and ASCII rendering.

## The 'Problem' 
This implementation works, but it's not perfect. The shading could be way better if we calculated surface normals instead of just using depth. The proportions might look a bit chunky compared to the classic donut.c. But hey—it's a solid learning project that covers the core concepts: parametric surfaces, 3D rotation matrices, perspective projection, and depth handling.

## Building
```bash
gcc -o donut src/donut.c -lm
./donut
```

Press `Ctrl+C` to exit.
