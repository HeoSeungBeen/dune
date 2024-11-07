#ifndef UNIT_H
#define UNIT_H

typedef struct {
	int camp;
	char name[10];
	char instruction[100];
	int construction_cost;
	int durability;
	int max_durability;
	int order;
} STRUCTURE;

typedef struct {
	int camp;
	char name[10];
	int production_cost;
	int population;
	int moving_cycle;
	int damage;
	int attack_cycle;
	int hp;
	int max_hp;
	int vision;
	int order[2]; 
} UNIT;

#endif // UNIT_H
