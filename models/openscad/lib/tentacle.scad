
$fa = 1;
$fs = 0.4;


// variables for the spring
SPRING_SIDE = 12;
SPRING_THICKNESS = 1.4;
SPRING_MIDDLE_SPACING = 2;
SPRING_FIRST_SPACING = 8;
SPRING_LAST_SPACING = 8;
first_square_length = SPRING_FIRST_SPACING + 2 * SPRING_THICKNESS;
last_square_length = SPRING_LAST_SPACING + 2 * SPRING_THICKNESS;

// variables for the joint
JOINT_THICKNESS = 2;
M3_HOLE_RADIUS = 1.7;
WIRE_HOLE_RADIUS = 1;


module spring_not_holed(num_of_squares=18) {
    
    assert((num_of_squares % 2), "num_of_squares must be ODD!");

    // vertical surfaces
    for (x=[1 : num_of_squares - 2]) {
        translate([x * (SPRING_MIDDLE_SPACING + SPRING_THICKNESS), 0, 0])
            cube([SPRING_THICKNESS, SPRING_SIDE, SPRING_SIDE]);
    }

    for (x=[0 : num_of_squares - 1]) {
        // top horizontal surfaces
        if (!(x % 2) && (x != num_of_squares - 1) && (x != 0)) {
            translate([x * (SPRING_MIDDLE_SPACING + SPRING_THICKNESS), 0, SPRING_SIDE - SPRING_THICKNESS])
                cube([2 * SPRING_THICKNESS + SPRING_MIDDLE_SPACING, SPRING_SIDE, SPRING_THICKNESS]);
        }
        // bottom horizontal surfaces
        if ((x % 2) && (x != num_of_squares - 2)) {
            translate([x * (SPRING_MIDDLE_SPACING + SPRING_THICKNESS), 0, 0])
                cube([SPRING_THICKNESS + SPRING_MIDDLE_SPACING, SPRING_SIDE, SPRING_THICKNESS]);
        }
        if (x == 0) {
            // first top horizontal surface
            translate([-first_square_length + SPRING_MIDDLE_SPACING + 2 * SPRING_THICKNESS, 0, SPRING_SIDE - SPRING_THICKNESS])
                cube([first_square_length, SPRING_SIDE, SPRING_THICKNESS]);
            // first vertical surface
            translate([-first_square_length + SPRING_MIDDLE_SPACING + 2 * SPRING_THICKNESS, 0, 0])
                cube([SPRING_THICKNESS, SPRING_SIDE, SPRING_SIDE]);
        }
        if (x == num_of_squares - 1) {
            // last vertical surface
            translate([(x - 1) * (SPRING_MIDDLE_SPACING + SPRING_THICKNESS) + last_square_length - SPRING_THICKNESS, 0, 0])
                cube([SPRING_THICKNESS, SPRING_SIDE, SPRING_SIDE]);
            // last bottom horizontal surface
            translate([(x - 1) * (SPRING_MIDDLE_SPACING + SPRING_THICKNESS), 0, 0])
                cube([last_square_length, SPRING_SIDE, SPRING_THICKNESS]);
        }
    }
    
}


module spring(num_of_squares=18) {
    difference() {
        spring_not_holed(num_of_squares);
        // holes in the two ends of the spring
        for (x=[0 : num_of_squares - 1]) {
            // hole in the first end
            if (x == 0) {
                translate([-(first_square_length - SPRING_MIDDLE_SPACING - 2 * SPRING_THICKNESS) - 0.01 / 2, SPRING_SIDE / 2, SPRING_SIDE / 2])
                    rotate([0, 90, 0])
                        cylinder(h=(SPRING_THICKNESS + 0.01), r=M3_HOLE_RADIUS);
            }
            // hole in the last end
            if (x == num_of_squares - 1) {
                translate([(x - 1) * (SPRING_MIDDLE_SPACING + SPRING_THICKNESS) - 0.01 / 2 + last_square_length - SPRING_THICKNESS, SPRING_SIDE / 2, SPRING_SIDE / 2])
                    rotate([0, 90, 0])
                        cylinder(h=(SPRING_THICKNESS + 0.01), r=M3_HOLE_RADIUS);
            }
        }
    }
}


module joint(joint_radius=16, last_joint=false) {
    difference() {
        cylinder(h=JOINT_THICKNESS, r=joint_radius);
        translate([0, 0, - 0.01 / 2])
            cylinder(h=JOINT_THICKNESS + 0.01, r=M3_HOLE_RADIUS);
        for (ang=[0:45:360])
            rotate([0, 0, ang])
                translate([SPRING_SIDE / 2 + (joint_radius - SPRING_SIDE / 2) / 1.5 , 0, - 0.01 / 2]) {
                    if (last_joint)
                        cylinder(h=(JOINT_THICKNESS + 0.01), r=(M3_HOLE_RADIUS + 0.1));
                    else
                        cylinder(h=(JOINT_THICKNESS + 0.01), r=WIRE_HOLE_RADIUS);
                }
         if (last_joint)
            for (ang=[0:90:360])
                rotate([0, 0, ang])
                    translate([SPRING_SIDE / 2 + (joint_radius - SPRING_SIDE / 2) / 4 , 0, - 0.01 / 2])
                            cylinder(h=(JOINT_THICKNESS + 0.01), r=WIRE_HOLE_RADIUS);
        // housing for placing an end of a spring
        housing_margin = 0.5;
        translate([-(SPRING_SIDE + housing_margin) / 2, -(SPRING_SIDE + housing_margin) / 2, JOINT_THICKNESS - (SPRING_THICKNESS / 2)])
            cube([SPRING_SIDE + housing_margin, SPRING_SIDE + housing_margin, SPRING_SIDE]);        
    }
    for (ang=[0:90:360])
        rotate([0, 0, ang])
            translate([joint_radius + (JOINT_THICKNESS / 2) - 1, 0, JOINT_THICKNESS / 2])
                cube(JOINT_THICKNESS, center=true);
}


module servo_mount(high_vertical) {
    
    length_y = 70;
    width = 10;
    thickness = 4;
    vertical_block_height = high_vertical ? 45 : 35;
    oblique_block_height = high_vertical ? vertical_block_height / 2.1 : vertical_block_height / 1.6;
    oblique_block_angle = 28;
    rail_outer_margin = 10;
    
    plate_length = 60;
    plate_width = 28;
    
    length_x = plate_length + 25;
    
    // main base of the piece
    difference() {
        cube([length_x, width, thickness]);
        translate([length_x - 14, width / 2, -0.1])
            cylinder(h=(thickness + 0.2), r=(M3_HOLE_RADIUS + 0.1));
        for (dist = [width * (1 / 3), width * (2 / 3)])
            translate([length_x - 21, dist, -0.1])
                cylinder(h=(thickness + 0.2), r=WIRE_HOLE_RADIUS);
        translate([-0.01, -0.01, -0.01])
            cube([plate_length, width + 0.02, thickness + 0.02]);
    }
    
    // vertical block that will connect to the tentacle
    translate([length_x - 0.01, 0, 0]) {
        difference() {
            cube([thickness, width, vertical_block_height]);
            holes_height = high_vertical ? vertical_block_height - 16 : vertical_block_height - 6;
            translate([0, width / 2, holes_height])
                rotate([0, 90, 0])
                    cylinder(h=(width + 0.1), r=M3_HOLE_RADIUS, center=true);
            translate([0,  width / 2, holes_height - 13])
                rotate([0, 90, 0])
                    cylinder(h=(50 * width), r=WIRE_HOLE_RADIUS, center=true);
            if(high_vertical == true)
                translate([0,  width / 2, holes_height + 13])
                    rotate([0, 90, 0])
                        cylinder(h=(50 * width), r=WIRE_HOLE_RADIUS, center=true);
        }
    }
    
    // oblique support for the vertical block
    difference() {
        holes_height = high_vertical ? vertical_block_height - 16 : vertical_block_height - 6;
        translate([length_x - 10, 0, thickness])
            rotate([0, oblique_block_angle, 0])
                cube([thickness, width, oblique_block_height]);
        translate([0,  width / 2, holes_height - 13])
            rotate([0, 90, 0])
                cylinder(h=(50 * width), r=WIRE_HOLE_RADIUS, center=true);
    }
    
    // rail for fine-tuning the length of the wires
    translate([length_x - 26, - (length_y / 2) + (width / 2), 0]) {
        difference() {
            cube([width, length_y, thickness]);
            hull() {
                for (dist = [rail_outer_margin, length_y - rail_outer_margin])
                    translate([width / 2, dist, thickness / 2])
                        cylinder(h=(thickness + 0.1), r=M3_HOLE_RADIUS, center=true);
            }
        }
    }
    
    // holed blocks at the ends of the rail
    blocks_height = 14;
    translate([length_x - 26 + width / 3 + 3 / 2, rail_outer_margin / 2, thickness - 0.01 + blocks_height / 2])
        difference() {
            linear_extrude(height=blocks_height, center = true, scale=[0.4, 1])
                square([width * (3 / 4), length_y], center=true);
            cube([width + 0.01, length_y - rail_outer_margin - 5, blocks_height + 0.01], center=true);
            for (dist = [length_y / 2 - 2, length_y / 2 - 5.25, - (length_y / 2 - 2), - (length_y / 2 - 5.25)])
                translate([0, dist, blocks_height / 2 - 3])
                    rotate([0, 90, 0])
                        cylinder(r=WIRE_HOLE_RADIUS, h=(width + 0.1), center=true);
    }
    
    // plate for mounting the servo
    translate([plate_length / 2, (0 + width) / 2, thickness / 2])
        difference() {
            cube([plate_length, plate_width, thickness], center=true);
            cube([41, 21, thickness + 0.01], center=true);
            translate([40 / 2 + 4, -5, 0])
                cylinder(h=(thickness + 0.01), r=M3_HOLE_RADIUS, center=true);
            translate([40 / 2 + 4, 5, 0])
                cylinder(h=(thickness + 0.01), r=M3_HOLE_RADIUS, center=true);
            translate([- (40 / 2 + 4), -5, 0])
                cylinder(h=(thickness + 0.01), r=M3_HOLE_RADIUS, center=true);
            translate([- (40 / 2 + 4), 5, 0])
                cylinder(h=(thickness + 0.01), r=M3_HOLE_RADIUS, center=true);
        
    }
    
}


module round_washer(radius=5, thickness=2) {
    difference() {
        cylinder(h=thickness, r=radius, center=true);
            cylinder(h=(thickness + 0.1), r=M3_HOLE_RADIUS, center=true);
        for (ang=[0:45:360])
            rotate([0, 0, ang])
                translate([radius / 3 * 2, 0, 0])
                        cylinder(h=(thickness + 0.01), r=WIRE_HOLE_RADIUS, center=true);
    }
}


module arc_support() {
    
    length = 50;
    width = 20;
    thickness = 4;

    height = 25;
    
    difference() {
        union() {
            cube([length, width, thickness]);
            translate([0, 0, 0])
                cube([thickness, width, height]);
            translate([length - thickness, 0, 0])
                cube([thickness, width, height + thickness]);
        }
        for (dist_y=[-5, 5]) {
            translate([thickness / 2, width / 2 + dist_y, height - 3])
                rotate([0, 90, 0])
                    cylinder(h=(thickness + 0.01), r=M3_HOLE_RADIUS, center=true);
            translate([thickness / 2 + length - thickness, width / 2 + dist_y, height - 3 + thickness])
                rotate([0, 90, 0])
                    cylinder(h=(thickness + 0.01), r=M3_HOLE_RADIUS, center=true);
        }
    }
    
    
    // oblique support for the vertical block
    oblique_block_height = 20;
    translate([7, width / 2, 10])
        rotate([0, -30, 0])
            cube([thickness, width, oblique_block_height], center=true);
    translate([length - 7, width / 2, 10])
        rotate([0, 30, 0])
            cube([thickness, width, oblique_block_height], center=true);

}


module tip() {
    
    scale([1, 1, 0.7]) {

        radius = 16;
        
        difference() {
            sphere(r=radius);
            translate([0, 0, -radius])
                cube(2 * radius, center=true);
            translate([0, 0, - 0.01])
                cylinder(h=radius + 0.01, r=M3_HOLE_RADIUS);
            translate([0, 0, 4])
                cylinder(h=radius + 0.01, r=3.5);
            for (ang=[0:45:360]) {
                rotate([0, 0, ang])
                    translate([SPRING_SIDE / 2 + (radius - SPRING_SIDE / 2) / 1.5 , 0, - 0.01])
                            cylinder(h=(radius + 0.01), r=(M3_HOLE_RADIUS + 0.1));
                rotate([0, 0, ang])
                    translate([SPRING_SIDE / 2 + (radius - SPRING_SIDE / 2) / 1.5 , 0, 4])
                            cylinder(h=(radius + 0.01), r=3.5);
            }
        }
    }
}


