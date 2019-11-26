#include "Game.hpp"

bool operator==(Position positionLeft, Position positionRight)
{
	if ((positionLeft.x == positionRight.x) && (positionLeft.y == positionRight.y))
	{
		return true;
	}
	return false;
}
//
Snake initialSnake(int size, Direction direction)
{
	Snake snake;
	snake.size = size;
	snake.position = new Position[snake.size];
	//
	if (direction == Direction::Up)
	{
		for (int i = 0; i < snake.size; i++)
		{
			snake.position[i].x = LEFT_WALL + 5;
			snake.position[i].y = TOP_WALL + 2 + i;
		}
	}
	else if (direction == Direction::Down)
	{
		for (int i = 0; i < snake.size; i++)
		{
			snake.position[i].x = LEFT_WALL + 5;
			snake.position[i].y = TOP_WALL + 2 + (snake.size - i);
		}
	}
	else if (direction == Direction::Left)
	{
		for (int i = 0; i < snake.size; i++)
		{
			snake.position[i].x = LEFT_WALL + 5 + i;
			snake.position[i].y = TOP_WALL + 2;
		}
	}
	else
	{
		for (int i = 0; i < snake.size; i++)
		{
			snake.position[i].x = LEFT_WALL + 5 + (snake.size - i);
			snake.position[i].y = TOP_WALL + 2;
		}
	}
	return snake;
}
Food initialFood()
{
	Food food;
	srand(time(NULL));
	food.x = (LEFT_WALL + 1) + rand() % (((RIGHT_WALL - 1) - (LEFT_WALL + 1)) + 1);
	food.y = (TOP_WALL + 1) + rand() % (((BOT_WALL - 1) - (TOP_WALL + 1)) + 1);
	return food;
}
Position nodeEnd(Snake snake)
{
	return{ snake.position[snake.size - 1].x, snake.position[snake.size - 1].y };
}
//
void pollEvent(Direction &direction)
{
	int key = inputKey();
	if ((key == 'W' || key == 'w' || key == DirectionKey::KeyUp) && (direction != Direction::Down))
	{
		direction = Direction::Up;
	}
	else if ((key == 'S' || key == 's' || key == DirectionKey::KeyDown) && (direction != Direction::Up))
	{
		direction = Direction::Down;
	}
	else if ((key == 'A' || key == 'a' || key == DirectionKey::KeyLeft) && (direction != Direction::Right))
	{
		direction = Direction::Left;
	}
	else if ((key == 'D' || key == 'd' || key == DirectionKey::KeyRight) && (direction != Direction::Left))
	{
		direction = Direction::Right;
	}
}
void drawWall()
{
	for (int i = LEFT_WALL; i <= RIGHT_WALL; i++)
	{
		gotoXY(i, TOP_WALL);
		cout << (char)223;
		gotoXY(i, BOT_WALL);
		cout << (char)220;
	}
	//
	for (int i = TOP_WALL; i <= BOT_WALL; i++)
	{
		gotoXY(LEFT_WALL, i);
		cout << (char)222;
		gotoXY(RIGHT_WALL, i);
		cout << (char)221;
	}
}
void drawSnake(Snake snake)
{
	gotoXY(snake.position[0].x, snake.position[0].y);
	cout << (char)HEAD_SNAKE;
	//
	for (int i = 1; i < snake.size; i++)
	{
		gotoXY(snake.position[i].x, snake.position[i].y);
		cout << (char)BODY_SNAKE;
	}
}
void drawFood(Food food)
{
	gotoXY(food.x, food.y);
	cout << (char)FOOD;
}
void eraseNode(Position node)
{
	gotoXY(node.x, node.y);
	cout << " ";
}
void displayScore(int score)
{
	gotoXY(1, TOP_WALL);
	cout << "Your score: " << score;
}
void move(Snake &snake, Direction direction)
{
	for (int i = snake.size; i >= 1; i--)
	{
		snake.position[i] = snake.position[i - 1];
	}
	if (direction == Direction::Up)
	{
		snake.position[0].y--;
	}
	else if (direction == Direction::Down)
	{
		snake.position[0].y++;
	}
	else if (direction == Direction::Left)
	{
		snake.position[0].x--;
	}
	else
	{
		snake.position[0].x++;
	}
}
void actionEatFood(Snake &snake)
{
	Position* temp = new Position[snake.size];
	for (int i = 0; i < snake.size; i++)
	{
		temp[i] = snake.position[i];
	}
	snake.position = nullptr;
	delete[] snake.position;
	snake.position = new Position[snake.size + 1];
	for (int i = 0; i < snake.size; i++)
	{
		snake.position[i] = temp[i];
	}
	snake.position[snake.size] = snake.position[snake.size - 1];
	snake.size++;
	temp = nullptr;
	delete[] temp;
}
void actionDie()
{
	gotoXY(1, TOP_WALL + 1);
	cout << "ahuhu!";
}
void run()
{
	int score = 0, count = 0, speed = 100, size = 3;
	Direction direction = Direction::Right;
	Snake snake = initialSnake(size, direction);
	Food food = initialFood();
	Position positionNodeEnd;
	//
	drawWall();
	drawSnake(snake);
	drawFood(food);
	displayScore(score);
	while (true)
	{
		positionNodeEnd = nodeEnd(snake);
		pollEvent(direction);
		move(snake, direction);
		drawSnake(snake);
		eraseNode(positionNodeEnd);
		//
		if (isErrorFood(snake, food) && count == 0)
		{
			food = initialFood();
			drawFood(food);
			count = 0;
		}
		else
		{
			count++;
		}
		//
		if (isEatFood(snake, food) && count != 0)
		{
			score++;
			displayScore(score);
			actionEatFood(snake);
			food = initialFood();
			drawFood(food);
			count = 0;
		}
		//
		if (isDie(snake))
		{
			actionDie();
			break;
		}
		Sleep(speed);
	}
	
	//
}
//
bool isErrorFood(Snake snake, Food food)
{
	for (int i = 0; i < snake.size; i++)
	{
		if (snake.position[i] == food)
		{
			return true;
		}
	}
	return false;
}
bool isEatFood(Snake snake, Food food)
{
	if (snake.position[0] == food)
	{
		return true;
	}
	return false;
}
bool isDie(Snake snake)
{
	bool flag = false;
	if ((snake.position[0].x == LEFT_WALL) || (snake.position[0].x == RIGHT_WALL))
	{
		flag = true;
	}
	if ((snake.position[0].y == TOP_WALL) || (snake.position[0].y == BOT_WALL))
	{
		flag = true;
	}
	//
	for (int i = 1; i < snake.size; i++)
	{
		if (snake.position[0] == snake.position[i])
		{
			flag = true;
		}
	}
	return flag;
}