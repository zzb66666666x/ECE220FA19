#include "Rectangle.h"

//Empty Constructor sets instantiates a rectangle with length and width set as 0
Rectangle::Rectangle()
{
//INSERT YOUR CODE HERE:
	Rectangle(0,0);
}

//Standard Constructor sets instantiates a rectangle with length and width set as input values
Rectangle::Rectangle(int input_length, int input_width)
{
//INSERT YOUR CODE HERE:
	set_length(input_length);
	set_width(input_width);
}

//Setter and Getter functions
void Rectangle::set_length(int input_length)
{
//INSERT YOUR CODE HERE:
	length = input_length;
	return;
}

void Rectangle::set_width(int input_width)
{
//INSERT YOUR CODE HERE:
	width = input_width;
	return;
}

int Rectangle::get_length(void) const
{
//INSERT YOUR CODE HERE:
	return length;
}

int Rectangle::get_width(void) const
{
//INSERT YOUR CODE HERE:
	return width;
}

//Calculate Area of rectangle
int Rectangle::area(void)
{
//INSERT YOUR CODE HERE:
	return (length*width);
}

//Calculate Perimeter of rectangle
int Rectangle::perimeter(void)
{
//INSERT YOUR CODE HERE:
	return (2*length+2*width);
}

/*Addition operator overload
* We define addition of two rectangles to be as follows: R3 = R1 + R2
* where length of R3 = length R1 + length R2
* and width R3 = max(width R1, width R2)
*/
Rectangle Rectangle::operator + (const Rectangle& other)
{
//INSERT YOUR CODE HERE:
	Rectangle ans;
	ans.set_length(length + other.length);
	if (width >= other.width){
		ans.set_width(width);
	}
	else{
		ans.set_width(other.width);
	}
	return ans;
}

/*Multiplication operator overload
* We define addition of two rectangles to be as follows: R3 = R1 * R2
* where length of R3 = length R1 + length R2
* and width R3 = width R1 + width R2
*/
Rectangle Rectangle::operator * (const Rectangle& other)
{
//INSERT YOUR CODE HERE:
	Rectangle ans;
	ans.set_length(length + other.length);
	ans.set_width(width + other.width);
	return ans;	
}