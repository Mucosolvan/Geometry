#include <utility>
#include <vector>
#include <assert.h>
#include <iostream>
#include "geometry.h"
// Pamietac o wykonywalnosci pliku ?

//Vector
Vector::Vector(long x, long y) : x_coord(x), y_coord(y) {}
long Vector::x() const {
	return x_coord;
}

long Vector::y() const {
	return y_coord;
}

Vector& Vector::operator += (const Vector &vec) {
	x_coord += vec.x();
	y_coord += vec.y();
	return *this;
}

Vector Vector::reflection() const {
	return Vector(y_coord, x_coord);
}

//Position
Position::Position(long x, long y) : x_coord(x), y_coord(y) {}
long Position::x() const {
	return x_coord;
}

long Position::y() const {
	return y_coord;
}

Position& Position::operator += (const Vector &vec) {
	x_coord += vec.x();
	y_coord += vec.y();
	return *this;
}
 
Position Position::reflection() const {
	return Position(y_coord, x_coord);
}

const Position &origin() {
	static const int x_static = 0;
	static const int y_static = 0;
	static const Position pos_static = Position(x_static, y_static);
	return pos_static;
}

//Rectangle
Rectangle::Rectangle(long width, long height)
	: w(width), h(height), position(Position(0,0)) {
	assert (w > 0);
	assert (h > 0);
}

Rectangle::Rectangle(long width, long height, Position p) 
	: w(width), h(height), position(p) {
	assert (w > 0);
	assert (h > 0);
}

long Rectangle::width() const {
	return w;
}

long Rectangle::height() const {
	return h;
}

Position Rectangle::pos() const {
	return position;
}

Rectangle& Rectangle::operator += (const Vector &vec) {
	position += vec;
	return *this;
}
 
long Rectangle::area() const {
	return w * h;
}

Rectangle Rectangle::reflection() const {
	return Rectangle(h, w, position.reflection());
}

rect_pair Rectangle::split_horizontally(long place) const {
	assert (place > position.y() && place < position.y() + h);
	Rectangle first = Rectangle(w, place, position);
	Rectangle second = Rectangle(w, h - place, 
						position + Vector(0, place));
	return std::make_pair(first, second);
}

rect_pair Rectangle::split_vertically(long place) const {
	assert (place > position.x() && place < position.x() + w);
	Rectangle first = Rectangle(place, h, position);
	Rectangle second = Rectangle(w - place, h, 
						position + Vector(place, 0));
	return std::make_pair(first, second);
}

//Rectangles
//constructor using vector's standard constructor from initializer list
Rectangles::Rectangles(std::vector<Rectangle> rects) : recs(std::move(rects)) {}
Rectangles::Rectangles() {}

const Rectangle& Rectangles::operator [](unsigned long i) const {
	assert (i >= 0 && i < recs.size());
	return (recs[i]);
}

long Rectangles::size() const {
	return recs.size();
}

Rectangles& Rectangles::operator += (const Vector &vec) {
	for (auto rec : recs) 
		rec+= vec;
	return *this;
}

rect_pair Rectangles::split_pair(std::vector<Rectangle>::iterator it,
								 long place, bool horizontally) const {
	if (horizontally)
		return it->split_horizontally(place);
	return it->split_vertically(place);
}

void Rectangles::split(unsigned long idx, long place, bool horizontally) {
	assert (idx >= 0 && idx < recs.size());
	auto it = recs.begin() + idx;
	auto rec_pair = split_pair(it, place, horizontally);
	Rectangle arr[] = {rec_pair.first, rec_pair.second};
	recs.insert(it, arr, arr + 2);
}

void Rectangles::split_horizontally(unsigned long idx, long place) {
	split(idx, place, true);
}

void Rectangles::split_vertically(unsigned long idx, long place) {
	split(idx, place, false);
}

//Operators

//Comparisons
bool operator ==(const Vector &vec1, const Vector &vec2) {
	return (vec1.x() == vec2.x() && vec1.y() == vec2.y());
}

bool operator ==(const Position &pos1, const Position &pos2) {
	return (pos1.x() == pos2.x() && pos1.y() == pos2.y());
}

bool operator ==(const Rectangle &rect1, const Rectangle &rect2) {
	return (rect1.width() == rect2.width() && 
			rect1.height() == rect2.height() &&
			rect1.pos() == rect2.pos());
}

bool operator ==(const Rectangles &recs1, const Rectangles &recs2) {
	bool same = (recs1.size() == recs2.size());
	if (same) {
		for (int i = 0; i < recs1.size() && same; i++) {
			same &= (recs1[i] == recs2[i]);
		}
	}
	return same;
}

//Additions
Position operator +(Position pos, Vector vec) {
	return (pos += vec); 
}

Position operator +(Vector vec, Position pos) {
	return (pos += vec);
}

Vector operator +(Vector vec1, Vector vec2) {
	return (vec1 += vec2);
}

Rectangle operator +(Rectangle rec, Vector vec) {
	return (rec += vec);
}

Rectangle operator +(Vector vec, Rectangle rec) {
	return (rec += vec);
}

Rectangles operator +(Rectangles recs, Vector vec) {
	return (recs += vec);
}

Rectangles operator +(Vector vec, Rectangles recs) {
	return (recs += vec);
}

//Merges
Rectangle merge_horizontally(const Rectangle &rec1, const Rectangle &rec2) {
	assert (rec1.pos().x() == rec2.pos().x() &&
			rec1.pos().y() + rec1.height() == rec2.pos().y() &&
			rec1.width() == rec2.width());
	return Rectangle(rec1.width(), rec1.height() + rec2.height(), rec1.pos());
}

Rectangle merge_vertically(const Rectangle &rec1, const Rectangle &rec2) {
	assert (rec1.pos().y() == rec2.pos().y() &&
			rec1.pos().x() + rec1.width() == rec2.pos().x() &&
			rec1.height() == rec2.height());
	return Rectangle(rec1.width() + rec2.width(), rec1.height(), rec1.pos());
}

int main() {
	Position p = Position(100, 200);
	//std::cout << p.x();
	Vector v = Vector(200, 300);
	//std::cout << " " << ( (p += v) += v).y();
	//std::cout << " " << (Position (500 , 800) == p);
	Position d = p + v;
	std::cout << d.x() << "\n";
	Rectangle r = Rectangle(2, 3, Position(1,0));
	Rectangle r2 = Rectangle(2, 5, Position(1,0));
	//Rectangle r = Rectangle();
	std::cout << " " << (r == r2) << "\n";
	
	Position dd = Position(d);
	std::cout << dd.x() << " " << dd.y() << "\n";
	return 0;
}
