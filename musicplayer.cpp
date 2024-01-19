#include "record.h"


using namespace std;

int main() {
    Record record;
    string filename;
    cout << "Enter file name from where you want to load files from : ";
    cin >> filename;
    record.addTracksFromFile(filename);
    int choice;
    do {
        cout << endl;
        cout << " ---------------------------------------- " << endl;
        cout << "|                                        |" << endl;
        cout << "|        Welcome to Audio Player         |" << endl;
        cout << "|                                        |" << endl;
        cout << " ---------------------------------------- " << endl;
        cout << "1. Add tracks from file" << endl << "2. Save tracks to file" << endl << "3. Search by artist" << endl << "4. Remove track" << endl << "5. Exit" << endl << "Enter your choice :";
        cin >> choice;
        switch (choice) {
            case 1: {
                cout << "Enter file name from where you want to add tracks: ";
                cin >> filename;
                record.addTracksFromFile(filename);
                cout << "Tracks added from " << filename << " added successfully!" << endl;
                break;
            }
            case 2: {
                cout << "Enter file name where you want to save the tracks: ";
                cin >> filename;
                record.saveTracksToFile(filename);
                cout << "Tracks saved to file " << filename << " successfully!" << endl;
                break;
            }
            case 3: {
                string artist;
                cout << "Enter artist name: ";
                cin >> artist;
                vector<Track> tracks = record.searchByArtistName(artist);
                if (tracks.empty()) {
                    cout << "Did you try adding tracks from the file using option 1?" << endl;
                    cout << "No tracks found for artist: " << artist << endl;
                } else {
                    cout << "Tracks for artist: " << artist << endl;
                    int a = 1;
                    for(Track i : tracks){
                        cout << a << ". ";
                        cout << i.title << "\t" << i.duration << endl;
                    }
                }
                break;
            }
            case 4: {
                cout << "Enter title: ";
                string title;
                cin >> title;
                cout << "Enter artist: ";
                string artist;
                cin >> artist;
                record.removeTrack(title, artist);
                break;
            }
            case 5: {
                cout << "Exiting the program..." << endl;
                break;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    } while (choice != 5);

    return 0;
}