#include <iostream>
#include <list>
#include <fstream>
#include <vector>
#include <sstream>
#include "map"
#include "Points.h"
#include "json-develop/single_include/nlohmann/json.hpp"
using json = nlohmann::json;

void readGEOJSON (const char *file_in){

    std::ifstream i(file_in);
    json j;
    i >> j;

//    for (int t = 0; t < j["features"].size(); t++){
        // Get the coordinates
//        std::string x = j["features"][t]["properties"]["_coordinates"];
//        std::cout << x << std::endl;
//        std::string new_s;
//        std::string second;
//        std::stringstream s(x);
//        std::stringstream p;
        std::vector<double> coord;

//        while (std::getline(s, new_s, '|')){
//            std::stringstream b(new_s);
//            while (std::getline(b, second, ',')){
//                double d = std::stod(second); // I tried to convert also to double here but we lose precision
//                coord.push_back(d);
//            }
//
//        }
        std::vector<Point> Points;
        std::vector<Point> floor_faces;
        std::vector<Point> roof_faces;
        std::vector<std::vector<Point>> all_vertices;
        std::vector<std::vector<Point>> all_floor;
        std::vector<Point> all_floor_new;
        std::vector<Point> all_roof_new;
        std::vector<std::vector<Point>> all_roof;
        auto features = j["features"];
        for (auto &all:features){
            auto coordinates =all["geometry"]["coordinates"];
//            std::cout << coordinates[0].back() << std::endl;
            auto id = all["properties"]["identificatie"];
            auto year_of_construction =all["properties"]["bouwjaar"];
            double roof_height = all["properties"]["z.median"];
            auto storeys = ceil(roof_height/3);
            std::vector<std::vector<Point>> faces;
            std::vector<Point> floor_vertices;
            std::vector<Point> roof_vertices;

            for (auto coord:coordinates) {
//                std::cout<<coord[0]<<std::endl;
                for (int x = 0; x < coord.size() - 1; x++) {
                    Point base = {coord[x][0], coord[x][1], coord[x][2]};
                    Point roof = {coord[x][0], coord[x][1], roof_height};
                    all_floor_new.push_back(base);
                    all_roof_new.push_back(roof);
                    floor_vertices.push_back(base);
                    roof_vertices.push_back(roof);
//                    std::cout << all_floor_new.size() << std::endl;
                }
            }
            all_floor.push_back(floor_vertices);
            all_roof.push_back(roof_vertices);
//                for (auto point:coord){
//                    Point base ={point[0],point[1],point[2]};
//                    Point roof ={point[0],point[1], roof_height};
//                    all_floor_new.push_back(base);
//                    all_roof_new.push_back(roof);
//                }

        }

    std::cout << all_floor.size() << std::endl;
    std::cout << all_roof.size() << std::endl;
    std::cout << features.size() << std::endl;



    for (int a = 0; a < all_floor_new.size()-1; a++) {

        std::vector<Point> wall;
        wall.push_back(all_floor_new[a]);
        wall.push_back(all_floor_new[a+1]);
        wall.push_back(all_roof_new[a+1]);
        wall.push_back(all_roof_new[a]);
        all_faces.push_back(wall);
    }

    int k = 0;
    std::vector<std::vector<std::vector<Point>>> all_faces;
    for(auto build: all_floor){
        std::vector<std::vector<Point>> all_walls;
        std::vector<Point> wall;
        for(int a = 0; a < build.size()-1; a++){
            wall.push_back(build[a]);
            wall.push_back(build[a+1]);
            wall.push_back(all_roof[k][a+1]);
            wall.push_back(all_roof[k][a]);
            k++;
        }
        all_walls.push_back(wall);
        all_faces.push_back(all_walls);
    }

//
//    std::cout << "all_faces" << all_faces.size() << std::endl;
//    std::cout << all_faces[0][0].x << std::endl;
//    std::cout << all_faces[0][0].y << std::endl;
//    std::cout << all_faces[0][0].z << std::endl;
}






//    for(int x = 0; x < j["features"].size(); x++){
//
//    }






std::map<int,Point> vmap;
int i=0;
std::vector<Point> vertices;
std::vector<std::vector<unsigned int>> faces;

//float minx = INFINITY;
//float miny = INFINITY;
//float minz = INFINITY;
//float maxx = -INFINITY;
//float maxy = -INFINITY;
//float maxz = -INFINITY;
//void importOBJ(const char *file_in) {
//    std::ifstream infile(file_in);
//    std::string line= "";
//    while (std::getline(infile, line)) {
//        std::stringstream str_str;
//        str_str.clear();
//        str_str.str(line);
//        std::string prefix = "";
//        str_str >> prefix;
//        if (prefix == "v") {
//            i++;
//            float x, y, z;
//            str_str >> x >> y >> z;
//            Point vertex={x,y,z};
//            vmap[i]=vertex;
//            vertices.push_back(vertex);
//            if (x<minx){minx = x;}
//            if (y<miny){miny = y;}
//            if (z<minz){minz = z;}
//            if (x>maxx){maxx = x;}
//            if (y>maxy){maxy = y;}
//            if (z>maxz){maxz = z;}
//        }
//        else if (prefix == "f") {
//            unsigned int v1,v2,v3;
//            str_str >> v1 >> v2 >> v3;
//            std::vector<unsigned int> temp = {v1,v2,v3};
//            faces.push_back(temp);
//        }
//        }
//        std::cout << vertices.size() << std::endl;
//        std::cout << faces.size() << std::endl;
//}
//void exportCityJSON(const char *file_out) {
//    std::ofstream outfile(file_out);
//    outfile <<"{\n";
//    outfile <<"  \"type\": \"CityJSON\",\n";
//    outfile <<"  \"version\": \"1.0\",\n";
//    outfile <<"  \"CityObjects\": {\n";
//    outfile << "       \"MyTerrain\": {\n";
//    outfile << "          \"type\": \"TINRelief\",\n";
//    outfile << "          \"geographicalExtent\": [ "<<minx<<", "<<miny<<", "<<minz<<", "<<maxx<<", "<<maxy<<", "<<maxz<<" ],\n";
//    outfile << "          \"geometry\": [{\n";
//    outfile << "              \"type\": \"CompositeSurface\",\n";
//    outfile << "              \"lod\": 1,\n";
//    outfile << "              \"boundaries\": [\n";
//    std::string delimeter="";
//    for (auto const &t:faces) {
//        outfile << delimeter << "[[";
//        outfile << t[0] - 1 << ", " << t[1] - 1 << ", " << t[2] - 1 << "]]";
//        delimeter = ", ";
//    }
//    outfile<<"\n";
//    outfile<<"          ]\n";
//    outfile<<"      }]\n";
//    outfile<<"      }\n";
//    outfile<<"    },"<<"\n";
//    outfile << "\"vertices\": [\n";
//    std::string d="";
//    for (auto const &v:vertices){
//        outfile<<"      "<<d<<"[ "<<v.x<<", "<<v.y<<", "<<v.z<<"]\n";
//        d=", ";
//    }
//    //close
//    outfile<<"   ]\n";
//    outfile<<"}\n";
//    outfile.close();
//}
int main(int argc, const char * argv[]) {
    const char *file_in = "../cpp_input.json";
    const char *file_out = "../Tin.json";
//    importOBJ(file_in);
//    exportCityJSON(file_out);
    readGEOJSON(file_in);
    return 0;
}