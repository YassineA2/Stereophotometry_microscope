#include <iostream>
#include <stdlib.h>
#include<unistd.h>
#include <stdio.h>
#define MAX_SHUTTER_SPEEDS 7


static uint8_t buffer_command[1000]; // used to pass the commands using the system() function

int shutter_speeds[MAX_SHUTTER_SPEEDS];
int i = 0;

// '''
// INIT:
// 	1. select led

// 	2. take RAW img && convert it to BMP
// 	3. demosaice the img

// 	4. repeat steps 2 && 3 for each shutter speed

// MAIN:
// 	1. select led

// 	2. take RAW img && convert it to BMP
// 	3. demosaice the img
// 	4. apply WHITE BALANCE using the WHITE REF IMG

// 	5. repeat steps 2 to 4 for each shutter speed
// '''

int main(int argc, char **argv){
	char s[100];
	int j = atoi(argv[1]);

	/* Open the file containing the shutter speeds, and affect them to the appropriate array */
    FILE *file = fopen("shutter_speeds.txt", "r");
    if (!file) {
        fprintf(stderr, "Error: failed to open shutter_speeds.txt\n");
        return 1;
    }
    // Read in the values
    while (fscanf(file, "%d", &shutter_speeds[i]) == 1) {
        i++;
        if (i >= MAX_SHUTTER_SPEEDS) break;
    }
    // Close the file
    fclose(file);
	
	/* change directory to the Main workspace */
	chdir("/home/eurposeidon/Documents/2_RESEARCH_LAB/MAIN_WS");
	printf("%s\n", getcwd(s,100));
	
	/* create a folder that will hold the images */
	sprintf((char *)buffer_command, "mkdir -p AWB_imgs" );
	system((char *)buffer_command);
	//printf("%s", (char *)buffer_command);
	
	/* change directory to the created folder */
	chdir("/home/eurposeidon/Documents/2_RESEARCH_LAB/MAIN_WS/AWB_imgs");
	printf("%s\n", getcwd(s,100));
	     
	/* Take a raw image with a specific shutter spd, convert it to bmp, and remove extra images */
	for(int i =0; i<MAX_SHUTTER_SPEEDS; i++)
	{	
		/* command that captures the raw image, you can specify extra parameters if needed */
		sprintf((char *)buffer_command, "libcamera-still -r -o WBI_LD%d_SS%d.jpg --shutter %d --gain 1 --awbgains 1,1 --immediate -n -v 0", j, i, shutter_speeds[i]);
	   	system((char *)buffer_command);

	   	/* uncomment to remove the generated jpg image */
	    // sprintf((char *)buffer_command, "rm WBI_LD%d_SS%d.jpg \r\n", j, i);
	    // system((char *)buffer_command);

	   	/* convert the dng image, to ppm, and then to bmp */ 
	    sprintf((char *)buffer_command, "/home/eurposeidon/Documents/2_RESEARCH_LAB/dcraw/dcraw -D -W -j -c WBI_LD%d_SS%d.dng | ppmtobmp > WBI_LD%d_SS%d.bmp", j, i, j, i);
	    system((char *)buffer_command);

	    /* uncomment to delete the dng image */
	    // sprintf((char *)buffer_command, "rm WBI_LD%d_SS%d.dng \r\n", j, i);
	    // system((char *)buffer_command);

	    /* demosaice the image */
	    sprintf((char *)buffer_command, "/home/eurposeidon/Documents/2_RESEARCH_LAB/demosaicing_ws/sample/demosaice_img WBI_LD%d_SS%d.bmp", j, i);
	    system((char *)buffer_command);
	}
	return 0;
}