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
} unit;

structure create_str_base(void);
structure create_str_plate(void);
structure create_str_dormitory(void);
structure create_str_garage(void);
structure create_str_barracks(void);
structure create_str_shelter(void);
structure create_str_arena(void);
structure create_str_factory(void);

unit create_unit_harvester(void);
unit create_unit_freman(void);
unit create_unit_soldier(void);
unit create_unit_fighter(void);
unit create_unit_htank(void);
unit create_unit_sandworm(void);

#endif // UNIT_H
