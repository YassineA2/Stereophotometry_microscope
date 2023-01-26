#include <iostream>
#include <stdlib.h>
#include<unistd.h>
#include <stdio.h>

int shutterspds[] =  {20, 30, 50, 60, 90, 150, 180, 270};
int nb_shutterspds = 8;
static uint8_t buffer_command[1000];

int nb_leds = 7;
int led_pos[] = {1, 2, 3, 4, 5, 6, 7};

// '''
// INIT:
// 	1. select led

// 	2. take RAW img && convert it to BMP
// 	3. demosaice the img

// 	4. repeat steps 2 && 3 for each shutter speed

// 	5. repeat steps 1 to 4 for each led

// MAIN:
// 	1. select led

// 	2. take RAW img && convert it to BMP
// 	3. demosaice the img
// 	4. apply WHITE BALANCE using the WHITE REF IMG

// 	5. repeat steps 2 to 4 for each shutter speed

// 	6. repeat steps 1 to 5 for each led
// '''

int main(){
	sprintf((char *)buffer_command, "cd ~/Documents/2_RESEARCH_LAB/MAIN_WS \r\n" );
	printf("%s", (char *)buffer_command);
	// system((char *)buffer_command);

	sprintf((char *)buffer_command, "mkdir -p AWB_imgs \r\n" );
	printf("%s", (char *)buffer_command);
	// system((char *)buffer_command);

	for (int j = 1; j < nb_leds; j++)
	{
		sprintf((char *)buffer_command, "cd ~/Documents/RESEARCH_LAB/led_control_ws/rpi_ws281x-master/build \r\n" );
    	printf("%s", (char *)buffer_command);
    	// system((char *)buffer_command);

		sprintf((char *)buffer_command, "./test %d %d %d %d %d %d %d\r\n", (led_pos[0]==j), (led_pos[1]==j), (led_pos[2]==j), (led_pos[3]==j), (led_pos[4]==j), (led_pos[5]==j), (led_pos[6]==j));
	   	printf("%s", (char *)buffer_command);
	   	// system((char *)buffer_command);
	   	// sleep(200); //in milliseconds

	   	sprintf((char *)buffer_command, "cd ~/Documents/2_RESEARCH_LAB/MAIN_WS/AWB_imgs \r\n" );
	    printf("%s", (char *)buffer_command);
	    // system((char *)buffer_command);

	    // // Take a raw image with a specific shutter spd, convert it to bmp, and remove extra images
		for(int i =0; i<nb_shutterspds; i++)
		{	
			sprintf((char *)buffer_command, "libcamera-still -r -o WBI_LD%d_SS%d.jpg --shutter %d --gain 1 --awbgains 1 --immediate \r\n", j, i, shutterspds[i]);
	    	printf("%s", (char *)buffer_command);
	    	// system((char *)buffer_command);

	    	sprintf((char *)buffer_command, "rm WBI_LD%d_SS%d.jpg \r\n", j, i);
	    	printf("%s", (char *)buffer_command);
	    	// system((char *)buffer_command);

	    	sprintf((char *)buffer_command, "./dcraw -D -c WBI_LD%d_SS%d.dng | ppmtobmp > WBI_LD%d_SS%d.bmp \r\n", j, i, j, i);
	    	printf("%s", (char *)buffer_command);
	    	// system((char *)buffer_command);

	    	sprintf((char *)buffer_command, "rm WBI_LD%d_SS%d.dng \r\n", j, i);
	    	printf("%s", (char *)buffer_command);
	    	// system((char *)buffer_command);

	    	sprintf((char *)buffer_command, "./demosaice_img WBI_LD%d_SS%d.bmp \r\n\r\n\r\n", j, i);
	    	printf("%s", (char *)buffer_command);
	    	// system((char *)buffer_command);
		}
	}

	return 0;
}
	
//int main(){
	// system("cd ~/Documents/2_RESEARCH_LAB/MAIN_WS");


	// system("cd ~/Documents/RESEARCH_LAB/led_control_ws/rpi_ws281x-master/build");
	// system("./test 1 1");
	// sleep(200); //in milliseconds

	// system("cd ~/Documents/2_RESEARCH_LAB/MAIN_WS");

	// // Take a raw image with a specific shutter spd, convert it to bmp, and remove extra images
	// system("libcamera-still -r -o WBI_LD1_SS1.jpg --shutter 20 --gain 1 --awbgains 1 --immediate"); //in microseconds
	// system("rm WBI_LD1_SS1.jpg");
	// system("./dcraw -D -c WBI_LD1_SS1.dng | ppmtobmp > WBI_LD1_SS1.bmp");
	// system("rm WBI_LD1_SS1.dng");


	// system("libcamera-still -r -o WBI_LD1_SS2.jpg --shutter 30 --gain 1 --awbgains 1 --immediate"); //in microseconds
	// system("rm WBI_LD1_SS2.jpg");
	// system("./dcraw -D -c WBI_LD1_SS2.dng | ppmtobmp > WBI_LD1_SS2.bmp");
	// system("rm WBI_LD1_SS2.dng");


	// system("libcamera-still -r -o WBI_LD1_SS3.jpg --shutter 50 --gain 1 --awbgains 1 --immediate"); //in microseconds
	// system("rm WBI_LD1_SS3.jpg");
	// system("./dcraw -D -c WBI_LD1_SS3.dng | ppmtobmp > WBI_LD1_SS3.bmp");
	// system("rm WBI_LD1_SS3.dng");


	// system("libcamera-still -r -o WBI_LD1_SS4.jpg --shutter 60 --gain 1 --awbgains 1 --immediate"); //in microseconds
	// system("rm WBI_LD1_SS4.jpg");
	// system("./dcraw -D -c WBI_LD1_SS4.dng | ppmtobmp > WBI_LD1_SS4.bmp");
	// system("rm WBI_LD1_SS4.dng");


	// system("libcamera-still -r -o WBI_LD1_SS5.jpg --shutter 90 --gain 1 --awbgains 1 --immediate"); //in microseconds
	// system("rm WBI_LD1_SS5.jpg");
	// system("./dcraw -D -c WBI_LD1_SS5.dng | ppmtobmp > WBI_LD1_SS5.bmp");
	// system("rm WBI_LD1_SS5.dng");


	// system("libcamera-still -r -o WBI_LD1_SS6.jpg --shutter 150 --gain 1 --awbgains 1 --immediate"); //in microseconds
	// system("rm WBI_LD1_SS6.jpg");
	// system("./dcraw -D -c WBI_LD1_SS6.dng | ppmtobmp > WBI_LD1_SS6.bmp");
	// system("rm WBI_LD1_SS6.dng");


	// system("libcamera-still -r -o WBI_LD1_SS7.jpg --shutter 180 --gain 1 --awbgains 1 --immediate"); //in microseconds
	// system("rm WBI_LD1_SS7.jpg");
	// system("./dcraw -D -c WBI_LD1_SS7.dng | ppmtobmp > WBI_LD1_SS7.bmp");
	// system("rm WBI_LD1_SS7.dng");


	// system("libcamera-still -r -o WBI_LD1_SS8.jpg --shutter 270 --gain 1 --awbgains 1 --immediate"); //in microseconds
	// system("rm WBI_LD1_SS8.jpg");
	// system("./dcraw -D -c WBI_LD1_SS8.dng | ppmtobmp > WBI_LD1_SS8.bmp");
	// system("rm WBI_LD1_SS8.dng");


	// system("libcamera-still -r -o WBI_LD1_SS9.jpg --shutter 350 --gain 1 --awbgains 1 --immediate"); //in microseconds
	// system("rm WBI_LD1_SS9.jpg");
	// system("./dcraw -D -c WBI_LD1_SS9.dng | ppmtobmp > WBI_LD1_SS9.bmp");
	// system("rm WBI_LD1_SS9.dng");


	// system("libcamera-still -r -o WBI_LD1_SS10.jpg --shutter 450 --gain 1 --awbgains 1 --immediate"); //in microseconds
	// system("rm WBI_LD1_SS10.jpg");
	// system("./dcraw -D -c WBI_LD1_SS10.dng | ppmtobmp > WBI_LD1_SS10.bmp");
	// system("rm WBI_LD1_SS10.dng");


	// system("./demosaice_img WBI_LD1_SS1.bmp");
	// system("./demosaice_img WBI_LD1_SS2.bmp");
	// system("./demosaice_img WBI_LD1_SS3.bmp");
	// system("./demosaice_img WBI_LD1_SS4.bmp");
	// system("./demosaice_img WBI_LD1_SS5.bmp");
	// system("./demosaice_img WBI_LD1_SS6.bmp");
	// system("./demosaice_img WBI_LD1_SS7.bmp");
	// system("./demosaice_img WBI_LD1_SS8.bmp");
	// system("./demosaice_img WBI_LD1_SS9.bmp");
	// system("./demosaice_img WBI_LD1_SS10.bmp");




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
	


//	return 0;
//}
