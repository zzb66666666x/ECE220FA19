#include "functions.h"
//#include<stdio.h>

/* Intro
 * This file implements several functions to process the signals of images;
 * 
 * We have functions including getRadius, calculateGausFilter, convolveImage,
 * convertToGray, invertImages, colorDodge, pencilSketch, pixelate, transform,
 * nearestPixel.
 *
 * This file provides service functions for two major files including imageData.c and main.c.
 *
 * This file takes the input in the form of color channels which are provided after decoding the png pictures.
 */



/*
 * getRadius - returns the radius based on the sigma value
 * INPUTS: sigma - sigma in the Guassian distribution
 * OUTPUTS: none
 * RETURN VALUE: radius - radius of the filter
 */
int getRadius(double sigma)
{
  /*Write your function here*/
	int radius;
	radius = ceil(3*sigma); 
  	return radius;
}

/*
 * calculateGausFilter - calculates the Gaussian filter
 * INTPUTS: gausFitler - pointer to the array for the gaussian filter
 *          sigma - the sigma in the Gaussian distribution
 * OUTPUTS: none
 * RETURN VALUE: none
 */
void calculateGausFilter(double *gausFilter,double sigma)
{
  /*Write your function here*/
	int radius = getRadius(sigma);
	int width,height;
	height = 2*radius+1;						//if the radius is 8, then the width and height should be 17: it means 17*17 elements, iterate from 0 to 16
	width = height;
	int origin_x,origin_y;
	origin_x = origin_y = radius;				//the index should start from 0 to perhaps 16, and the origin should be 8: 0-7 and 9-16
	int index;
	double gauss_val;
	double gauss_val_norm;
	double sum = 0;
	int x,y;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			index = i + j*width;				//calculate the index in the array called gausFilter
			x = i-origin_x;						//try to calculate the difference
			y = j-origin_y;
			gauss_val = 1/(sqrt(2*M_PI*sigma*sigma)) * exp(-1*((x*x+y*y)/(2*sigma*sigma)));
			sum = sum+gauss_val;
			gausFilter[index] = gauss_val;		//The gausFilter here is a pointer which contains the entry address of an array, I can use it as an double array.
		}
	}
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			index = i + j*width;
			gauss_val_norm = gausFilter[index]/sum;
			gausFilter[index] = gauss_val_norm;
		}
	}
  return;
}

/* convolveImage - performs a convolution between a filter and image
 * INPUTS: inRed - pointer to the input red channel
 *         inGreen - pointer to the input green channel
 *         inBlue - pointer to the input blue channel
 *         inAlpha - pointer to the input alpha channel
 *         filter - pointer to the convolution filter
 *         radius - radius of the convolution filter
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel
 *          outGreen - pointer to the output green channel
 *          outBlue - pointer to the output blue channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void convolveImage(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                   uint8_t *inAlpha, uint8_t *outRed,uint8_t *outGreen,
                   uint8_t *outBlue,uint8_t *outAlpha,const double *filter,
                   int radius,int width,int height)
{
  /*Write your function here*/
	uint8_t * ch_in[4] = {inRed, inGreen, inBlue, inAlpha};		//Now the ch_in is an array to contain four pointers
	uint8_t * ch_out[4] = {outRed,outGreen,outBlue,outAlpha};	//which contains the address of variables like inRed, inGreen, etc.
  /* use ch_in[0] to represent pointer inRed */
	int index;													
	int filterSize=(2*radius+1)*(2*radius+1);
	uint8_t tempSection[filterSize] = {0};						//this is for taking out sections of images for convolution
	int left,right,up,down;
	int x_origin,y_origin;
	x_origin = y_origin = radius;
	int sectionIndex;
	int deltaIndex;												//index + deltaIndex = the index of a pixel in the input color channels
	int x_diff,y_diff;
	double sum;
	uint8_t ans; 
	int k;														//clear the tempSection at the beginning of every loop
	for (int channel = 0; channel < 4; channel++)
	{
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				index = j*width + i;				
				if (channel == 3){								//the condition for alpha channel
					ch_out[channel][index] = ch_in[channel][index];				
				}
				else if (radius < 1){
					ch_out[channel][index] = ch_in[channel][index];
				}
				else{
				/*code for convolution*/
					for (k = 0; k < filterSize; k++ )			//clear the tempSection
					{
						tempSection[k] = 0;
					}
					sum = 0;									//reset the sum of convolution
				/*first pick the section from the image*/
					if ((i-radius)<0){left = i;}				//the length of possible extension from the origin(how many blocks are allowed in each direction)
					else{left = radius;}
					if ((j-radius)<0){up = j;}
					else{up = radius;}
					if ((i+radius)>(width-1)){right = width-1-i;}
					else{right = radius;}
					if ((j+radius)>(height-1)){down = height-1-j;}
					else{down = radius;}
					/*finish calculating the extension from origin*/
					for (int x = 0; x < 2*radius+1; x++)
						{
							for(int y = 0; y < 2*radius +1; y++)
							{
								if ((x>=x_origin-left)&&(x<=x_origin+right)&&(y>=y_origin-up)&&(y<=y_origin+down)){
									sectionIndex = x + y*(2*radius+1);
									x_diff = x - x_origin;
									y_diff = y - y_origin;		//for calculating the delta index
									deltaIndex = (x_diff + y_diff*width);
									tempSection[sectionIndex] = ch_in[channel][index+deltaIndex];
								}
							} 
						}
					/*successfully pick the appropriate section of original image for convolution*/
					/*implement the convolution*/
					for (int x = 0; x < 2*radius+1; x++)
						{
							for(int y = 0; y < 2*radius +1; y++)
							{
								sectionIndex = x + y*(2*radius+1);
								sum = sum + filter[sectionIndex]*((double)tempSection[sectionIndex]);
							}
						}
					/*finish the convoltion*/
					ans = (uint8_t)sum;
					if (ans > 255){ans = 255;}
					ch_out[channel][index] = ans;				//save the answer
				}
			}
		}
	}
  return;
}

/* convertToGray - convert the input image to grayscale
 * INPUTS: inRed - pointer to the input red channel
 *         inGreen - pointer to the input green channel
 *         inBlue - pointer to the input blue channel
 *         inAlpha - pointer to the input alpha channel
 *         gMonoMult - pointer to array with constants to be multipiled with 
 *                     RBG channels to convert image to grayscale
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel
 *          outGreen - pointer to the output green channel
 *          outBlue - pointer to the output blue channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void convertToGray(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                   uint8_t *inAlpha,uint8_t *outRed,uint8_t *outGreen,
                   uint8_t *outBlue,uint8_t *outAlpha,
                   const double *gMonoMult,int width,int height)
{
  /*Challenge- Write your function here*/
	uint8_t * ch_in[4] = {inRed, inGreen, inBlue, inAlpha};		//Now the ch_in is an array to contain four pointers
	uint8_t * ch_out[4] = {outRed,outGreen,outBlue,outAlpha};	//which contains the address of variables like inRed, inGreen, etc..
	int index;
	double coef1,coef2,coef3;
	coef1 = gMonoMult[0];										//coeficients
	coef2 = gMonoMult[1];
	coef3 = gMonoMult[2];
	double R,G,B;
	double ans;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			index = i + j*width;
			R = (double)ch_in[0][index];
			G = (double)ch_in[1][index];
			B = (double)ch_in[2][index];
			ans = (double)(coef1*R + coef2*G + coef3*B);		//the gray value
			ch_out[0][index] = ch_out[1][index] = ch_out[2][index] = ans;
		}
	}
  return;
}

/* invertImage - inverts the colors of the image
 * INPUTS: inRed - pointer to the input red channel
 *         inGreen - pointer to the input green channel
 *         inBlue - pointer to the input blue channel
 *         inAlpha - pointer to the input alpha channel
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel
 *          outGreen - pointer to the output green channel
 *          outBlue - pointer to the output blue channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void invertImage(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                 uint8_t *inAlpha,uint8_t *outRed,uint8_t *outGreen,
                 uint8_t *outBlue,uint8_t *outAlpha,int width,int height)
{
  /*Challenge- Write your function here*/
  /*Inverts the value of the pixel p, in each channel to 255 - p. Alpha channel is not inverted but just copied from the input channel*/
	uint8_t * ch_in[4] = {inRed, inGreen, inBlue, inAlpha};		//Now the ch_in is an array to contain four pointers
	uint8_t * ch_out[4] = {outRed,outGreen,outBlue,outAlpha};	//which contains the address of variables like inRed, inGreen, etc..
	int index;
	for (int channel = 0; channel < 4; channel++)
	{
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				index = i + j*width;
				if (channel == 3){
					ch_out[channel][index] = ch_in[channel][index]; 
				}			
				else{											//not in alpha channel: 255 - pixel value
					ch_out[channel][index] = 255 - ch_in[channel][index];
				}
			}
		}
	}
  return;
}

/* pixelate - pixelates the image
 * INPUTS: inRed - pointer to the input red channel
 *         inGreen - pointer to the input green channel
 *         inBlue - pointer to the input blue channel
 *         inAlpha - pointer to the input alpha channel
 *         pixelateY - height of the block
 *         pixelateX - width of the block
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel
 *          outGreen - pointer to the output green channel
 *          outBlue - pointer to the output blue channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void pixelate(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,uint8_t *inAlpha,
              uint8_t *outRed,uint8_t *outGreen,uint8_t *outBlue,
              uint8_t *outAlpha,int pixelY,int pixelX,int width,int height)
{
  /*Challenge- Write your function here*/
	uint8_t * ch_in[4] = {inRed,inGreen,inBlue,inAlpha};
	uint8_t * ch_out[4] = {outRed,outGreen,outBlue,outAlpha};
	int starti = 0;
	int startj = 0;
	int blockSum = 0;
	int index;
	int blockIndex;
	int blocki;
	int blockj;
	double average;
	int right_loops;											//how many iterations when the block is moving right
	int down_loops;
	int right_loop_end = pixelX;
	int down_loop_end = pixelY;	
	right_loops = ceil(width/pixelX);							//the ceil function show how many times should we iterate each row/column
	down_loops = ceil(height/pixelY);
	for (int channel = 0; channel < 4; channel++)
	{
		for (int j = 0; j <	down_loops; j++)
		{	
			if (j == down_loops-1){
				down_loop_end = height - startj;				//border condition(not enough space), we use height(width) to replace 
			}
			else{
				down_loop_end = pixelY;
			}
			for (int i = 0; i < right_loops; i++)
			{
				//printf("the j is %d\n",j);
				//printf("the i is %d\n",i);
				//printf("the startj is %d\n",startj);
				//printf("the starti is %d\n",starti);
				//printf("\n");
				if (i == right_loops-1){						//last iteration
					right_loop_end = width - starti;			//right_loop_end will be used in the following for loops			
				}
				else{
					right_loop_end = pixelX;
				}
				index = starti + startj*width;
				blockSum = 0;									//clear the sum
				for (blockj = 0; blockj < down_loop_end; blockj++)
				{
					for (blocki = 0; blocki < right_loop_end; blocki++)
					{
						blockIndex = blocki + blockj*width;		//relative index
						blockSum = blockSum + ch_in[channel][index + blockIndex];
					}
				}
				average = blockSum / (right_loop_end*down_loop_end);
				for (blockj = 0; blockj < down_loop_end;blockj++)//begin to assign values for each pixel by the average value
				{
					for (blocki = 0; blocki < right_loop_end; blocki++)
					{
						blockIndex = blocki + blockj*width;
						ch_out[channel][index + blockIndex] = (uint8_t)average;
					}
				}
				starti += pixelX;
			}
			starti = 0;
			startj += pixelY;		
		}	
	starti = 0;
	startj = 0;									
	}
  return;
}

/* colorDodge - blends the bottom layer with the top layer
 * INPUTS: aRed - pointer to the bottom red channel
 *         aGreen - pointer to the bottom green channel
 *         aBlue - pointer to the bottom blue channel
 *         aAlpha - pointer to the bottom alpha channel
 *         bRed - pointer to the top red channel
 *         bGreen - pointer to the top green channel
 *         bBlue - pointer to the top blue channel
 *         bAlpha - pointer to the top alpha channel
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel
 *          outGreen - pointer to the output green channel
 *          outBlue - pointer to the output blue channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void colorDodge(uint8_t *aRed,uint8_t *aGreen,uint8_t *aBlue,
                uint8_t *aAlpha,uint8_t *bRed,uint8_t *bGreen,
                uint8_t *bBlue,uint8_t *bAlpha,uint8_t *outRed,
                uint8_t *outGreen,uint8_t *outBlue,uint8_t *outAlpha,
                int width,int height)
{
   /*Challenge- Write your function here*/
	uint8_t * bottom_ch_in[4] = {aRed, aGreen, aBlue, aAlpha};	//Now the ch_in is an array to contain four pointers
	uint8_t * top_ch_in[4] = {bRed, bGreen, bBlue, bAlpha};		//this is the top layer
	uint8_t * ch_out[4] = {outRed,outGreen,outBlue,outAlpha};	//which contains the address of variables like inRed, inGreen, etc..
	int index;
	for (int channel = 0; channel < 4; channel++)
	{
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				index = i + j*width;
				if (channel == 3){								//alpha channel
					ch_out[channel][index] = bottom_ch_in[channel][index]; 
				}			
				else{											//other channels
					if (top_ch_in[channel][index] == 255){		//the channel has 255
						ch_out[channel][index] = top_ch_in[channel][index];
					}
					else{										//the value is not 255
						ch_out[channel][index] = min(((bottom_ch_in[channel][index]<<8)/(255-top_ch_in[channel][index])),255);
					}
				}
			}
		}
	}	
   return;
}

/* pencilSketch - creates a pencil sketch of the input image
 * INPUTS: inRed - pointer to the input red channel
 *         inGreen - pointer to the input green channel
 *         inBlue - pointer to the input blue channel
 *         inAlpha - pointer to the input alpha channel
 *         invRed - pointer to temporary red channel for inversion
 *         invGreen - pointer to temporary green channel for inversion
 *         invBlue - pointer to temporary blue channel for inversion
 *         invAlpha - pointer to temporary alpha channel for inversion
 *         blurRed - pointer to temporary red channel for blurring
 *         blurGreen - pointer to temporary green channel for blurring
 *         blurBlue - pointer to temporary blue channel for blurring
 *         blurAlpha - pointer to temporary alpha channel for blurring
 *         filter - pointer to the gaussian filter to blur the image
 *         radius - radius of the gaussian filter
 *         width - width of the input image
 *         height - height of the input image
 *         gMonoMult - pointer to array with constants to be multipiled with 
 *                     RBG channels to convert image to grayscale
 * OUTPUTS: outRed - pointer to the output red channel
 *          outGreen - pointer to the output green channel
 *          outBlue - pointer to the output blue channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void pencilSketch(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                  uint8_t *inAlpha,uint8_t *invRed,uint8_t *invGreen,
                  uint8_t *invBlue,uint8_t *invAlpha,uint8_t *blurRed,
                  uint8_t *blurGreen,uint8_t *blurBlue,uint8_t *blurAlpha,
                  uint8_t *outRed,uint8_t *outGreen,uint8_t *outBlue,
                  uint8_t *outAlpha,const double *filter,int radius,int width,
                  int height,const double *gMonoMult)
{
    /*Challenge- Write your function here*/
	convertToGray(inRed,inGreen,inBlue,inAlpha,outRed,outGreen,outBlue,outAlpha,gMonoMult,width,height);
	invertImage(outRed,outGreen,outBlue,outAlpha,invRed,invGreen,invBlue,invAlpha,width,height);
	convolveImage(inRed,inGreen,inBlue,inAlpha,blurRed,blurGreen,blurBlue,blurAlpha,filter,radius,width,height);
	colorDodge(blurRed,blurGreen,blurBlue,blurAlpha,invRed,invGreen,invBlue,invAlpha,outRed,outGreen,outBlue,outAlpha,width,height);
    return;
}

/* transformImage - Computes an linear transformation of the input image
 * INPUTS: inRed - pointer to the input red channel
 *         inGreen - pointer to the input green channel
 *         inBlue - pointer to the input blue channel
 *         inAlpha - pointer to the input alpha channel
 *	    transform - two dimensional array containing transform coefficients of matrix T and vector S
 *         width - width of the input and output image
 *         height - height of the input and output image
 * OUTPUTS: outRed - pointer to the output red channel
 *          outGreen - pointer to the output green channel
 *          outBlue - pointer to the output blue channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void transformImage(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,uint8_t *inAlpha,
              uint8_t *outRed,uint8_t *outGreen,uint8_t *outBlue,
              uint8_t *outAlpha,double transform[2][3],int width,int height)
{
     /*Write your function here*/
	uint8_t * ch_in[4] = {inRed, inGreen, inBlue, inAlpha};		//Now the ch_in is an array to contain four pointers
	uint8_t * ch_out[4] = {outRed,outGreen,outBlue,outAlpha};	//which contains the address of variables like inRed, inGreen, etc..
	int index;
	int origin_index;
	int pixelX,pixelY;											//the pointer of this variable will be passed to the nearestPixel
	for (int channel = 0; channel < 4; channel++)
	{						
		for (int i = 0; i < width; i++)								
		{	
			for (int j = 0; j < height; j++)
			{
				index = i + j*width;
				/*pixelXTransform generates from i and pixelYTransform generates from j*/
				nearestPixel(j,i,transform,&pixelY,&pixelX,width,height);
				origin_index = pixelY*width + pixelX;
				if (!((pixelX>=0)&&(pixelX<=width-1)&&(pixelY>=0)&&(pixelY<=height-1))){
					if (channel == 3){							//alpha channel
						ch_out[channel][index] = 255;
					}
					else{										//not alpha channel
						ch_out[channel][index] = 0;				
					}
				}
				else{
					ch_out[channel][index] = ch_in[channel][origin_index];
				}
			}
		}
	}



     return;
}

/* nearestPixel - computes the inverse transform to find the closest pixel in the original image
 * INPUTS: pixelYtransform - row value in transformed image
 *         pixelXtransform - column value in transformed image
 *         transform - two dimensional array containing transform coefficients of matrix T and vector S
 *         width - width of the input and output image
 *         height - height of the input and output image
 * OUTPUTS: pixelY - pointer to row value in original image
 *	    pixelX - pointer to column value in original image
 * RETURN VALUES: none
 */
void nearestPixel(int pixelYTransform, int pixelXTransform, double transform[2][3],
              int *pixelY, int *pixelX, int width, int height)
{
    /*Write your function here*/
	/*all the X and Y here is relative to the */
	double Inv_Mat_T[4];
	double Vec_S[2];
	double detT = (transform[0][0]*transform[1][1])-(transform[0][1]*transform[1][0]);
	double tempX,tempY;
	double ansX,ansY;
	double centerX,centerY;
	centerX = (width-1)/2;
	centerY = (height-1)/2;
	pixelXTransform = (int)((double)pixelXTransform - centerX);
	pixelYTransform = (int)((double)pixelYTransform - centerY);
	Inv_Mat_T[0] = (transform[1][1])/(detT);							//use determinant to calculate the inverse matrix
	Inv_Mat_T[1] = (transform[0][1])*(-1)*(1/detT);
	Inv_Mat_T[2] = (transform[1][0])*(-1)*(1/detT);
	Inv_Mat_T[3] = (transform[0][0])/(detT);
	Vec_S[0] = transform[0][2];											//get vector S
	Vec_S[1] = transform[1][2];
	tempX = (double)pixelXTransform - Vec_S[0];
	tempY = (double)pixelYTransform - Vec_S[1];					
	ansX = (Inv_Mat_T[0] * tempX) + (Inv_Mat_T[1] * tempY) + centerX;	//calculate the result by doing the matrix multiplication
	ansY = (Inv_Mat_T[2] * tempX) + (Inv_Mat_T[3] * tempY) + centerY;
	*pixelX = (int)round(ansX);
	*pixelY = (int)round(ansY);											//assign value back to the variable pixelX by pointers						
    return;
}

