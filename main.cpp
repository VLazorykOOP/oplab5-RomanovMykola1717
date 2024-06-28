#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

// ������� ��� ���������� ����� �� ����� ���'�
sf::Vector2f bezierPoint(const sf::Vector2f& P1, const sf::Vector2f& P2, const sf::Vector2f& P3, const sf::Vector2f& P4, float t) {
    float u = 1.0f - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    sf::Vector2f point = uuu * P1;
    point += 3 * uu * t * P2;
    point += 3 * u * tt * P3;
    point += ttt * P4;

    return point;
}

// ������� ��� ��������� �������� ����
void drawKoch(sf::RenderWindow& window, sf::VertexArray& lines, sf::Vector2f a, sf::Vector2f b, int order) {
    if (order == 0) {
        lines.append(sf::Vertex(a, sf::Color::Blue));
        lines.append(sf::Vertex(b, sf::Color::Blue));
        return;
    }

    sf::Vector2f v = (b - a) / 3.0f;
    sf::Vector2f p1 = a + v;
    sf::Vector2f p2 = b - v;
    sf::Vector2f mid = p1 + v * 0.5f + sf::Vector2f(-v.y, v.x) * sqrt(3.0f) / 2.0f;

    drawKoch(window, lines, a, p1, order - 1);
    drawKoch(window, lines, p1, mid, order - 1);
    drawKoch(window, lines, mid, p2, order - 1);
    drawKoch(window, lines, p2, b, order - 1);
}

int main() {
    // ������� ����� ������������� P1, P2, P3, P4
    sf::Vector2f P1(100, 100);
    sf::Vector2f P2(300, 50);
    sf::Vector2f P3(400, 200);
    sf::Vector2f P4(200, 300);

    // ����������� ���� ���� SFML
    sf::RenderWindow window1(sf::VideoMode(500, 500), "Bezier Curve in Quadrilateral");
    sf::RenderWindow window2(sf::VideoMode(800, 600), "Koch Fractal");

    window1.setFramerateLimit(60);
    window2.setFramerateLimit(60);

    // �������� ���� ��������
    while (window1.isOpen() || window2.isOpen()) {
        // ������� ���� ��� ���� ����
        sf::Event event;
        while (window1.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window1.close();
        }
        while (window2.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window2.close();
        }

        // �������� ���� 1
        window1.clear(sf::Color::White);

        // ³���������� �������������
        sf::ConvexShape quadrilateral;
        quadrilateral.setPointCount(4);
        quadrilateral.setPoint(0, P1);
        quadrilateral.setPoint(1, P2);
        quadrilateral.setPoint(2, P3);
        quadrilateral.setPoint(3, P4);
        quadrilateral.setFillColor(sf::Color::Transparent);
        quadrilateral.setOutlineColor(sf::Color::Black);
        quadrilateral.setOutlineThickness(2);
        window1.draw(quadrilateral);

        // ³���������� ����� ���'�
        sf::VertexArray bezierCurve(sf::LineStrip, 100);
        for (int i = 0; i < 100; ++i) {
            float t = static_cast<float>(i) / 99.0f;
            sf::Vector2f point = bezierPoint(P1, P2, P3, P4, t);
            bezierCurve[i].position = point;
            bezierCurve[i].color = sf::Color::Red; 
        }
        window1.draw(bezierCurve);

        // �������� ���� 2
        window2.clear(sf::Color::White);

        // ³���������� �������� ����
        sf::VertexArray kochFractal(sf::Lines);
        sf::Vector2f A(100, 300);
        sf::Vector2f B(700, 300);
        drawKoch(window2, kochFractal, A, B, 4);
        window2.draw(kochFractal);

        // ³���������� ����� ����
        window1.display();
        window2.display();
    }

    return 0;
}
