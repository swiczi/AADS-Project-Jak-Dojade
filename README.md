# Algorithms-And-Data-Structures
</br>
🌱 University project implemented in C++ for the Algorithms and Data Structures course. The objective of the project is to write the program capable of finding the shortest path between two cities.
</br> --------------------------------------------------------------------------------------------------------------------- </br>

## Project Name: Jak-Dojade
A rectangular map divided into squares is given. Each field on the map can be empty, be part of a road (passable in both directions), or be a city, (passable like a road). The name of each city is given on the map, and each letter occupies one field (the field with the letter is impassable). Moving through one field takes one minute. We can only move between fields adjacent by sides. Additionally, selected cities are connected by one-way air connections. The sign of a city will be adjacent (by side or corner) to the city with the first or last letter of the name.
The name will be unambiguously assigned to the city. There will be no near number or letter before or after the name of the city (if there is such a field).
</br>
🌱 Implementation notes:
Using standard string class and other standard library containers is prohibited.

</br> --------------------------------------------------------------------------------------------------------------------- </br>

### Input Information:
The first line will contain the dimensions of the map: width w and height h. The next h lines (each containing w characters) will describe the map. Each character in the description is a dot (.) representing an empty field, a cross (#) representing a road, an asterisk (*) representing a city, or a letter or number that is part of the city name.
The next line will contain a single integer k - the number of flight connections. The next k lines will describe the connections in the format source destination time, where source is the name of the starting city, destination is the name of the destination city, and time is the flight time in minutes. The next line will contain a single integer q - the number of queries. Each query will appear on a separate line and will have the format source destination type. This is a query for the shortest travel time from the source city to the destination city. If the type is zero, the query is only for the time. If the type is one, the route should also be provided - the path must be printed to the screen.

</br> --------------------------------------------------------------------------------------------------------------------- </br>

### Output Information:
For each query, output one line. At the beginning of the line should be the number representing the shortest travel time between the cities. If the query has a type of one, all intermediate cities (excluding the starting and ending cities) should also be listed in the order they were visited, separated by spaces.

</br> --------------------------------------------------------------------------------------------------------------------- </br>

🌱 Example files are attached as: example_in.in and example_out.out

## Summary:

Project requirements were not only related to "give correct answers" but also to develop an efficient program capable of handling a lot of data within specified time intervals.
