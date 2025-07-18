#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>
using namespace std;

#define MAX_TURNS 20

int nb_enemies = 2;
bool game_over = false;

class Entity
{
protected:
    bool is_alive;
    char id[50];
    int hp;
    int hp_max;
    int heal_value;
    int deal_dmg;

public:
    void Attack(Entity& target)
    {
        if (!is_alive || !target.is_alive) return;

        int target_hp = target.getHP();

        target_hp = target_hp - deal_dmg;
        target.setHP(target_hp);
        if (target.getHP() == 0)
            target.is_alive = false;

        cout << id << " attacked " << target.id << " for " << deal_dmg << " points\n";
    }

    void Heal(Entity &target)
    {
        if (!is_alive || !target.is_alive) return;

        if (target.hp + target.heal_value >= target.hp_max)
        {
            target.hp = target.hp_max;
        }
        else
        {
            target.hp = target.hp + target.heal_value;
        }

        cout << target.id << " healed for " << target.heal_value << " points\n";
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
        return hp_max;
    }

    int getDmg()
    {
        return deal_dmg;
    }

    int getHealVal()
    {
        return heal_value;
    }

    string getID()
    {
        return id;
    }
};

class Player : public Entity
{
public:
    Player(char name[])
    {
        is_alive = true;
        strcpy(id, name);
        hp = 20;
        hp_max = 20;
        deal_dmg = 5;
        heal_value = 4;
    }
};

class NPC : public Entity
{
protected:
    bool is_hostile;
};

class Goblin : public NPC
{
public:
    Goblin()
    {
        is_hostile = true;
        is_alive = true;
        strcpy(id, "Goblin");
        hp = 14;
        hp_max = 14;
        deal_dmg = 2;
        heal_value = 3;
    }
};

class Draugr : public NPC
{
public:
    Draugr()
    {
        is_hostile = true;
        is_alive = true;
        strcpy(id, "Draugr");
        hp = 16;
        hp_max = 16;
        deal_dmg = 3;
        heal_value = 2;
    }
};

void AttackEvent(Entity &attacker, Entity &target)
{
    attacker.Attack(target);

    if (target.getHP() == 0)
    {
        cout << attacker.getID() << " defeated " << target.getID() << "!\n";
    }
}

void EnemyTurn(NPC& enemy, Player &player)
{
    if (player.getHP() == 0) return;

    if (rand() % 2 || enemy.getHP() == enemy.getMaxHP())
    {
        enemy.Attack(player);

        if (player.getHP() == 0)
        {
            cout << "You died!\n";
            game_over = true;
            return;
        }
    }
    else
    {
        enemy.Heal(enemy);
    }
}

void PlayerTurn(Player& player, Entity& target, const char action[])
{
    if (strcmp(action, "Heal") == 0)
    {
        player.Heal(player);
    }
    else if (strcmp(action, "Attack") == 0)
    {
        if (target.getHP() == 0)
        {
            cout << target.getID() << "is already dead\n";
            return;
        }

        AttackEvent(player, target);

        if (target.getHP() == 0) nb_enemies--;
    }
    else
    {
        cout << "Invalid action\n";
        exit(-1);
    }
}

int main()
{
    srand((int)time(0));

    char name[50];

    cout << "Type your character's name: ";
    cin >> name;

    Player *player = new Player(name);
    Goblin *goblin = new Goblin();
    Draugr *draugr = new Draugr();

    int turn = 1;

    while (!game_over && (turn <= MAX_TURNS && nb_enemies > 0))
    {
        cout << ">> Turn " << turn << "\n";
        cout << "You: " << player->getHP() << "/" << player->getMaxHP() <<
            " Goblin: " << goblin->getHP() << "/" << goblin->getMaxHP() << 
            " Draugr: " << draugr->getHP() << "/" << draugr->getMaxHP() << "\n";
        
        cout << "Choose action:\n" << "1. Attack Goblin\n" << "2. Attack Draugr\n" << "3. Heal\n";

        int opt = 0;
        cin >> opt;

        if (opt == 1)
        {
            PlayerTurn(*player, *goblin, "Attack");
        }
        else if (opt == 2)
        {
            PlayerTurn(*player, *draugr, "Attack");
        }
        else if (opt == 3)
        {
            PlayerTurn(*player, *player, "Heal");
        }
        else
        {
            cout << "Error choosing option\n";
            return 0;
        }
        
        EnemyTurn(*goblin, *player);
        EnemyTurn(*draugr, *player);

        turn++;
    }
    printf("Game over!");

    delete(goblin);
    delete(draugr);
    delete(player);

    return 0;
}