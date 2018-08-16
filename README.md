# Unreal Education
## Ed_04_Battle_Tank
Educational Game Development from Udemy Unreal Course with Ben Tristam - Open World Tank Fight with Simple AI and Terrain Using Unreal 4.

**Features**

* 3rd Person Camera 
* AI
* Aiming system for player and AI
* Start Menu

# Aiming Architecture
* Tank Player Controller AimAt (crosshair) and Tank AI Controller AimAt(Player). Both send to Tank. A tank can be AI or Player.
	* The AI Contoller gets the player location to aim at. 
	* The Player Controller gets the crosshair 2d viewport location (hard coded), then translates that to a 3d position to aim at.
	* The Tank has an aim at function that takes a location from the controllers, then points the turret at that position. 