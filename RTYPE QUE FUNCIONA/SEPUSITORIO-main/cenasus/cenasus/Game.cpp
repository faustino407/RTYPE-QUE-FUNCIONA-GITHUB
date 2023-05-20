#include "Game.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <algorithm>
#include <functional>
#include "constants.h"

Game::Game() {}
void Game::init() {
	background = new Background("res/Fundo.png");
	player.init();


	


	//for (int i = 0; i < 4; i++) {
	//	enemies.emplace_back(new Enemy(1));
	//	enemies.emplace_back(new Enemy(2));
		
	//}
	currentLevel = 1;
	levelTimer = al_create_timer(5);
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(levelTimer));
	al_start_timer(levelTimer);

	font = al_create_builtin_font();

}
void Game::update() {

	player.update();

	if (al_get_timer_started(levelTimer)) {
		
		ALLEGRO_EVENT event;
		if (al_get_next_event(event_queue, &event)) {
			al_stop_timer(levelTimer);
			if (enemies.size() == 0) {

				

				switch (currentLevel)
				{
				case 1:
					for (int i = 0; i < 4; i++) {
						enemies.emplace_back(new Enemy(1));
					}
					for (int i = 0; i < 2; i++) {
						enemies.emplace_back(new Enemy(2));
					}
					break;
				case 2:
					for (int i = 0; i < 8; i++) {
						enemies.emplace_back(new Enemy(1));
					}
					for (int i = 0; i < 4; i++) {
						enemies.emplace_back(new Enemy(2));
					}
					break;
				case 3:
					for (int i = 0; i < 4; i++) {
						enemies.emplace_back(new Enemy(1));
					}
					for (int i = 0; i < 2; i++) {
						enemies.emplace_back(new Enemy(2));
					}
					for (int i = 0; i < 2; i++) {
						enemies.emplace_back(new Enemy(3));
					}
					break;
				}
				
			}
			currentLevel++;
		}
		return;
	}

	background->update();
	

	for (auto& enemy : enemies) {
		enemy->update();
	}


	
	// Player - Enemies Collosion
	for (int i = 0; i < player.getBullets().size(); i++) {
		Bullet* bullet = player.getBullets()[i];
		float bx = bullet->getX();
		float by = bullet->getY();
		float br = bullet->getRadius();
		for (int j = 0; j < enemies.size(); j++) {
			Enemy* enemy = enemies[j];
			float ex = enemy->getX();
			float ey = enemy->getY();
			float er = enemy->getRadius();
			if (collide(bx, by, br, ex, ey, er)) {
				// Decrease enemy's life
				enemy->hit();
				// Remove the bullet
				bullet->kill();
				//if (player.isDead()){ // Game Over}
			}
		}
	}


	// Remove dead enemies
	for (int i = enemies.size() - 1; i >= 0; i--) {
		Enemy* enemy = enemies[i];
		if (enemy->isDead()) {
			delete enemy;
			enemies.erase(enemies.begin() + i);
		}
	}

	if (enemies.size() == 0)al_start_timer(levelTimer);
}


void Game::handleInput() {
	player.handleInput();
}

void Game::render() {

	background->render();
	player.render();

	for (auto& enemy : enemies) {
		enemy->render();
	}

	//Draw the level text "level 1"
	if (al_get_timer_started(levelTimer)) {
		al_draw_textf(font, al_map_rgb_f(1, 1, 1), GAME_WIDTH / 2, GAME_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "Level %i", currentLevel);
	}

}

void Game::dispose() {
	background->dispose();
	player.dispose();

	for (auto& enemy : enemies) {
		enemy->dispose();
		delete enemy;
	}
	enemies.clear();
	al_destroy_timer(levelTimer);

	al_destroy_font(font);
}