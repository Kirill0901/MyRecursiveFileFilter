#include <iostream>
#include <regex>
#include <vector>
#include <filesystem>

using namespace std::filesystem;

int main(int argc, char **argv){
    path target_directory("/mnt/d/PrevPC/Desktop/Task/Files/directory");
    int depth = 0;
    std::cin >> depth;

    std::string filter = "^(.)*\.cpp$";

    std::vector<std::pair<path, int>> path_stack = {{target_directory, 0}};
    std::unordered_map<std::string, bool> visited;

    auto pattern = std::regex(filter);

    if (!exists(target_directory) 
        || (!is_directory(target_directory) && !is_block_file(target_directory))){
        std::cout << "Directory not found." << "\n"; 
        return 0;
    }

    while (!path_stack.empty()){
        path cur_dir = path_stack.back().first;
        int cur_depth = path_stack.back().second;
        path_stack.pop_back();

        if (cur_depth == depth + 1){
            continue;
        }

        std::string path_to_cur_dir = "";

        for (auto entry: directory_iterator(cur_dir)) {
            path_to_cur_dir = entry.path().parent_path().string();

            if (visited[path_to_cur_dir]){
                break;
            }

            if (is_directory(entry)){
                path_stack.push_back({entry, cur_depth + 1});
                continue;
            }

            if (is_regular_file(entry) && std::regex_match(entry.path().filename().string(), pattern)){
                std::cout << "file: " << entry << "\n" <<
                "size: " << file_size(entry) << " bytes" << "\n\n";
            }
        }

        visited[path_to_cur_dir] = true;
    }

}
