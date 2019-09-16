// class inheritance example
#include <iostream>
using namespace std;

class CPolygon {
	protected:
	int width, height;
	public:
	void setValues(int w, int h) {
		width = w;
		height = h;
	}
};

class CRectangle: public CPolygon {
	// int width, height already defined
	// void setValues() already defined
	// CPolygon's width and height can be used by derived classes,
		// like CRectangle, but not non-members
	public:
	int area() { return (width * height); }
};

class CTriangle: public CPolygon {
	public:
	int area() { return ((width * height) / 2); }
};

int main(void) {
	CRectangle rect;
	CTriangle trgl;
	rect.setValues(4, 5);
	trgl.setValues(4, 5);
	cout << rect.area() << endl;
	cout << trgl.area() << endl;
	rect.setwh(2, 3);
	cout << rect.area() << endl;
	return 0;
}
