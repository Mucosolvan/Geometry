// Bartosz Burny, Marcin Wawerka

#include "geometry.h"

//Position
Position::Position(long x, long y) : x_coord(x), y_coord(y) {}

long Position::x() const {
	return x_coord;
}

long Position::y() const {
	return y_coord;
}

Position& Position::operator +=(const Vector& vec) {
	x_coord += vec.x();
	y_coord += vec.y();
	return *this;
}

bool Position::operator ==(const Position& pos2) const {
	return (x_coord == pos2.x() && y_coord == pos2.y());
}

Position Position::reflection() const {
	return Position(y_coord, x_coord);
}

const Position Position::origin() {
	return Position(0, 0);
}

//Vector
Vector::Vector(long x, long y) : x_coord(x), y_coord(y) {}

long Vector::x() const {
	return x_coord;
}

long Vector::y() const {
	return y_coord;
}

Vector& Vector::operator +=(Vector vec) {
	x_coord += vec.x();
	y_coord += vec.y();
	return *this;
}

bool Vector::operator ==(const Vector& vec2) const {
	return (x_coord == vec2.x() && y_coord == vec2.y());
}

Vector Vector::reflection() const {
	return Vector(y_coord, x_coord);
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

Rectangle& Rectangle::operator +=(const Vector& vec) {
	position += vec;
	return *this;
}

bool Rectangle::operator ==(const Rectangle& rect2) const {
	return (w == rect2.width() && 
			h == rect2.height() &&
			position == rect2.pos());
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
	return {first, second};
}

rect_pair Rectangle::split_vertically(long place) const {
	assert (place > 0 && place < w);
	Rectangle first = Rectangle(place, h, position);
	Rectangle second = Rectangle(w - place, h, 
						position + Vector(place, 0));
	return {first, second};
}

//Rectangles
//constructor using vector's standard constructor from initializer list
Rectangles::Rectangles(std::vector<Rectangle> rects) : rect_vec(rects) {}

Rectangles::Rectangles() {}

Rectangle& Rectangles::operator [](size_t i) {
	assert (i >= 0 && i < rect_vec.size());
	return rect_vec[i];
}

size_t Rectangles::size() const {
	return rect_vec.size();
}

Rectangles& Rectangles::operator +=(const Vector& vec) {
	for (size_t i = 0; i < rect_vec.size(); i++) {
		rect_vec[i] += vec;
	}
	return *this;
}

bool Rectangles::operator ==(const Rectangles& rects2) const {
	return rect_vec == rects2.rect_vec;
}

rect_pair Rectangles::split_pair(std::vector<Rectangle>::iterator it,
								 long place, bool horizontally) const {
	if (horizontally)
		return it->split_horizontally(place);
	return it->split_vertically(place);
}

void Rectangles::split(size_t idx, long place, bool horizontally) {
	assert (idx < rect_vec.size());
	auto it = rect_vec.begin() + idx;
	auto rec_pair = split_pair(it, place, horizontally);
	*it = rec_pair.second;
	rect_vec.insert(it, rec_pair.first);
}

void Rectangles::split_horizontally(size_t idx, long place) {
	split(idx, place, true);
}

void Rectangles::split_vertically(size_t idx, long place) {
	split(idx, place, false);
}

/* Addition operators
 * Passing basic classes containing only constant number of primitive types
 * is practically the same as passing integers, 
 * no need for rvalues or const references
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

const Rectangles operator +(const Rectangles& recs, Vector vec) {
	Rectangles rectangles(recs);
	return (rectangles += vec);
}

const Rectangles operator +(Rectangles&& recs, Vector vec) {
	return (recs += vec);
}

const Rectangles operator +(Vector vec, Rectangles&& recs) {
	return (recs += vec);
}

const Rectangles operator +(Vector vec, const Rectangles& recs) {
	Rectangles rec(recs);
	return (rec += vec);
}

//Merges
Rectangle merge_horizontally(const Rectangle& rec1, const Rectangle& rec2) {
	assert (rec1.pos().x() == rec2.pos().x() &&
			rec1.pos().y() + rec1.height() == rec2.pos().y() &&
			rec1.width() == rec2.width());
	return Rectangle(rec1.width(), rec1.height() + rec2.height(), rec1.pos());
}

Rectangle merge_vertically(const Rectangle& rec1, const Rectangle& rec2) {
	assert (rec1.pos().y() == rec2.pos().y() &&
			rec1.pos().x() + rec1.width() == rec2.pos().x() &&
			rec1.height() == rec2.height());
	return Rectangle(rec1.width() + rec2.width(), rec1.height(), rec1.pos());
}
