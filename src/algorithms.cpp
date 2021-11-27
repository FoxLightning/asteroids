#include <AbstractPhysicalObject.hpp>
#include <math.h>

inline float dotProduct(sf::Vector2f rv, sf::Vector2f normal) {
    return (rv.x * normal.x + rv.y * normal.y) / sqrt(pow(normal.x, 2) + pow(normal.y, 2));
}

void ResolveColision(AbstractPhysicalObject* A, AbstractPhysicalObject* B) {
    // Вычисляем относительную скорость
    sf::Vector2f rv = B->GetSpeed()- A->GetSpeed();
    sf::Vector2f normal = B->GetPosition() - A->GetPosition();
    float normal_k = sqrt(pow(normal.x, 2) + pow(normal.y, 2));
    normal.x /= normal_k;
    normal.y /= normal_k;

    // Вычисляем относительную скорость относительно направления нормали
    float velAlongNormal = dotProduct(rv, normal);

    // Не выполняем вычислений, если скорости разделены
    if(velAlongNormal > 0) {
            return;
    }

    // Вычисляем упругость
    float e = 0.5;

    // Вычисляем скаляр импульса силы
    float j = -(1 + e) * velAlongNormal;
    j /= 1.f / A->GetMass() + 1.f / B->GetMass();

    // Прикладываем импульс силы
    sf::Vector2f impulse = j * normal;
    A->SetSpeed(A->GetSpeed()-1.f/A->GetMass()*impulse);
    B->SetSpeed(B->GetSpeed()+1.f/B->GetMass()*impulse);
}

bool CheckColision(AbstractPhysicalObject* lvalue, AbstractPhysicalObject* rvalue) {
    sf::Vector2f    PosA = lvalue->GetPosition();
    float           RadA = lvalue->GetRadious();
    sf::Vector2f    PosB = rvalue->GetPosition();
    float           RadB = rvalue->GetRadious();

    return pow(PosA.x - PosB.x, 2) + pow(PosA.y - PosB.y, 2) < pow(RadA + RadB, 2);
}