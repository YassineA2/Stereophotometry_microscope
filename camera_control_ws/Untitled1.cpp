#include <iostream>
#include <stdlib.h>
#include<unistd.h>


// This code will take raw pics for 10 diff shutter speeds, convert to bmp, demosaice them.
int main(){
	system("cd ~/Documents/2_RESEARCH_LAB/MAIN_WS");


	system("cd ~/Documents/RESEARCH_LAB/led_control_ws/rpi_ws281x-master/build");
	system("./test 1 1");
	sleep(200); //in milliseconds

	system("cd ~/Documents/2_RESEARCH_LAB/MAIN_WS");

	// Take a raw image with a specific shutter spd, convert it to bmp, and remove extra images
	system("libcamera-still -r -o WBI_LD1_SS1.jpg --shutter 20 --gain 1 --awbgains 1 --immediate"); //in microseconds
	system("rm WBI_LD1_SS1.jpg");
	system("./dcraw -D -c WBI_LD1_SS1.dng | ppmtobmp > WBI_LD1_SS1.bmp");
	system("rm WBI_LD1_SS1.dng");


	system("libcamera-still -r -o WBI_LD1_SS2.jpg --shutter 30 --gain 1 --awbgains 1 --immediate"); //in microseconds
	system("rm WBI_LD1_SS2.jpg");
	system("./dcraw -D -c WBI_LD1_SS2.dng | ppmtobmp > WBI_LD1_SS2.bmp");
	system("rm WBI_LD1_SS2.dng");


	system("libcamera-still -r -o WBI_LD1_SS3.jpg --shutter 50 --gain 1 --awbgains 1 --immediate"); //in microseconds
	system("rm WBI_LD1_SS3.jpg");
	system("./dcraw -D -c WBI_LD1_SS3.dng | ppmtobmp > WBI_LD1_SS3.bmp");
	system("rm WBI_LD1_SS3.dng");


	system("libcamera-still -r -o WBI_LD1_SS4.jpg --shutter 60 --gain 1 --awbgains 1 --immediate"); //in microseconds
	system("rm WBI_LD1_SS4.jpg");
	system("./dcraw -D -c WBI_LD1_SS4.dng | ppmtobmp > WBI_LD1_SS4.bmp");
	system("rm WBI_LD1_SS4.dng");


	system("libcamera-still -r -o WBI_LD1_SS5.jpg --shutter 90 --gain 1 --awbgains 1 --immediate"); //in microseconds
	system("rm WBI_LD1_SS5.jpg");
	system("./dcraw -D -c WBI_LD1_SS5.dng | ppmtobmp > WBI_LD1_SS5.bmp");
	system("rm WBI_LD1_SS5.dng");


	system("libcamera-still -r -o WBI_LD1_SS6.jpg --shutter 150 --gain 1 --awbgains 1 --immediate"); //in microseconds
	system("rm WBI_LD1_SS6.jpg");
	system("./dcraw -D -c WBI_LD1_SS6.dng | ppmtobmp > WBI_LD1_SS6.bmp");
	system("rm WBI_LD1_SS6.dng");


	system("libcamera-still -r -o WBI_LD1_SS7.jpg --shutter 180 --gain 1 --awbgains 1 --immediate"); //in microseconds
	system("rm WBI_LD1_SS7.jpg");
	system("./dcraw -D -c WBI_LD1_SS7.dng | ppmtobmp > WBI_LD1_SS7.bmp");
	system("rm WBI_LD1_SS7.dng");


	system("libcamera-still -r -o WBI_LD1_SS8.jpg --shutter 270 --gain 1 --awbgains 1 --immediate"); //in microseconds
	system("rm WBI_LD1_SS8.jpg");
	system("./dcraw -D -c WBI_LD1_SS8.dng | ppmtobmp > WBI_LD1_SS8.bmp");
	system("rm WBI_LD1_SS8.dng");


	system("libcamera-still -r -o WBI_LD1_SS9.jpg --shutter 350 --gain 1 --awbgains 1 --immediate"); //in microseconds
	system("rm WBI_LD1_SS9.jpg");
	system("./dcraw -D -c WBI_LD1_SS9.dng | ppmtobmp > WBI_LD1_SS9.bmp");
	system("rm WBI_LD1_SS9.dng");


	system("libcamera-still -r -o WBI_LD1_SS10.jpg --shutter 450 --gain 1 --awbgains 1 --immediate"); //in microseconds
	system("rm WBI_LD1_SS10.jpg");
	system("./dcraw -D -c WBI_LD1_SS10.dng | ppmtobmp > WBI_LD1_SS10.bmp");
	system("rm WBI_LD1_SS10.dng");


	system("./demosaice_img WBI_LD1_SS1.bmp");
	system("./demosaice_img WBI_LD1_SS2.bmp");
	system("./demosaice_img WBI_LD1_SS3.bmp");
	system("./demosaice_img WBI_LD1_SS4.bmp");
	system("./demosaice_img WBI_LD1_SS5.bmp");
	system("./demosaice_img WBI_LD1_SS6.bmp");
	system("./demosaice_img WBI_LD1_SS7.bmp");
	system("./demosaice_img WBI_LD1_SS8.bmp");
	system("./demosaice_img WBI_LD1_SS9.bmp");
	system("./demosaice_img WBI_LD1_SS10.bmp");




	// system("cd ~/Documents/RESEARCH_LAB/led_control_ws/rpi_ws281x-master/build")
	// system("./test 2 2 255")
	// sleep(200) //in milliseconds

	// system("cd ~/Documents/RESEARCH_LAB/led_control_ws/rpi_ws281x-master/build")
	// system("./test 3 3 255")
	// sleep(200) //in milliseconds

	// system("cd Desktop");
	// system("libcamera-still -r -o img_3.jpg --shutter 1000000 --gain 1 --awbgains 1 --immediate"); //in microseconds
	// system("rm img_3.jpg")
	// sleep(200)
	


	return 0;
}
