#include "pch.h"
#include "gtest/gtest.h"
#include "../SNAKEANDLADDER/SnakesAndLadders.h"

TEST(CreateBoardTest, SnakeLadderPositions) {

	Game game("../SNAKEANDLADDER/map.txt", 4);

	ASSERT_TRUE(game.IsLadder(4));

	ASSERT_TRUE(game.IsSnake(32));

	ASSERT_TRUE(game.IsLadder(67));

	ASSERT_TRUE(game.IsSnake(99));

}

TEST(CreateBoardTest, BoardLinks) {

	Game game("../SNAKEANDLADDER/map.txt", 4);

	for (int i = 1; i < 100; ++i) {

		Tile* current = game.GetTile(i);
		Tile* next = game.GetTile(i + 1);

		if (i % 10 != 0) {
			ASSERT_TRUE(current->next == next);
			ASSERT_TRUE(next->previous == current);
		}
		else {
			ASSERT_TRUE(current->up == next);
			ASSERT_TRUE(next->down == current);
		}
	}
}

TEST(CreateBoardTest, EdgeTiles) {


	Game game("../SNAKEANDLADDER/map.txt", 4);

	for (int i = 1; i < 10; ++i) {
		ASSERT_TRUE(game.GetTile(i)->down == NULL);
	}

	for (int i = 91; i <= 100; ++i) {
		ASSERT_TRUE(game.GetTile(i)->up == NULL);
	}
}

TEST(RollDiceTest, GameStart) {

	Game game("../SNAKEANDLADDER/map.txt", 4);

	auto& queue = game.GetTurnQueue();

	for (int i = 1; i <= 4; ++i) {
		// P1 P2 P3 P4
		// P2 P3 P4 P1
		// P3 P4 P1 P2
		// P4 P1 P2 P3 
		ASSERT_TRUE(queue.front() == i);

		game.RollDice(6);
	}
}

TEST(RollDiceTest, ReverseQueue) {


	Game game("../SNAKEANDLADDER/map.txt", 4);

	for (int i = 1; i <= 4; ++i) {
		// bringing all players on the board
		game.RollDice(6);
	}

	auto& queue = game.GetTurnQueue();

	ASSERT_TRUE(queue.front() == 1);

	// roll divisible by 3, queue should reverse
	game.RollDice(3);

	ASSERT_TRUE(queue.front() == 4);

	ASSERT_TRUE(queue.back() == 1);
}

TEST(MovePlayerTest, NormalTraversal) {


	Game game("../SNAKEANDLADDER/map.txt", 4);

	RollStack stack;

	stack.push_roll(6);
	stack.push_roll(5);

	ASSERT_TRUE(game.TraverseBoard(44, stack) == 55);

	stack.empty();

	stack.push_roll(6);
	stack.push_roll(6);
	stack.push_roll(4);

	ASSERT_TRUE(game.TraverseBoard(13, stack) == 29);
}

TEST(MovePlayerTest, LadderTraversal) {


	Game game("../SNAKEANDLADDER/map.txt", 4);

	RollStack stack;

	stack.push_roll(3);

	ASSERT_TRUE(game.TraverseBoard(1, stack) == 39);

	stack.empty();

	stack.push_roll(6);
	stack.push_roll(1);
	ASSERT_TRUE(game.TraverseBoard(60, stack) == 92);
}

TEST(MovePlayerTest, SnakeTraversal) {

	Game game("../SNAKEANDLADDER/map.txt", 4);

	RollStack stack;

	stack.push_roll(8);

	ASSERT_TRUE(game.TraverseBoard(24, stack) == 6);

	stack.empty();

	stack.push_roll(6);
	stack.push_roll(6);
	stack.push_roll(2);
	ASSERT_TRUE(game.TraverseBoard(85, stack) == 63);
}