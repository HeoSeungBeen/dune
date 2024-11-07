/*
*  display.c:
* 화면에 게임 정보를 출력
* 맵, 커서, 시스템 메시지, 정보창, 자원 상태 등등
* io.c에 있는 함수들을 사용함
*/

#include "display.h"
#include "io.h"
#include "unit.h"

// 출력할 내용들의 좌상단(topleft) 좌표
const POSITION resource_pos = { 0, 0 };
const POSITION map_pos = { 1, 0 };


char backbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };
char frontbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };

void project(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH]);
void display_resource(RESOURCE resource);
void display_map(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH]);
void display_cursor(CURSOR cursor);
void display_object_info(void); // 상태창 초기화 
void display_structure_info(STRUCTURE structure);
void display_unit_info(UNIT unit);
//void display_construction(CURSOR cursor);
//void display_unit(CURSOR cursor);


void display(RESOURCE resource, char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH], CURSOR cursor)
{
	display_resource(resource);
	display_map(map);
	display_cursor(cursor);
	display_object_info(void);
	// display_system_message()
	// display_commands()
	// ...
}

void display_resource(RESOURCE resource) {
	set_color(COLOR_RESOURCE);
	gotoxy(resource_pos);
	printf("spice = %d/%d, population=%d/%d\n",
		resource.spice, resource.spice_max,
		resource.population, resource.population_max
	);
}

// subfunction of draw_map()
void project(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH]) {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			for (int k = 0; k < N_LAYER; k++) {
				if (src[k][i][j] >= 0) {
					dest[i][j] = src[k][i][j];
				}
			}
		}
	}
}

void display_map(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH]) {
	project(map, backbuf);

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (frontbuf[i][j] != backbuf[i][j]) {
				POSITION pos = {i, j };
				printc(padd(map_pos, pos), backbuf[i][j], COLOR_DEFAULT);
			}
			frontbuf[i][j] = backbuf[i][j];
		}
	}
}

// frontbuf[][]에서 커서 위치의 문자를 색만 바꿔서 그대로 다시 출력
void display_cursor(CURSOR cursor) {
	POSITION prev = cursor.previous;
	POSITION curr = cursor.current;

	char ch = frontbuf[prev.row][prev.column];
	printc(padd(map_pos, prev), ch, COLOR_DEFAULT);

	ch = frontbuf[curr.row][curr.column];
	printc(padd(map_pos, curr), ch, COLOR_CURSOR);
}

void display_object_info(void) {

}

void display_structure_info(STRUCTURE structure) {
	if (structure.camp == 0) {
		printf(" House Atreides \n");
	}
	else if(structure.camp == 1){
		printf(" House Harkonnen \n");
	}
	else {
		printf(" Neutrality \n");
	}
	printf("name : % s\n", structure.name);
	printf("%s\n", structure.instruction);
	printf("cost : %d\n", structure.construction_cost);
	printf("durability : %d / %d\n", structure.durability, structure.max_durability);

}

void display_unit_info(UNIT unit) {
	if (unit.camp == 0) {
		printf(" House Atreides ");
	}
	else if (unit.camp == 1) {
		printf(" House Harkonnen ");
	}
	else {
		printf(" Neutrality \n");
	}
	printf("%s\n", unit.name);
	printf("hp : %d / %d\n", unit.hp, unit.max_hp);
	printf("cost : %d\n", unit.production_cost);
	printf("population : %d\n", unit.population);
	printf("damage / cycle : %d / %d\n", unit.damage, unit.attack_cycle);
	printf("speed : %d\n", unit.moving_cycle);
	printf("vision : %d\n", unit.vision);
}