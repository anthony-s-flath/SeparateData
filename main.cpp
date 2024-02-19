#include <iostream>
#include <filesystem>
#include <cstdlib>


using std::cout, std::endl, std::string;

int main(int argc, char** argv) {
    if (argc != 5) {
        cout << "Usage: .exe <percentage of training data as decimal> <text directory> <designated test directory> <designated train directory> " << endl;
        return -1;
    }

    double split = atof(argv[1]);
    if (split <= 0) {
        cout << "Percentage of training data is 0 or less." << endl;
        split = 0;
    } else if (split >= 1) {
        cout << "Percentage of training data is 100 or more." << endl;
        split = 1;
    }

    string split_dir = argv[2];
    string test_dir = argv[3];
    string train_dir = argv[4];

    cout << "Split: " << split << endl;
    cout << "Split directory: " << split_dir << endl;
    cout << "Test directory: " << test_dir << endl;
    cout << "Train directory: " << train_dir << endl;
    
    
    std::filesystem::create_directory(train_dir);
    std::filesystem::create_directory(test_dir);

    double total = 0;
    double train = 0;
    double test = 0;
    for (auto &f : std::filesystem::recursive_directory_iterator(split_dir)) {
        string path = f.path().string();
        path = path.substr(path.find_first_of('/') + 1);

        if (f.is_directory()) {
            std::filesystem::create_directory(train_dir + '/' + path);
            std::filesystem::create_directory(test_dir + '/' + path);
            continue;
        }

        double random = (std::rand() % 100) / 100.0;
        if (random < split) {
            // training
            std::filesystem::copy_file(f.path(), train_dir + '/' + path);
            ++train;
        } else {
            // test
            std::filesystem::copy_file(f.path(), test_dir + '/' + path);
            ++test;
        }
        ++total;
    }
 
    cout << "Total files: " << total << endl;
    cout << "Total train files: " << train << endl;
    cout << "Total test files: " << test << endl;
    cout << "Percentage train files: " << train / total << endl;

    return 0;
}
