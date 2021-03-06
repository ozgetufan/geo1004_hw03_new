#include <iostream>
#include <list>
#include <fstream>
#include <vector>
#include "Points.h"
#include <iomanip>
#include "json-develop/single_include/nlohmann/json.hpp"
using json = nlohmann::json;


int main(int argc, const char * argv[]) {
//    const char *file_in = "../cpp_input.json";
//    const char *file_out = "../Tin.json";
    const char *file_out = "../buildings.json";


    std::ifstream k("../cpp_input.json");
    json j;
    k >> j;

    std::vector<std::vector<std::vector<Point>>> all_floor_rings;
    std::vector<std::vector<std::vector<Point>>> all_roof_rings;
    std::vector<int> new_indices;
    std::vector<int> new_roof_indices;
    // For walls
    std::vector<Point> wall_vertices;
    std::vector<int> wall_indices;
    std::vector<std::vector<std::vector<Point>>> all_floor_rings_new;
    std::vector<std::vector<std::vector<Point>>> all_roof_rings_new;
    std::vector<std::string> ids;
    std::vector<std::string> years;
    std::vector<double> heights;
    std::vector<double> all_storeys;
    //
    auto features = j["features"];
    for (const auto &all:features){
        auto coordinates =all["geometry"]["coordinates"];
        auto id = all["properties"]["identificatie"];
        ids.push_back(id);
        std::string year_of_construction =all["properties"]["bouwjaar"];
        std::string just_year = year_of_construction.substr(0, 4);
        years.push_back(just_year);
        double roof_height = all["properties"]["z.median"];
        heights.push_back(roof_height);
        auto storeys = ceil(roof_height/3);
        all_storeys.push_back(storeys);
        std::vector<std::vector<Point>> faces;
        std::vector<std::vector<Point>> all_floor_inside;
        std::vector<std::vector<Point>> all_roof_inside;
        std::vector<std::vector<Point>> all_floor_inside_new;
        std::vector<std::vector<Point>> all_roof_inside_new;


        // Vertices for determining roof and floor
        for (auto coord:coordinates) {
            std::vector<Point> floor_vertices;
            std::vector<Point> roof_vertices;
            for (int x = 0; x < coord.size()-1; x++) {
                Point base = {coord[x][0], coord[x][1], coord[x][2]};
                Point roof = {coord[x][0], coord[x][1], roof_height};
                floor_vertices.push_back(base);
                roof_vertices.push_back(roof);
            }
            all_floor_inside.push_back(floor_vertices);
            all_roof_inside.push_back(roof_vertices);
        }
        all_floor_rings.push_back(all_floor_inside);
        all_roof_rings.push_back(all_roof_inside);

//         Vertices for determining walls
        for (auto coord_new:coordinates) {
            std::vector<Point> new_floor_vertices;
            std::vector<Point> new_roof_vertices;
            for (int x = 0; x < coord_new.size(); x++) {
                Point base_new = {coord_new[x][0], coord_new[x][1], coord_new[x][2]};
                Point roof_new = {coord_new[x][0], coord_new[x][1], roof_height};
                new_floor_vertices.push_back(base_new);
                new_roof_vertices.push_back(roof_new);
            }
            all_floor_inside_new.push_back(new_floor_vertices);
            all_roof_inside_new.push_back(new_roof_vertices);
        }
        all_floor_rings_new.push_back(all_floor_inside_new);
        all_roof_rings_new.push_back(all_roof_inside_new);

    }

    int t1 = 0;
    for (const auto& building: all_floor_rings){
        for (const auto& ring: building) {
            for (auto vertex: ring){
                new_indices.push_back(t1);
                t1++;
            }
        }
    }

    int t2 = new_indices.back()+1;
    for (const auto& building: all_roof_rings){
        for (const auto& ring: building) {
            for (auto vertex: ring){
                new_roof_indices.push_back(t2);
                t2++;
            }
        }
    }


    std::vector<std::vector<std::vector<std::vector<Point>>>> all_faces;
    for(int build = 0; build < all_floor_rings_new.size(); build++){
        std::vector<std::vector<std::vector<Point>>> all_walls;
//    std::cout << build.size() << std::endl;
        for (int ring = 0; ring < all_floor_rings_new[build].size(); ring++){
//            std::vector<std::vector<Point>> ring_wall;
            std::vector<std::vector<Point>> walls;
            for(int a = 0; a < all_floor_rings_new[build][ring].size()-1; a++){
                std::vector<Point> wall;
                wall.push_back(all_floor_rings_new[build][ring][a]);
                wall.push_back(all_floor_rings_new[build][ring][a+1]);
                wall.push_back(all_roof_rings_new[build][ring][a+1]);
                wall.push_back(all_roof_rings_new[build][ring][a]);
                wall_vertices.push_back(all_floor_rings_new[build][ring][a]);
                wall_vertices.push_back(all_floor_rings_new[build][ring][a+1]);
                wall_vertices.push_back(all_roof_rings_new[build][ring][a+1]);
                wall_vertices.push_back(all_roof_rings_new[build][ring][a]);
                walls.push_back(wall);
            }
            all_walls.push_back(walls);
        }
        all_faces.push_back(all_walls);
    }

    std::cout << new_roof_indices.back() << std::endl;
    int t3 = new_roof_indices.back()+1;
    for(auto x:wall_vertices){
        wall_indices.push_back(t3);
        t3++;
    }

    std::cout << t3 << std::endl;

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
        int t = 0;
        int w = 0;
        int v = 0;
        int p = 0;
        for (int i = 0; i < features.size(); i++) {
            output_file << "\n\t\"id-" << ids[t] << "\" : {\n"
                                                    "\t\t\"type\": \"Building\",\n"
                                                    "\t\t\"attributes\": {\n"
                                                    "\t\t\t\"yearOfConstruction\": " << std::stoi(years[t]) << ",\n"
                                                                                                      "\t\t\t\"measuredHeight\": "
                        << heights[t] << ",\n"
                                         "\t\t\t\"storeysAboveGround\": " << all_storeys[t] << "\n"
                                                                                               "\t\t},\n";
            output_file << "\t\t\"geometry\":[{\n"
                           "\t\t\t\"type\": \"Solid\",\n"
                           "\t\t\t\"lod\": 1.2,\n"
                           "\t\t\t\"boundaries\":[[\n";
            output_file << "[";
            for (int y = 0; y < all_floor_rings[i].size(); y++) {
                output_file << "\t\t\t\t[";
                std::reverse(all_floor_rings[i][y].begin(), all_floor_rings[i][y].end());
                for (int z = 0; z < all_floor_rings[i][y].size(); z++) {
                    output_file << new_indices[p];
                    if (z == all_floor_rings[i][y].size() - 1) {
                        if (y == all_floor_rings[i].size() - 1) {
                            output_file << "]\n";
                        } else {
                            output_file << "],\n";
                        }
                    } else {
                        output_file << ",";
                    }
                    p++;
                }
            }
            output_file << "],\n";
            output_file<< "[";
            for (int y = 0; y < all_roof_rings[i].size(); y++) {
                output_file << "\t\t\t\t[";
                for (int z = 0; z < all_roof_rings[i][y].size(); z++) {
                    output_file << new_roof_indices[w];
                    if (z == all_roof_rings[i][y].size() - 1) {
                        if (y == all_roof_rings[i].size() - 1) {
                            output_file << "]\n";
                        } else {
                            output_file << "],\n";
                        }
                    } else {
                        output_file << ",";
                    }
                    w++;
                }

            }
            output_file << "],";
            int ctr1 = 0;
            int ctr2 = 0;
            int ctr3 = 0;
            for (int rings = 0; rings < all_faces[i].size(); rings++){
                for (int walls = 0; walls < all_faces[i][rings].size(); walls++){
                    output_file << "\n\t\t\t\t[[";
                    for (int point = 0; point < all_faces[i][rings][walls].size(); point++){
                        output_file << wall_indices[v];
                        v++;
                        ctr3++;
                        if (point == all_faces[i][rings][walls].size()-1){
                            continue;
                        } else {
                            output_file << ",";
                        }
                    }
                    output_file << "]]";
                    if (rings == all_faces[i].size()-1 && walls == all_faces[i][rings].size()-1){
                        continue;
                    } else {
                        output_file <<",";
                    }
                    ctr2++;
                }
                ctr1++;
            }


            output_file << "\t\t\t]],\n"
                           "\t\t\t\"semantics\":{\n"
                           "\t\t\t\t\"surfaces\":[\n"
                           "\t\t\t\t\t{\"type\":\"GroundSurface\"},\n"
                           "\t\t\t\t\t{\"type\":\"RoofSurface\"},\n"
                           "\t\t\t\t\t{\"type\":\"WallSurface\"}\n"
                           "\t\t\t\t],\n"
                           "\t\t\t\t\"values\": [[\n"
                           "\t\t\t\t" << 0 << ",\n"
                                              "\t\t\t\t" << 1 << ",\n";

            for (int n = 0; n < all_faces[i].size(); n++){
                for (int r = 0; r < all_faces[i][n].size(); r++) {
                    output_file << "\t\t\t\t" << 2 ;
                    if (n==all_faces[i].size()-1 && r==all_faces[i][n].size()-1){
                        continue;
                    }
                    else {
                        output_file<<",\n";
                    }
                }
            }

            output_file <<"\t\t\t\t]]\n"
                          "\t\t\t}\n"
                          "\t\t}]\n";

            if (i == features.size()-1){
                output_file << "\t}\n";
            }
            else {
                output_file << "\t},\n";
            }

            t++;
        }
        output_file<<"},";
        output_file<<"\"vertices\": [\n";
        for (const auto& building: all_floor_rings){
            for (const auto& ring: building) {
                for (Point vertex: ring){
                    output_file <<std::setprecision(8)<< "[" << vertex.x << "," <<std::setprecision(9)<< vertex.y << "," <<std::setprecision(5)<< vertex.z << "],\n";
                }
            }
        }
        for (const auto& building: all_roof_rings){
            for (const auto& ring: building) {
                for (Point vertex: ring){
                    output_file <<std::setprecision(8)<< "[" << vertex.x << "," <<std::setprecision(9)<< vertex.y << "," <<std::setprecision(5)<< vertex.z << "],\n";
                }
            }
        }
        for (int each_build = 0; each_build < all_faces.size(); each_build++) {
            for( int each_ring = 0; each_ring < all_faces[each_build].size(); each_ring++){
                for (int each_wall = 0; each_wall < all_faces[each_build][each_ring].size(); each_wall++) {
                    for (int each_point = 0; each_point < all_faces[each_build][each_ring][each_wall].size(); each_point++){
                        Point p_curr = all_faces[each_build][each_ring][each_wall][each_point];
                        if (each_build == all_faces.size() - 1
                            && each_ring == all_faces[each_build].size() - 1
                            && each_wall == all_faces[each_build][each_ring].size() - 1
                            && each_point == all_faces[each_build][each_ring][each_wall].size() - 1) {
                            output_file << std::setprecision(8)<<"[" << p_curr.x << "," <<std::setprecision(9)<< p_curr.y << "," <<std::setprecision(5)<< p_curr.z << "]\n";
                        } else {
                            output_file << std::setprecision(8)<<"[" << p_curr.x << "," <<std::setprecision(9)<< p_curr.y << "," <<std::setprecision(5)<< p_curr.z << "],\n";
                        }
                    }
                }
            }
        }

        output_file << "]\n";
        output_file << "}";

        output_file.close();
    }
    return 0;

}