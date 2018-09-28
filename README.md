# crystal_controller
arduino based controller for LEDBoard based Crystal prop

simple arduino sketch to control one [LEDBoard_4x4_16bit](https://github.com/s-light/LEDBoard_4x4_16bit) with an attached crystal -
for the mounting see [LEDBoard_Layouts/mounting_lightguide.md](https://github.com/s-light/LEDBoard_Layouts/blob/master/mounting_lightguide.md)

connect one push button between 7 and 8.
Single Click:
toggle sequencer / channel check
hold down: fade to ~100% as long as you push down

as board i used an [Pololu A-Star Mini LV](https://www.pololu.com/docs/0J61/4.1) and two LiPo-Cells to power it.
To have a basic Low-Bat warning i have connected the VIN pin to A0 (with resistor-divider)
to measure Battery Voltage after Polarity Protection (for details see [Schematics](https://www.pololu.com/file/download/a-star-32u4-mini-schematic.pdf?file_id=0J780))
If the battery voltage drops below 2*3.1V the controller Switches to LOWBAT_WARNING.
This means Animations are Stopped and one LED flashes shortly red every 2s.
