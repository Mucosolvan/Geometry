#include <algorithm>
#include <iostream>

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

int main() {
	Position p = Position(100, 200);
	std::cout << p.x();
	Vector v = Vector(200, 300);
	std::cout << " " << ( (p += v) += v).y();
	std::cout << " " << (Position (500 , 800) == p);
	return 0;
}
