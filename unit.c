#include <string.h>
#include "unit.h"

structure create_str_base(void) {
    structure str = {
        .camp = 0,
        .name = "Base",
        .instruction = "This is the Base",
        .durability = 50,
        .max_durability = 50,
        .order = 72
    };
    return str;
}

structure create_str_plate(void) {
    structure str = {
        .camp = 0,
        .name = "plate",
        .instruction = "Laying before building",
        .durability = 50,
        .max_durability = 50,
        .order = 72,
        .construction_cost = 0
    };
    return str;
}

structure create_str_dormitory(void) {
    structure str = {
        .camp = 0,
        .name = "domitory",
        .instruction = "Increase the max population(+10)",
        .durability = 50,
        .max_durability = 50,
        .construction_cost = 0,
        .order = 72
    };
    return str;
}

structure create_str_garage(void) {
    structure str = {
        .camp = 0,
        .name = "Garage",
        .instruction = "Increase the max spice(+10)",
        .durability = 50,
        .max_durability = 50,
        .construction_cost = 0,
        .order = 72
    };
    return str;
}

structure create_str_barracks(void) {
    structure str = {
        .camp = 1,
        .name = "Barracks",
        .instruction = "Get a soldier",
        .durability = 20,
        .max_durability = 20,
        .construction_cost = 4,
        .order = 83 // s
    };
    return str;
}

structure create_str_shelter(void) {
    structure str = {
        .camp = 1,
        .name = "Shelter",
        .instruction = "Get a special unit",
        .durability = 30,
        .max_durability = 30,
        .construction_cost = 5,
        .order = 70 // f
    };
    return str;
}

structure create_str_arena(void) {
    structure str = {
        .camp = 0,
        .name = "Arena",
        .instruction = "Get a fighter",
        .durability = 15,
        .max_durability = 15,
        .construction_cost = 3,
        .order = 70
    };
    return str;
}

structure create_str_factory(void) {
    structure str = {
        .camp = 0,
        .name = "Factory",
        .instruction = "Get a special unit",
        .durability = 30,
        .max_durability = 30,
        .construction_cost = 0,
        .order = 84
    };
    return str;
}

unit create_unit_harvester(void) {
    unit u = {
        u.camp = 0,
        .name = "harvester",
        .production_cost = 5,
        .population = 5,
        .moving_cycle = 2000,
        .damage = 0,
        .attack_cycle = 0,
        .hp = 70,
        .max_hp = 70,
        .vision = 0,
        .order[0] = 72, // h, harvest
        .order[1] = 77, // m, moving
    };
    return u;
}

unit create_unit_freman(void) {
    unit u = {
        u.camp = 1,
        .name = "freman",
        .production_cost = 5,
        .population = 2,
        .moving_cycle = 400,
        .damage = 15,
        .attack_cycle = 200,
        .hp = 25,
        .max_hp = 25,
        .vision = 8,
        .order[0] = 77, // m, moving
        .order[1] = 80, // p, patrol
    };
    return u;
}

unit create_unit_soldier(void) {
    unit u = {
        u.camp = 1,
        .name = "soldier",
        .production_cost = 1,
        .population = 1,
        .moving_cycle = 1000,
        .damage = 5,
        .attack_cycle = 800,
        .hp = 15,
        .max_hp = 15,
        .vision = 1,
        .order[0] = 77, // m, moving
        .order[1] = 80  // p, patrol
    };
    return u;
}

unit create_unit_fighter(void) {
    unit u = {
        u.camp = 2,
        .name = "fighter",
        .production_cost = 1,
        .population = 1,
        .moving_cycle = 1200,
        .damage = 6,
        .attack_cycle = 600,
        .hp = 15,
        .max_hp = 15,
        .vision = 1,
        .order[0] = 77, // m, moving
        .order[1] = 80  // p, patrol
    };
    return u;
}

unit create_unit_htank(void) {
    unit u = {
        u.camp = 0,
        .name = "htank",
        .production_cost = 12,
        .population = 5,
        .moving_cycle = 3000,
        .damage = 40,
        .attack_cycle = 4000,
        .hp = 15,
        .max_hp = 15,
        .vision = 4,
        .order[0] = 77, // m, moving
        .order[1] = 80  // p, patrol
    };

    return u;
}

unit create_unit_sandworm(void) {
    unit u = {
        u.camp = 3,
        .name = "sandworm",
        .production_cost = 0,
        .population = 0,
        .moving_cycle = 2500,
        .damage = 999,
        .attack_cycle = 10000,
        .hp = 999,
        .max_hp =999,
        .vision = 999,
        .order[0] = 0,
        .order[1] = 0
    };
    return u;
}
