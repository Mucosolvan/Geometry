#include "geometry.h"
#include <iostream>
#include<cassert>
void position_vector_test()
{
    Position pos(2, 3);
    pos += Vector(3, 4);
    assert(pos.x() == 5 && pos.y() == 7);

    Position pos2 = Position(3, 4) + Vector(1, 2);
    assert(pos2.x() == 4 && pos2.y() == 6);

    Position pos3 = Vector(1, 2) + Position(3, 4);
    assert(pos3.x() == 4 && pos3.y() == 6);

    Vector vec(2, 3);
    vec += Vector(2, 1);
    assert(vec.x() == 4 && vec.y() == 4);

    Vector vec2 = vec + Vector(2, 3);
    assert(vec2.x() == 6 && vec2.y() == 7);
}

void rectangle_test()
{
    Rectangle rect(10, 20, Position(1, 1));
    std::pair<Rectangle, Rectangle> split = rect.split_horizontally(3);
    std::pair<Rectangle, Rectangle> splitY = rect.split_vertically(3);
    Rectangle merged = merge_horizontally(split.first, split.second);
    Rectangle mergedY = merge_vertically(splitY.first, splitY.second);

    assert(split.first.width() == rect.width());
    assert(split.second.width() == rect.width());
    assert(split.first.height() == 3);
    assert(split.second.height() == 17);
    assert(split.first.pos() == rect.pos());
    assert(split.second.pos() == (rect.pos() + Vector(0, 3)));

    assert(splitY.first.height() == rect.height());
    assert(splitY.second.height() == rect.height());
    assert(splitY.first.width() == 3);
    assert(splitY.second.width() == 7);
    assert(splitY.first.pos() == rect.pos());
    assert(splitY.second.pos() == (rect.pos() + Vector(3, 0)));

    assert(merged.width() == rect.width());
    assert(merged.height() == rect.height());
    assert(merged.pos() == rect.pos());

    assert(mergedY.width() == rect.width());
    assert(mergedY.height() == rect.height());
    assert(mergedY.pos() == rect.pos());

    rect += Vector(2, 3);

    assert(rect.width() == 10);
    assert(rect.height() == 20);
    assert(rect.pos() == Position(3, 4));
}

void rectangles_test()
{
    { // size
        Rectangles rect({Rectangle(10, 20), Rectangle(20, 20)});
        assert(rect.size() == 2);
    }

    { // split_vertically
        Rectangles rect({Rectangle(10, 20), Rectangle(20, 20)});
        rect.split_vertically(0, 4);
        assert(rect.size() == 3);
        assert(rect[0].width() == 4);
        assert(rect[1].width() == 6);
        assert(rect[2].width() == 20);
        assert(rect[0].pos().x() == 0);
        assert(rect[1].pos().x() == 4);
    }


    { // split_horizontally
        Rectangles rect({Rectangle(10, 20)});
        rect.split_horizontally(0, 4);
        assert(rect.size() == 2);

        assert(rect[0].width() == 10);
        assert(rect[1].width() == 10);
        assert(rect[0].height() == 4);
        assert(rect[1].height() == 16);
        assert(rect[0].pos().y() == 0);
        assert(rect[1].pos().y() == 4);
    }

    { // operator[]
        Rectangles rect({Rectangle(10, 20), Rectangle(20, 20)});
        Rectangle const& r = rect[0];
        Rectangle& r2 = rect[0];   
    }

    { // += Vector
        Rectangles rect({Rectangle(10, 20, Position(10, 20)), Rectangle(20, 20)});
        rect += Vector(1, 1);
        assert(rect[0].pos() == Position(11, 21));
        assert(rect[1].pos() == Position(1, 1));
    }

    { // operator +, operator==
        Rectangles rect({Rectangle(10, 20, Position(2, 2)), Rectangle(20, 20, Position(2, 3))});
        Rectangles rect2 = Rectangles({Rectangle(10, 20), Rectangle(20, 20, Position(0, 1))}) + Vector(2, 2);
        Rectangles const& constRef = rect2;
        assert(constRef == rect); 
        assert(rect == constRef); 
    }
}
int main() {
	position_vector_test();
	rectangle_test();
	rectangles_test();
	std::cout << "OK\n";
}