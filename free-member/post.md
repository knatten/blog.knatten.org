In this post we'll look at the classical object oriented problem of drawing a number of different shapes to a canvas. 

Say we have a few shapes `Rectangle`, `Triangle` etc., and we want to draw them all on a `Canvas`. Where do we put the implementation of drawing?

One alternative is to make `draw` functions in the shapes, which takes a `Canvas` on which to draw them:

<!-- snippetysnip:main.cpp:n00:(before='```', after='```') -->

```
    class Canvas{};

    class Rectangle{
    public:
        void draw(Canvas&){}
    };

    class Triangle{
    public:
        void draw(Canvas&){}
    };
```

<!-- snippetysnip_end:main.cpp:n00 -->

Then we can draw a shape on the canvas like this:

<!-- snippetysnip:main.cpp:n01:(before='```', after='```') -->

```
        Canvas canvas;
        Rectangle rectangle;
        rectangle.draw(canvas);
```

<!-- snippetysnip_end:main.cpp:n01 -->

An alternative is to put the drawing functionality in `Canvas` instead, allowing us to do `canvas.draw(rectangle)`, which some might prefer. But then we need some sort of polymorphism to allow `Canvas::draw` to work with any kind of shape. The classical object oriented way is to extract an abstract base class (aka interface) which provides all the information we need to draw the hape. Let's call the abstract base class `Shape`, and give it a method that gives us enough information about the shape to able to draw it:

<!-- snippetysnip:main.cpp:n10:(before='```', after='```') -->

```
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

```

<!-- snippetysnip_end:main.cpp:n10 -->

Then we can draw a shape on the canvas like this:

<!-- snippetysnip:main.cpp:n11:(before='```', after='```') -->

```
        Canvas canvas;
        Rectangle rectangle;
        canvas.draw(rectangle);
```

<!-- snippetysnip_end:main.cpp:n11 -->

There are two vital pieces of information here, which guides our placement of the draw functionality. The shapes know about their geometry, and the canvas knows how to be drawn on. From this we can conclude:

- If it's possible to draw on a canvas solely based on its public interface, we can implement `draw` in the shape classes, which know about their geometry.
- If it's possible to draw a shape solely based on its public interface, we can implement `draw` in the canvas class, which knows how to be drawn to.

But as a corollary, if it's possible to draw on a canvas solely based on its public interface, *and* it's possible to draw a shape solely based on its public interface, we can implement `draw` as free functions!


<!-- snippetysnip:main.cpp:n20:(before='```', after='```') -->

```
    class Canvas{};
    class Rectangle{};
    class Triangle{};

    void draw(Canvas&, Rectangle const& r) {}
    void draw(Canvas&, Triangle const& r) {}
```

<!-- snippetysnip_end:main.cpp:n20 -->

Then we can draw a shape on the canvas like this:
<!-- snippetysnip:main.cpp:n21:(before='```', after='```') -->

```
        Canvas canvas;
        Rectangle rectangle;
        draw(canvas, rectangle);
```

<!-- snippetysnip_end:main.cpp:n21 -->

Other consideration:
- Cost of virtual / runtime polymorphism
- Do we control everything we want to draw
- Maybe I need to be a bit more specific about the mechanisms of finding out what exactly to draw here. If I want to be able to do this in free functions, the one in canvas also needs to be able to do it


