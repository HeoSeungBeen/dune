#ifndef UNIT_H
#define UNIT_H

#include "common.h"

typedef struct {
	int camp;
	char name[10];
	char instruction[100];
	int construction_cost;
	int durability;
	int max_durability;
	int order;
	POSITION pos;

} structure;

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
	POSITION pos;
} unit;

structure create_str_base(int, int);
structure create_str_plate(int, int);
structure create_str_dormitory(int, int);
structure create_str_garage(int, int);
structure create_str_barracks(int, int);
structure create_str_shelter(int, int);
structure create_str_arena(int, int);
structure create_str_factory(int, int);
structure create_str_spa(int, int);

unit create_unit_harvester(int, int);
unit create_unit_freman(int, int);
unit create_unit_soldier(int, int);
unit create_unit_fighter(int, int);
unit create_unit_htank(int, int);
unit create_unit_sandworm(int, int);

#endif // UNIT_H
