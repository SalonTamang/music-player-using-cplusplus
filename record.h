#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

//defining the structure for each track in text file.
struct Track {
    string title;
    string artist;
    int duration;

    Track() {}

    Track(string t, string a, int d) {
        title = t;
        artist = a;
        duration = d;
    }
};

class Record {
    private:
        unordered_map<string, vector<Track>> tracksByArtist;
        vector<Track> allTracks;
    public:
        void addTracksFromFile(string filename);
        void saveTracksToFile(string filename);
        vector<Track> searchByArtistName(string artist);
        void removeTrack(string title, string artist);
};

#endif // RECORD_H