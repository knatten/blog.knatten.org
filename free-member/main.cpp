#include <vector>
namespace n0 {

//snippetysnip_begin:n00
    class Canvas{};

    class Rectangle{
    public:
        void draw(Canvas&){}
    };

    class Triangle{
    public:
        void draw(Canvas&){}
    };
//snippetysnip_end

    int main () {
//snippetysnip_begin:n01
        Canvas canvas;
        Rectangle rectangle;
        rectangle.draw(canvas);
//snippetysnip_end
        return 0;
    }
}

namespace n1 {

    class PolygonInfo{};
//snippetysnip_begin:n10
    class Shape{
    public:
        virtual PolygonInfo getPolygonInfo();
        virtual ~Shape(){}
    };
    class Rectangle : public Shape{
    public:
        PolygonInfo getPolygonInfo() override;
    };
    class Triangle : public Shape{
        PolygonInfo getPolygonInfo() override;
    };

    class Canvas{
    public:
        void draw(Shape& shape) {
            //Do stuff with:
            shape.getPolygonInfo();
        }
    };

//snippetysnip_end

//snippetysnip_begin:classical_canvas
//snippetysnip_end

    int main () {
//snippetysnip_begin:n11
        Canvas canvas;
        Rectangle rectangle;
        canvas.draw(rectangle);
//snippetysnip_end
        return 0;
    }
}


namespace n2 {
//snippetysnip_begin:n20
    class Canvas{};
    class Rectangle{};
    class Triangle{};

    void draw(Canvas&, Rectangle const& r) {}
    void draw(Canvas&, Triangle const& r) {}
//snippetysnip_end

    int main () {
//snippetysnip_begin:n21
        Canvas canvas;
        Rectangle rectangle;
        draw(canvas, rectangle);
//snippetysnip_end
        return 0;
    }

}




namespace cpp {

    class Rectangle {};
    class Triangle {};

    class Canvas {
    };

    int main () {
        return 0;
    }
}

int main() {
    n1::main();
    n2::main();
}
