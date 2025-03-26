#ifndef COORD_H
#define COORD_H

class Coord {
    int x;
    int y;
    
 public: 
    // constructor, destructor
    Coord(int x, int y); // x is width, y is height
    ~Coord();

    void setx(const int x);
    void sety(const int y);

    int getx() const;
    int gety() const;
};

#endif
