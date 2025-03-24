#include <iostream>
#include <regex>
#include <filesystem>

using namespace std::filesystem;

int main(int argc, char **argv){
    path target_directory("/mnt/d/PrevPC/Desktop/Task/Files/directory");
    int depth = 0;
    std::cin >> depth;

    std::string filter = "^(.)*\.cpp$";

    auto pattern = std::regex(filter);


    if (exists(target_directory) 
        && is_directory(target_directory)) { 
        for (auto file_ptr = recursive_directory_iterator(target_directory);
        file_ptr != recursive_directory_iterator(); ++file_ptr) {
            
            path entry = *file_ptr;

            if (file_ptr.depth() == depth && is_directory(entry)){
                file_ptr.disable_recursion_pending();
                continue;
            }

            if (is_regular_file(entry) && std::regex_match(std::string(entry.filename()), pattern)){
                std::cout << "file: " << entry << "\n" <<
                "size: " << file_size(entry) << " bytes" << "\n\n";
            }
        } 
    } 
    else { 
        std::cout << "Directory not found." << "\n"; 
    }
}
