#include <utility>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>
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

Vector& Vector::operator += (Vector vec) {
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

const Position Position::origin() {
	return Position(0, 0);
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
	assert (place > 0 && place < h);
	Rectangle first = Rectangle(w, place, position);
	Rectangle second = Rectangle(w, h - place, 
						position + Vector(0, place));
	return std::make_pair(first, second);
}

rect_pair Rectangle::split_vertically(long place) const {
	assert (place > 0 && place < w);
	Rectangle first = Rectangle(place, h, position);
	Rectangle second = Rectangle(w - place, h, 
						position + Vector(place, 0));
	return std::make_pair(first, second);
}

//Rectangles
//constructor using vector's standard constructor from initializer list
Rectangles::Rectangles(std::vector<Rectangle> rects) : recs(std::move(rects)) {}
Rectangles::Rectangles() {}

Rectangle& Rectangles::operator [](size_t i) {
	assert (i >= 0 && i < recs.size());
	return recs[i];
}

size_t Rectangles::size() const {
	return recs.size();
}

Rectangles& Rectangles::operator += (const Vector &vec) {
	for (auto rec : recs) 
		rec += vec;
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
	*it = rec_pair.second;
	recs.insert(it, rec_pair.first);
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

bool operator ==(Rectangles &recs1, Rectangles &recs2) {
	bool same = (recs1.size() == recs2.size());
	if (same) {
		for (size_t i = 0; i < recs1.size() && same; i++) {
			same &= (recs1[i] == recs2[i]);
		}
	}
	return same;
}

/* Additions
 * Passing classes containing only constant number of primitive types
 * is practically the same as passing integers, no need for rvalues 
 */

const Position operator +(Position pos, Vector vec) {
	return (pos += vec); 
}

const Position operator +(Vector vec, Position pos) {
	return (pos += vec);
}

const Vector operator +(Vector vec1, Vector vec2) {
	return (vec1 += vec2);
}

const Rectangle operator +(Rectangle rec, Vector vec) {
	return (rec += vec);
}

const Rectangle operator +(Vector vec, Rectangle rec) {
	return (rec += vec);
}

const Rectangles operator +(const Rectangles &recs, Vector vec) {
	Rectangles rec(recs);
	return (rec += vec);
}

const Rectangles operator +(Rectangles &&recs, Vector vec) {
	return (recs += vec);
}

const Rectangles operator +(Vector vec, Rectangles &&recs) {
	return (recs += vec);
}

const Rectangles operator +(Vector vec, const Rectangles &recs) {
	Rectangles rec(recs);
	return (rec += vec);
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
	/* Position p = Position(100, 200);
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
	std::cout << dd.x() << " " << dd.y() << "\n"; */
	Vector v = Vector(1, 2);
	Vector p = v;
	std::cout << (p == v) <<" ";
	p += v;
	std::cout << (p == v) <<" ";
	Vector d = Vector(1, 2);
	std::cout << (d == v) << " ";
	
	std::cout << (d + v == p + Vector(-1,0)) << " ";
	
	std::cout << (v.reflection() == Vector(2, 1)) << " ";
	
	Position::origin();
	Rectangle r = Rectangle(2, 3, Position(1, 2));
	
	Rectangles rects = Rectangles({r, Rectangle(1, 1, Position(0,0))});
	rects[0] += v;
	std::cout << rects[0].pos().x() << " " << rects[0].pos().y() << " ";
	
	std::cout << rects[1].pos().x() << " " << rects[1].pos().y() << " ";
	
	rects[1] = Rectangle(2, 2, Position(2,2));
	std::cout << rects[1].pos().x() << " " << rects[1].pos().y() << "\n";
	Rectangle r2 = Rectangle(5, 3, Position(3, 2));
	Rectangle z = merge_vertically(r, r2);
	std::cout << z.pos().x() << " " << z.pos().y() << " " << z.height() << " " << z.width() << "\n";
	rect_pair para = z.split_vertically(5);
	std::cout << (para.first == Rectangle(5, 3, Position(1, 2))) << " " << (para.second == Rectangle(2, 3, Position(6,2))) << "\n";
	
	(v += v) = v;
	return 0;
}
