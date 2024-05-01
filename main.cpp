#include <iostream>
#include <dirent.h>
#include <string>
#include <iomanip>
#include <sys/stat.h>

using namespace std;

int main() {
string directory_path;

while (true) {
    cout << ":";
    getline(cin, directory_path);

    DIR* dir = opendir(directory_path.c_str());
    if (dir == NULL) {
        cerr << "Error: Unable to open directory." << endl;
        continue;}

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        string file_name(entry->d_name);        
        if (file_name == "." || file_name == "..") 
            continue;
        string full_path = directory_path + "/" + file_name;

        struct stat file_stat;
        stat(full_path.c_str(), &file_stat);

        if (S_ISDIR(file_stat.st_mode)) // if folder:
            cout << std::setw(15) <<  file_name << "/" << endl; 
        else {                          // if file:
            // Round up to nearest 4KB block
            long file_size_kb = (file_stat.st_size + 4095) / 1024; 

            cout << std::setw(16) << file_name.substr(0, 16)
                << " | " << file_size_kb << " KB" << endl;
        }
    }
    closedir(dir);
}
return 0;
}
