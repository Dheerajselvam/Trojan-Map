#include <map>
#include <vector>

#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

// TEST(TrojanMapStudentTest, Test1) {
//   TrojanMap m;
//   m.CreateGraphFromCSVFile();
//   std::string id = "269633667";
//   double ac = m.GetLat(id);
//   double ex = 34.0146495; // -118.2812433
//   EXPECT_EQ(ac, ex);
// }

// TEST(TrojanMapStudentTest2, Test1) {
//   TrojanMap m;
//   m.CreateGraphFromCSVFile();
//   std::string id = "358793609";
//   double ac = m.GetLat(id);
//   double ex = 34.0122358; //-118.2689631
//   EXPECT_EQ(ac, ex);
// }

// TEST(TrojanMapStudentTest3, Test1) {
//   TrojanMap m;
//   m.CreateGraphFromCSVFile();
//   std::string id = "358828789";
//   double ac = m.GetLat(id);
//   double ex = 34.0302903; //-118.2903526
//   EXPECT_EQ(ac, ex);
// }

// TEST(TrojanMapStudentTest4, Test1) {
//   TrojanMap m;
//   m.CreateGraphFromCSVFile();
//   std::string id = "269633667";
//   double ac = m.GetLon(id);
//   double ex = -118.2812433;
//   EXPECT_EQ(ac, ex);
// }

// TEST(TrojanMapStudentTest5, Test1) {
//   TrojanMap m;
//   m.CreateGraphFromCSVFile();
//   std::string id = "358793609";
//   double ac = m.GetLon(id);
//   double ex = -118.2689631;
//   EXPECT_EQ(ac, ex);
// }

// TEST(TrojanMapStudentTest6, Test1) {
//   TrojanMap m;
//   m.CreateGraphFromCSVFile();
//   std::string id = "358828789";
//   double ac = m.GetLon(id);
//   double ex = -118.2903526;
//   EXPECT_EQ(ac, ex);
// }

// TEST(TrojanMapStudentTest7, Test1) {
//   TrojanMap m;
//   m.CreateGraphFromCSVFile();
//   std::string id = "358786623";
//   std::string ac = m.GetName(id);
//   std::string ex = "John Adams Middle School";
//   EXPECT_EQ(ac, ex);
// }

// TEST(TrojanMapStudentTest8, Test1) {
//   TrojanMap m;
//   m.CreateGraphFromCSVFile();
//   std::string id = "358850019";
//   std::string ac = m.GetName(id);
//   std::string ex = "University Seventh Day Adventist Church";
//   EXPECT_EQ(ac, ex);
// }

// TEST(TrojanMapStudentTest9, Test1) {
//   TrojanMap m;
//   m.CreateGraphFromCSVFile();
//   std::string id = "269633667";
//   std::string ac = m.GetName(id);
//   std::string ex = {"Martin Luther King Jr Blvd  Coliseum"};
//   EXPECT_EQ(ac, ex);
// }

// TEST(TrojanMapStudentTest10, Test1) {
//   TrojanMap m;
//   m.CreateGraphFromCSVFile();
//   std::string id = "368172344";
//   std::vector<std::string> ac = m.GetNeighborIDs(id);
//   std::vector<std::string> ex = {"6512287152", "4399693646"};
//   EXPECT_EQ(ac, ex);
// }

// TEST(TrojanMapStudentTest11, Test1) {
//   TrojanMap m;
//   m.CreateGraphFromCSVFile();
//   std::string name = "Aldewaniah";
//   std::string  ac = m.GetID(name);
//   std::string  ex = "4944439089";
//   EXPECT_EQ(ac, ex);
// }

// TEST(TrojanMapStudentTest166, Test1) {
//   TrojanMap m;
//   m.CreateGraphFromCSVFile();
//   std::string name = "XXX";
//   std::string  ac = m.GetID(name);
//   std::string  ex = "-1";
//   EXPECT_EQ(ac, ex);
// }

// TEST(TrojanMapStudentTest12, Test1) {
//   TrojanMap m;
//   m.CreateGraphFromCSVFile();
//   std::string name = "Martin Luther King Jr Blvd  Coliseum";
//   std::pair<double, double>  ac = m.GetPosition(name);
//   std::pair<double, double>  ex = {34.0146495, -118.2812433};
//   EXPECT_EQ(ac, ex);
// }

// TEST(TrojanMapStudentTest15, Test1) {
//   TrojanMap m;
//   m.CreateGraphFromCSVFile();
//   std::string name = "XXX";
//   std::pair<double, double>  ac = m.GetPosition(name);
//   std::pair<double, double>  ex = {-1, -1};
//   EXPECT_EQ(ac, ex);
// }

// TEST(TrojanMapStudentTest16, Test1) {
//   TrojanMap m;
//   m.CreateGraphFromCSVFile();
//   std::vector<std::string> name = {"1","2","3","4","5"};
//   std::vector<std::string> ac = m.opt2swap(name,1,3);
//   std::vector<std::string> ex = {"1","4","3","2","5"};
//   EXPECT_EQ(ac, ex);
// }

// TEST(TrojanMapStudentTest17, Test1) {
//   TrojanMap m;
//   m.CreateGraphFromCSVFile();
//   std::vector<std::string> name = {"1","2","3","4","5","6","7","8","9","10"};
//   std::vector<std::string> ac = m.opt2swap(name,2,8);
//   std::vector<std::string> ex = {"1","2","9","8","7","6","5","4","3","10"};
//   EXPECT_EQ(ac, ex);
// }

TEST(TrojanMapTest, TSP) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"1873056015", "6905329551", "213332060", "1931345270"}; // Input location ids 
  auto result = m.TravellingTrojan_3opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"1873056015", "213332060", "1931345270", "6905329551", "1873056015"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  
  
  EXPECT_EQ(result.second[result.second.size()-1], gt);
}

// TEST(TrojanMapTest, TopologicalSort) {
//   TrojanMap m;
//   m.CreateGraphFromCSVFile();
//   std::vector<std::string> location_names = {"Ralphs", "Coffee Bean1","CVS","Cardinal Gardens"};
//   std::vector<std::vector<std::string>> dependencies = {{"Ralphs","Coffee Bean1"}, {"Ralphs","CVS"}, {"Ralphs","Cardinal Gardens"},{"Coffee Bean1","CVS"},{"CVS","Cardinal Gardens"},{"Coffee Bean1","Cardinal Gardens"}};
//   auto result = m.DeliveringTrojan(location_names, dependencies);
//   std::vector<std::string> gt ={"Ralphs", "Coffee Bean1","CVS","Cardinal Gardens"};
//   EXPECT_EQ(result, gt);
// }

