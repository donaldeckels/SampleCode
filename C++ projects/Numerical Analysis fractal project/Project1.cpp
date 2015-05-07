/*
Donald Eckels
Math 481A
Numerical Analysis Project 1
10/20/13
This program compiles and runs without errors
It is hard-coded to find the roots of x^4 - 4x + 1
by using different iterative methods and a user input starting point
*/

//include statements
#include <iostream>
#include <math.h>
#include <complex>//complex numbers have a real and imaginary part. can be initialized with both values separated by a comma.
				  //operators are overloaded to handle doubles, but not integers
#include <iomanip>
#include <windows.h>//to create bitmaps
using namespace std;

//function headers
complex<double> eval(complex<double> x);
complex<double> deriv_eval(complex<double> x);
complex<double> second_deriv_eval(complex<double> x);
complex<double> ux(complex<double> x);
complex<double> deriv_ux(complex<double> x);
void display_root(int sel);
complex<double> Newton(complex<double> x);
complex<double> Newton2(complex<double> x, complex<double> x0);
complex<double> Newton3(complex<double> x);
complex<double> Steffensen(complex<double> x);
complex<double> Halley(complex<double> x);
complex<double> Secant(complex<double> x2, complex<double> x);
complex<double> Muller(complex<double> x3, complex<double> x2, complex<double> x);
void fractal();

int main(){
	int sel = 1;
	//while loop to continue allowing the user to try different things until they want to exit
	while(sel > 0 && sel <= 8){
		cout << "\nFinding the Roots" << endl << "This program is designed to find roots of f(x) = x^4 - 4x + 1" << endl << "with an accuracy of E-08.\n";
		cout << "----------------------------------" << endl;
		cout << "1) Newton's method" << endl << "2) 1st modified Newton's method" << endl << "3) 2nd modified Newton's method" << endl << "4) Steffensen's method" << endl;
		cout << "5) Halley's method" << endl << "6) Secant method" << endl << "7) Muller's method" << endl << "8) Fractal!" << endl << "9) Exit\n" << endl << "Choice: ";
		cin >> sel;
		//go to manual root finding
		if(sel > 0 && sel <= 7){
			display_root(sel);
		}
		//go to fractal drawing
		if(sel == 8){
			fractal();
		}

	}
	return 0;
}

//evaluates f(x) at the given value
complex<double> eval(complex<double> x)
{
	complex<double> y;
	y= (x*x*x*x) - (x * 4.0) + 1.0;

	return y;
}

//evaluates f'(x) at the given value
complex<double> deriv_eval(complex<double> x)
{
	complex<double> y;
	y = (4.0 * x*x*x) - 4.0;
	return y;
}

//evaluates f''(x) at the given value
complex<double> second_deriv_eval(complex<double> x)
{
	return (12.0 * x * x);
}

//calculates u(x) at the given value.
complex<double> ux(complex<double> x){
	return (eval(x) / deriv_eval(x));
}

//calculates u'(x) at the given value.
complex<double> deriv_ux(complex<double> x){
	complex<double> num, denom;
	num = (pow(x, 6.0) + (4.0 * pow(x, 3.0)) - (3.0 * pow(x, 2.0)) + 4.0);
	denom = (4.0 * ((pow(x, 6.0)) - (2.0 * pow(x, 3.0)) + 1.0));
	
	return (num / denom);
}

//formats and prints the final result of a manual root calculation
void rootprint(complex<double> x, int i){
		cout << setprecision(9);
	cout << "\n\nThe root at " << x.real();
	if(abs(x.imag()) >= 0.00000001){
		if(x.imag() > 0){
			cout << "+";
		}
		cout <<x.imag() << "i";
	}
	cout << " was found after " << i << " iterations." << endl;
}

//this function serves as a guide to handle whichever method is going to be used to manually find a root
void display_root(int sel){
	complex<double> input, input2, input3, temp_out, initial;//holds the current estimate of the root
	complex<double> delta(999,999);
	int max_loop = 10000;
	double temp, tempi;	//will hold the read in values temporarily until they are passed to input
	int i = 0;//start i at 0, kept out of any loops since it's not used multiple times in a single call of display_root
	char yes;//used for indicator to change maximum number of iterations the function can call

	cout << "Would you like to change the maximum number of iterations each point can calculate?\nDefault = 10000 (Y/N): ";
	cin >> yes;
	if(yes == 'y' || yes == 'Y'){
		cout << "please input the maximum number of iterations: ";
		cin >> max_loop;
	}

	cout << "Please input a start point (X_0) to find a root by typing in two doubles to represent a complex number (ie: X+Yi): ";
	//get the user intput and store it
	cin >> temp >> tempi;
	input.real(temp);
	input.imag(tempi);
	initial = input;//for newton's 1st mod
	//get second and third points from user for secant's and Muller's methods
	if(sel == 6 || sel == 7){
		cout << "Please input the second point (X_1) to be used by typing in two doubles to represent a complex number: ";
		cin >> temp >> tempi;
		input2.real(temp);
		input2.imag(tempi);
	}
	if(sel == 7){
		cout << "Please input the third point (X_2) to be used by typing in two doubles to represent a complex number: ";
		cin >> temp >> tempi;
		input3.real(temp);
		input3.imag(tempi);
	}

	//start display table for output information
	cout << "\n\n #  |      x       |    result    |  delta" << endl;
	cout << "----------------------------" << endl;
	
	//loop allows it to keep going until a root is found with a relative error less than the absolute error. This way the absolute is within error as well.
	while(abs(delta) > 0.000000001 && i < max_loop){
		//switch uses the passed in variable to call the requested method each loop iteration with its required input.
		switch(sel){
		case 1:
			temp_out = Newton(input);
			break;
		case 2:
			temp_out = Newton2(input, initial);
			break;
		case 3:
			temp_out = Newton3(input);
			break;
		case 4:
			temp_out = Steffensen(input);
			break;
		case 5:
			temp_out = Halley(input);
			break;
		case 6:
			temp_out = Secant(input, input2);
			break;
		case 7:
			temp_out = Muller(input, input2, input3);
			break;
		}
		i++;
		delta = input - temp_out;
		//display calculated info for user
		cout << setprecision(9) << i << setw(12) << input.real() << "+" << input.imag() << "i  |  " << temp_out.real() << "+" << temp_out.imag() << "i  |  " << abs(delta) << endl;
		
		//shuffle inputs to their new variables
		if(sel == 7){
			input3 = input2;
		}
		if(sel == 6 || sel == 7){
			input2 = input;
		}
		input = temp_out;
	}

	//print if a root was found or not
	if(i < max_loop){
		rootprint(input, i);
	}
	else{
		cout << "No root was found after " << max_loop << " iterations." << endl;
	}
}

//completes one iteration of the Newton's method
complex<double> Newton(complex<double> x)
{

	x = x - (ux(x));

	return x;

}

//completes one iteration of the 1st modification of the Newton's method
complex<double> Newton2(complex<double> x, complex<double> x0)
{
	x = x - (eval(x)/deriv_eval(x0));
	
	return x;
}

//completes one iteration of the 2nd modification of the Newton's method
complex<double> Newton3(complex<double> x)
{
	x = x - (ux(x)/deriv_ux(x));

	return x;
}

//completes one iteration of the Steffensen's method
complex<double> Steffensen(complex<double> x)
{
	complex<double>  numerator, denominator;
	numerator = eval(x) * eval(x);
	denominator = eval(x + eval(x)) - eval(x);
	x = x - (numerator / denominator);

	return x;
}

//completes one iteration of the Halley's method
complex<double> Halley(complex<double> x)
{
	complex<double> numerator, denominator;
	numerator = (eval(x) * deriv_eval(x));
	denominator = (pow(deriv_eval(x), 2.0) - (0.5 * eval(x) * second_deriv_eval(x)));
	x = x - (numerator/denominator);

	return x;
}

//completes one iteration of the secant method
complex<double> Secant(complex<double> x2, complex<double> x)
{

	complex<double> numerator, denominator;
	

	numerator = ((x2 - x) * eval(x2) );
	denominator = (eval(x2) - eval(x));
	x2 = x2 - (numerator/denominator);
	
	return x2;
}

//completes one iteration of the Muller's method
/*
utilized the calculation of a, b, and c on the top of pg 97 instead of the pseudo code on the bottom of the page
*/
complex<double> Muller(complex<double> x2, complex<double> x1, complex<double> x)
{
	complex<double> a, b, c, numerator, denominator;


	c = eval(x2);

	//calculate b
	numerator = (pow((x - x2), 2.0) * (eval(x1) - eval(x2))) - (pow((x1 - x2), 2.0) * (eval(x) - eval(x2)));
	denominator = (x - x2)*(x1 - x2)*(x - x1);
	b = numerator / denominator;

	//calculate a
	numerator = ((x1 - x2) * (eval(x) - eval(x2))) - ((x - x2) * (eval(x1) - eval(x2)));
	
	//denominator is still the same
	a = numerator / denominator;

	//setup for final value
	numerator = 2.0 * c;
	
	denominator = b + ((b/abs(b)) * pow(((b*b) - (4.0 * a * c)), 0.5));

	return (x2 - (numerator/denominator));
}

//function handles the creation of a fractal
void fractal(){
	//variables to handle the processing
	int sel = 1;
	int scale;
	double h = 0.00000001;
	int max_loop = 10000;
	//allows user editing of some calculations
	char yes;

	//the 4 roots of the given function. used for color coding
	complex<double> root1(1.49335856, 0);
	complex<double> root2(0.25099216, 0);
	complex<double> root3(-0.872175357,1.3801316);
	complex<double> root4(-0.872175357, -1.3801316);
	//long pointer to constant wide string - required for bitmap filename
	LPCWSTR filename;

	//user selection of the type of fractal to be generated
	cout << "\nSelect which method you would like to use in making the fractal image.\n";
	cout << "----------------------------------" << endl;
	cout << "1) Newton's method" << endl << "2) 1st modified Newton's method" << endl << "3) 2nd modified Newton's method" << endl << "4) Steffensen's method (WARNING: Will take considerable time to run)" << endl;
	cout << "5) Halley's method" << endl << "6) Secant method" << endl << "7) Muller's method" << endl << "8) back\n" << endl << "Choice: ";
	cin >> sel;

	//allow user to change the max number of iterations and the default distance between the points used in the calculation of secant and Muller
	cout << "Would you like to change the maximum number of iterations each point can calculate?\nDefault = 10000 (Y/N): ";
	cin >> yes;
	if(yes == 'y' || yes == 'Y'){
		cout << "please input the maximum number of iterations: ";
		cin >> max_loop;
	}
	if (sel == 6 || sel == 7){
		cout << "Would you like to change the default h value?\nDefault = 1.0E-08 (Y/N): ";
		cin >> yes;
		if(yes == 'y' || yes == 'Y'){
			cout << "Please input the h distance:";
			cin >> h;
		}
	}

	//switch sets the filename so a fractal of each type can be generated without overwriting
	switch(sel){
	case 1:
		filename = L"Newton_Fractal.bmp";
		break;
	case 2:
		filename = L"Newton_1st_Mod_Fractal.bmp";
		break;
	case 3:
		filename = L"Newton_2nd_Mod_Fractal.bmp";
		break;
	case 4:
		filename = L"Steffensen_Fractal.bmp";
		break;
	case 5:
		filename = L"Halley_Fractal.bmp";
		break;
	case 6:
		filename = L"Secant_Fractal.bmp";
		break;
	case 7:
		filename = L"Muller_Fractal.bmp";
		break;
	default:
		filename = L"Fractal.bmp";
	}


	//set in if statement if user wanted to go back
	if(sel >=1 && sel <=7){
		cout << "Processing - please wait." << endl;

		//variable for handling the bitmap
		HANDLE file;
		BITMAPFILEHEADER fileHeader;
		BITMAPINFOHEADER fileInfo;
		RGBTRIPLE *image;
		DWORD write = 0;
		image = new RGBTRIPLE[1000*1000*24];//define that the image is 1000 X 1000 pixels and each is 24 bits
	 
		file = CreateFile(filename,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);  //Sets up the new bmp to be written to
 
		fileHeader.bfType = 19778;                                                                    //Sets our type to BM or bmp
		fileHeader.bfSize = sizeof(fileHeader.bfOffBits) + sizeof(RGBTRIPLE);                         //Sets the size equal to the size of the header struct
		fileHeader.bfReserved1 = 0;                                                                    //sets the reserves to 0
		fileHeader.bfReserved2 = 0;
		fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);                    //Sets offbits equal to the size of file and info header
 
		fileInfo.biSize = sizeof(BITMAPINFOHEADER);//set all of the file info
		fileInfo.biWidth = 1000;
		fileInfo.biHeight = 1000;
		fileInfo.biPlanes = 1;
		fileInfo.biBitCount = 24;
		fileInfo.biCompression = BI_RGB;
		fileInfo.biSizeImage = 1000 * 1000 * (24/8);
		fileInfo.biXPelsPerMeter = 2400;
		fileInfo.biYPelsPerMeter = 2400;
		fileInfo.biClrImportant = 0;
		fileInfo.biClrUsed = 0;
 
		WriteFile(file,&fileHeader,sizeof(fileHeader),&write,NULL);
		WriteFile(file,&fileInfo,sizeof(fileInfo),&write,NULL);

		//i incriments x axis, or the real value
		for(int i=0 ; i <= 1000 ; i++){
			//incriments the y axis, or imaginary value
			for(int j=0; j <= 1000 ; j++){
				complex<double> input, input2, input3, temp_out, initial;//holds the current estimate of the root
				double temp, tempi;	//will hold the read in values temporarily until they are passed to input
				complex<double> delta(999, 999);
				int loop = 0;//reset loop for each point

				//setup the initial input for each point being located.
				//since 1000 points across were requested for [-2, 2] 250 points are alloted per each full digit
				temp = (i/250.0) - 2.0;
				tempi = 2.0 - (j/250.0);
				input.real(temp);
				input.imag(tempi);
				input2.real(temp+h);
				input2.imag(tempi);
				input3.real(temp+(2*h));
				input3.imag(tempi);
				initial.real(temp);
				initial.imag(tempi);

				//loop to calculate each point 
				while(abs(delta) >= 0.00000001 && loop < max_loop){
					switch(sel){
						case 1:
							temp_out = Newton(input);
							break;
						case 2:
							temp_out = Newton2(input, initial);
							break;
						case 3:
							temp_out = Newton3(input);
							break;
						case 4:
							temp_out = Steffensen(input);
							break;
						case 5:
							temp_out = Halley(input);
							break;
						case 6:
							temp_out = Secant(input, input2);
							break;
						case 7:
							temp_out = Muller(input, input2, input3);
						break;
					}
					loop++;
					//shuffle appropriate variables
					delta = input - temp_out;
					input3 = input2;
					input2 = input;
					input = temp_out;
				}

				//when point is calculated, setup variable for how intense the color will be
				//different functions perform differently further away from a root so the intensity is scaled
				switch(sel){
				case 1:
					if(loop <=3){
						scale = 0;
					}
					else{
						scale = (loop-3) *20;
					}
					break;
				case 2:
					scale = (int)(((loop*1.0)/max_loop) * 255);
					break;
				case 4:
					if(loop <=3){
						scale = 0;
					}
					else{
						scale = (loop-3) *2;
					}
					break;
				case 6:
					if(loop <=3){
						scale = 0;
					}
					else{
						scale = (loop-3) *10;
					}
					break;
				default:
					if(loop <=3){
						scale = 0;
					}
					else{
						scale = (loop-3) *20;
					}
					break;
				}
				
				//add info to bmp. pixels can be accessed by an iterator where 0 is at the bottom left corner and moves right
				//the second row starts on the left just above the previoius and repeats until the last pixel is reached at the top right.
				//since j starts at +2i, the index must be shifted to the last row and -2i, the final of j, to the first.
				
				//if no value was found, color white
				if(loop >= max_loop){
					image[i+(1000*(1000-j))].rgbtRed = 255;
					image[i+(1000*(1000-j))].rgbtGreen = 255;
					image[i+(1000*(1000-j))].rgbtBlue = 255;
				}
				//root 1 gives red
				else if(abs(input.real() - root1.real()) <= 0.1){
					image[i+(1000*(1000-j))].rgbtRed = 255;
					image[i+(1000*(1000-j))].rgbtGreen = scale;
					image[i+(1000*(1000-j))].rgbtBlue = scale;
				}
				//root 2 green
				else if(abs(input.real() - root2.real()) <= 0.1){
					image[i+(1000*(1000-j))].rgbtRed = scale;
					image[i+(1000*(1000-j))].rgbtGreen = 255;
					image[i+(1000*(1000-j))].rgbtBlue = scale;
				}
				//root 3 (positive i)
				else if(abs(input.imag() - root3.imag()) <= 0.1){
					image[i+(1000*(1000-j))].rgbtRed = scale;
					image[i+(1000*(1000-j))].rgbtGreen = scale;
					image[i+(1000*(1000-j))].rgbtBlue = 255;
				}
				// root 4 gives magenta
				else if(abs(input.imag() - root4.imag()) <= 0.1){
					image[i+(1000*(1000-j))].rgbtRed = 255;
					image[i+(1000*(1000-j))].rgbtGreen = scale;
					image[i+(1000*(1000-j))].rgbtBlue = 255;
				}

				//and if no root is found, but the function terminated after less than the maximum (usually due to fast divergence or division by zero at some point)
				//it is colored black/grey depending upon how quickly it died out
				else{
					image[i+(1000*(1000-j))].rgbtRed = (int)(((loop*1.0)/max_loop) * 255.0);
					image[i+(1000*(1000-j))].rgbtGreen = (int)(((loop*1.0)/max_loop) * 255.0);
					image[i+(1000*(1000-j))].rgbtBlue = (int)(((loop*1.0)/max_loop) * 255.0);
				}
			}

			//keep the user updated on the completeness of the fractal because some take a long time
			if(i%250 == 0 && i != 0){
				cout << i/10 << "% complete." << endl;
			}
		}
		//finish and close the bitmap
		WriteFile(file, image, fileInfo.biSizeImage, &write, NULL);
		CloseHandle(file);
		//inform the user.
		cout<< "Fractal image created! Check the directory.\n\n";
	}
}