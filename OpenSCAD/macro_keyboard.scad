include <lcd.scad>;
include <potentiometer.scad>;

box_width = 100;
box_length = 140;
box_min_height = 18;
box_angle = 10;
box_hyp = box_length / cos(box_angle);
box_ramp_height = box_hyp * sin(box_angle);
box_wall_thickness = 3;
box_top_wall_thickness = 3;
box_bottom_wall_thickness = 3;
box_total_height = box_min_height + box_ramp_height;

lcd_width = 71.38 + 0.20;
lcd_length = 24.18 + 0.20;
lcd_top_margin = 30;
lcd_screw_width = 75.40;
lcd_screw_length = 31.40;
lcd_screw_outer_radius = 3;
lcd_screw_inner_radius = 1.6;
lcd_screw_height = 7;

switch_width = 14;
switch_margin = 4;

encoder_top_margin = 1;
encoder_x = -2;
encoder_z = -6.14 - 0.8;

usb_length = 7.46 + 0.2;
usb_height = 2.56 + 0.2;

arduino_width = 18.1;
arduino_length = 33;
arduino_height = 1.6;
arduino_mount_wall_thickness = 4;
arduino_mount_wall_height = 2.6;
arduino_connector_width = 7.8 + 0.4;
arduino_connector_height = 4.12 + 0.4;


module macro_keyboard_top_case_hull() {
    hull() {
        translate([0, 0, 0])
        cube([box_width, box_length, 0.1], center=true);
    
        translate([0, -box_hyp/2, -box_min_height])
        rotate([-box_angle, 0, 0])
        translate([0, box_hyp/2, 0])
        cube([box_width, box_hyp, 0.1], center=true);
    }
}

module macro_keyboard_top_body() {
    difference() {
        macro_keyboard_top_case_hull();
        
        translate([0, 0, -box_top_wall_thickness])
        scale(v=[
            (box_width - box_wall_thickness) / box_width,
            (box_hyp - box_wall_thickness) / box_hyp,
            1])
        macro_keyboard_top_case_hull();
    }
}

module macro_keyboard_top_lcd_mount() {
    // https://www.openhacks.com/uploadsproductos/eone-1602a1.pdf
    translate([0, (box_hyp/2) -lcd_length/2 - lcd_top_margin, 0])
    cube([lcd_width, lcd_length, 50], center=true);
}

module macro_keyboard_top_lcd_mount_screws() {
    // lcd mount screws
    lcd_start = (box_hyp/2) -lcd_length/2 - lcd_top_margin;
    
    for (i = [-1:2:1]) {
        for (j = [-1:2:1]) {
            translate([i*lcd_screw_width/2, lcd_start + j*lcd_screw_length/2, -lcd_screw_height/2])
            difference() {
                cylinder(r=lcd_screw_outer_radius, h=lcd_screw_height, $fn=60, center=true);
                cylinder(r=lcd_screw_inner_radius, h=lcd_screw_height*1.2, $fn=60, center=true);
            }
        }
    }
}

module macro_keyboard_top_key_mount() {
    total_width = 3 * (switch_width + switch_margin);
    total_hole_width = (4 * (switch_width + switch_margin)) + 6;
    
    translate([-total_width/2, -total_width/2 - 28, 0]) {
    for(i = [0: 3]) {
        for(j = [0: 3]) {
            x_space = switch_margin * i;
            y_space = switch_margin * j;
            x = i * switch_width + x_space;
            y = j * switch_width + y_space;
            
            translate([x, y, 0])
            cube([switch_width, switch_width, 50], center=true);
        }
    }
    }
}

module macro_keyboard_top_key_cols() {
    total_width = 3 * (switch_width + switch_margin);
    pin_height = 40;
    cut_size = 40;
    
    difference() {
    translate([-total_width/2 + switch_width/2 + 2, -total_width/2 - switch_width - 5, -pin_height/2]) {
        for(i = [0: 2]) {
            for(j = [0: 2]) {
                x_space = switch_margin * i;
                x = i * switch_width + x_space;
                y_space = switch_margin * j;
                y = j * switch_width + y_space;
                translate([x, y, 0])

                cylinder(r=2, h=pin_height, $fn=60, center=true);
            }
        }
    }
    
    translate([0, -box_hyp/2, -0.2-box_min_height-(cut_size/2)])
        rotate([-box_angle, 0, 0])
        translate([0, box_hyp/2, 0])
        cube([box_width, box_hyp, cut_size], center=true);  
    }
}

module macro_keyboard_top_mount_screws_base() {
    translate([
        box_width/2 - lcd_screw_outer_radius - 0.6,
        box_length/2 - lcd_screw_outer_radius - 1.4,
        -box_total_height/2])
    difference() {
        cylinder(r=lcd_screw_outer_radius, h=box_total_height, $fn=60, center=true);
        cylinder(r=lcd_screw_inner_radius, h=box_total_height*1.2, $fn=60, center=true);
    }
    
    translate([
        -box_width/2 + lcd_screw_outer_radius + 0.6,
        box_length/2 - lcd_screw_outer_radius - 1.4,
        -box_total_height/2])
    difference() {
        cylinder(r=lcd_screw_outer_radius, h=box_total_height, $fn=60, center=true);
        cylinder(r=lcd_screw_inner_radius, h=box_total_height*1.2, $fn=60, center=true);
    }
    
    translate([
        -box_width/2 + lcd_screw_outer_radius + 0.6,
        -box_length/2 + lcd_screw_outer_radius,
        -box_min_height/2])
    difference() {
        cylinder(r=lcd_screw_outer_radius, h=box_min_height, $fn=60, center=true);
        cylinder(r=lcd_screw_inner_radius, h=box_min_height*1.2, $fn=60, center=true);
    }
    
    translate([
        box_width/2 - lcd_screw_outer_radius - 0.6,
        -box_length/2 + lcd_screw_outer_radius,
        -box_min_height/2])
    difference() {
        cylinder(r=lcd_screw_outer_radius, h=box_min_height, $fn=60, center=true);
        cylinder(r=lcd_screw_inner_radius, h=box_min_height*1.2, $fn=60, center=true);
    }
}

module macro_keyboard_top_mount_screws() {
    cut_size = 2;
    
    difference() {
    macro_keyboard_top_mount_screws_base();
    translate([0, -box_hyp/2, -box_min_height-(cut_size/2)])
        rotate([-box_angle, 0, 0])
        translate([0, box_hyp/2, 0])
        cube([box_width, box_hyp, cut_size], center=true);  
    }
}

module macro_keyboard_top_case() {
    difference() {
        macro_keyboard_top_body();
        macro_keyboard_top_lcd_mount();
        macro_keyboard_top_key_mount();
        macro_keyboard_top_mount_arduino();
        
        translate([encoder_x, (box_hyp/2) -lcd_length/2 - encoder_top_margin, encoder_z])
        rotate([0, 0, 180])
        ky040();
    }
    macro_keyboard_top_key_cols();
    macro_keyboard_top_lcd_mount_screws();
    macro_keyboard_top_mount_screws();
    
    // Render the LCD
    /*
    translate([0, (box_hyp/2) -lcd_length/2 - lcd_top_margin, -lcd_screw_height])
    lcd1602();
    */
    
    translate([encoder_x, (box_hyp/2) -lcd_length/2 - encoder_top_margin, encoder_z])
    rotate([0, 0, 180])
    ky040_mount();
    
    // Render the KY-040 encoder
    /*
    translate([encoder_x, (box_hyp/2) -lcd_length/2 - encoder_top_margin, encoder_z])
    rotate([0, 0, 180])
    ky040();
    */
}

module macro_keyboard_bottom_case_hull() {
    hull() {
    translate([0, 0, -box_height-box_bottom_height/2+6])
    rotate([-box_angle, 0, 0])
    cube([box_width, box_length, 0.1], center=true);
    
    translate([0, 0, -box_height-box_bottom_height/2-6])
    rotate([-box_angle, 0, 0])
    scale([0.98, 0.98, 0.98])
    cube([box_width, box_length, 0.1], center=true);
    }
}

module macro_keyboard_bottom_usb() {
    translate([0, box_width/2 + 18, -box_height -24])
    rotate([-box_angle, 0, 0])
    cube([10, usb_length, usb_height], center=true);
}

module macro_keyboard_bottom_mount_screws_base() {
    translate([
        box_width/2 - lcd_screw_outer_radius - 0.6,
        box_length/2 - lcd_screw_outer_radius - 1.4,
        0])
    cylinder(r=lcd_screw_inner_radius, h=box_total_height*1.2, $fn=60, center=true);
    
    translate([
        -box_width/2 + lcd_screw_outer_radius + 0.6,
        box_length/2 - lcd_screw_outer_radius - 1.4,
        0])
    cylinder(r=lcd_screw_inner_radius, h=box_total_height*1.2, $fn=60, center=true);
    
    translate([
        -box_width/2 + lcd_screw_outer_radius + 0.6,
        -box_length/2 + lcd_screw_outer_radius,
        0])
    cylinder(r=lcd_screw_inner_radius, h=box_min_height*1.2, $fn=60, center=true);
    
    translate([
        box_width/2 - lcd_screw_outer_radius - 0.6,
        -box_length/2 + lcd_screw_outer_radius,
        0])
    cylinder(r=lcd_screw_inner_radius, h=box_min_height*1.2, $fn=60, center=true);
}

module macro_keyboard_top_mount_arduino() {
    translate([0, box_length/2, -box_total_height+arduino_height+arduino_connector_height/2])
    cube([
        arduino_connector_width,
        30,
        arduino_connector_height], center=true);
}

module macro_keyboard_bottom_mount_arduino() {
    difference() {
    cube([
        arduino_width+(arduino_mount_wall_thickness*2),
        arduino_length+arduino_mount_wall_thickness,
        arduino_mount_wall_height], center=true);
    
    translate([0, arduino_mount_wall_thickness/2, 0])
    cube([
        arduino_width+2,
        arduino_length+2,
        arduino_mount_wall_height*2], center=true);
    }        
}

module macro_keyboard_bottom_case() {
    translate([0, 0, box_bottom_wall_thickness/2])
    difference(){
        cube([box_width + box_wall_thickness, box_hyp + box_wall_thickness, box_bottom_wall_thickness], center=true);
        cube([box_width+1.4, box_hyp+1.4, box_bottom_wall_thickness*1.2], center=true);
             translate([0, box_length/2, box_wall_thickness])
        cube([
        arduino_connector_width,
        30,
        arduino_connector_height], center=true);
        }
        
        difference() {
        cube([box_width + box_wall_thickness, box_hyp + box_wall_thickness, box_bottom_wall_thickness], center=true);
        macro_keyboard_bottom_mount_screws_base();
    }       
    
    translate([
        0,
        box_hyp/2 - arduino_length/2 -arduino_mount_wall_thickness/2 - box_wall_thickness,
        arduino_mount_wall_height])
    macro_keyboard_bottom_mount_arduino();
}

module macro_keyboard() {   
    macro_keyboard_top_case();
    translate([0, 0, -60])
    macro_keyboard_bottom_case();
}


macro_keyboard();