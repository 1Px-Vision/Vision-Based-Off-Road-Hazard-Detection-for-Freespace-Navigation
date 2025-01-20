# Project: OpenStreetMap Route Planner

Create a route planner that maps a path between two locations using real-world map data from the [OpenStreetMap](https://www.openstreetmap.org/#map=5/23.94/-102.58) project. Once the project is complete, your output should resemble the provided image.

![map_render](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project%3A%20OpenStreetMap%20Route%20Planner/map_render.jpg)


## Using the Route Planner

After compiling and running the program, you will be prompted to enter four coordinates from 0 to 99: start x, start y, end x, and end y. The program then calculates the distance between the specified points and visually renders the route from the starting position to the destination on the map.

To function correctly, the map file (in .osm format) must be named map.osm and placed in the project directory. A sample map is included in the repository, but you can also download your own from the website linked below.

````
Enter start x in range of 0 to 100: 20
start x is 20
Enter start y in range of 0 to 100: 30
start y is 30
Enter end x in range of 0 to 100: 40
end x is 40
Enter end y in range of 0 to 100: 50
end y is 50
Distance: 297.188 meters. 
````
