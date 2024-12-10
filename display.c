/*
*  display.c:
* ȭ�鿡 ���� ������ ���
* ��, Ŀ��, �ý��� �޽���, ����â, �ڿ� ���� ���
* io.c�� �ִ� �Լ����� �����
*/

#include "display.h"
#include "io.h"
#include "unit.h"

// ����� ������� �»��(topleft) ��ǥ
const POSITION resource_pos = { 0, 0 };
const POSITION map_pos = { 1, 0 };
const POSITION status_pos = { 1, 60 };
const POSITION sys_pos = { 19, 0 };
const POSITION command_pos = { 19, 60 };

char backbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };
char frontbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };

void project(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH]);
void display_resource(RESOURCE resource);
void display_map(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH]);
void display_cursor(CURSOR cursor);
void display_status_info();
void display_structure_info(structure structure);
void display_unit_info(unit unit);


void display(RESOURCE resource, char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH], CURSOR cursor)
{
	display_resource(resource);
	display_map(map);
	display_cursor(cursor);
	display_status_info();

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
	int color = 15;

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (frontbuf[i][j] != backbuf[i][j]) {
				POSITION pos = {i, j };
				if (backbuf[i][j] == 'B' || backbuf[i][j] == 'H') {
					color = 0x17;
				}
				else if (backbuf[i][j] == 'W') {
					color = 0x67;
				}
				else if (backbuf[i][j] == 'P') {
					color = 0x87;
				}
				else if (backbuf[i][j] == 'S') {
					color = 0xC7;
				}
				printc(padd(map_pos, pos), backbuf[i][j], color);

			}
			frontbuf[i][j] = backbuf[i][j];
		}
		color = 15;
	}
}

// frontbuf[][]���� Ŀ�� ��ġ�� ���ڸ� ���� �ٲ㼭 �״�� �ٽ� ���
void display_cursor(CURSOR cursor) {
	POSITION prev = cursor.previous;
	POSITION curr = cursor.current;

	char ch = frontbuf[prev.row][prev.column];
	printc(padd(map_pos, prev), ch, COLOR_DEFAULT);

	ch = frontbuf[curr.row][curr.column];
	printc(padd(map_pos, curr), ch, COLOR_CURSOR);
}
void display_status_info(void) {
	set_color(15);
	gotoxy(status_pos);
	printf("%s", "<status information>");

	gotoxy(sys_pos);
	printf("%s", "<system message>");

	gotoxy(command_pos);
	printf("%s", "<command line>");
}

void display_structure_info(structure structure) {
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

void display_unit_info(unit unit) {
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