# snake game

This is a simple C++ application to denote game loop pattern by snake game. We know, the game loop pattern we are using in every game engine. Second to second every changes happens from this game loop. This allows to run game smoothly frame by frame changes. The game loop runs continuously during gameplay. Each turn of the loop, it processes user input without blocking, updates the game state, and renders the game. It tracks the passage of time to control the rate of gameplay.

The game loop contain five core functions,
	1. init()
	2. run()
	3. processInput()
	4. update()
	5. render()
