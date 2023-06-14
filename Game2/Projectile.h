#pragma once
class Projectile
{
public:
    class ObRect*   collider;
    class ObImage*  skin;

    Vector2         dir;                    // 방향
    float           speed;                  // 속도
    int             damage;                 // 공격력
    float           range;                  // 사정거리
    float           traveledDistance;       // 이동거리

public:
    Projectile(Vector2 spawnPos, Vector2 dir, float speed, float range, float damage);
    ~Projectile();
    void            Update();
    void            Render();
    
    bool            hasCollideWithMonster();
    /* 탄이 이동한 거리가 range를 넘었는지 확인 */
    bool            hasTraveledTooFar() const { return traveledDistance >= range; }
};

