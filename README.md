# Project Liane (Working Title)  

Third person shooter developed with Unreal Engine 4 in C++ and blueprints

This build features enemy guards, written in c++, that will run to cover if it is low on health or ammo, while attacking, and will search for the nearst health or ammo pack present in its path of retreat. The guards will also be alerted in its patrol route, by sounds caused by the player like gunshots.   

The drone a.i., written in Unreal blueprints, patrols along a set route of waypoints and contains logic of alerting nearby allies of the player's location, within its radius, if a player overlaps with the drone's spotlight.

Logic for enemies to shoot enviroment hazards (i.e. explosive barrels) that are closest to the player within their line of sight , written in blueprints, is a work in progress.
