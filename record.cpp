#include <fstream>
#include <sstream>
#include <string>
#include "record.h"
#include <iostream>
#include <algorithm>

//prompting the user filename and adding the tracks from the given file
void Record::addTracksFromFile(string filename) {
    ifstream infile(filename);
    string line;
    while (getline(infile, line)) {
        vector<string> tokens;
        size_t pos = 0;
        //using tabs as delimiter
        string delimiter = "\t";
        while ((pos = line.find(delimiter)) != string::npos) {
            string token = line.substr(0, pos);
            tokens.push_back(token);
            line.erase(0, pos + delimiter.length());
        }
        //using vectors to store individual items i.e title, artist and album after seperating by tabs
        tokens.push_back(line);
        if (tokens.size() == 3) {
            string title = tokens[0];
            string artist = tokens[1];
            int duration = stoi(tokens[2]);
            Track track(title, artist, duration);
            if (tracksByArtist.find(artist) == tracksByArtist.end()) {
                vector<Track> tracks;
                tracks.push_back(track);
                tracksByArtist[artist] = tracks;
            } else {
                vector<Track>& tracks = tracksByArtist[artist];
                auto it = find_if(tracks.begin(), tracks.end(), [&title](const Track& t) {
                    return t.title == title;
                });
                if (it == tracks.end()) {
                    tracks.push_back(track);
                }
            }
            auto it = find_if(allTracks.begin(), allTracks.end(), [&title, &artist](const Track& t) {
                return t.title == title && t.artist == artist;
            });
            if (it == allTracks.end()) {
                allTracks.push_back(track);
            }
        }
    }
    
    infile.close();
}
//save track function
void Record::saveTracksToFile(string filename) {
    ofstream outfile(filename);
    for (const Track& track : allTracks) {
        outfile << track.title << "\t" << track.artist << "\t" << track.duration << endl;
    }
    outfile.close();
}
//searching the track by using artist name
vector<Track> Record::searchByArtistName(string artist) {
    vector<Track> results;
    if(tracksByArtist.size() == 0){
        return results;
    } else {    
        auto it = tracksByArtist.find(artist);
        if (it != tracksByArtist.end()) {
            results = it->second;
        }
        return results;
    }
}

//removing track from the file using title and artist
void Record::removeTrack(string title, string artist) {
    auto it = find_if(allTracks.begin(), allTracks.end(), [&title, &artist](const Track& t) {
        return t.title == title && t.artist == artist;
    });
    if (it != allTracks.end()) {
        allTracks.erase(it);
        vector<Track>& tracks = tracksByArtist[artist];
        it = find_if(tracks.begin(), tracks.end(), [&title](const Track& t) {
            return t.title == title;
        });
        if (it != tracks.end()) {
            tracks.erase(it);
        }
    }
}