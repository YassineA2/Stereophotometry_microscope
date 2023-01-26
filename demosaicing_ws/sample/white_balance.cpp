#include "../EasyBMP.h"
using namespace std;


void copy_img_to_img(BMP Image_input, BMP &Image_output){
  for(int img_x = 0; img_x < Image_input.TellWidth(); img_x++){
    for(int img_y = 0; img_y < Image_input.TellHeight(); img_y++){
      Image_output(img_x,img_y)->Red= Image_input(img_x,img_y)->Red;
      Image_output(img_x,img_y)->Green = Image_input(img_x,img_y)->Green;
      Image_output(img_x,img_y)->Blue = Image_input(img_x,img_y)->Blue;
      Image_output(img_x,img_y)->Alpha = Image_input(img_x,img_y)->Alpha;
    }
  }
}

void clean_channels(BMP Image_input, BMP &Image_output){
  for(int img_x = 0; img_x < Image_input.TellWidth(); img_x = img_x + 2){
    for(int img_y = 0; img_y < Image_input.TellHeight(); img_y = img_y +2){

      Image_output(img_x,img_y)->Red= 0;
      Image_output(img_x,img_y)->Green= 0;
      Image_output(img_x,img_y)->Blue= Image_input(img_x,img_y)->Blue;
      Image_output(img_x,img_y)->Alpha= 0;

      Image_output(img_x+1,img_y)->Red = 0;
      Image_output(img_x+1,img_y)->Green = Image_input(img_x+1,img_y)->Green;
      Image_output(img_x+1,img_y)->Blue = 0;
      Image_output(img_x+1,img_y)->Alpha = 0;

      Image_output(img_x,img_y+1)->Red = 0;
      Image_output(img_x,img_y+1)->Green = Image_input(img_x,img_y+1)->Green;
      Image_output(img_x,img_y+1)->Blue = 0;
      Image_output(img_x,img_y+1)->Alpha = 0;

      Image_output(img_x+1,img_y+1)->Red = Image_input(img_x+1,img_y+1)->Red;
      Image_output(img_x+1,img_y+1)->Green = 0;
      Image_output(img_x+1,img_y+1)->Blue = 0;
      Image_output(img_x+1,img_y+1)->Alpha = 0;
    }
  }
}

void demosaicing_basic(BMP Image_input, BMP &Image_output){
  for(int img_x = 0; img_x < Image_input.TellWidth(); img_x = img_x + 2){
      for(int img_y = 0; img_y < Image_input.TellHeight(); img_y = img_y + 2){

        Image_output(img_x/2,img_y/2)->Red= Image_input(img_x+1,img_y+1)->Red;;
        Image_output(img_x/2,img_y/2)->Green= (Image_input(img_x+1,img_y)->Green + Image_input(img_x,img_y+1)->Green)/2;
        Image_output(img_x/2,img_y/2)->Blue= Image_input(img_x,img_y)->Blue;
        Image_output(img_x/2,img_y/2)->Alpha= 0;
      }
    }
}

void homegenise_light(BMP &Image_output, BMP demosaiced_white){
  int max_x=0, max_y=0;

  //Get max intensity
  for(int x = 0; x < demosaiced_white.TellWidth(); x++){
    for(int y = 0; y < demosaiced_white.TellHeight(); y++){
      if(demosaiced_white(x,y)->Green >= demosaiced_white(max_x,max_y)->Green){
        max_x = x;
        max_y = y;
      }
    }
  }
  // white balance
  for(int x = 0; x < demosaiced_white.TellWidth(); x++){
    for(int y = 0; y < demosaiced_white.TellHeight(); y++){
      Image_output(x,y)->Red = demosaiced_white(max_x,max_y)->Red * Image_output(x,y)->Red / demosaiced_white(x,y)->Red;
      Image_output(x,y)->Green = demosaiced_white(max_x,max_y)->Green * Image_output(x,y)->Green / demosaiced_white(x,y)->Green;
      Image_output(x,y)->Blue = demosaiced_white(max_x,max_y)->Blue * Image_output(x,y)->Blue / demosaiced_white(x,y)->Blue;
    }
  }
}

void white_balance(BMP &Image_output, BMP demosaiced_white){
    int max_val=0; 
    float coeff_R=0.0, coeff_G=0.0, coeff_B=0.0;

    //Get max intensity
  for(int x = 0; x < demosaiced_white.TellWidth(); x++)
  {
      for(int y = 0; y < demosaiced_white.TellHeight(); y++)
      {
        if((demosaiced_white(x,y)->Red >= demosaiced_white(x,y)->Green) && (demosaiced_white(x,y)->Red >= demosaiced_white(x,y)->Blue))
          max_val = demosaiced_white(x,y)->Red;
        if((demosaiced_white(x,y)->Green >= demosaiced_white(x,y)->Red) && (demosaiced_white(x,y)->Green >= demosaiced_white(x,y)->Blue))
            max_val = demosaiced_white(x,y)->Green;
        if((demosaiced_white(x,y)->Blue >= demosaiced_white(x,y)->Red) && (demosaiced_white(x,y)->Blue >= demosaiced_white(x,y)->Green))
          max_val = demosaiced_white(x,y)->Blue;

        coeff_R = max_val / demosaiced_white(x,y)->Red;
        coeff_G = max_val / demosaiced_white(x,y)->Green;
        coeff_B = max_val / demosaiced_white(x,y)->Blue;

        Image_output(x,y)->Red   = coeff_R * Image_output(x,y)->Red;
        Image_output(x,y)->Green = coeff_G * Image_output(x,y)->Green;
        Image_output(x,y)->Blue  = coeff_B * Image_output(x,y)->Blue;
      }
    }
}


int main( int argc, char* argv[] )
{
  
  BMP Image_input;
  BMP White_img_input;

  Image_input.ReadFromFile(argv[1]);
  White_img_input.ReadFromFile(argv[2]);

  white_balance(Image_input, White_img_input);
  Image_input.WriteToFile(argv[1]);
}

// g++ -o demosaice_img init_test.cpp ../EasyBMP.cpp




  


  

  