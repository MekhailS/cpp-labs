#include "Game.h"


Game::Game(ifstream& fileWithLevel, int defaultMaxLives, int defaultRespawnTime) :
	maze(fileWithLevel), pacman(maze.GetSpawnPacman(), 2 * defaultMaxLives, 40) {

	pacman = Pacman(maze.GetSpawnPacman(), 2 * defaultMaxLives, 40);

	ghostsDeadWRespawn.push_back(shared_ptr<Ghost>(new
		Ghost(maze.GetSpawnGhosts(), defaultMaxLives, defaultRespawnTime, GHOST_CLEVER, maze.GetJailGhosts())));
	ghostsDeadWRespawn.push_back(shared_ptr<Ghost>(new
		Ghost(maze.GetSpawnGhosts(), defaultMaxLives, defaultRespawnTime, GHOST_STUPID, maze.GetJailGhosts())));
	ghostsDeadWRespawn.push_back(shared_ptr<Ghost>(new
		Ghost(maze.GetSpawnGhosts(), defaultMaxLives, defaultRespawnTime, GHOST_RANDOM, maze.GetJailGhosts())));

	scoreToWin = maze.GetMaxScore();
}


GAME_STATUS Game::Update() {
	switch (pacman.MakeStep(maze)) {
	case 2:
		SetStatusAliveGhosts(ENT_FRIGHTENED);
		break;

	case 3:
		SetStatusAliveGhosts(ENT_NORMAL);
		break;
	}
	ConflictPacmanGhosts();

	RespawnGhosts();
	for (auto& ghost : ghostsAlive) {
		ghost->MakeStep(maze, pacman.GetPosition());
	}
	ConflictPacmanGhosts();

	for (auto& ghost : ghostsDeadWRespawn) {
		ghost->MakeStep(maze, pacman.GetPosition());
	}

	if (pacman.TryRespawn()) {
		RestartGhosts();
	}

	if (pacman.GetLives() > 0) {
		if (pacman.GetScore() >= scoreToWin)
			return GAME_WIN;
		return GAME_NORMAL;
	}
	else {
		return GAME_LOSE;
	}
}


void Game::SetPacmanDirection(DIRECTION direction) {
	pacman.SetMoveDirection(direction);
}


bool Game::ConflictPacmanGhosts() {
	auto it = ghostsAlive.begin();
	while (it != ghostsAlive.end()) {
		if (pacman.GetPosition() == (*it)->GetPosition()) {
			if ((*it)->GetStatus() == ENT_FRIGHTENED) {
				(*it)->Kill();
				if ((*it)->GetLives() > 0) {
					ghostsDeadWRespawn.push_back(*it);
				}
				else {
					ghostsDead.push_back(*it);
				}
				it = ghostsAlive.erase(it);
			}
			else {
				pacman.Kill();
				++it;
			}
		}
		else {
			++it;
		}
	}
	return 1;
}


bool Game::RespawnGhosts() {
	auto it = ghostsDeadWRespawn.begin();
	while (it != ghostsDeadWRespawn.end()) {
		if ((*it)->TryRespawn()) {
			ghostsAlive.push_back(*it);
			it = ghostsDeadWRespawn.erase(it);
		}
		else {
			++it;
		}
	}
	return 1;
}


void Game::RestartGhosts() {
	ghostsDeadWRespawn.splice(ghostsDeadWRespawn.begin(), ghostsAlive);
	for (auto& ghost : ghostsDeadWRespawn) {
		ghost->MoveToJail();
	}
}


void Game::SetStatusAliveGhosts(ENT_STATUS newStatus) {
	for (auto& ghost : ghostsAlive) {
		ghost->SetStatus(newStatus);
	}
}


void Game::DrawCellsOnEntities(HDC hdc) const {
	for (auto& ghost : ghostsAlive) {
		maze.DrawCellByVector(hdc, ghost->GetPosition());
	}
	for (auto& ghost : ghostsDeadWRespawn) {
		maze.DrawCellByVector(hdc, ghost->GetPosition());
	}
	maze.DrawCellByVector(hdc, pacman.GetPosition());
}


void Game::DrawEntities(HDC hdc) const {
	for (auto& ghost : ghostsAlive) {
		ghost->Draw(hdc);
	}
	for (auto& ghost : ghostsDeadWRespawn) {
		ghost->Draw(hdc);
	}
	pacman.Draw(hdc);
}


void Game::DrawAll(HDC hdc) const {
	maze.DrawMaze(hdc);
	DrawEntities(hdc);
}