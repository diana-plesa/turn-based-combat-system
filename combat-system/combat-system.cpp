#include <iostream>
#include <ctime>
using namespace std;

#define MAX_TURNS 4

class Entity
{
protected:
    int hp;
    int max_hp;
    int heal_value;
    int deal_dmg;

public:
    void Heal()
    {
        if (hp + heal_value >= max_hp)
        {
            hp = max_hp;
        }
        else
        {
            hp = hp + heal_value;
        }
    }

    void setHP(int val)
    {
        if (val < 0) hp = 0;
        else hp = val;
    }

    int getHP()
    {
        return hp;
    }

    int getMaxHP()
    {
        return max_hp;
    }

    int getDmg()
    {
        return deal_dmg;
    }

    int getHealVal()
    {
        return heal_value;
    }

    void Attack(Entity &target)
    {
        int target_hp = target.getHP();

        target_hp = target_hp - deal_dmg;
        target.setHP(target_hp);
    }
};

class Player : public Entity
{
public:
    Player()
    {
        hp = 20;
        max_hp = 20;
        heal_value = 6;
        deal_dmg = 4;
    }
};

class Enemy : public Entity
{
public:
    Enemy()
    {
        hp = 16;
        max_hp = 16;
        heal_value = 4;
        deal_dmg = 4;
    }
};

int main()
{
    srand(time(NULL));

    Player player;
    Enemy goblin;

    int turn = 1;
    int nb_enemies = 1;

    while (turn <= MAX_TURNS && nb_enemies > 0)
    {
        cout << ">> Turn " << turn << "\n";
        cout << "You: " << player.getHP() << "/" << player.getMaxHP() <<
            " Goblin: " << goblin.getHP() << "/" << goblin.getMaxHP() << "\n";
        cout << "Choose action:\n" << "1. Attack\n" << "2. Heal\n";

        int opt = 0;
        cin >> opt;

        if (opt == 1)
        {
            player.Attack(goblin);
            cout << "You attacked Goblin for " << goblin.getDmg() << " points \n";

            if (goblin.getHP() == 0)
            {
                cout << "You defeated Goblin!\n";
                nb_enemies--;
            }
        }
        else if (opt == 2)
        {
            player.Heal();
            cout << "You healed for " << player.getHealVal() << " points\n";
        }
        else
        {
            cout << "Error choosing option\n";
            return 0;
        }

        if (rand() % 2 == 1)
        {
            goblin.Attack(player);
            cout << "Goblin attacked you for " << goblin.getDmg() << " points\n";

            if (player.getHP() == 0)
            {
                cout << "You died!\n";
                break;
            }
        }
        else
        {
            goblin.Heal();
            cout << "Goblin healed for " << goblin.getHealVal() << " points\n";
        }

        turn++;
    }

    return 0;
}