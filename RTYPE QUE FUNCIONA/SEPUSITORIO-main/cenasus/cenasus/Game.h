#pragma once
#include "Background.h"
#include "player.h"
#include "Enemy.h"
#include <vector>
#include <cmath>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

class Game{;
public:
	Game();
	void init();
	void update();
	void render();
	void handleInput();
	void dispose();

	bool collide(float x1, float y1, float r1, float x2, float y2, float r2) {
		float distX = x1 - x2;
		float distY = y1 - y2;

		float dist = sqrt(distX * distX + distY * distY);

		if (dist <= r1 + r2) {
			return true;
		}
		return false;
	}
	

private:
	Background* background;
	player player;


	std::vector<Enemy*> enemies;

	ALLEGRO_TIMER* levelTimer;
	ALLEGRO_EVENT_QUEUE* event_queue;
	int currentLevel;

	ALLEGRO_FONT* font;
};

