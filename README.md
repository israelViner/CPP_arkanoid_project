# Brick Breaker Game

Welcome to the Brick Breaker Game! This project implements the classic game of Brick Breaker, with various extensions, using object-oriented principles and following SOLID coding principles. The game challenges you to destroy all bricks on the screen using a ball controlled by the player using a paddle. You earn points for every brick you destroy, based on its type and color.
The game features 6 levels, with each level featuring different visuals, background music, and brick layouts. 
Watch out for the ball falling off the bottom of the screen, as doing so results in the loss of one life. You start with three lives, and you can earn additional lives throughout the game.

### special bricks
The game includes several types of special bricks, which are easily recognizable by their appearance:
- **Gold brick:** does not explode upon first contact with the ball, but only after three collisions.
- **Explosive brick:** destroys all bricks within a 2-brick radius upon impact.
- **Life-giving brick:** awards an extra life upon destruction.
- **Slow brick:** slows down the ball's movement by half for 20 seconds upon destruction.
- **Expanding brick:** doubles the length of the game bar until the end of the stage or the next disqualification.
- **Concrete brick:** completely resistant to collisions.

### How to Play
When you open the game, a splash screen with the options to **Play** or **Quit** will appear. Clicking on "Play" will start the game.
Upon completing the game, either by winning or losing, a summary screen will display the top 10 scores in the game's history. If the player's score qualifies, they will be prompted to enter their name and add their score to the list.

### Game Controls
- Use the **left** and **right** arrow keys to move the paddle.
- Press the **up** arrow to release the ball at the beginning of each level.
- Press the **p** key to pause the game.
- Press the **q** key to mute/unmute the sound.
- Press the **escape** key to quit the game.

## Project Structure
The game structure is divided into several areas:

- **Main:** This class manages the transitions between game levels.

- **Game Flow:** This class controls the game flow, including the main loop that manages each level, pausing the game for important messages, and displaying the game on the screen.

- **Player:** This class manages everything related to the player, and inherits from three different classes:

   - *Score:* Manages the player's score, including controlling the score differences for each brick that is destroyed.

   - *Lives Player:* Manages the player's lives, including adding or subtracting lives when necessary.

   - *Paddle:* This class manages the game paddle, which is controlled by the player. It includes displaying the paddle, controlling its size, position, and movement.

- **Ball:** This class controls the game ball, including its appearance, size, and position.

- **Ball Direct:** This class manages the ball movement, controlling its direction, speed (including slowing it down if necessary), and changing direction when needed.

- **Brick:**
This superclass controls the basic principles of the game bricks, including their appearance, size, and position. It inherits from Lives Brick, and all the other classes that are dedicated to each individual brick (which are found in the brick classes file).

- **Bricks:**
This class manages the group of bricks for each level, from producing the group of bricks based on the unique structure of each level, to destroying them when there is a collision, according to the game conditions.

- **Collisions:** This file manages collisions between the ball and the bricks, as well as between the ball and the game paddle.

- **Opening screen:** This file contains the initial screen that users see when they open the application.

- **Top high score:** This file controls the game's end screen, which displays the ten highest scores previously achieved in the game.

- **Gifts:** This file contains all the images of gifts that users can choose from in the application.

- **Explosion:** This file manages the results of destroying a brick that should cause an explosion, including the radius closest to it.

- The **Event tools** and **Graphic tools** files contain several helper functions, as their names suggest.

- **Settings folder:** This folder includes several essential classes for managing the game, including different settings that are used by game components. These classes are designed to produce a single object used throughout the game (e.g. singleton).

   - *Texture settings:* This class manages all game textures, and all game objects load their textures from this class.

   - *Font settings:* This class manages the fonts used for various text notifications during the game.

   - *Audio:* This class manages all background music and sound effects during the game.

   - *Structure bricks settings:* This file manages the structure of bricks for the various game stages, including writing the structures to data files.

#### Notes:
 - **Back door**: Pressing the 'tab' key during a stage will move the game to the next stage.

- Running the game requires the installation of the SFML library. Please note that if you don't have the brick structure files, you can activate the call to the Structure bricks settings class in the main file, and the computer will write the information to new files (assuming that the level_structures folder exists).

5/03/23

