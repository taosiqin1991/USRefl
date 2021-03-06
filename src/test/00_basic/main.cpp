#include <USRefl/USRefl.h>
#include <iostream>

using namespace Ubpa::USRefl;
using namespace std;

struct Point {
    float x;
    float y;
};

template<>
struct Ubpa::USRefl::TypeInfo<Point> :
    TypeInfoBase<Point>
{
    static constexpr AttrList attrs = {};
    static constexpr FieldList fields = {
        Field {TSTR("x"), &Type::x},
        Field {TSTR("y"), &Type::y},
    };
};

int main() {
    Point p{ 1.f, 2.f };
    TypeInfo<Point>::ForEachVarOf(p, [](auto field, auto&& var) {
        cout << field.name << ": " << var << endl;
    });
    constexpr const auto& field_x = TypeInfo<Point>::fields.Find(TSTR("x"));
    cout << p.*field_x.value << endl;
    constexpr bool contains_y = TypeInfo<Point>::fields.Contains(TSTR("y"));
    static_assert(contains_y);
}
