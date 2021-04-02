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


//    std::vector<double> coord;
    std::vector<std::vector<Point>> all_vertices;
    std::vector<std::vector<Point>> all_floor;
    std::vector<std::vector<Point>> all_roof;
    // For walls
    std::vector<std::vector<Point>> all_floor_new;
    std::vector<std::vector<Point>> all_roof_new;
    //
    auto features = j["features"];
    for (auto &all:features){
        auto coordinates =all["geometry"]["coordinates"];
        auto id = all["properties"]["identificatie"];
        auto year_of_construction =all["properties"]["bouwjaar"];
        double roof_height = all["properties"]["z.median"];
        auto storeys = ceil(roof_height/3);
        std::vector<std::vector<Point>> faces;
        std::vector<Point> floor_vertices;
        std::vector<Point> roof_vertices;

        // Vertices for determining roof and floor
        for (auto coord:coordinates) {
            for (int x = 0; x < coord.size()-1; x++) {
                Point base = {coord[x][0], coord[x][1], coord[x][2]};
                Point roof = {coord[x][0], coord[x][1], roof_height};
                floor_vertices.push_back(base);
                roof_vertices.push_back(roof);
            }
        }
        all_floor.push_back(floor_vertices);
        all_roof.push_back(roof_vertices);


        // Vertices for determining walls
        std::vector<Point> new_floor_vertices;
        std::vector<Point> new_roof_vertices;
        for (auto coord_new:coordinates) {
            for (int x = 0; x < coord_new.size(); x++) {
                Point base_new = {coord_new[x][0], coord_new[x][1], coord_new[x][2]};
                Point roof_new = {coord_new[x][0], coord_new[x][1], roof_height};
                new_floor_vertices.push_back(base_new);
                new_roof_vertices.push_back(roof_new);
            }
        }
        all_floor_new.push_back(new_floor_vertices);
        all_roof_new.push_back(new_roof_vertices);
    }

//    std::cout << all_floor.size() << std::endl;
//    std::cout << all_roof.size() << std::endl;
//    std::cout << features.size() << std::endl;


    int k = 0;
    std::vector<std::vector<std::vector<Point>>> all_faces;
    for(auto build: all_floor_new){
        std::vector<std::vector<Point>> all_walls;
//        std::cout << build.size() << std::endl;
        for(int a = 0; a < build.size()-1; a++){
            std::vector<Point> wall;
            wall.push_back(build[a]);
            wall.push_back(build[a+1]);
            wall.push_back(all_roof_new[k][a+1]);
            wall.push_back(all_roof_new[k][a]);
            all_walls.push_back(wall);
        }
        all_faces.push_back(all_walls);
        k++;
    }
//    std::cout << "Number of faces: " << all_faces[0].size() << std::endl;
}











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