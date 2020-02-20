# Project Liane (Working Title)  

Third person shooter developed with Unreal Engine 4 in C++ and Unreal blueprints

This build features guard NPCs, written in blueprints and C++, that will run to cover if it is low on health or ammo, while attacking, and will search for the nearst health or ammo pack present in its path of retreat. The guards will also be alerted in its patrol route, by sounds caused by the player like gunshots.   

The drone, written in Unreal blueprints, patrols along a set route of waypoints and contains logic of alerting nearby allies of the player's location, within its radius if the player is in the drone's light. 

TODO:Create Logic for guard NPCs to shoot enviroment hazards (i.e. explosive barrels) that are nearest the player and within their line of sight.
