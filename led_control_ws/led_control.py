import board
import neopixel
import argparse

#import sys
#import getopt



my_parser = argparse.ArgumentParser()
my_parser.add_argument('--led_1', action='store', type=int, nargs=3)
my_parser.add_argument('--led_2', action='store', type=int, nargs=3)
args = my_parser.parse_args()

pixels = neopixel.NeoPixel(board.D18, 2)
pixels[0] = (args.led_1[0], args.led_1[1], args.led_1[2])
pixels[1] = (args.led_2[0], args.led_2[1], args.led_2[2])


#					 #
# COMMAND TO EXECUTE #
#					 #

# sudo python3 test.py --led_1 255 255 255  --led_2 255 255 255







#			 #
#  METHOD 1  #
#			 #
#argv = sys.argv[1:]
#try:
#	opts, args = getopt.getopt(argv, "", ["led_1_r =", "led_1_g =", "led_1_b =", "led_2_r =", "led_2_g =", "led_2_b ="])
#except:
#	print("error")

#for opt, arg in opts:
#	if opt== "--led_1_r ":
#		led_1_r = int(arg)		
#	elif opt == "--led_1_g ":
#		led_1_g = int(arg)
#	elif opt == "--led_1_b ":
#		led_1_b = int(arg)

#	elif opt== "--led_2_r ":
#		led_2_r = int(arg)		
#	elif opt == "--led_2_g ":
#		led_2_g = int(arg)
#	elif opt == "--led_2_b ":
#		led_2_b = int(arg)

#print ('Argument List:', str(sys.argv))
#print(sys.argv[1])
#print(sys.argv[2])

#pixels = neopixel.NeoPixel(board.D18, 2)
#pixels[0] = (led_1_r, led_1_g, led_1_b)
#pixels[1] = (led_2_r, led_2_g, led_2_b)

#					 #
# COMMAND TO EXECUTE #
#					 #

# sudo python3 test.py --led_1_r 0 --led_1_g 255 --led_1_b 0 --led_2_r 0 --led_2_g 0 --led_2_b 255




#			 #
#  METHOD 2  #
#			 #

##led_1_r = sys.argv[2]
##led_1_g = sys.argv[4]
##led_1_b = sys.argv[6]
##led_2_r = sys.argv[8]
##led_2_g = sys.argv[10]
##led_2_b = sys.argv[12]
#
##pixels[0] = (led_1_r, led_1_g, led_1_b)
##pixels[1] = (led_2_r, led_2_g, led_2_b)








