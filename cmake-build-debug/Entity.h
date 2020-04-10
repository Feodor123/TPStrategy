#ifndef TPSTRATEGY_ENTITY_H
#define TPSTRATEGY_ENTITY_H


class Entity {
public:
    int id;
    int hp;
    virtual void PerformAction() = 0;

protected:
    Entity(int hp);
private:
    static int currId;
};


#endif
