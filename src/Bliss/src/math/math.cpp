#include <math/math.h>

v2 _v2(double x, double y) {
    return v2 {x,y};
}

rect _rect(v2 start, v2 end) {
    return rect {start,end};
}