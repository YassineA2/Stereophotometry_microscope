#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>
#include <stdarg.h>
#include <getopt.h>


#include "clk.h"
#include "gpio.h"
#include "dma.h"
#include "pwm.h"
#include "version.h"

#include "ws2811.h"

#define LED_COUNT 8
#define LED_GPIO 18

ws2811_t ledstring =
{
    .freq = WS2811_TARGET_FREQ,
    .dmanum = 5,
    .channel =
    {
        [0] =
        {
            .gpionum = LED_GPIO,
            .count = LED_COUNT,
            .invert = 0,
            .brightness = 255,
        },
        [1] =
        {
            .gpionum = 0,
            .count = 0,
            .invert = 0,
            .brightness = 0,
        },
    },
};

int main(int argc, char **argv) {
    int var = atoi(argv[1]);
    int ret;
    if ((ret = ws2811_init(&ledstring)) != WS2811_SUCCESS)
    {
        fprintf(stderr, "ws2811_init failed: %s\n", ws2811_get_return_t_str(ret));
        return ret;
    }


    for(int i=0; i<LED_COUNT; i++)
    {
        if(var == i)
        {
            // Change color of the selected LED to white
            ledstring.channel[0].leds[i] = 0xFFFFFF;
            ws2811_render(&ledstring);
        }
        else
        {
            // Turn off the other LED's
            ledstring.channel[0].leds[i] = 0x000000;
            ws2811_render(&ledstring);
        }
    }
    ws2811_fini(&ledstring);
}
