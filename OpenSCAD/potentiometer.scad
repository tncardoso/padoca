ky040_pcb_width = 25.10;
ky040_pcb_length = 18.48;
ky040_pcb_height = 1.60;

ky040_base_width = 12;
ky040_base_length = 12;
ky040_base_height = 6.14 - ky040_pcb_height;
ky040_base_x = -ky040_pcb_width/2 + ky040_base_width/2 + (16.6 - ky040_base_width);
ky040_base_y = ky040_pcb_length/2 - ky040_base_length/2 - (14.52 - ky040_base_length);
ky040_base_z = ky040_base_height/2 + ky040_pcb_height/2;

ky040_shaft_radius = 7.50 / 2;
ky040_shaft_height = 22.90 - ky040_base_z;
ky040_shaft_z = ky040_base_z + ky040_shaft_height/2;

ky040_shaft_dent_l = ky040_shaft_radius * 3;
ky040_shaft_dent_height = 5.34;
ky040_shaft_dent_z = ky040_base_z - ky040_shaft_dent_height/2 + ky040_shaft_height + 0.01;
ky040_shaft_dent_x = ky040_shaft_dent_l / 2 + (4.48 - ky040_shaft_radius);

ky040_screw_radius = 1.6;
ky040_screw_x_from_border = 4.56;
ky040_screw_y_from_border = 2;
ky040_screw_distance = 14;
ky040_screw_x = -ky040_pcb_width/2 + ky040_screw_x_from_border;
ky040_screw_y = -ky040_pcb_length/2 + ky040_screw_y_from_border;
ky040_screw_mount_length = 6.14;
ky040_screw_inner_radius = 1;

module ky040() {

    
    // pcb
    color("green")
    difference() {
        cube([ky040_pcb_width, ky040_pcb_length, ky040_pcb_height], center=true);
        // screw mount
        translate([ky040_screw_x, ky040_screw_y, 0])
        cylinder(r=ky040_screw_radius, h=6, $fn=60, center=true);
        
        translate([ky040_screw_x + ky040_screw_distance, ky040_screw_y, 0])
        cylinder(r=ky040_screw_radius, h=6, $fn=60, center=true);
    }
    
    // shaft
    translate([ky040_base_x, ky040_base_y, 0]) {
        // shaft base
        color("gray")
        translate([0, 0, ky040_base_z])
        cube([ky040_base_width, ky040_base_length, ky040_base_height], center=true);
        
        // shaft
        color("gray")
        difference() {
            translate([0, 0, ky040_shaft_z])
            cylinder(r=4, h=ky040_shaft_height, $fn=60, center=true);
        
            translate([ky040_shaft_dent_x, 0, ky040_shaft_dent_z])
            cube([ky040_shaft_dent_l, ky040_shaft_dent_l, ky040_shaft_dent_height], center=true);
        }
    }    
}

module ky040_mount() {
    difference() {
        translate([ky040_screw_x, ky040_screw_y, ky040_screw_mount_length/2 + ky040_pcb_height/2])
        cylinder(r=ky040_screw_radius, h=ky040_screw_mount_length, $fn=60, center=true);
        
        translate([ky040_screw_x, ky040_screw_y, ky040_screw_mount_length/2 + ky040_pcb_height/2])
        cylinder(r=ky040_screw_inner_radius, h=ky040_screw_mount_length*1.2, $fn=60, center=true);
    }
    
     difference() {
        translate([ky040_screw_x + ky040_screw_distance, ky040_screw_y, ky040_screw_mount_length/2 + ky040_pcb_height/2])
        cylinder(r=ky040_screw_radius, h=ky040_screw_mount_length, $fn=60, center=true);
        
        translate([ky040_screw_x + ky040_screw_distance, ky040_screw_y, ky040_screw_mount_length/2 + ky040_pcb_height/2])
        cylinder(r=ky040_screw_inner_radius, h=ky040_screw_mount_length*1.2, $fn=60, center=true);
    }
}

//ky040();
//ky040_mount();