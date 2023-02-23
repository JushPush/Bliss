#ifndef MATH_H
#define MATH_H

typedef struct v2 {
    double x;
    double y;
}
v2;

v2 _v2(double x, double y);

typedef struct rect {
    v2 start;
    v2 end;
}
rect;

rect _rect(v2 start, v2 end);

#define v2(x,y) _v2(x,y)
#define rect(a,b) _rect(a,b)

#endif