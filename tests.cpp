#ifndef CATCH_CONFIG_MAIN
#   define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"
#include <string>
#include <sstream>
#include "record.h"
#include "record.cpp"

//test to see if adding tracks from file works or not
TEST_CASE("addTracksFromFile adds tracks to record") {
    Record record;
    record.addTracksFromFile("songs.txt");
    vector<Track> tracks = record.searchByArtistName("Joy Division");
    REQUIRE(tracks.size() == 66);
    REQUIRE(tracks[0].title == "Decades (2007 Remaster)");
    REQUIRE(tracks[1].title == "At A Later Date (Live)");
}


//test to see if search by artist name gives valid output or not
TEST_CASE("searchByArtistName finds tracks by artist name") {
    Record record;
    record.addTracksFromFile("songs.txt");
    vector<Track> tracks = record.searchByArtistName("Destruction");
    REQUIRE(tracks.size() == 5);
    REQUIRE(tracks[0].title == "Total Desaster");
}

TEST_CASE("saveTracksToFile saves all tracks in record") {
    Record record;
    record.addTracksFromFile("songs.txt");
    record.saveTracksToFile("test_output.txt");
    std::ifstream infile("test_output.txt");
    std::stringstream buffer;
    std::string line1;
    getline(infile, line1);
    buffer << infile.rdbuf();
    std::string file_contents = buffer.str();
    infile.close();
    REQUIRE(line1 == "Decades (2007 Remaster)      Joy Division    374");
    
}

//test to see if track gets remove from the file or not
TEST_CASE("removeTrack removes track from record") {
    Record record;
    record.addTracksFromFile("songs.txt");
    record.removeTrack("Decades (2007 Remaster)", "Joy Division");
    vector<Track> tracks = record.searchByArtistName("Joy Division");
    REQUIRE(tracks.size() == 65);
    REQUIRE(tracks[0].title == "At A Later Date (Live)");
}
