include <lib/tentacle.scad>


// use the plain model when modifying the module 
//spring(num_of_squares=11);

// use the already rotated model when exporting the stl
rotate([90, 0, 0]) spring(num_of_squares=13);
