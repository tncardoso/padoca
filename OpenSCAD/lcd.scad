// Data sheet: https://www.openhacks.com/uploadsproductos/eone-1602a1.pdf
module lcd1602() {
    pcb_width = 80;
    pcb_length = 36;
    pcb_height = 1.6;
    pcb_screw_width = 75.40 / 2;
    pcb_screw_length = 31.40 / 2;
    pcb_screw_radius = 1.20;
    
    frame_width = 71.38;
    frame_length = 24.18;
    frame_height = 8.88 - pcb_height;
    
    display_width = 61.60;
    display_length = 14.50;
    display_height = 6.00;
    
    // pcb
    difference() {
        color("#00722f")
        cube([pcb_width, pcb_length, pcb_height], center=true);
        
        translate([pcb_screw_width, pcb_screw_length, -5])
        cylinder(r=pcb_screw_radius, h=10, $fn=60);
        translate([-pcb_screw_width, pcb_screw_length, -5])
        cylinder(r=pcb_screw_radius, h=10, $fn=60);
        translate([pcb_screw_width, -pcb_screw_length, -5])
        cylinder(r=pcb_screw_radius, h=10, $fn=60);
        translate([-pcb_screw_width, -pcb_screw_length, -5])
        cylinder(r=pcb_screw_radius, h=10, $fn=60);
    }
    
    // frame
    difference() {
        color("#4d546b")
        translate([0, 0, frame_height/2])
        cube([frame_width, frame_length, frame_height], center=true);
        
        // display hole
        color("#17a2fc")
        translate([0, 0, frame_height/2])
        cube([display_width, display_length, frame_height*2], center=true);
    }
    
    // display
    color("#17a2fc")
    translate([0, 0, frame_height/2])
    cube([display_width, display_length, frame_height], center=true);    
}