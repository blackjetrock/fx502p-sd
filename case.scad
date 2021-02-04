// Case for PCB

case_th = 13/2;
pcb_th = 5;

module PCB()
{
  cube([70.2, 65.5, pcb_th], center = true);
  translate([-65.5/2-15/2+15+20, -70.2/2-2/2+0.1, 0])
    cube([15, 2, pcb_th], center=true);
}


module case()
{
    cube([80, 100, case_th], center=true);
}

module calculator()
{
    cube([76.0, 50.0, 2.0], center=true);
    cube([70.7, 50, 9.5], center=true);
}

module case2 ()
{
difference()
{
  translate([0, 0, 0.5])
  case();
  translate([0,0+7.5, case_th/2-1.6/2+0.1-0.8+(5-1.6)/2])
    PCB();
    translate([0, -50, 9.5/2+5/2-9.5/2-1.6/2])
    calculator();
}
}

difference()
{
case2();
    translate([0, 50,0])
    cube([100,100,100], center=true);
}