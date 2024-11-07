#include "unit.h"

STRUCTURE create_str_base(void);
STRUCTURE create_str_plate(void);
STRUCTURE create_str_dormitory(void);
STRUCTURE create_str_garage(void);
STRUCTURE create_str_barracks(void);
STRUCTURE create_str_shelter(void);
STRUCTURE create_str_arena(void);
STRUCTURE create_str_factory(void);

UNIT create_unit_harvest(void);
UNIT create_unit_freman(void);
UNIT create_unit_soldier(void);
UNIT create_unit_fighter(void);
UNIT create_unit_htank(void);
UNIT create_unit_sandworm(void);

STRUCTURE create_str_base(void) {
    STRUCTURE str;
    str.camp = 0;
    strcpy(str.name, "Base");
    strcpy(str.instruction, "");
    str.construction_cost = 0;
    str.durability = 50;
    str.max_durability = 50;
    str.order = 72; // H

    return str;
}

STRUCTURE create_str_plate(void) {
    STRUCTURE str;
    str.camp = 0;
    strcpy(str.name, "Plate");
    strcpy(str.instruction, "laying before building");
    str.construction_cost = 1;
    str.durability = 0;
    str.max_durability = 0;
    str.order = 0;

    return str;
}

STRUCTURE create_str_dormitory(void) {
    STRUCTURE str;
    str.camp = 0;
    strcpy(str.name, "Dormitory");
    strcpy(str.instruction, "increase the max population(10)");
    str.construction_cost = 2;
    str.durability = 10;
    str.max_durability = 10;
    str.order = 0;

    return str;
}

STRUCTURE create_str_garage(void) {
    STRUCTURE str;
    str.camp = 0;
    strcpy(str.name, "Garage");
    strcpy(str.instruction, "increase the max spice(10)");
    str.construction_cost = 4;
    str.durability = 10;
    str.max_durability = 10;
    str.order = 0;

    return str;
}

STRUCTURE create_str_barracks(void) {
    STRUCTURE str;
    str.camp = 1;
    strcpy(str.name, "Barracks");
    strcpy(str.instruction, "get a soldier");
    str.construction_cost = 4;
    str.durability = 20;
    str.max_durability = 20;
    str.order = 83; // S

    return str;
}

STRUCTURE create_str_shelter(void) {
    STRUCTURE str;
    str.camp = 1;
    strcpy(str.name, "Shelter");
    strcpy(str.instruction, "get a special unit");
    str.construction_cost = 5;
    str.durability = 30;
    str.max_durability = 30;
    str.order = 70; // F

    return str;
}

STRUCTURE create_str_arena(void) {
    STRUCTURE str;
    str.camp = 0;
    strcpy(str.name, "Arena");
    strcpy(str.instruction, "get a fighter");
    str.construction_cost = 3;
    str.durability = 15;
    str.max_durability = 15;
    str.order = 70; // F

    return str;
}

STRUCTURE create_str_factory(void) {
    STRUCTURE str;
    str.camp = 0;
    strcpy(str.name, "Factory");
    strcpy(str.instruction, "get a special unit");
    str.construction_cost = 5;
    str.durability = 30;
    str.max_durability = 30;
    str.order = 84; // T

    return str;
}

UNIT create_unit_harvest(void) {
    UNIT u;
    u.camp = 0;
    strcpy(u.name, "Harvester");
    u.production_cost = 5;
    u.population = 5;
    u.moving_cycle = 2000;
    u.damage = 0;
    u.attack_cycle = 0;
    u.hp = 70;
    u.max_hp = 70;
    u.vision = 0;
    u.order[0] = 72; // H, harvest
    u.order[1] = 77; // M, moving

    return u;
}

UNIT create_unit_freman(void) {
    UNIT u;
    u.camp = 1;
    strcpy(u.name, "Freman");
    u.production_cost = 5;
    u.population = 2;
    u.moving_cycle = 400;
    u.damage = 15;
    u.attack_cycle = 200;
    u.hp = 25;
    u.max_hp = 25;
    u.vision = 8;
    u.order[0] = 77; // M, moving
    u.order[1] = 80; // P, patrol

    return u;
}

UNIT create_unit_soldier(void) {
    UNIT u;
    u.camp = 1;
    strcpy(u.name, "Soldier");
    u.production_cost = 1;
    u.population = 1;
    u.moving_cycle = 1000;
    u.damage = 5;
    u.attack_cycle = 800;
    u.hp = 15;
    u.max_hp = 15;
    u.vision = 1;
    u.order[0] = 77; // M, moving
    u.order[1] = 80; // P, patrol

    return u;
}

UNIT create_unit_fighter(void) {
    UNIT u;
    u.camp = 2;
    strcpy(u.name, "Fighter");
    u.production_cost = 1;
    u.population = 1;
    u.moving_cycle = 1200;
    u.damage = 6;
    u.attack_cycle = 600;
    u.hp = 15;
    u.max_hp = 15;
    u.vision = 1;
    u.order[0] = 77; // M, moving
    u.order[1] = 80; // P, patrol

    return u;
}

UNIT create_unit_htank(void) {
    UNIT u;
    u.camp = 0;
    strcpy(u.name, "HTank");
    u.production_cost = 12;
    u.population = 5;
    u.moving_cycle = 3000;
    u.damage = 40;
    u.attack_cycle = 4000;
    u.hp = 15;
    u.max_hp = 15;
    u.vision = 4;
    u.order[0] = 77; // M, moving
    u.order[1] = 80; // P, patrol

    return u;
}

UNIT create_unit_sandworm(void) {
    UNIT u;
    u.camp = 3;
    strcpy(u.name, "Sandworm");
    u.production_cost = 0;
    u.population = 0;
    u.moving_cycle = 2500;
    u.damage = 999;
    u.attack_cycle = 10000;
    u.hp = 999;
    u.max_hp = 999;
    u.vision = 999;
    u.order[0] = 0;
    u.order[1] = 0;

    return u;
}
