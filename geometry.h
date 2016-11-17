// Bartosz Burny, Marcin Wawerka

#include <utility>
#include <vector>
#include <cassert>
#include <cstddef>

#ifndef GEOMETRY_H
#define GEOMETRY_H

class Position;
class Vector;
class Rectangle;
class Rectangles;
typedef std::pair<Rectangle, Rectangle> rect_pair;

class Position {

private:
    long x_coord;
    long y_coord;

public:
    Position(long x, long y);
    
    long x() const;
    long y() const;
    
    Position& operator +=(const Vector &vec);
    bool operator ==(const Position& pos2) const;
    
    Position reflection() const;
    static const Position origin();
};

class Vector {

private:
    long x_coord;
    long y_coord;

public:
    Vector(long x, long y);
    
    long x() const;
    long y() const;
    
    Vector& operator +=(Vector vec);
    bool operator ==(const Vector& vec2) const;
    
    Vector reflection() const;
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
    
    Rectangle& operator +=(const Vector &vec);
    bool operator ==(const Rectangle& rect2) const;
    
    long area() const;
    Rectangle reflection() const;
    
    rect_pair split_horizontally(long place) const;
    rect_pair split_vertically(long place) const;
};

class Rectangles {

private:
    std::vector<Rectangle> rect_vec;
    rect_pair split_pair(std::vector<Rectangle>::iterator it,
                         long place, bool horizontally) const;
    void split(size_t idx, long place, bool horizontally);

public:
    Rectangles(std::vector<Rectangle> rects);
    Rectangles();
    
    Rectangle& operator [](size_t i);
    size_t size() const;
    
    Rectangles& operator +=(const Vector& vec);
    bool operator ==(const Rectangles& rects2) const;
    
    void split_horizontally(size_t idx, long place);
    void split_vertically(size_t idx, long place);
    
};

const Position operator +(Position pos, Vector vec);
const Position operator +(Vector vec, Position pos);
const Vector operator +(Vector vec1, Vector vec2);
const Rectangle operator +(Rectangle rec, Vector vec);
const Rectangle operator +(Vector vec, Rectangle rec);
const Rectangles operator +(const Rectangles& recs, Vector vec);
const Rectangles operator +(Rectangles&& recs, Vector vec);
const Rectangles operator +(Vector vec, const Rectangles& recs);
const Rectangles operator +(Vector vec, Rectangles&& recs);

Rectangle merge_horizontally(const Rectangle& rec1, const Rectangle& rec2);
Rectangle merge_vertically(const Rectangle& rec1, const Rectangle& rec2);

#endif
