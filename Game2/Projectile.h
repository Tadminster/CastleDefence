#pragma once
class Projectile : public ObRect
{
public:
    ObImage* skin;

    Vector2         dir;                    // 방향
    float           speed;                  // 속도
    int             damage;                 // 공격력
    float           range;                  // 사정거리
    float           traveledDistance;       // 이동거리

public:
    Projectile(Vector2 spawnPos, Vector2 dir, float speed, float range, float damage);
    void Update() override;
    void Render() override;

    /* 탄이 이동한 거리가 range를 넘었는지 확인 */
    bool hasTraveledTooFar() const { return traveledDistance >= range; }
};

