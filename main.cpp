#include <iostream>
#include <list>
#include <fstream>
#include <vector>
#include <sstream>
#include "map"
#include "Points.h"
#include "json-develop/single_include/nlohmann/json.hpp"
using json = nlohmann::json;

//void readGEOJSON (const char *file_in){
//
//    std::ifstream i(file_in);
//    json j;
//    i >> j;
//
//
////    std::vector<double> coord;
//    std::vector<std::vector<Point>> all_vertices;
//    std::vector<std::vector<Point>> all_floor;
//    std::vector<std::vector<Point>> all_roof;
//    // For walls
//    std::vector<std::vector<Point>> all_floor_new;
//    std::vector<std::vector<Point>> all_roof_new;
//    std::vector<std::string> ids;
//    //
//    auto features = j["features"];
//    for (auto &all:features){
//        auto coordinates =all["geometry"]["coordinates"];
//        auto id = all["properties"]["identificatie"];
//        ids.push_back(id);
//        auto year_of_construction =all["properties"]["bouwjaar"];
//        double roof_height = all["properties"]["z.median"];
//        auto storeys = ceil(roof_height/3);
//        std::vector<std::vector<Point>> faces;
//        std::vector<Point> floor_vertices;
//        std::vector<Point> roof_vertices;
//
//        // Vertices for determining roof and floor
//        for (auto coord:coordinates) {
//            for (int x = 0; x < coord.size()-1; x++) {
//                Point base = {coord[x][0], coord[x][1], coord[x][2]};
//                Point roof = {coord[x][0], coord[x][1], roof_height};
//                floor_vertices.push_back(base);
//                roof_vertices.push_back(roof);
//            }
//        }
//        all_floor.push_back(floor_vertices);
//        all_roof.push_back(roof_vertices);
//
//
//        // Vertices for determining walls
//        std::vector<Point> new_floor_vertices;
//        std::vector<Point> new_roof_vertices;
//        for (auto coord_new:coordinates) {
//            for (int x = 0; x < coord_new.size(); x++) {
//                Point base_new = {coord_new[x][0], coord_new[x][1], coord_new[x][2]};
//                Point roof_new = {coord_new[x][0], coord_new[x][1], roof_height};
//                new_floor_vertices.push_back(base_new);
//                new_roof_vertices.push_back(roof_new);
//            }
//        }
//        all_floor_new.push_back(new_floor_vertices);
//        all_roof_new.push_back(new_roof_vertices);
//    }
//
////    std::cout << all_floor.size() << std::endl;
////    std::cout << all_roof.size() << std::endl;
////    std::cout << features.size() << std::endl;
//
//
//    int k = 0;
//    std::vector<std::vector<std::vector<Point>>> all_faces;
//    for(auto build: all_floor_new){
//        std::vector<std::vector<Point>> all_walls;
////        std::cout << build.size() << std::endl;
//        for(int a = 0; a < build.size()-1; a++){
//            std::vector<Point> wall;
//            wall.push_back(build[a]);
//            wall.push_back(build[a+1]);
//            wall.push_back(all_roof_new[k][a+1]);
//            wall.push_back(all_roof_new[k][a]);
//            all_walls.push_back(wall);
//        }
//        all_faces.push_back(all_walls);
//        k++;
//    }
////    std::cout << "Number of faces: " << all_faces[0].size() << std::endl;
////    std::cout << all_roof_new.size() << std::endl;
////    std::cout << features.size() << std::endl;
////    std::cout << ids.size() << std::endl;
//}




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
//    const char *file_in = "../cpp_input.json";
//    const char *file_out = "../Tin.json";
    const char *file_out = "../buildings.json";
//    importOBJ(file_in);
//    exportCityJSON(file_out);
//    readGEOJSON(file_in);


    std::ifstream k("../cpp_input.json");
    json j;
    k >> j;


//  d::vector<double> coord;
    std::vector<Point> all_vertices;
    std::vector<std::vector<Point>> all_floor;
    std::vector<std::vector<Point>> all_roof;
    std::vector<int> indices;
    // For walls
    std::vector<std::vector<Point>> all_floor_new;
    std::vector<std::vector<Point>> all_roof_new;
    std::vector<std::string> ids;
    std::vector<std::string> years;
    std::vector<double> heights;
    std::vector<double> all_storeys;
    //
    auto features = j["features"];
    for (auto &all:features){
        auto coordinates =all["geometry"]["coordinates"];
        auto id = all["properties"]["identificatie"];
        ids.push_back(id);
        auto year_of_construction =all["properties"]["bouwjaar"];
        years.push_back(year_of_construction);
        double roof_height = all["properties"]["z.median"];
        heights.push_back(roof_height);
        auto storeys = ceil(roof_height/3);
        all_storeys.push_back(storeys);
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
                all_vertices.push_back(base);
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

    int t1 = 1;
    for(auto x:all_vertices){
        indices.push_back(t1);
        t1++;
    }

    int l = 0;
    std::vector<std::vector<std::vector<Point>>> all_faces;
    for(auto build: all_floor_new){
        std::vector<std::vector<Point>> all_walls;
//    std::cout << build.size() << std::endl;
        for(int a = 0; a < build.size()-1; a++){
            std::vector<Point> wall;
            wall.push_back(build[a]);
            wall.push_back(build[a+1]);
            wall.push_back(all_roof_new[l][a+1]);
            wall.push_back(all_roof_new[l][a]);
            all_walls.push_back(wall);
        }
        all_faces.push_back(all_walls);
        l++;
    }
    std::cout << "Number of faces: " << all_faces[0].size() << std::endl;
    std::cout << all_roof_new.size() << std::endl;
    std::cout << features.size() << std::endl;
    std::cout << ids.size() << std::endl;




    // Write CityJSON
    std::ofstream output_file(file_out);
    if (output_file.is_open()) {
        // Headers
        output_file << "{\n"
                       "\"type\": \"CityJSON\",\n"
                       "\"version\": \"1.0\",\n"
                       "\"metadata\": {"
                       "\"referenceSystem\":\"urn:ogc:def:crs:EPSG::7415\"\n"
                       "\t\t},\n"
                       "\"CityObjects\": {";
        // CityObjects
        int id_obj = 1, id_obj_count = 1;
        int t = 0;
        for (int i=0;i<all_floor.size(); i++){
            output_file << "\n\t\"id-" << ids[t] << "\" : {\n"
                                                   "\t\t\"type\": \"Building\",\n"
                                                    "\t\t\"attributes\": {\n"
                                                    "\t\t\t\"yearOfConstruction\": \"" << years[t] << "\",\n"
                                                    "\t\t\t\"measuredHeight\": " << heights[t] << ",\n"
                                                    "\t\t\t\"storeysAboveGround\": " << all_storeys[t] << "\n"
                                                    "\t\t},\n"
                                                    ;
            output_file<< "\t\t\"geometry\":[{\n"
                          "\t\t\t\"type\": \"Solid\",\n"
                          "\t\t\t\"lod\": 1.2,\n"
                          "\t\t\t\"boundaries\":[\n";
                          for (auto build:all_floor){
                              for (Point b:build){
                                  output_file<< "\t\t\t\t\"[[\n";
                                  output_file << indices[t] << ",]\n";
                              }
                          }
                          "\t\t\t],\n"
                          "\t\t\t\"semantics\":{\n"
                          "\t\t\t\t\"surfaces\":[\n"
                          "\t\t\t\t\t{\"type\":\"GroundSurface\"},\n"
                          "\t\t\t\t\t{\"type\":\"WallSurface\"},\n"
                          "\t\t\t\t\t{\"type\":\"RoofSurface\"}\n"
                          "\t\t\t\t],\n"
                          "\t\t\t\t\"values\": [\n"
                          "\t\t\t\t]\n"
                          "\t\t\t}\n"
                          "\t\t}]\n"
                          "\t},\n";


            t++;
        }
        output_file<<"},";
        output_file<<"\"vertices\": [\n";
        for (auto v:all_floor) {
            for (Point p:v) {
                output_file << "[" << p.x << "," << p.y << "," << p.z << "],\n";
            }
        }
        for (auto v:all_roof) {
            for (Point p:v) {
                output_file << "[" << p.x << "," << p.y << "," << p.z << "],\n";
            }
        }
        for (auto v:all_faces) {
            for (auto p:v) {
                for (Point p1:p)
                output_file << "[" << p1.x << "," << p1.y << "," << p1.z << "],\n";
            }
        }


//            outfile << "\"vertices\": [\n";
//            std::string d4="";
//            for (auto const &v:D.vertices()){
//                outfile<<"      "<<d4<<"[ "<<v->x<<", "<<v->y<<", "<<v->z<<"]\n";
//                d4=", ";
//            }
                         "\"CityObjects\": {";
//        }
//            for (std::vector<Face *> face_list:buildings) {
//                output_file << "\n\t\"id-" << id_obj << "\" : {\n"
//                                                        "\t\t\"geometry\": [{\n"
//                                                        "\t\t\t\"boundaries\": [\n";
//                int f_count = 0;
//                for (Face *f:face_list) {
//                    if (f->isEliminated()) {
//                        continue;
//                    }
//                    if (f_count > 0) {
//                        output_file << ",\n";
//                    }
//                    int length_boundary = 1;
//                    HalfEdge *e1 = f->exteriorEdge;
//                    std::vector<int> id_fvertices;
//                    id_fvertices.push_back(vertex_toId[e1->origin]);
//                    // Faces boundaries may have different length. We check the length here.
//                    while (f->exteriorEdge != e1->next) {
//                        int nextID = vertex_toId[e1->destination];
//                        id_fvertices.push_back(nextID);
//                        e1 = e1->next;
//                        length_boundary++;
//                    }
//
//                    output_file << "\t\t\t\t[[";
//                    int id_count = 1;
//                    for (int id:id_fvertices) {
//                        if (id_count != id_fvertices.size()) {
//                            output_file << id - 1 << ", ";
//                            id_count++;
//                        } else (output_file << id - 1);
//                    }
//
//                    // Holes
//                    if (f->holes.size() > 0) {
//                        //std::cout << "Hole size " << f->holes.size() << std::endl;
//                        for (HalfEdge *hole_e:f->holes) {
//                            int hole_count = 1;
//                            std::vector<int> id_holes_vertices;
//                            output_file << "], \n[";
//                            HalfEdge *hole_e_next = hole_e;
//                            // Holes boundaries may have different length. We check the length here.
//                            do {
//                                id_holes_vertices.push_back(vertex_toId[hole_e_next->origin]);
//                                hole_e_next = hole_e_next->next;
//                            } while (hole_e_next != hole_e);
//                            for (int id_hole:id_holes_vertices) {
//                                if (hole_count != id_holes_vertices.size()) {
//                                    output_file << id_hole - 1 << ", ";
//                                    hole_count++;
//                                } else (output_file << id_hole - 1);
//                            }
//                            id_holes_vertices.clear();
//                        }
//                    }
//                    // Close boundaries
//                    output_file << "]]";
//                    f_count++;
//                }
//                output_file << "\t],\n"
//                               "\t\t\"lod\": 2,\n"
//                               "\t\t\"type\": \"MultiSurface\"}],\n";
//                id_obj++;
//                if (id_obj_count != buildings.size()) {
//                    output_file << "\t\"type\": \"Building\"\n},";
//                    id_obj_count++;
//                } else (output_file << "\t\"type\": \"Building\"\n}");
//            }
//        output_file << "\n},";
//        // Vertices
//        int vertices_count = 1;
//        output_file << "\n\"vertices\": \n[";
//        for (const auto &v : D.vertices()) {
//            if (vertices_count != vertex_toId.size()) {
//                output_file << "[" << float(v->x) << ", " << float(v->y) << ", " << float(v->z) << "],\n";
//                vertices_count++;
//            } else (output_file << "[" << float(v->x) << ", " << float(v->y) << ", " << float(v->z) << "]");
//        }
//        output_file << "\n]\n}";
//        std::cout << "file is written in " << file_out << std::endl;
        output_file.close();
    }
    return 0;

}