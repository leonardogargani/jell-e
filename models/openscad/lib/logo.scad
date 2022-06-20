
$fa = 1;
$fs = 0.4;


PLATE_X = 100;
PLATE_Y = 40;
PLATE_Z = 2;

PLATE_ROUNDNESS = 5;
LOGO_HEIGHT = 3;

STAND_HEIGHT = 8;


module logo_plate() {
    
    // extruded logo
    color("Blue")
        translate([0, 0, PLATE_Z / 2 - 0.01])
            linear_extrude(height=LOGO_HEIGHT, convexity=4)
                scale(0.5)
                    import("img/logo.svg", center=true);

    // plate under the logo
    color("White")
        hull() {
            transl_x = (PLATE_X / 2) - PLATE_ROUNDNESS;
            transl_y = (PLATE_Y / 2) - PLATE_ROUNDNESS;
            translate([transl_x, transl_y, 0])
                cylinder(h=PLATE_Z, r=PLATE_ROUNDNESS, center=true);
            translate([transl_x, -transl_y, 0])
                cylinder(h=PLATE_Z, r=PLATE_ROUNDNESS, center=true);
            translate([-transl_x, -transl_y, 0])
                cylinder(h=PLATE_Z, r=PLATE_ROUNDNESS, center=true);
            translate([-transl_x, transl_y, 0])
                cylinder(h=PLATE_Z, r=PLATE_ROUNDNESS, center=true);
        }
        
}


module logo_plate_oblique(difference_mode=false) {
    scale = difference_mode ? 1.1 : 1.0;
    translate([0, -4, -2 * scale])
        rotate([70, 0, 0])
            translate([0, scale * PLATE_Y / 2, scale * PLATE_Z / 2])
    scale([scale, scale, scale])
        logo_plate();
}


module plate_stand() {
    difference() {
        linear_extrude(height=STAND_HEIGHT, center=true, scale=0.6)
            square([30, 20], center=true);
        logo_plate_oblique(difference_mode=true);
    }
}


