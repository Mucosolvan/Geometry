#include <utility>
#include <algorithm>
#include <assert.h>
#include <iostream>
// Pamietac o wykonywalnosci pliku ?
class Vector {
	
	protected:
		int xCoord;
		int yCoord;
	
	public:
		Vector(const int x, const int y) {
			xCoord = x;
			yCoord = y;
		}
		
		int x() const {
			return xCoord;
		}
		
		bool operator ==(const Vector &pos) const {
			return (xCoord == pos.x() && yCoord == pos.y());
		}
		
		int y() const {
			return yCoord;
		}
		
		Vector& operator += (const Vector &vec) {
			xCoord += vec.x();
			yCoord += vec.y();
			return *this;
		} 
		
		Vector reflection() {
			return Vector(-xCoord, yCoord);
		}
};

class Position : public Vector {
	
	public:
		Position(const int x, const int y) : Vector(x, y) {}
		
		static const Position origin() {
			return Position(0, 0);
		}
};


class Rectangle {
	private:
		int w;
		int h;
		Position position = Position(0,0);
		
	public:
		Rectangle(const int width, const int height) {
			assert (width > 0);
			assert (height > 0);
			w = width;
			h = height;
		}
		
		Rectangle(const int width, const int height, const Position p) {
			assert (width > 0);
			assert (height > 0);
			w = width;
			h = height;
			position = p;
		}
		
		int width() const {
			return w;
		}
		
		int height() const {
			return h;
		}
		
		Position pos() const {
			return position;
		}
		
		bool operator ==(const Rectangle &rect) const {
			return (w == rect.width() && h == rect.height() &&
					position == rect.pos());
		}
		
		Rectangle& operator += (const Vector &vec) {
			position += vec;
			return *this;
		} 
		
		int area() {
			return w * h;
		}
		
		// to modify after adding operator +
		
		Rectangle reflection() {
			return Rectangle(w, h, Position(- position.x() - w, position.y()));
		}
		
		std::pair<Rectangle, Rectangle> split_horizontally(int place) {
			Rectangle first = Rectangle(w, place, position);
			Rectangle second = Rectangle(w, h - place, 
							   Position(position.x(), position.y() + place));
			return std::make_pair(first, second);
		}
		
		std::pair<Rectangle, Rectangle> split_vertically(int place) {
			Rectangle first = Rectangle(place, h, position);
			Rectangle second = Rectangle(w - place, h, 
							   Position(position.x() + place, position.y()));
			return std::make_pair(first, second);
		}
};

int main() {
	Position p = Position(100, 200);
	//std::cout << p.x();
	Vector v = Vector(200, 300);
	//std::cout << " " << ( (p += v) += v).y();
	//std::cout << " " << (Position (500 , 800) == p);
	
	Rectangle r = Rectangle(2, 3, Position(1,0));
	Rectangle r2 = Rectangle(2, 5, Position(1,0));
	//Rectangle r = Rectangle();
	std::cout << " " << (r == r2);
	return 0;
}
