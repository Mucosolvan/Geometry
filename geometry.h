#include <utility>
#include <vector>
#include <assert.h>

#ifndef GEOMETRY_H
#define GEOMETRY_H

class Rectangle;
typedef std::pair<Rectangle, Rectangle> rect_pair;

class Vector {
	
	private:
		long x_coord;
		long y_coord;
	
	public:
		Vector(long x, long y);
		
		long x() const;
		long y() const;
		
		Vector& operator += (const Vector &vec);
		
		Vector reflection() const;
};

class Position {
	
	private:
		long x_coord;
		long y_coord;
	
	public:
		Position(long x, long y);
		
		long x() const;
		long y() const;
		
		Position& operator += (const Vector &vec);
		
		Position reflection() const;
		static const Position &origin();
};

class Rectangle {
	
	private:
		long w;
		long h;
		Position position;
	
	public:
		Rectangle(long width, long height);
		Rectangle(long width, long height, Position p);
		
		long width() const;
		long height() const;
		Position pos() const;
		
		Rectangle& operator += (const Vector &vec);
		
		long area() const;
		Rectangle reflection() const;
		
		rect_pair split_horizontally(long place) const;
		rect_pair split_vertically(long place) const;
};

class Rectangles {
	
	private:
		std::vector<Rectangle> recs;
		rect_pair split_pair(std::vector<Rectangle>::iterator it,
							 long place, bool horizontally) const;
		void split(unsigned long idx, long place, bool horizontally);
	
	public:
		Rectangles(std::vector<Rectangle> rects);
		Rectangles();
		
		const Rectangle& operator [](unsigned long i) const;
		long size() const;
		
		Rectangles& operator += (const Vector &vec);
		
		void split_horizontally(unsigned long idx, long place);
		void split_vertically(unsigned long idx, long place);
};

bool operator ==(const Vector &vec1, const Vector &vec2);
bool operator ==(const Position &pos1, const Position &pos2);
bool operator ==(const Rectangle &rect1, const Rectangle &rect2);
bool operator ==(const Rectangles &recs1, const Rectangles &recs2);

Position operator +(Position pos, Vector vec);
Position operator +(Vector vec, Position pos);
Vector operator +(Vector vec1, Vector vec2);
Rectangle operator +(Rectangle rec, Vector vec);
Rectangle operator +(Vector vec, Rectangle rec);
Rectangles operator +(Rectangles recs, Vector vec);
Rectangles operator +(Vector vec, Rectangles recs);

Rectangle merge_horizontally(const Rectangle &rec1, const Rectangle &rec2);
Rectangle merge_vertically(const Rectangle &rec1, const Rectangle &rec2);

#endif
