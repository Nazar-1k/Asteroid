# Asteroid
The mini game is written the library (SDL2)
![image](https://user-images.githubusercontent.com/82716260/224651621-61c52f96-1683-4293-bae6-7a9ba3790397.png)

# About project
The game is set in outer space, where the player controls a small spaceship that must navigate through an asteroid field while avoiding collisions with the various obstacles. The game is played on a single screen, with the player's ship located in the center and the asteroids coming at them from all sides.

The player can rotate their ship in any direction and fire lasers to destroy the asteroids. The asteroids break into smaller pieces when hit, making them even more challenging to avoid. 

The game features simple but addictive gameplay, with the player's objective being to destroy as many asteroids as possible without running out of lives.

# Menu
In  menu, there are two buttons in the middle of the screen - one to start the game and the other to exit. Additionally, in the bottom left corner, we have three buttons:

The first button (Leaderboard) displays the 5 latest records with names on the screen.
![image](https://user-images.githubusercontent.com/82716260/224655950-348ca134-10a7-4ada-ba26-ec47f3642726.png)

The second button (Settings menu) is for settings, where you can set your name or nickname, and if you make it to the top 5, you will be added to the table, which you can access in the Leaderboard menu.You can also toggle the shooting flag (using either the mouse or the spacebar) or turn off the sounds and music.
![image](https://user-images.githubusercontent.com/82716260/224656090-cbd35bfa-4ab3-47a8-baed-c1c367832e74.png)

The third button opens my GitHub repository and refers to the code and description of the game.

All displayed buttons change their transparency and you will be sure that you have clicked on this button

# Gameplay

![image](https://user-images.githubusercontent.com/82716260/224657651-07c07b6a-a2a3-4b83-9851-e4716d616716.png)

The game starts with the player's ship appearing in the middle of the screen and the game being paused until the player moves or shoots.
In the settings menu, the player can choose to shoot either by left-clicking the mouse or pressing the spacebar.
If the player chooses the spacebar as the button for shooting, the bullet will move in the direction of the ship's rotation angle.
If the player chooses the left mouse click, the bullet will fly in the direction of the cursor, which is depicted as a crosshair.
At the top of the game, we can see how many lives we have left, the number of points and the pause menu.


While the ship is moving, there is an animation of fire from its engine.
Also during the destruction of asteroids there is an animation of their destruction
![image](https://user-images.githubusercontent.com/82716260/224660828-7af61e35-2df0-4fb3-8cb9-94271f2522a3.png)

Destroying a boat also triggers a boat explosion animation and destroys a life and restarts the game
![image](https://user-images.githubusercontent.com/82716260/224661254-e7e13287-08b7-4bd2-8a38-871adce1b19c.png)

# Force
We have 4 powers that can fall out of i Asteroids randomly.

1. Auto - automatic fire that aims the bullet at the nearest asteroid.
![image](https://user-images.githubusercontent.com/82716260/224661949-c13ab3c1-01b8-49cd-ad4d-cb0bc4b3dfcb.png)
Work example:
![image](https://user-images.githubusercontent.com/82716260/224662849-3b04246a-a817-49dd-91b0-960d3291fa03.png)

2. Shild - creates a shield around the player.
![image](https://user-images.githubusercontent.com/82716260/224662125-6609cfc0-d255-40f7-96eb-f56a4c1db919.png)
Work example:
![image](https://user-images.githubusercontent.com/82716260/224663370-c0dd7f93-ecbf-44b3-a4cb-a5f96a56ca8c.png)

3. Helper shot - guides the bullet in the direction of the shot
![image](https://user-images.githubusercontent.com/82716260/224662380-afeb02e1-2ab9-445e-9dc7-43f8e4c3e22f.png)
Work example:
![image](https://user-images.githubusercontent.com/82716260/224664747-8d5a4644-6a21-4d87-b21f-6d97773b01cb.png)

4. Score - adds 100 points.
![image](https://user-images.githubusercontent.com/82716260/224662252-30c50744-c710-497c-bb6f-d50506474734.png)

During the action of the force from below, the current force is shown at the bottom
# Stop menu and Game over

![image](https://user-images.githubusercontent.com/82716260/224671409-b936bdf3-1b70-41c5-8241-27ce65d34f2b.png)
![image](https://user-images.githubusercontent.com/82716260/224671498-25e1a4a7-6732-460c-8df5-f6661f532061.png)

# Enjoy yourself
