# Snake Game

This is a simple C++ application to denote game loop pattern by snake game. We know, the game loop pattern we are using in every game engine. Second to second every changes happens from this game loop. So this is a Behavioral design pattern. The game loop runs continuously during gameplay. Each turn of the loop, it processes user input without blocking, updates the game state, and renders the game. It tracks the passage of time to control the rate of gameplay.

The game loop contain five core functions,
* init()
* run()
* processInput()
* update()
* render()

## init()

This function is doing the initializations at the startup.

## run()

This function is run the game loop.

## processInput()

This function processing user inputs without blocking loop.

## update()

This is handle logic inside the game by changing status. So this is handle, object movings, score calculations, game over status change, etc.

## render()

This the visual content part. So this convert the game status to visual content.

## Diagram

![Untitled presentation](https://github.com/naradarathna/snake_game_cpp/assets/118175795/20698c92-e955-465e-9b4a-5622de23e764)


