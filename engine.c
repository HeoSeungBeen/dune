#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <Windows.h>
#include "common.h"
#include "io.h"
#include "display.h"
#include "unit.h"


void init(void);
void intro(void);
void outro(void);
void init_object(void); // 최초 오브젝트 생성 함수
void cursor_move(DIRECTION dir);
void cursor_move_quad(DIRECTION dir);
void sample_obj_move(void);
void dot_structure(structure);
int is_double_click(int);
POSITION sample_obj_next_position(void);

/* ================= control =================== */
int sys_clock = 0;		// system-wide clock(ms)
CURSOR cursor = { { 1, 1 }, {1, 1} };


/* ================= game data =================== */
char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH] = { 0 };

structure player_str[30] = { 0 };
structure computer_str[30] = { 0 };
structure neutral_zone[30] = { 0 };

unit player_unit[50] = { 0 };
unit computer_unit[50] = { 0 };
unit neutral_unit[50] = { 0 };


int index_global_player_str = 0;
int index_global_player_unit = 0;
int index_global_computer_str = 0;
int index_global_computer_unit = 0;
int index_neutral_zone = 0;
int index_neutral_unit = 0;

KEY prev_key = k_none;

RESOURCE resource = { 
	.spice = 0,
	.spice_max = 5,
	.population = 0,
	.population_max = 10
};

OBJECT_SAMPLE obj = {
	.pos = {1, 1},
	.dest = {MAP_HEIGHT - 2, MAP_WIDTH - 2},
	.repr = 'o',
	.speed = 300,
	.next_move_time = 300
};

/* ================= main() =================== */
int main(void) {
	srand((unsigned int)time(NULL));

	init();
	intro();
	display(resource, map, cursor);
	init_object();

	while (1) {
		// loop 돌 때마다(즉, TICK==10ms마다) 키 입력 확인
		KEY key = get_key();
		// 키 입력이 있으면 처리
		if (is_arrow_key(key)) {
			if (is_double_click(key)) {
				cursor_move_quad(key);
			}
			else {
				cursor_move(key);
			}
		}
		else {
			// 방향키 외의 입력
			switch (key) {
			case k_quit: outro();
			case k_space: 
				//오브젝트 선택
				// display_object_info()
			case k_esc:
				// 상태창 클리어
			case k_none:
			case k_undef:
			default: break;
			}
		}
		prev_key = key;
		// 샘플 오브젝트 동작
		sample_obj_move();

		// 화면 출력
		display(resource, map, cursor);

		Sleep(10);
		sys_clock += 10;
	}
}

/* ================= subfunctions =================== */
void intro(void) {
	printf("DUNE 1.5\n");
	printf("%c", '■');
	Sleep(100);
	system("cls");
}

void outro(void) {
	printf("exiting...\n");
	exit(0);
}

void init(void) {
	// layer 0(map[0])에 지형 생성
	// 전체 맵 크기 설정 (가로 100, 세로 24)
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			map[0][i][j] = ' ';  // 기본 값은 공백으로 설정
			map[1][i][j] = -1;    // layer 1은 -1로 채우기
		}
	}

	// 각 사분면의 테두리 만들기 (각각 '#')
	// 1사분면
	for (int i = 0; i < 18; i++) {
		map[0][i][0] = '#';             // 왼쪽
		map[0][i][59] = '#';            // 오른쪽
	}
	for (int j = 0; j < 60; j++) {
		map[0][0][j] = '#';             // 위쪽
		map[0][17][j] = '#';            // 아래쪽
	}

	// object sample
	map[1][obj.pos.row][obj.pos.column] = 'o';

}
void dot_structure(structure st) {
	char S = NULL;
	if (strcmp(st.name, "Base") == 0) {
		S = 'B';
	}
	if (strcmp(st.name, "Plate") == 0) {
		S = 'P';
	}
	if (strcmp(st.name, "spaice") == 0) {
		S = 'S';
		map[0][st.pos.row][st.pos.column] = S;
		return;
	}
	map[0][st.pos.row][st.pos.column] = S;
	map[0][st.pos.row][st.pos.column + 1] = S;
	map[0][st.pos.row + 1][st.pos.column + 1] = S;
	map[0][st.pos.row + 1][st.pos.column] = S;
}
void dot_unit(unit u) {
	char S = NULL;
	if (strcmp(u.name, "harvester") == 0) {
		S = 'H';
	}
	if (strcmp(u.name, "sandworm") == 0) {
		S = 'W';
	}
	map[1][u.pos.row][u.pos.column] = S;
}

void init_object(void) {
	player_str[index_global_player_str] = create_str_base(15, 1);
	dot_structure(player_str[index_global_player_str]);

	player_unit[index_global_player_unit] = create_unit_harvester(13, 1);
	dot_unit(player_unit[index_global_player_unit]);

	computer_str[index_global_computer_str] = create_str_base(1, 57);
	dot_structure(computer_str[index_global_computer_str]);

	computer_unit[index_global_computer_unit] = create_unit_harvester(4, 58);
	dot_unit(computer_unit[index_global_computer_unit]);



	neutral_zone[0] = create_str_plate(15, 3);
	dot_structure(neutral_zone[0]);
	neutral_zone[1] = create_str_plate(1, 55);
	dot_structure(neutral_zone[1]);
	neutral_zone[2] = create_str_spa(11, 1);
	dot_structure(neutral_zone[2]);
	neutral_zone[3] = create_str_spa(6, 58);
	dot_structure(neutral_zone[3]);


	neutral_unit[0] = create_unit_sandworm(7, 8);
	dot_unit(neutral_unit[0]);
	neutral_unit[1] = create_unit_sandworm(3, 46);
	dot_unit(neutral_unit[1]);
	
	// 인덱스 변경
	index_global_player_str = 1;
	index_global_player_unit = 1;
	index_global_computer_str = 1;
	index_global_computer_unit = 1;
	index_neutral_zone = 4;
	index_neutral_unit = 2;

	resource.population += 5;

}
int is_double_click(int key) {
	static int last_key = 0;
	static clock_t last_time = 0;

	clock_t current_time = clock();
	int time_difference = (current_time - last_time) * 1000 / CLOCKS_PER_SEC;  // 밀리초로 변환

	if (key == last_key && time_difference <= DOUBLE_CLICK_INTERVAL) {
		last_key = 0;  // 더블 클릭 감지 후 초기화
		return 1;       // 더블 클릭 감지됨
	}
	else {
		last_key = key;      // 현재 키와 시간 저장
		last_time = current_time;
		return 0;            // 더블 클릭 아님
	}
}

// (가능하다면) 지정한 방향으로 커서 이동
void cursor_move(DIRECTION dir) {
	POSITION curr = cursor.current;
	POSITION new_pos = pmove(curr, dir);

	// validation check
	if (1 <= new_pos.row && new_pos.row <= MAP_HEIGHT - 2 && 
		1 <= new_pos.column && new_pos.column <= MAP_WIDTH - 2) {

		cursor.previous = cursor.current;
		cursor.current = new_pos;
	}
}

void cursor_move_quad(DIRECTION dir) {
	POSITION curr = cursor.current;
	POSITION new_pos = pmove_quad(curr, dir);

	// validation check
	if (1 <= new_pos.row && new_pos.row <= MAP_HEIGHT - 2 &&
		1 <= new_pos.column && new_pos.column <= MAP_WIDTH - 2) {

		cursor.previous = cursor.current;
		cursor.current = new_pos;
	}
}


/* ================= sample object movement =================== */
POSITION sample_obj_next_position(void) {
	// 현재 위치와 목적지를 비교해서 이동 방향 결정	
	POSITION diff = psub(obj.dest, obj.pos);
	DIRECTION dir;

	// 목적지 도착. 지금은 단순히 원래 자리로 왕복
	if (diff.row == 0 && diff.column == 0) {
		if (obj.dest.row == 1 && obj.dest.column == 1) {
			// topleft --> bottomright로 목적지 설정
			POSITION new_dest = { MAP_HEIGHT - 2, MAP_WIDTH - 2 };
			obj.dest = new_dest;
		}
		else {
			// bottomright --> topleft로 목적지 설정
			POSITION new_dest = { 1, 1 };
			obj.dest = new_dest;
		}
		return obj.pos;
	}
	
	// 가로축, 세로축 거리를 비교해서 더 먼 쪽 축으로 이동
	if (abs(diff.row) >= abs(diff.column)) {
		dir = (diff.row >= 0) ? d_down : d_up;
	}
	else {
		dir = (diff.column >= 0) ? d_right : d_left;
	}
	
	// validation check
	// next_pos가 맵을 벗어나지 않고, (지금은 없지만)장애물에 부딪히지 않으면 다음 위치로 이동
	// 지금은 충돌 시 아무것도 안 하는데, 나중에는 장애물을 피해가거나 적과 전투를 하거나... 등등
	POSITION next_pos = pmove(obj.pos, dir);
	if (1 <= next_pos.row && next_pos.row <= MAP_HEIGHT - 2 && \
		1 <= next_pos.column && next_pos.column <= MAP_WIDTH - 2 && \
		map[1][next_pos.row][next_pos.column] < 0) {
		
		return next_pos;
	}
	else {
		return obj.pos;  // 제자리
	}
}

void sample_obj_move(void) {
	if (sys_clock <= obj.next_move_time) {
		// 아직 시간이 안 됐음
		return;
	}

	// 오브젝트(건물, 유닛 등)은 layer1(map[1])에 저장
	map[1][obj.pos.row][obj.pos.column] = -1;
	obj.pos = sample_obj_next_position();
	map[1][obj.pos.row][obj.pos.column] = obj.repr;

	obj.next_move_time = sys_clock + obj.speed;
}

void sandworm_move(void) {
	int num = rand() % 4;
	neutral_unit[0] = create_unit_sandworm(7, 8);
	dot_unit(neutral_unit[0]);
	map[1][neutral_unit[0].pos.row][neutral_unit[0].pos.column];
}