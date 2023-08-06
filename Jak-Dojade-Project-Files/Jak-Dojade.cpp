#include <iostream>
#include "String.h"
#include "SingleLinkedList.h"
#include "Queue.h"
#include "HashMap.h"
#include "PriorityQueue.h"

#define PRINT_PATH 1 //type of the user's querie
#define CITY_SIGN '*' //sign that represents the city
#define ROAD_SIGN '#' //sign that represents a path segment
#define EMPTY_SIGN '.' //sign that represents empty field on a map
#define NEIGHBOURHOOD_FIELDS_NUMBER 3
#define NEAR_FIELDS_NUMBER 4
#define END_OF_WORD '\0'
#define ENTER '\n'
#define YES 'Y'
#define NO 'N'

using namespace std;

struct mapInfo {
    int width = 0;
    int height = 0;
};

struct shortestPaths {
    int* distances = nullptr;
    String* previousVertex = nullptr;
};

//functions reading user's input
char** readMap(mapInfo* mapSize, HashMap* cityNames);
void readFlights(SingleLinkedList* adjencyList, HashMap* cityNames);
void readQueries(SingleLinkedList* adjencyList, HashMap* cityNames, shortestPaths* shortestDistances);

//functions to analyze connections between cities - the paths
void analyseMap(char** map, mapInfo mapSize, HashMap* cityNames);
void analysePathsForCities(char** map, mapInfo mapSize, SingleLinkedList* adjencyList, HashMap* cityNames, int numberOfCityNames);
int lookForPossibleRoad(char** map, int height, int width, mapInfo mapSize);
void travelEveryPath(char** map, int startI, int startJ, mapInfo mapSize, char* visitedCities, char** roadVisited,
    SingleLinkedList* adjencyList, int cityNumber, String cityName, HashMap* cityNames);

//functions to search for full city names
String* lookForCityName(char** map, int heightI, int widthJ, mapInfo mapSize);
String* readCityName(char** map, int heightI, int widthJ, mapInfo mapSize);

//functions to search for shortest connection between cities
void calculateShortestPaths(int cityPosition, int toCity, int type, shortestPaths* shortestDistances, SingleLinkedList* adjencyList,
    HashMap* cityNames);
void buildShortestPath(shortestPaths* shortestDistances, int cityPosition, int toCityPosition, int querieType, HashMap* cityNames);

bool checkPoint(mapInfo mapSize, int height, int width);
void checkNearPoints(mapInfo mapSize, int x, int y, char** map, char** roadVisited, Queue* roadQueue, int currentRoadLenght);
bool isCityNameComponent(char sign);
void reflectCharArray(char* array, int lenght);
void addSizeToBuffer(char* buffer, int* size);

//direction from which we should start reading the word
enum cityDirection { LEFT, RIGHT, NO_DIRECTION };

int main()
{
    mapInfo mapSize;
    SingleLinkedList* adjencyList;
    HashMap cityNames;

    //reading map to buffer
    char** map = readMap(&mapSize, &cityNames);

    //creating list for information about connections between cities
    int numberOfCityNames = cityNames.getSize();
    adjencyList = new SingleLinkedList[numberOfCityNames];

    //transform information from map to an adjency list
    analysePathsForCities(map, mapSize, adjencyList, &cityNames, numberOfCityNames);
    readFlights(adjencyList, &cityNames);

    //array to keep informations about shortest paths
    shortestPaths* shortestDistances = new shortestPaths[numberOfCityNames];
    readQueries(adjencyList, &cityNames, shortestDistances);

    delete[] adjencyList;
    delete[] shortestDistances;
    system("pause");
    return 0;
}

//reading map and analysing its content -> transforming it into a graph
char** readMap(mapInfo* mapSize, HashMap* cityNames) {

    cout << "Enter Map Width: ";
    cin >> mapSize->width;
    cout << "Enter Map Height: ";
    cin >> mapSize->height;
    cout << endl;

    char** charMap = new char* [mapSize->height];
    for (int i = 0; i < mapSize->height; i++) {
        charMap[i] = new char[mapSize->width];
    }

    //reading '\n' - enter sign
    getchar();

    for (int i = 0; i < mapSize->height; i++) {

        for (int j = 0; j < mapSize->width; j++) {
            charMap[i][j] = getchar();

        }
        getchar();
    }

    analyseMap(charMap, *mapSize, cityNames);

    return charMap;
}

//reading flights from the user, adding them to adjency list
void readFlights(SingleLinkedList* adjencyList, HashMap* cityNames) {
    int numberOfFlights, time;
    cin >> numberOfFlights;

    String cityName;
    String destinationName;
    for (int i = 0; i < numberOfFlights; i++) {
        cin >> cityName;

        cin >> destinationName;

        cin >> time;

        int cityNumber = cityNames->getPosition(cityName);
        int destinationNameNumber = cityNames->getPosition(destinationName);
        adjencyList[cityNumber].addLast(destinationName, time, destinationNameNumber);
    }
}

//reading queries from the user
void readQueries(SingleLinkedList* adjencyList, HashMap* cityNames, shortestPaths* shortestDistances) {
    int numberOfQueries, querieType;
    cin >> numberOfQueries;
    String fromCity, toCity;

    while (numberOfQueries--) {
        cin >> fromCity;
        cin >> toCity;
        cin >> querieType;

        int cityPosition = cityNames->getPosition(fromCity);
        int toCityPosition = cityNames->getPosition(toCity);

        calculateShortestPaths(cityPosition, toCityPosition, querieType, shortestDistances, adjencyList, cityNames);

    }

}

//converting information from map to adjency list
void analyseMap(char** map, mapInfo mapSize, HashMap* cityNames) {

    //look for cities -> the vertices
    Point point;
    for (int i = 0; i < mapSize.height; i++) {
        for (int j = 0; j < mapSize.width; j++) {
            if (map[i][j] == CITY_SIGN) {
                point = { i, j };
                cityNames->addWord(*lookForCityName(map, i, j, mapSize), point);
            }
        }
    }

}

//for each city generate possible connections to other cities and write it to array
void analysePathsForCities(char** map, mapInfo mapSize, SingleLinkedList* adjencyList, HashMap* cityNames, int numberOfCityNames) {

    char* visitedCities = new char[numberOfCityNames];
    for (int i = 0; i < numberOfCityNames; i++) {
        visitedCities[i] = NO;
    }

    char** roadVisited = new char* [mapSize.height];
    for (int i = 0; i < mapSize.height; i++) {
        roadVisited[i] = new char[mapSize.width];
    }

    int cityNumber = 0;
    City city;

    //go throught each city
    while (cityNumber < numberOfCityNames) {

        city = cityNames->searchForStructure(cityNumber);
        visitedCities[cityNumber] = YES;

        if (lookForPossibleRoad(map, city.cityPoint.x, city.cityPoint.y, mapSize)) {
            travelEveryPath(map, city.cityPoint.x, city.cityPoint.y, mapSize, visitedCities, roadVisited, adjencyList, cityNumber, city.cityName, cityNames);
        }
        cityNumber++;
    }

    for (int i = 0; i < mapSize.height; i++) {
        delete[] roadVisited[i];
    }
    delete[] roadVisited;

    delete[] visitedCities;
}

//looking for possible road around given point
int lookForPossibleRoad(char** map, int height, int width, mapInfo mapSize) {

    if (checkPoint(mapSize, height - 1, width)) {
        if (map[height - 1][width] == ROAD_SIGN || map[height - 1][width] == CITY_SIGN) {
            return true;
        }
    }
    if (checkPoint(mapSize, height + 1, width)) {
        if (map[height + 1][width] == ROAD_SIGN || map[height + 1][width] == CITY_SIGN) {
            return true;
        }

    }

    if (checkPoint(mapSize, height, width - 1)) {
        if (map[height][width - 1] == ROAD_SIGN || map[height][width - 1] == CITY_SIGN) {
            return true;
        }
    }

    if (checkPoint(mapSize, height, width + 1)) {
        if (map[height][width + 1] == ROAD_SIGN || map[height][width + 1] == CITY_SIGN) {
            return true;
        }
    }

    return false;
}

//travels every segment of road using bfs algorithm, starting form one of the cities
void travelEveryPath(char** map, int startI, int startJ, mapInfo mapSize, char* visitedCities, char** roadVisited,
    SingleLinkedList* adjencyList, int cityNumber, String cityName, HashMap* cityNames) {

    //queue for road segments
    Queue roadQueue;
    Point* point;
    Point* lastPoint = new Point{ 0,0,NO_VALUE };
    bool firstMove = true;
    String* destinationName = nullptr;
    int currentRoadLenght = 0;

    for (int i = 0; i < mapSize.height; i++) {
        for (int j = 0; j < mapSize.width; j++) {
            roadVisited[i][j] = NO;
        }
    }

    //putting the first vertex
    roadQueue.put(startI, startJ, 0);
    roadVisited[startI][startJ] = YES;

    //while there is some road path still in the queue
    while (roadQueue.getSize()) {

        point = roadQueue.pop();

        if ((map[point->x][point->y]) == ROAD_SIGN || firstMove) {

            //checking if we started a new road segment
            if (lastPoint->distance != point->distance) {
                currentRoadLenght = point->distance + 1;
            }

            //checking all fields around the point
            checkNearPoints(mapSize, point->x - 1, point->y, map, roadVisited, &roadQueue, currentRoadLenght);
            checkNearPoints(mapSize, point->x + 1, point->y, map, roadVisited, &roadQueue, currentRoadLenght);
            checkNearPoints(mapSize, point->x, point->y - 1, map, roadVisited, &roadQueue, currentRoadLenght);
            checkNearPoints(mapSize, point->x, point->y + 1, map, roadVisited, &roadQueue, currentRoadLenght);

            lastPoint = point;
            firstMove = false;

        }
        else if ((map[point->x][point->y]) == CITY_SIGN) {

            destinationName = lookForCityName(map, point->x, point->y, mapSize);
            int destinationPositionInArray = cityNames->getPosition(*destinationName);
            int addedLenght = adjencyList[cityNumber].lookForValue(*destinationName);
            roadVisited[point->x][point->y] = YES;

            //adding edge for the first time
            if (addedLenght == NO_VALUE && visitedCities[destinationPositionInArray] == NO) {
                adjencyList[cityNumber].addLast(*destinationName, point->distance, destinationPositionInArray);
                adjencyList[destinationPositionInArray].addLast(cityName, point->distance, cityNumber);
            }
            else if (addedLenght > point->distance) {
                //we need to only change length of already existing edge
                adjencyList[cityNumber].changeValue(*destinationName, point->distance);
                adjencyList[destinationPositionInArray].changeValue(cityName, point->distance);
            }

        }

    }

    delete lastPoint;

}

//getting name of a city around given position -> the '*' sign
String* lookForCityName(char** map, int heightI, int widthJ, mapInfo mapSize) {

    //starting from the left right corner
    int pointHeight = heightI - 1, pointWidth = widthJ - 1;
    String* cityName = nullptr;
    bool cityFound = false;

    for (int i = 0; i < NEIGHBOURHOOD_FIELDS_NUMBER; i++) {
        if (pointHeight >= 0 && pointHeight < mapSize.height) {
            pointWidth = widthJ - 1;

            for (int j = 0; j < NEIGHBOURHOOD_FIELDS_NUMBER; j++) {

                if (pointWidth >= 0 && pointWidth < mapSize.width) {

                    if (isCityNameComponent(map[pointHeight][pointWidth])) {

                        //getting first letter index
                        int lastWidth = pointWidth;
                        pointWidth--;
                        while (pointWidth >= 0 && isCityNameComponent(map[pointHeight][pointWidth])) {
                            lastWidth = pointWidth;
                            pointWidth--;

                        }
                        cityName = readCityName(map, pointHeight, lastWidth, mapSize);

                        cityFound = true;
                    }

                    if (cityFound) break;
                }
                pointWidth++;
            }
        }
        pointHeight++;

        if (cityFound) break;
    }

    return cityName;

}

//reading city name from given point
String* readCityName(char** map, int heightI, int widthJ, mapInfo mapSize) {

    int bufferSize = DEFAULT_SIZE, bufferLength = 0, id = widthJ, indexLeft = widthJ - 1, indexRight = widthJ + 1;
    char* nameBuffer = new char[bufferSize];
    cityDirection direction = NO_DIRECTION;

    //adding first letter to buffer
    nameBuffer[bufferLength] = map[heightI][id];
    bufferLength++;

    if (indexRight > mapSize.width && indexLeft >= 0) {
        if (isCityNameComponent(map[heightI][indexLeft]) && isCityNameComponent(map[heightI][indexRight])) {
            delete[] nameBuffer;
            return nullptr;
        }
    }

    //deciding on which side is the rest of a word
    if (indexLeft >= 0 && isCityNameComponent(map[heightI][indexLeft])) {
        direction = LEFT;
        id = indexLeft;
    }
    else if (indexRight < mapSize.width && isCityNameComponent(map[heightI][indexRight])) {
        direction = RIGHT;
        id = indexRight;
    }
    else if (indexLeft < 0) {
        direction = RIGHT;
        id = indexRight;
    }
    else if (indexRight < mapSize.width) {
        direction = LEFT;
        id = indexLeft;
    }

    //reading city name letter by letter
    while (isCityNameComponent(map[heightI][id])) {
        if (id >= 0 && id < mapSize.width) {
            nameBuffer[bufferLength] = map[heightI][id];
            bufferLength++;
            if (direction == LEFT) id--;
            else id++;
        }
        else break;

        while (bufferLength >= bufferSize) {
            addSizeToBuffer(nameBuffer, &bufferSize);
        }

    }
    nameBuffer[bufferLength] = END_OF_WORD;

    if (direction == LEFT) {
        reflectCharArray(nameBuffer, bufferLength);
    }

    String* cityName = new String(nameBuffer);
    delete[] nameBuffer;

    return cityName;
}

//calculate shortest paths using dijkstra algorithm to all cities from given city
void calculateShortestPaths(int cityPosition, int toCity, int type, shortestPaths* shortestDistances, SingleLinkedList* adjencyList,
    HashMap* cityNames) {

    int numberOfCityNames = cityNames->getSize();
    char* visitedCities = new char[numberOfCityNames];

    //check if we have already calculated distances for this vertex(city)
    if (shortestDistances[cityPosition].distances != nullptr) {
        buildShortestPath(shortestDistances, cityPosition, toCity, type, cityNames);
        delete[] visitedCities;
        return;
    }

    int* citiesDistances = new int[numberOfCityNames];
    String* previousCity = new String[numberOfCityNames];
    int currentVertexValue, currentVertex, oldValue, position;

    PriorityQueue unvisitedCities;
    nearCity newCity, newCityToAdd;
    for (int i = 0; i < numberOfCityNames; i++) {
        citiesDistances[i] = NO_VALUE;
        previousCity[i] = "";
        if (i == cityPosition) {
            citiesDistances[i] = 0;
        }
        visitedCities[i] = NO;
    }

    newCity.distance = 0;
    newCity.nameIndex = cityPosition;
    newCity.name = cityNames->searchForWord(cityPosition);
    unvisitedCities.heapInsert(newCity);

    //caculating shortest distances to every vertex
    while (unvisitedCities.getSize()) {

        //we go to the smallest unvisited vertex from start vertex
        newCity = unvisitedCities.heapGetMax();
        currentVertex = newCity.nameIndex;

        if (visitedCities[currentVertex] == NO) {
            currentVertexValue = newCity.distance;

            //going throught all edges of current vertex
            Node* tmp = adjencyList[currentVertex].getNode();
            while (tmp != nullptr) {

                position = tmp->namePosition;
                if (visitedCities[position] == NO) {
                    oldValue = citiesDistances[position];

                    //if it is the first value or the old value(distance) is greater than the current we found
                    if (oldValue == NO_VALUE || oldValue > tmp->value1 + currentVertexValue) {
                        int value = tmp->value1 + currentVertexValue;
                        if (tmp->value1 == NO_VALUE) value++;
                        citiesDistances[position] = value;

                        previousCity[position] = newCity.name;
                        newCityToAdd.distance = value;
                        newCityToAdd.name = tmp->name;
                        newCityToAdd.nameIndex = position;

                        //adding new city to heap
                        unvisitedCities.heapInsert(newCityToAdd);

                    }

                }
                tmp = tmp->next;
            }

            visitedCities[currentVertex] = YES;

        }

    }

    shortestPaths forCurrentCity = { citiesDistances, previousCity };
    shortestDistances[cityPosition] = forCurrentCity;
    buildShortestPath(shortestDistances, cityPosition, toCity, type, cityNames);

}

//building shortest path to city, calculating its lenght
void buildShortestPath(shortestPaths* shortestDistances, int cityPosition, int toCityPosition, int querieType, HashMap* cityNames) {

    String city;

    int pathLength = 0, position = toCityPosition, pathSize = DEFAULT_SIZE, i = 0;
    String* path = new String[DEFAULT_SIZE];

    pathLength = shortestDistances[cityPosition].distances[toCityPosition];
    cout << "Shortest path: " << endl;
    cout << pathLength << " ";

    //keep city names in path array
    if (cityPosition != toCityPosition) {
        city = shortestDistances[cityPosition].previousVertex[toCityPosition];
        position = cityNames->getPosition(city);
        while (position != cityPosition && querieType == PRINT_PATH) {

            path[i] = city;
            i++;
            if (i == pathSize) {
                int newSize = SIZE_MULTIPLICATION * pathSize;
                String* newBuffer = new String[newSize];
                memcpy(newBuffer, path, pathSize * sizeof(String));
                path = newBuffer;
                pathSize = newSize;
            }
            city = shortestDistances[cityPosition].previousVertex[position];
            position = cityNames->getPosition(city);
        }

    }

    //printing reversed path
    if (querieType == PRINT_PATH) {
        for (int j = i - 1; j >= 0; j--) {
            cout << path[j] << " ";
        }
    }

    cout << endl;

    delete[] path;
}

//checking corectness of a given point
bool checkPoint(mapInfo mapSize, int height, int width) {
    if (height >= 0 && height < mapSize.height && width >= 0 && width < mapSize.width) {
        return true;
    }
    return false;
}

//checking all near points around and adding them to queue
void checkNearPoints(mapInfo mapSize, int x, int y, char** map, char** roadVisited, Queue* roadQueue, int currentRoadLenght) {
    if (checkPoint(mapSize, x, y)) {
        if (roadVisited[x][y] == NO && map[x][y] == ROAD_SIGN || map[x][y] == CITY_SIGN) {
            roadQueue->put(x, y, currentRoadLenght);
            roadVisited[x][y] = YES;
        }
    }
}

//checking whether given char/sign is a part of a city name
bool isCityNameComponent(char sign) {
    if (sign != EMPTY_SIGN && sign != ROAD_SIGN && sign != CITY_SIGN && sign != ENTER) return true;
    return false;
}

//reflicting char array
void reflectCharArray(char* array, int lenght) {
    for (int i = 0; i < lenght / 2; i++) {
        char tmp = array[i];
        array[i] = array[lenght - i - 1];
        array[lenght - i - 1] = tmp;
    }
}

//function to multiply buffer size
void addSizeToBuffer(char* buffer, int* size) {
    int newSize = *size * SIZE_MULTIPLICATION;
    char* newBuffer = new char[newSize];

    //push the content of old buffer to new 1
    for (int i = 0; i < newSize; i++) {
        newBuffer[i] = buffer[i];
    }
    delete[] buffer;
    buffer = newBuffer;
    *size = newSize;

}
