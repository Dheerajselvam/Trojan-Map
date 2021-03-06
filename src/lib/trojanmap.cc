#include "trojanmap.h"
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<bits/stdc++.h>

#include <algorithm>
#include <fstream>
#include <locale>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <sstream>
#include <string>
#include <utility>
#include <cmath>
#include <iostream>
#include <cctype>
#include <unordered_set>
#include <stack>
#include <chrono>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

//-----------------------------------------------------
// TODO (Students): You do not and should not change the following functions:
//-----------------------------------------------------

/**
 * PrintMenu: Create the menu
 * 
 */
void TrojanMap::PrintMenu() {

  std::string menu =
      "**************************************************************\n"
      "* Select the function you want to execute.                    \n"
      "* 1. Autocomplete                                             \n"
      "* 2. Find the position                                        \n"
      "* 3. CalculateShortestPath                                    \n"
      "* 4. Travelling salesman problem                              \n"
      "* 5. Cycle Detection                                          \n"
      "* 6. Topological Sort                                         \n"
      "* 7. Find K Closest Points                                    \n"
      "* 8. Exit                                                     \n"
      "**************************************************************\n";
  std::cout << menu << std::endl;
  std::string input;
  getline(std::cin, input);
  char number = input[0];
  switch (number)
  {
  case '1':
  {
    menu =
        "**************************************************************\n"
        "* 1. Autocomplete                                             \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input a partial location:";
    std::cout << menu;
    getline(std::cin, input);
    auto start = std::chrono::high_resolution_clock::now();
    auto results = Autocomplete(input);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.size() != 0) {
      for (auto x : results) std::cout << x << std::endl;
    } else {
      std::cout << "No matched locations." << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '2':
  {
    menu =
        "**************************************************************\n"
        "* 2. Find the position                                        \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input a location:";
    std::cout << menu;
    getline(std::cin, input);
    auto start = std::chrono::high_resolution_clock::now();
    auto results = GetPosition(input);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.first != -1) {
      std::cout << "Latitude: " << results.first
                << " Longitude: " << results.second << std::endl;
      PlotPoint(results.first, results.second);
    } else {
      std::cout << "No matched locations." << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '3':
  {
    menu =
        "**************************************************************\n"
        "* 3. CalculateShortestPath                                    \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input the start location:";
    std::cout << menu;
    std::string input1;
    getline(std::cin, input1);
    menu = "Please input the destination:";
    std::cout << menu;
    std::string input2;
    getline(std::cin, input2);
    auto start = std::chrono::high_resolution_clock::now();
    auto results = CalculateShortestPath_Dijkstra(input1, input2);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.size() != 0) {
      for (auto x : results) std::cout << x << std::endl;
      std::cout << "The distance of the path is:" << CalculatePathLength(results) << " miles" << std::endl;
      PlotPath(results);
    } else {
      std::cout << "No route from the start point to the destination."
                << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '4':
  {
    menu =
        "**************************************************************\n"
        "* 4. Traveling salesman problem                              \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "In this task, we will select N random points on the map and you need to find the path to travel these points and back to the start point.";
    std::cout << menu << std::endl << std::endl;
    menu = "Please input the number of the places:";
    std::cout << menu;
    getline(std::cin, input);
    int num = std::stoi(input);
    std::vector<std::string> keys;
    for (auto x : data) {
      keys.push_back(x.first);
    }
    std::vector<std::string> locations;
    srand(time(NULL));
    for (int i = 0; i < num; i++)
      locations.push_back(keys[rand() % keys.size()]);
    PlotPoints(locations);
    std::cout << "Calculating ..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    auto results = TravellingTrojan_2opt(locations);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    CreateAnimation(results.second);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.second.size() != 0) {
      for (auto x : results.second[results.second.size()-1]) std::cout << x << std::endl;
      menu = "**************************************************************\n";
      std::cout << menu;
      std::cout << "The distance of the path is:" << results.first << " miles" << std::endl;
      PlotPath(results.second[results.second.size()-1]);
    } else {
      std::cout << "The size of the path is 0" << std::endl;
    }
    menu = "**************************************************************\n"
           "You could find your animation at src/lib/output.avi.          \n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '5':
  {
    menu =
        "**************************************************************\n"
        "* 5. Cycle Detection                                          \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input the left bound longitude(between -118.299 and -118.264):";
    std::cout << menu;
    getline(std::cin, input);
    std::vector<double> square;
    square.push_back(atof(input.c_str()));

    menu = "Please input the right bound longitude(between -118.299 and -118.264):";
    std::cout << menu;
    getline(std::cin, input);
    square.push_back(atof(input.c_str()));

    menu = "Please input the upper bound latitude(between 34.011 and 34.032):";
    std::cout << menu;
    getline(std::cin, input);
    square.push_back(atof(input.c_str()));

    menu = "Please input the lower bound latitude(between 34.011 and 34.032):";
    std::cout << menu;
    getline(std::cin, input);
    square.push_back(atof(input.c_str()));

    auto start = std::chrono::high_resolution_clock::now();
    auto results = CycleDetection(square);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results == true)
      std::cout << "there exists cycle in the subgraph " << std::endl;
    else
      std::cout << "there exist no cycle in the subgraph " << std::endl;
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '6':
  {
    menu =
        "**************************************************************\n"
        "* 6. Topological Sort                                         \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input the locations filename:";
    std::cout << menu;
    std::string locations_filename;
    getline(std::cin, locations_filename);
    menu = "Please input the dependencies filename:";
    std::cout << menu;
    std::string dependencies_filename;
    getline(std::cin, dependencies_filename);
    
    // Read location names from CSV file
    std::vector<std::string> location_names;
    if (locations_filename == "") 
      // location_names = {"Cardinal Gardens", "Coffee Bean1","CVS"};
      location_names = {"Ralphs", "ChickfilA", "Coffee Bean1","CVS","Cardinal Gardens","Target","Metro 40","USC Parking"};
    else
      location_names = ReadLocationsFromCSVFile(locations_filename);
    
    // Read dependencies from CSV file
    std::vector<std::vector<std::string>> dependencies;
    if (dependencies_filename == "")
      // dependencies = {{"Cardinal Gardens","Coffee Bean1"}, {"Cardinal Gardens","CVS"}, {"Coffee Bean1","CVS"}};
      dependencies = {{"Ralphs","Coffee Bean1"}, {"Ralphs", "ChickfilA"}, {"Ralphs","CVS"}, {"Ralphs","Target"}, {"Ralphs","Metro 40"}, {"Target","Metro 40"}, {"Metro 40","USC Parking"}, {"Ralphs","Cardinal Gardens"}, {"ChickfilA", "Coffee Bean1"}, {"ChickfilA","CVS"}, {"ChickfilA","Cardinal Gardens"}, {"Coffee Bean1","CVS"},{"CVS","Cardinal Gardens"},{"Coffee Bean1","Cardinal Gardens"}};
    else
      dependencies = ReadDependenciesFromCSVFile(dependencies_filename);

    // std::vector<std::string> location_names = {"Cardinal Gardens", "Coffee Bean1","CVS"};
    // std::vector<std::vector<std::string>> dependencies = {{"Coffee Bean1","Cardinal Gardens"}, {"CVS","Cardinal Gardens"}, {"CVS","Coffee Bean1"}};
    auto start = std::chrono::high_resolution_clock::now();
    auto result = DeliveringTrojan(location_names, dependencies);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************";
    std::cout << menu << std::endl;
    std::cout << "Topological Sorting Results:" << std::endl;
    for (auto &x : result) std::cout << x << std::endl;
    std::vector<std::string> node_ids;
    for (auto &x: result) {
      std::string id = GetID(x);
      node_ids.push_back(id);
    }
    PlotPointsOrder(node_ids);
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
    case '7':
  {
    menu =
        "**************************************************************\n"
        "* 7. Find K Closest Points                                    \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    
    menu = "Please input the locations:";
    std::cout << menu;
    std::string origin;
    getline(std::cin, origin);
    menu = "Please input k:";
    std::cout << menu;
    getline(std::cin, input);
    int k = std::stoi(input);
    
    auto start = std::chrono::high_resolution_clock::now();
    auto result = FindKClosestPoints(origin, k);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************";
    std::cout << menu << std::endl;
    std::cout << "Find K Closest Points Results:" << std::endl;
    int cnt = 1;
    for (auto x : result) { 
      std::cout << cnt << " " << data[x].name << std::endl;
      cnt++;
    }
    PlotPointsLabel(result, GetID(origin));
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '8':
    break;
  default:
  {
    std::cout << "Please select 1 - 8." << std::endl;
    PrintMenu();
    break;
  }
  }
}


/**
 * CreateGraphFromCSVFile: Read the map data from the csv file
 * 
 */
void TrojanMap::CreateGraphFromCSVFile() {
  std::fstream fin;
  fin.open("src/lib/map.csv", std::ios::in);
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);

    Node n;
    int count = 0;
    while (getline(s, word, ',')) {
      word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
      word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '['), word.end());
      word.erase(std::remove(word.begin(), word.end(), ']'), word.end());
      if (count == 0)
        n.id = word;
      else if (count == 1)
        n.lat = stod(word);
      else if (count == 2)
        n.lon = stod(word);
      else if (count == 3)
        n.name = word;
      else {
        word.erase(std::remove(word.begin(), word.end(), ' '), word.end());
        n.neighbors.push_back(word);
      }
      count++;
    }
    data[n.id] = n;
  }
  fin.close();
}

/**
 * PlotPoint: Given a location id, plot the point on the map
 * 
 * @param  {std::string} id : location id
 */
void TrojanMap::PlotPoint(std::string id) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto result = GetPlotLocation(data[id].lat, data[id].lon);
  cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}
/**
 * PlotPoint: Given a lat and a lon, plot the point on the map
 * 
 * @param  {double} lat : latitude
 * @param  {double} lon : longitude
 */
void TrojanMap::PlotPoint(double lat, double lon) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto result = GetPlotLocation(lat, lon);
  cv::circle(img, cv::Point(int(result.first), int(result.second)), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  cv::startWindowThread();
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPath: Given a vector of location ids draws the path (connects the points)
 * 
 * @param  {std::vector<std::string>} location_ids : path
 */
void TrojanMap::PlotPath(std::vector<std::string> &location_ids) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
  cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  for (auto i = 1; i < location_ids.size(); i++) {
    auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
    auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
    cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    cv::line(img, cv::Point(int(start.first), int(start.second)),
             cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
             LINE_WIDTH);
  }
  cv::startWindowThread();
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPoints: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points
 */
void TrojanMap::PlotPoints(std::vector<std::string> &location_ids) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPoints: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points inside square
 * @param  {std::vector<double>} square : boundary
 */
void TrojanMap::PlotPointsandEdges(std::vector<std::string> &location_ids, std::vector<double> &square) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto upperleft = GetPlotLocation(square[2], square[0]);
  auto lowerright = GetPlotLocation(square[3], square[1]);
  cv::Point pt1(int(upperleft.first), int(upperleft.second));
  cv::Point pt2(int(lowerright.first), int(lowerright.second));
  cv::rectangle(img, pt2, pt1, cv::Scalar(0, 0, 255));
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    for(auto y : data[x].neighbors) {
      auto start = GetPlotLocation(data[x].lat, data[x].lon);
      auto end = GetPlotLocation(data[y].lat, data[y].lon);
      cv::line(img, cv::Point(int(start.first), int(start.second)),
              cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
              LINE_WIDTH);
    }
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPointsOrder: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points
 */
void TrojanMap::PlotPointsOrder(std::vector<std::string> &location_ids) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::putText(img, data[x].name, cv::Point(result.first, result.second), cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(255, 0, 0), 2);
  }
  // Plot dots and lines
  auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
  cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  for (auto i = 1; i < location_ids.size(); i++) {
    auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
    auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
    cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    cv::arrowedLine(img, cv::Point(int(start.first), int(start.second)),
             cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
             LINE_WIDTH);
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPoints: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points
 */
void TrojanMap::PlotPointsLabel(std::vector<std::string> &location_ids, std::string origin) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  int cnt = 1;
  auto result = GetPlotLocation(data[origin].lat, data[origin].lon);
  cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 255, 0), cv::FILLED);
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    cv::putText(img, std::to_string(cnt), cv::Point(result.first, result.second), cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(255, 0, 0), 2);
    cnt++;
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * CreateAnimation: Create the videos of the progress to get the path
 * 
 * @param  {std::vector<std::vector<std::string>>} path_progress : the progress to get the path
 */
void TrojanMap::CreateAnimation(std::vector<std::vector<std::string>> path_progress){
  cv::VideoWriter video("src/lib/output.avi", cv::VideoWriter::fourcc('M','J','P','G'), 10, cv::Size(1248,992));
  for(auto location_ids: path_progress) {
    std::string image_path = cv::samples::findFile("src/lib/input.jpg");
    cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
    auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
    cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE,
              cv::Scalar(0, 0, 255), cv::FILLED);
    for (auto i = 1; i < location_ids.size(); i++) {
      auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
      auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
      cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE,
                cv::Scalar(0, 0, 255), cv::FILLED);
      cv::line(img, cv::Point(int(start.first), int(start.second)),
              cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
              LINE_WIDTH);
    }
    video.write(img);
    cv::imshow("TrojanMap", img);
    cv::waitKey(1);
  }
	video.release();
}
/**
 * GetPlotLocation: Transform the location to the position on the map
 * 
 * @param  {double} lat         : latitude 
 * @param  {double} lon         : longitude
 * @return {std::pair<double, double>}  : position on the map
 */
std::pair<double, double> TrojanMap::GetPlotLocation(double lat, double lon) {
  std::pair<double, double> bottomLeft(34.01001, -118.30000);
  std::pair<double, double> upperRight(34.03302, -118.26502);
  double h = upperRight.first - bottomLeft.first;
  double w = upperRight.second - bottomLeft.second;
  std::pair<double, double> result((lon - bottomLeft.second) / w * 1248,
                                   (1 - (lat - bottomLeft.first) / h) * 992);
  return result;
}

//-----------------------------------------------------
// TODO: Student should implement the following:
//-----------------------------------------------------
/**
 * GetLat: Get the latitude of a Node given its id.
 * 
 * @param  {std::string} id : location id
 * @return {double}         : latitude
 */
double TrojanMap::GetLat(std::string id) {
  return data[id].lat;
}


/**
 * GetLon: Get the longitude of a Node given its id. 
 * 
 * @param  {std::string} id : location id
 * @return {double}         : longitude
 */
double TrojanMap::GetLon(std::string id) { 
    return data[id].lon;
}

/**
 * GetName: Get the name of a Node given its id.
 * 
 * @param  {std::string} id : location id
 * @return {std::string}    : name
 */
std::string TrojanMap::GetName(std::string id) { 
  
    return (data[id].name);
}

/**
 * GetNeighborIDs: Get the neighbor ids of a Node.
 * 
 * @param  {std::string} id            : location id
 * @return {std::vector<std::string>}  : neighbor ids
 */
std::vector<std::string> TrojanMap::GetNeighborIDs(std::string id) {
    return data[id].neighbors;
}

/**
 * CalculateDistance: Get the distance between 2 nodes. 
 * 
 * @param  {std::string} a  : a_id
 * @param  {std::string} b  : b_id
 * @return {double}  : distance in mile
 */
double TrojanMap::CalculateDistance(const std::string &a_id, const std::string &b_id) {
  // Do not change this function
  // TODO: Use Haversine Formula:
  // dlon = lon2 - lon1;
  // dlat = lat2 - lat1;
  // a = (sin(dlat / 2)) ^ 2 + cos(lat1) * cos(lat2) * (sin(dlon / 2)) ^ 2;
  // c = 2 * arcsin(min(1, sqrt(a)));
  // distances = 3961 * c;

  // where 3961 is the approximate radius of the earth at the latitude of
  // Washington, D.C., in miles
  Node a = data[a_id];
  Node b = data[b_id];
  double dlon = (b.lon - a.lon) * M_PI / 180.0;
  double dlat = (b.lat - a.lat) * M_PI / 180.0;
  double p = pow(sin(dlat / 2),2.0) + cos(a.lat * M_PI / 180.0) * cos(b.lat * M_PI / 180.0) * pow(sin(dlon / 2),2.0);
  double c = 2 * asin(std::min(1.0,sqrt(p)));
  return c * 3961;
}

/**
 * CalculatePathLength: Calculates the total path length for the locations inside the vector.
 * 
 * @param  {std::vector<std::string>} path : path
 * @return {double}                        : path length
 */
double TrojanMap::CalculatePathLength(const std::vector<std::string> &path) {
  // Do not change this function
  double sum = 0;
  for (int i = 0;i < path.size()-1; i++) {
    sum += CalculateDistance(path[i], path[i+1]);
  }
  return sum;
}

/**
 * Autocomplete: Given a parital name return all the possible locations with
 * partial name as the prefix.
 *
 * @param  {std::string} name          : partial name
 * @return {std::vector<std::string>}  : a vector of full names
 */
std::vector<std::string> TrojanMap::Autocomplete(std::string name){
  
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);
    name[0] = toupper(name[0]);
    std::vector<std::string> results;
    std::unordered_map<std::string, Node>::iterator it;
    for (it = data.begin(); it != data.end(); it++){
      if(name.size() > ((data[it->first].name).size())){continue;}
      else if (name == (data[it->first].name).substr(0,name.size())){
        results.push_back((data[it->first].name));
      }
    }
  return results;
}

/**
 * GetPosition: Given a location name, return the position.
 *
 * @param  {std::string} name          : location name
 * @return {std::pair<double,double>}  : (lat, lon)
 */
std::pair<double, double> TrojanMap::GetPosition(std::string name) {
  std::string id = GetID(name);
  std::pair<double, double> results;
  if (id == "-1"){
    results = {-1, -1};
  }
  else{
  results.first = data[id].lat;
  results.second = data[id].lon;
  }
  return results;
}

/**
 * GetID: Given a location name, return the id. 
 * If the node does not exist, return an empty string. 
 *
 * @param  {std::string} name          : location name
 * @return {int}  : id
 */
std::string TrojanMap::GetID(std::string name) {

  std::unordered_map<std::string, Node>::iterator it;
    for (it = data.begin(); it != data.end(); it++){

      if (name == (data[it->first].name)){
        return (it->first);
      }

    }
    return "-1";

}

/**
 * CalculateShortestPath_Dijkstra: Given 2 locations, return the shortest path which is a
 * list of id.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra(std::string location1_name, std::string location2_name) {
  std::vector<std::string> path;
  std::string start = GetID(location1_name);
  std::string dest = GetID(location2_name);
  if (start == "-1" || dest == "-1"){ 
    path = {"-1"}; 
  }
  typedef std::pair<float, std::string> pa;
  std::priority_queue <pa, std::vector<pa> , std::greater<pa> > heap;
  heap.push(make_pair(0,start));
  std::map<std::string,float> cur_map;
  std::map<std::string, std::string> pred_map;
  std::unordered_map<std::string, Node>::iterator it;
  for (it = data.begin(); it != data.end(); it++){
    if (data[it->first].id == start){
      cur_map.insert(std::pair<std::string,float> (start,0));}
    else{
      cur_map.insert(std::pair<std::string,float> (data[it->first].id,INT_MAX));}
  }

  while(!heap.empty()){
    float c_d = heap.top().first;
    std::string prev = heap.top().second;
    heap.pop();
    if(prev != dest){
    if(c_d > cur_map[prev]){continue;}
    else{
    
      for(auto n : data[prev].neighbors){
          if (cur_map[n] > c_d+CalculateDistance(prev, n)){
            cur_map[n] = c_d + CalculateDistance(prev, n);
            heap.push(make_pair(cur_map[n],n));
            pred_map[n] = prev;
          }
      }
    }
  }
  }
  std::string a = dest;
  path.push_back(dest);
  for(auto i=0;i<pred_map.size();i++){
    if(pred_map[a] == start){break;}
    else{
    path.push_back(pred_map[a]);
    a = pred_map[a];
  }
  }
  path.push_back(start);
  std::reverse(path.begin(),path.end());
  return path;
}


/**
 * CalculateShortestPath_Bellman_Ford: Given 2 locations, return the shortest path which is a
 * list of id.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Bellman_Ford(std::string location1_name, std::string location2_name){
  std::vector<std::string> path;
  std::string start = GetID(location1_name);
  std::string dest = GetID(location2_name);
  if (start == "-1" || dest == "-1"){ 
    return path; 
  }
  std::map<std::string,float> cur_map;
  std::map<std::string, std::string> pred_map;
  std::unordered_map<std::string, Node>::iterator it;
  for (it = data.begin(); it != data.end(); it++){
    if (data[it->first].id == start){
      cur_map.insert(std::pair<std::string,float> (start,0));}
    else{
      cur_map.insert(std::pair<std::string,float> (data[it->first].id,INT_MAX));}
  }
  bool flag;
  for(auto i=1;i<cur_map.size();i++){
    flag = false;
  for(auto &x : cur_map){
    
    for(auto &n : data[x.first].neighbors){
      if (cur_map[n] > x.second + CalculateDistance(x.first, n)){
        cur_map[n] = x.second + CalculateDistance(x.first, n);
        pred_map[n] = x.first;
        flag = true;
      }
    }
  }
  if(flag==false){break;}
  }
  std::string a = dest;
  path.push_back(dest);
  for(auto i=0;i<pred_map.size();i++){
    if(pred_map[a] == start){break;}
    else{
    path.push_back(pred_map[a]);
    a = pred_map[a];
  }
  }
  path.push_back(start);
  std::reverse(path.begin(),path.end());


  return path;
}

/**
 * Travelling salesman problem: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of total distance and the all the progress to get final path
 */
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan(std::vector<std::string> &location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> results;
  std::vector<std::vector<std::string>> ids;
  std::vector<std::string> min_path;
  double min = INT_MAX;
  
  sort(location_ids.begin(), location_ids.end());
  do{
    location_ids.push_back(location_ids[0]);
    ids.push_back(location_ids);
    if(min > CalculatePathLength(location_ids)){
      min = CalculatePathLength(location_ids);
      min_path = location_ids;
    }
    location_ids.pop_back();
  }while(next_permutation(location_ids.begin(), location_ids.end()));

  ids.push_back(min_path);
  min =CalculatePathLength(min_path);
  results = {min, ids};
  return results;
}

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_2opt(std::vector<std::string> &location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> results;
  std::vector<std::string> ex_r = location_ids;
  ex_r.push_back(ex_r[0]);
  std::vector<std::string> new_r;
  std::vector<std::string> min_path;
  std::vector<std::vector<std::string>> ids;
  double best_dis;
  double new_dis;

  int n = 0;
  int max = location_ids.size()*location_ids.size();
  while(n < max){
    best_dis = CalculatePathLength(ex_r);
    for(int i=1;i<=location_ids.size()-1;i++){
      for(int k=i+1;k<=location_ids.size();k++){
        new_r = opt2swap(ex_r,i,k);
        new_r.push_back(new_r[0]);
        new_dis = CalculatePathLength(new_r);
        new_r.pop_back();
        if(new_dis < best_dis){
          ex_r = new_r;
          best_dis = new_dis;
          new_r.push_back(new_r[0]);
          ids.push_back(new_r);
          min_path = new_r;
          new_r.pop_back();
          results.first = new_dis;
        }
      }
    }
    n++;
  }
  
  min_path.pop_back();
  ids.push_back(min_path);
  best_dis = CalculatePathLength(min_path);
  
  results = {best_dis, ids};
  return results;
}

std::vector<std::string> TrojanMap::opt2swap(std::vector<std::string> &lids, int i, int k){
  
  auto start = lids.begin();
  auto iv = lids.begin()+i;
  auto kv = lids.begin()+k;
  auto end = lids.end();
  
  std::vector<std::string> new_r1(start,iv);
  std::vector<std::string> new_r2(iv,kv+1);
  std::vector<std::string> new_r3(kv+1,end);

  std::reverse(new_r2.begin(),new_r2.end());



  new_r1.insert(new_r1.end(),new_r2.begin(),new_r2.end());
  new_r1.insert(new_r1.end(),new_r3.begin(),new_r3.end());

  return new_r1;


}

/**
 * Given CSV filename, it read and parse locations data from CSV file,
 * and return locations vector for topological sort problem.
 *
 * @param  {std::string} locations_filename     : locations_filename
 * @return {std::vector<std::string>}           : locations 
 */
std::vector<std::string> TrojanMap::ReadLocationsFromCSVFile(std::string locations_filename){
  std::vector<std::string> location_names_from_csv;
  return location_names_from_csv;
}

/**
 * Given CSV filenames, it read and parse dependencise data from CSV file,
 * and return dependencies vector for topological sort problem.
 *
 * @param  {std::string} dependencies_filename     : dependencies_filename
 * @return {std::vector<std::vector<std::string>>} : dependencies
 */
std::vector<std::vector<std::string>> TrojanMap::ReadDependenciesFromCSVFile(std::string dependencies_filename){
  std::vector<std::vector<std::string>> dependencies_from_csv;
  return dependencies_from_csv;
}

/**
 * DeliveringTrojan: Given a vector of location names, it should return a sorting of nodes
 * that satisfies the given dependencies.
 *
 * @param  {std::vector<std::string>} locations                     : locations
 * @param  {std::vector<std::vector<std::string>>} dependencies     : prerequisites
 * @return {std::vector<std::string>} results                       : results
 */
void TrojanMap::TraverseDFS(std::string root, std::unordered_map<std::string, std::vector<std::string> > graph, std::map<std::string, bool> &visited, std::vector<std::string> &traversal) {
  visited[root] = true;
  traversal.push_back(root);
  std::vector<std::string>::iterator i;
  for (i = graph[root].begin(); i != graph[root].end(); i++) {
    if (!visited[*i])
      TraverseDFS(*i, graph, visited, traversal);
  }
  return;
}

std::vector<std::string> TrojanMap::DeliveringTrojan(std::vector<std::string> &locations,std::vector<std::vector<std::string>> &dependencies){
  std::vector<std::string> result, dfs;
  std::unordered_map<std::string, std::vector<std::string> > adj;
  std::map<std::string, bool> visited;
  for (auto location : locations) {
    std::vector<std::string> temp;
    adj[location] = temp;
  }

  for (auto dependency: dependencies) {
    adj[dependency[0]].push_back(dependency[1]);
  }

  TraverseDFS(locations[0], adj, visited, dfs);
  result.insert(result.end(), dfs.rbegin(), dfs.rend());
  std::reverse(result.begin(),result.end());
  return result;                                                     
}      

/**
 * Cycle Detection: Given four points of the square-shape subgraph, return true if there
 * is a cycle path inside the square, false otherwise.
 * 
 * @param {std::vector<double>} square: four vertexes of the square area
 * @return {bool}: whether there is a cycle or not
 */
bool TrojanMap::CycleDetection(std::vector<double> &square) {
  std::map<std::string, bool> visited;
  std::unordered_map<std::string, Node>::iterator it;
    for (it = data.begin(); it != data.end(); it++){
      auto lati = data[it->first].lat;
      auto longi = data[it->first].lon;
      if(longi > square[0] && longi < square[1] && lati < square[2] && lati > square[3]){
        visited.insert(std::pair<std::string,bool>(it->first,false));
      }
    }

    for(auto &x : visited){
      if(x.second == false){
        if(hasCycle(x.first,visited,"-1",square)){return true;}
      }
    }

  return false;
}

bool TrojanMap::hasCycle(std::string cur_id, std::map<std::string, bool> &visited, std::string par_id, std::vector<double> &square){
  visited[cur_id] = true;
  std::map<std::string, std::string> pred;
  for(auto &n : data[cur_id].neighbors){
    pred[n] = cur_id;
    auto lati = data[n].lat;
    auto longi = data[n].lon;
    if(longi > square[0] && longi < square[1] && lati < square[2] && lati > square[3]){
      if(!visited[n]){
        if(hasCycle(n,visited,pred[n],square)){return true;}
      }
      if(visited[n] == true && n != par_id){
          return true;
      }
    }
  }
  return false;
}
/**
 * FindKClosetPoints: Given a location id and k, find the k closest points on the map
 * 
 * @param {std::string} name: the name of the location
 * @param {int} k: number of closest points
 * @return {std::vector<std::string>}: k closest points
 */
std::vector<std::string> TrojanMap::FindKClosestPoints(std::string name, int k) {
  std::vector<std::string> res;
  std::string id = GetID(name);
  double dist;
  std::map<double, std::string> maps;
  std::unordered_map<std::string, Node>::iterator it;
    for (it = data.begin(); it != data.end(); it++){
      if(data[it->first].name == "" || data[it->first].name == name ){continue;}
      dist = CalculateDistance(it->first, id);
      maps.insert(std::pair<double, std::string> (dist,(it->first)));
      
    }
    int count=0;
    std::map<double, std::string>::iterator x;
    for(x=maps.begin(); x != maps.end();x++){
      if(count==k){break;}
      else{
      res.push_back(x->second);
      count++;
      }
      
    }
    

  return res;

}

// Extra TSP 3 opt
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_3opt(std::vector<std::string> &location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> results;
  std::vector<std::string> ex_r = location_ids;
  ex_r.push_back(ex_r[0]);
  std::vector<std::string> new_r;
  std::vector<std::string> min_path;
  std::vector<std::vector<std::string>> ids;
  double best_dis;
  double new_dis;

  int n = 0;
  int max = location_ids.size()*location_ids.size();
  while(n < max){
    best_dis = CalculatePathLength(ex_r);
    for(int i=1;i<=location_ids.size();i++){
      for(int j=i+2;j<=location_ids.size();j++){
        for(int k=j+1;k<=(location_ids.size() + (i > 0 ));k++){
          new_r = opt3swap(ex_r,i,j,k);
          new_r.push_back(new_r[0]);
          new_dis = CalculatePathLength(new_r);
          new_r.pop_back();
          if(new_dis < best_dis){
            ex_r = new_r;
            best_dis = new_dis;
            new_r.push_back(new_r[0]);
            ids.push_back(new_r);
            min_path = new_r;
            new_r.pop_back();
            results.first = new_dis;
          }
        }
      }
    }
    n++;
  }
  
  ids.erase(ids.begin());
  ids.push_back(min_path);
  best_dis = CalculatePathLength(min_path);
  
  results = {best_dis, ids};
  return results;
}

std::vector<std::string> TrojanMap::opt3swap(std::vector<std::string> &lids, int i, int j, int k){
  
  std::string a = lids[i-1];
  std::string b = lids[i];
  std::string c = lids[j-1];
  std::string d = lids[j];
  std::string e = lids[k-1];
  std::string f = lids[k];

  auto d0 = CalculateDistance(a,b) + CalculateDistance(c,d) + CalculateDistance(e,f);
  auto d1 = CalculateDistance(a,c) + CalculateDistance(b,d) + CalculateDistance(e,f);
  auto d2 = CalculateDistance(a,b) + CalculateDistance(c,e) + CalculateDistance(d,f);
  auto d3 = CalculateDistance(a,d) + CalculateDistance(e,b) + CalculateDistance(c,f);
  auto d4 = CalculateDistance(f,b) + CalculateDistance(c,d) + CalculateDistance(e,a);


  if (d0 > d1){
    std::reverse(lids.begin()+i,lids.begin()+j);
  }
  else if (d0 > d2){
    std::reverse(lids.begin()+j,lids.begin()+k);
  }
  else if (d0 > d4){
      std::reverse(lids.begin()+i,lids.begin()+k);
  }
  else if (d0 > d3){
    std::vector<std::string> t1(lids.begin()+i,lids.begin()+j);
    std::vector<std::string> t2(lids.begin()+j,lids.begin()+k);
    t2.insert(t2.end(),t1.begin(),t1.end());
    lids.insert(lids.begin()+i,t2.begin(),t2.end());
  }



  return lids;


}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Genetic TSP

// #define V 5
// #define GENES ABCDE
// #define START 0
// #define POP_SIZE 10
 
// std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_Genetic(std::vector<std::string> &location_ids){
//   std::pair<double, std::vector<std::vector<std::string>>> results;
 
//   return results;
// }


// struct individual {
//     string gnome;
//     int fitness;
// };
 

// int rand_num(int start, int end)
// {
//     int r = end - start;
//     int rnum = start + rand() % r;
//     return rnum;
// }

// bool repeat(string s, char ch)
// {
//     for (int i = 0; i < s.size(); i++) {
//         if (s[i] == ch)
//             return true;
//     }
//     return false;
// }
 

// string mutatedGene(string gnome)
// {
//     while (true) {
//         int r = rand_num(1, V);
//         int r1 = rand_num(1, V);
//         if (r1 != r) {
//             char temp = gnome[r];
//             gnome[r] = gnome[r1];
//             gnome[r1] = temp;
//             break;
//         }
//     }
//     return gnome;
// }
 

// string create_gnome()
// {
//     string gnome = "0";
//     while (true) {
//         if (gnome.size() == V) {
//             gnome += gnome[0];
//             break;
//         }
//         int temp = rand_num(1, V);
//         if (!repeat(gnome, (char)(temp + 48)))
//             gnome += (char)(temp + 48);
//     }
//     return gnome;
// }
 

// int cal_fitness(string gnome)
// {
//     int map[V][V] = { { 0, 2, INT_MAX, 12, 5 },
//                       { 2, 0, 4, 8, INT_MAX },
//                       { INT_MAX, 4, 0, 3, 3 },
//                       { 12, 8, 3, 0, 10 },
//                       { 5, INT_MAX, 3, 10, 0 } };
//     int f = 0;
//     for (int i = 0; i < gnome.size() - 1; i++) {
//         if (map[gnome[i] - 48][gnome[i + 1] - 48] == INT_MAX)
//             return INT_MAX;
//         f += map[gnome[i] - 48][gnome[i + 1] - 48];
//     }
//     return f;
// }
 
// int cooldown(int temp)
// {
//     return (90 * temp) / 100;
// }
 

// bool lessthan(struct individual t1,
//               struct individual t2)
// {
//     return t1.fitness < t2.fitness;
// }
 

// void TSPUtil(int map[V][V])
// {
    
//     int gen = 1;
    
//     int gen_thres = 5;
 
//     vector<struct individual> population;
//     struct individual temp;
 
    
//     for (int i = 0; i < POP_SIZE; i++) {
//         temp.gnome = create_gnome();
//         temp.fitness = cal_fitness(temp.gnome);
//         population.push_back(temp);
//     }
 
//     cout << "\nInitial population: " << endl
//          << "GNOME     FITNESS VALUE\n";
//     for (int i = 0; i < POP_SIZE; i++)
//         cout << population[i].gnome << "   "
//              << population[i].fitness << endl;
//     cout << "\n";
 
//     bool found = false;
//     int temperature = 10000;
 
    
//     while (temperature > 1000 && gen <= gen_thres) {
//         sort(population.begin(), population.end(), lessthan);
//         cout << "\nCurrent temp: " << temperature << "\n";
//         vector<struct individual> new_population;
 
//         for (int i = 0; i < POP_SIZE; i++) {
//             struct individual p1 = population[i];
 
//             while (true) {
//                 string new_g = mutatedGene(p1.gnome);
//                 struct individual new_gnome;
//                 new_gnome.gnome = new_g;
//                 new_gnome.fitness = cal_fitness(new_gnome.gnome);
 
//                 if (new_gnome.fitness <= population[i].fitness) {
//                     new_population.push_back(new_gnome);
//                     break;
//                 }
//                 else {
 
//                     float prob = pow(2.7,
//                                      -1 * ((float)(new_gnome.fitness
//                                                    - population[i].fitness)
//                                            / temperature));
//                     if (prob > 0.5) {
//                         new_population.push_back(new_gnome);
//                         break;
//                     }
//                 }
//             }
//         }
 
//         temperature = cooldown(temperature);
//         population = new_population;
//         cout << "Generation " << gen << " \n";
//         cout << "GNOME     FITNESS VALUE\n";
 
//         for (int i = 0; i < POP_SIZE; i++)
//             cout << population[i].gnome << "   "
//                  << population[i].fitness << endl;
//         gen++;
//     }
// }