Crazy Taxi
Crazy Taxi is a high speed dodging game in which the player has to dodge the oncoming traffic and is allowed a limited helth to reach the highest score they can score. The player can move the taxi using the left, right, up and down keyboard keys. The player can collect powerups like a sheild that protects the players' health and a speed powerup that speeds up the car's motion.
The game ends when the health of the player reaches zero. After which the player hass the option to start again.

Packages used:
SDL_image
SDL_ttf

Requirements Met:
Memory is correctly managed: Destructors are made where neccessary and SDL Textures and Surface are destroyed where they are no longer needed, or to be reused.
Polymorphism is implemented: gameObject is a parent class that has many child classes such as perks, traffic and player, which all have shared attributes and functions that are overloaded as required.
At least 3 design patterns are implemented: itemFactory is an object pool that has perks and traffic cars that are reused during the game. gameObject is a factory. Game is a singleton.
At least 1 menu with working buttons is implemented: The game has a start menu from which the user can choose to start the game, move to the game instructions or exit the game. The game over menu gives the player an option to restart.
Operator Overloading is used: Not used
File I/O is incorporated: To store and update highscore
