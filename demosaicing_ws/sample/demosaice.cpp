// #include "../EasyBMP.h"
// using namespace std;

// int main( int argc, char* argv[] )
// {
//   cout << endl
//       << "Using EasyBMP Version " << _EasyBMP_Version_ << endl << endl
//       << "Copyright (c) by the EasyBMP Project 2005-6" << endl
//       << "WWW: http://easybmp.sourceforge.net" << endl << endl
//       << "TESTING BMP image manipulation"<<endl<<endl;
  
//   BMP Image_input;
//   Image_input.ReadFromFile("EasyBMPbackground.bmp");

//   BMP Output;
//   Output.SetSize( Image_input.TellWidth() , Image_input.TellHeight() );
//   Output.SetBitDepth( 24 );

//   cout << "File info:" <<endl;
//   cout << Output.TellWidth() << "x" << Output.TellHeight() << "  at  " << Output.TellBitDepth()<< "bpp"<<endl;

//   // // show the color of pixel (14,18) + change it + show it again
//   // cout << "(" << (int) Output(14,18)->Red
//   //     << ","
//   //     << (int) Output(14,18)->Green << ","
//   //     << (int) Output(14,18)->Blue << ","
//   //     << (int) Output(14,18)->Alpha << ")" << endl;


//   //     Output(14,18)->Red= 50;
//   //     Output(14,18)->Green = 50;
//   //     Output(14,18)->Blue = 192;
//   //     Output(14,18)->Alpha = 0;

//   //     cout << "(" << (int) Output(14,18)->Red
//   //     << ","
//   //     << (int) Output(14,18)->Green << ","
//   //     << (int) Output(14,18)->Blue << ","
//   //     << (int) Output(14,18)->Alpha << ")" << endl;


// Output.WriteToFile("copied.bmp")
// }

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
  
  // Open a BMP IMG, and demosaice it
  BMP Image_input;
  //Image_input.ReadFromFile("first_test.bmp");
  Image_input.ReadFromFile(argv[1]);

  // show img dimensions
  // cout << "File info:" <<endl;
  // cout << Image_input.TellWidth() << "x" << Image_input.TellHeight() << "  at  " << Image_input.TellBitDepth()<< "bpp"<<endl;

  BMP Image_output;
  Image_output.SetSize( Image_input.TellWidth()/2 , Image_input.TellHeight()/2 );
  Image_output.SetBitDepth( 24 );
  demosaicing_basic(Image_input, Image_output);


  // // open white ref image and demosaice it
  // BMP white_ref_img;
  // white_ref_img.ReadFromFile("white_ref.bmp");

  // BMP demosaiced_white;
  // demosaiced_white.SetSize( white_ref_img.TellWidth()/2 , white_ref_img.TellHeight()/2 );
  // demosaiced_white.SetBitDepth( 24 );
  // demosaicing_basic(white_ref_img, demosaiced_white);

  // // white balancing 
  // homegenise_light(Image_output, demosaiced_white);

  //Image_output.WriteToFile("first_test.bmp");
  Image_output.WriteToFile(argv[1]);
}

// g++ -o demosaice_img init_test.cpp ../EasyBMP.cpp