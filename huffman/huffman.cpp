#include <fstream>
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <cmath>

class node {
private:
    unsigned char frequency;
    unsigned char character;
    bool is_letter_node;
    node* left_child;
    node* right_child;
public:
    node(unsigned char new_frequency, unsigned char new_character):
            frequency(new_frequency),
            character(new_character),
            is_letter_node(true),
            left_child(nullptr),
            right_child(nullptr) {}
    node(unsigned char new_frequency):
            frequency(new_frequency),
            character('_'),
            is_letter_node(false),
            left_child(nullptr),
            right_child(nullptr) {}
    node(node* l_child, node* r_child):
            frequency((l_child -> get_frequency()) + (r_child -> get_frequency())),
            character('_'),
            is_letter_node(false),
            left_child(l_child),
            right_child(r_child) {}
    node():
            frequency(0),
            character('_'),
            is_letter_node(false),
            left_child(nullptr),
            right_child(nullptr) {}
    unsigned char get_frequency() {
        return frequency;
    }
    unsigned char get_character() {
        return character;
    }
    node* get_left_child() {
        return left_child;
    }
    node* get_right_child() {
        return right_child;
    }
    void set_left_child(node* child) {
        left_child = child;
    }
    void set_right_child(node* child) {
        right_child = child;
    }
    bool is_character() {
        return is_letter_node;
    }
    void set_is_character() {
        is_letter_node = true;
    }
    void set_character(unsigned char c) {
        character = c;
    }
    unsigned char find_path(std::map<unsigned char, std::vector<unsigned char>>& paths, std::vector<std::pair<unsigned char, std::vector<unsigned char>>>& codes, std::vector<unsigned char>& path) {
        if (is_letter_node) {
            //std::cout << "NODE of " << (int) character << std::endl;
            if (paths.count(character) > 0) {
                paths[character] = path;
            }
            else {
                paths.insert({character, path});
            }
            codes.push_back({character, path});
            return character;
        }
        //std::cout << "GOT HERE" << std::endl;
        std::vector<unsigned char> left_path(path);
        std::vector<unsigned char> right_path(path);
        left_path.push_back(0);
        right_path.push_back(1);
        /*for (const auto& c: left_path) {
            std::cout << (int) c;
        }
        std::cout << std::endl;
        for (const auto& c: right_path) {
            std::cout << (int) c;
        }
        std::cout << std::endl;*/
        if (left_child)
            left_child -> find_path(paths, codes, left_path);
        if (right_child)
            right_child -> find_path(paths, codes, right_path);
        return 0;
    }

    ~node() {
        if (left_child)
            delete(left_child);
        if (right_child)
            delete(right_child);
    }
    friend std::ostream& operator<< (std::ostream& os, const node& obj);
};
std::ostream& operator<< (std::ostream& os, const node& obj) {
    os << "frequency: " << obj.frequency << " character: " << obj.character << std::endl;
    if (obj.left_child) {
        os << *obj.left_child;
    }
    if (obj.right_child) {
        os << *obj.right_child;
    }
    return os;
}


void print_tree(node* my_node, int level, char lr) {
    for (int i = 0; i < level; ++i) {
       // std::cout << "*";
    }
    if (my_node -> is_character()) {
        //std::cout << lr << " " << my_node->get_character() << std::endl;
    } else {
       // std::cout << lr << " " << std::endl;
    }

    if (my_node -> get_left_child())
        print_tree(my_node -> get_left_child(), level + 1, 'l');
    if (my_node -> get_right_child())
        print_tree(my_node -> get_right_child(), level + 1, 'r');
}

std::pair<unsigned char, bool> find_in_tree(node* my_node, std::vector<char>& path, int i) {
    if (i >= path.size())
        return {0, false};
    if (my_node -> is_character())
        return {my_node -> get_character(), true};
    if (path[i] == 0) {
        return find_in_tree(my_node->get_left_child(), path, i + 1);
    }
    else {
        return find_in_tree(my_node->get_right_child(), path, i + 1);
    }
}

void insert_in_tree(unsigned char let, node* my_node, std::vector<unsigned char>& path, int i) {
    if (i == path.size())
        return;
    node* new_dir;
    if (path[i] == 1) {
        if (my_node -> get_right_child()) {
            new_dir = my_node -> get_right_child();
            //insert_in_tree(let, my_node -> get_right_child(), path, i + 1);
        }
        else {
            my_node -> set_right_child(new node());
            new_dir = my_node -> get_right_child();
            //insert_in_tree(let, my_node -> get_right_child(), path, i + 1);
        }
    } else {
        if (my_node -> get_left_child()) {
            new_dir = my_node -> get_left_child();
            //insert_in_tree(let, my_node -> get_left_child(), path, i + 1);
        }
        else {
            my_node -> set_left_child(new node());
            new_dir = my_node -> get_left_child();
            //insert_in_tree(let, my_node -> get_left_child(), path, i + 1);
        }
    }
    if (i == path.size() - 1) {
        new_dir -> set_character(let);
        new_dir -> set_is_character();
        return;
    }
    insert_in_tree(let, new_dir, path, i + 1);
}


std::pair<std::map<unsigned char, unsigned char>, int> get_map_of_characters(std::string& s, std::uint32_t& total_input) {
    std::map<unsigned char, unsigned char> my_map;
    int number = 0;
    total_input = 0;
    std::ifstream fin(s, std::ios::binary);
    if (!fin.is_open())
        {}//std::cout << "File can not be opened" << std::endl;
    else {
        while(!(fin.eof())) {
            // std::vector<unsigned char> buff;
            unsigned char buff[1];
            buff[0] = 0;
            unsigned char temp;
            fin.read(reinterpret_cast<char*>(buff), 1);
            //std::cout << "have read " << (int)buff[0] << "\n";   /////////////////////////////
            if(fin.eof())
                break;
           // std::cout << "really have read " << (int)buff[0] << "\n";
            ++total_input;
          //  std::cout << "have read2\n";
            temp = buff[0];
            //temp = (unsigned char)(fin.get());
            ++number;
            /*if (temp == '\n')
                continue;*/
            //std::cout << "____" << (unsigned char)temp << " " << temp << std::endl;
            if (my_map.find(temp) != my_map.end()) {
                ++my_map[temp];
            }
            else {
                my_map.insert({temp, 1});
            }
        }
    }
    fin.close();

   // std::cout << "have read3\n";
    return {my_map, number};
}
std::vector<std::pair<unsigned char, std::vector<unsigned char>>> get_vector_from_map_of_paths(std::map<unsigned char, std::vector<unsigned char>> my_map) {
    std::vector<std::pair<unsigned char, std::vector<unsigned char>>> result;
    for (const auto& e: my_map) {
        result.push_back(e);
    }
    return result;
}
std::vector<std::pair<unsigned char, unsigned char>> get_vector_from_map(const std::map<unsigned char, unsigned char>& my_map) {
    std::vector<std::pair<unsigned char, unsigned char>> result;
    for (const auto& my_pair: my_map) {
        result.push_back({my_pair.first, my_pair.second});
    }
    return result;
}
void sort_vector_of_pairs(std::vector<std::pair<unsigned char, unsigned char>>& my_vector) {
    std::stable_sort(my_vector.begin(), my_vector.end(), [](const std::pair<unsigned char, unsigned char>& lhs, const std::pair<unsigned char, unsigned char>& rhs) {
                         return lhs.second < rhs.second;
                     }
    );
}
struct LessThanByFrequency {
    bool operator()(node* lhs, node* rhs) const {
        return (lhs -> get_frequency()) >= (rhs -> get_frequency());
    }
};

struct LessThanByFrequency1 {
    bool operator()(const std::pair<unsigned char, unsigned char>& lhs, const std::pair<unsigned char, unsigned char>& rhs) const {
        return lhs.second > rhs.second;
    }
};
unsigned char get_byte(std::vector<unsigned char> arr) {
    unsigned char res = 0;
    for (int i = 0; i < arr.size(); ++i) {
        res += (arr[arr.size() - 1 - i]) ? (pow(2, i)) : (0);
    }
    return res;
}
void write_to_file_binary(std::string f_in_path, std::string& f_out_path, std::vector<std::pair<unsigned char, std::vector<unsigned char>>>& codes, int number_of_ch, std::uint32_t& total_aux, std::uint32_t& total_coded) {
    std::ofstream fout(f_out_path, std::ios::binary);
    std::ifstream fin(f_in_path, std::ios::binary);
    std::map<unsigned char, std::vector<unsigned char>> my_map;
    for (const auto& e: codes) {
        my_map.insert(e);
    }
    if (!fin.is_open() || !fout.is_open()){
    } else {
        fout << (std::uint32_t)number_of_ch << '\n';
        fout << (std::uint32_t)codes.size() << '\n';
        for (const auto& e: codes) {
            fout << (unsigned char) e.first << ' ';
            for (const auto& c: e.second) {
                fout << (unsigned char)c;
            }
            fout << '\n';
        }
        std::vector<unsigned char> buffer(8,8);
        int ptr = -1;
        total_aux = fout.tellp();
        while (!fin.eof()) {
            unsigned char buf[1];
            buf[0] = 0;
            fin.read(reinterpret_cast<char*>(buf), 1);
            if (fin.eof())
                break;
            if (my_map.find(buf[0]) == my_map.end())
                std::cout << "ALERT! ALERT!\n\n\n\n\nALERT\n";
            std::vector<unsigned char> temp = my_map[buf[0]];
            //std::cout << (int)buf[0] << " ";
            for (const auto& e: temp) {
              // std::cout << (int) e << "_";
            }
            //std::cout << std::endl;      /////problems with 1-symbol file
            /////// 9*0 file problems
            for (int i = 0; i < temp.size(); ++i) {
                ++ptr;
                if (ptr == 7) {
                    buffer[ptr % 8] = temp[i];
                    ptr = -1;
                    fout << (unsigned char)get_byte(buffer);
                    for (int i = 0; i < buffer.size(); ++i) {
                        buffer[i] = 8;
                    }
                } else {
                    buffer[ptr] = temp[i];
                }
                for (const auto& e: buffer) {
                  //  std::cout << (int)e;
                }
                //std::cout << " and after thatcurrent position is: " << ptr << std::endl;
            }
        }
        if (ptr >= 0) {
            for (int i = ptr + 1; i < buffer.size(); ++i)
                buffer[i] = 0;
           // std::cout << "got to extra point!!\n";
            fout << (unsigned char) get_byte(buffer);
        }
    }
    total_coded = fout.tellp();
    total_coded -= total_aux;
    fin.close();
    fout.close();
  //  std::cout << "written  succesfully\n";
}

std::vector<unsigned char> get_vector_from_int(unsigned char c) {
    std::vector<unsigned char> res(8,0);
    if (c == 0) {
        res.push_back(0);
        return res;
    }
    int j = 1;
    while (c > 0) {
        res[8 - j] = c % 2;
        c = c / 2;
        ++j;
    }
    return res;
}

void print_paths_v(node* root, std::vector<int> path1) {

    if (root -> is_character()) {
        std::cout << (char) root -> get_character() << ":: ";
        for (const auto& e: path1) {
            std::cout << e;
        }
        std::cout << std::endl;
        return;
    }
    if (root -> get_left_child()) {
        std::vector<int> path(path1);
        path.push_back(0);
        print_paths_v(root -> get_left_child(), path);
    }
    if (root -> get_right_child()) {
        std::vector<int> path(path1);
        path.push_back(1);
        print_paths_v(root -> get_right_child(), path);
    }
}

void print_path(node* my_node, node* root, std::string path1) {
    if (root == my_node) {
        std::cout << (int) root -> get_character() << ": " << path1 << std::endl;
        return;
    }
    if (root -> get_left_child()) {
        std::string path(path1);
        path += "0";
        print_path(my_node, root -> get_left_child(), path);
    }
    if (root -> get_right_child()) {
        std::string path(path1);
        path += "1";
        print_path(my_node, root -> get_right_child(), path);
    }
}
void print_one_path(node* my_node, node* root) {
    std::string paths = "";
    print_path(my_node, root, paths);
}

void print_paths(node* root, std::string path1) {
    if (root -> is_character()) {
        std::cout << (int) root -> get_character() << ": " << path1 << std::endl;
        return;
    }
    if (root -> get_left_child()) {
        std::string path(path1);
        path += "0";
        print_paths(root -> get_left_child(), path);
    }
    if (root -> get_right_child()) {
        std::string path(path1);
        path += "1";
        print_paths(root -> get_right_child(), path);
    }
}
void print_me(node* root) {
    std::string paths = "";
    print_paths(root, paths);
}
void print_me_v(node* root) {
    std::vector<int> p;
    print_paths_v(root, p);
}


std::pair<node*, bool> find_in_tree_one_step(node* my_node, unsigned char step) {
    if (my_node -> is_character())
        return {my_node, true};
    node* new_node = nullptr;
    if (((int)step) == 1) {
        new_node = my_node -> get_right_child();
    } else {
        new_node = my_node -> get_left_child();
    }
    return {new_node, false};
}
void empty_file(std::string& path) {
    std::ofstream fout(path, std::ios::binary);
    fout.close();
}
void print_sorted_codes(std::vector<std::pair<unsigned char, std::vector<unsigned char>>>& codes) {
    for (const auto& pair: codes) {
        for (const auto& e: pair.second) {
            std::cout << (int)e;
        }
        std::cout << " " << (int)pair.first << std::endl;;
    }
}
void read_file_to_console(std::string& s) {
    std::ifstream fin(s);
    std::cout << s << " file is:\n";
    while(!fin.eof()) {
        unsigned char buf[1];
        fin.read(reinterpret_cast<char*>(buf), 1);
        unsigned char c = buf[0];
        if(fin.eof())
            break;
        if ((c == '\n') || (c == ' '))
            std::cout << (char) c;
        else {
            std::cout << (int) c;
            }
    }
    std::cout << "\n end of file!\n";
}
std::uint32_t huffman_decode(std::string &f_in_path, std::string &f_out_path, bool flag_v) {
    std::uint32_t total_input = 0;
    std::uint32_t total_aux = 0;
    std::uint32_t total_coded = 0;
    std::ifstream fin(f_in_path, std::ios::binary);
    std::ofstream fout(f_out_path, std::ios::binary);
    std::map<unsigned char, std::vector<unsigned char>> codes;
    node* root_of_tree = new node();
    std::uint32_t number = 0;
    unsigned char lit = 0;
    std::uint32_t number_of_ch = 0;
    if (!fin.is_open()) {
    } else {
        unsigned char buf[1];
        fin >> number_of_ch;
        fin.read(reinterpret_cast<char*>(buf), 1);
        if (!fin.eof()) {
            fin >> number;
            fin.read(reinterpret_cast<char*>(buf), 1);
            for (int i = 0; i < number; ++i) {
                std::vector<unsigned char> path;
                fin.read(reinterpret_cast<char*>(buf), 1);
                lit = buf[0];
                fin.read(reinterpret_cast<char*>(buf), 1);
                unsigned char curr = 0;
                int counter = 0;
                while ((curr != '\n') && (counter < 100)) {
                    fin.read(reinterpret_cast<char*>(buf), 1);
                    if (buf[0] != '\n')
                        path.push_back(buf[0]);
                    curr = buf[0];
                    ++counter;
                }
                codes.insert({lit, path});
                insert_in_tree(lit, root_of_tree, path, 0);
            }
            total_aux = fin.tellg();
        }
    }
    node* root = root_of_tree;
    int i = 0;
    int count = 0;
    while (!fin.eof() && (count < number_of_ch)) {
        unsigned char buf[1];
        unsigned char c = 0;
        fin.read(reinterpret_cast<char*>(buf), 1);
        if (!fin.eof()) {
            c = buf[0];
            auto vector_form_of_ch = get_vector_from_int(c);
            for (int j = 0; j < 8; ++j) {
                node* child = nullptr;
                if (vector_form_of_ch[j] == 0) {
                    if (root -> get_left_child()) {
                        root = root -> get_left_child();
                    }
                }
                else {
                    if (root -> get_right_child()) {
                        root = root -> get_right_child();
                    }
                }
                if (root -> is_character()) {
                    fout << (char) root -> get_character();
                    root = root_of_tree;
                    ++count;
                    if (count >= number_of_ch)
                        break;
                }
            }
        }
        total_input = fin.tellg();
    }
    total_coded = fout.tellp();
    total_input -= total_aux;
    fin.close();
    fout.close();
    std::vector<std::pair<unsigned char, std::vector<unsigned char>>> sorted_codes;
    std::map<unsigned char, std::vector<unsigned char>> paths;
    std::vector<unsigned char> path;
    node* temp_node = root_of_tree;
    if (total_input != 0) {  
        if (temp_node) {
            if (number_of_ch != 0) {
                temp_node -> find_path(paths, sorted_codes, path);
            } else {
                unsigned char letter = temp_node -> get_character();
                paths.insert({letter, {0}});
                sorted_codes.push_back({letter, {0}});
            }
        }
    }
    delete root_of_tree;
    std::cout << total_input << std::endl;
    std::cout << total_coded << std::endl;
    std::cout << total_aux << std::endl;
    if (flag_v) {
        print_sorted_codes(sorted_codes);
    }
    return number_of_ch;
}

node* get_tree_of_characters(std::string& fin_path, int& number_of_ch, bool& flag, std::uint32_t& total_input) {
    std::ifstream fin(fin_path, std::ios::binary);
    auto map_of_ch = get_map_of_characters(fin_path, total_input);
    auto my_map = map_of_ch.first;
    number_of_ch = map_of_ch.second;
    auto vector_map = get_vector_from_map(my_map);
    std::priority_queue<node*, std::vector<node*>, LessThanByFrequency> pq;
    for (const auto& e: vector_map) {
        //std::cout << (unsigned int) e.first << " " << e.second << std::endl;
        pq.push((new node(e.second, e.first)));
    }
    //std::cout << "here: " << pq.size() <<  "\n";
    flag = false;
    if (pq.size() == 1)
        flag = true;
    while (pq.size() > 1) {
        auto p1 = pq.top();
        pq.pop();
        auto p2 = pq.top();
        pq.pop();
        auto n = new node(p1, p2);
        pq.push(n);
    }
    if (pq.empty()) {
        return nullptr;
    }
    node* res = pq.top();
    fin.close();
    return res;
}

std::vector<std::pair<unsigned char, std::vector<unsigned char>>> get_sorted_codes(std::string& fin_path, int& number_of_ch, bool& flag, std::uint32_t& total_input) {
    std::vector<std::pair<unsigned char, std::vector<unsigned char>>> sorted_codes;
    node* res = get_tree_of_characters(fin_path, number_of_ch, flag, total_input);
    std::map<unsigned char, std::vector<unsigned char>> paths;
    std::vector<unsigned char> path;
    if (res) {
        if (!flag) {
            res -> find_path(paths, sorted_codes, path);
        } else {
            unsigned char letter = res->get_character();
            paths.insert({letter, {0}});
            sorted_codes.push_back({letter, {0}});
        }
        delete res;
        return sorted_codes;
    }
    return sorted_codes;
}
void huffman(std::string& fin_path, std::string& fout_path, bool flag_v) {
    std::ifstream fin(fin_path, std::ios::binary);
    std::ofstream fout(fout_path, std::ios::binary);
    int number_of_ch = 0;
    bool flag = false;
    std::uint32_t total_input = 0;
    std::uint32_t total_aux = 0;
    std::uint32_t total_coded = 0;
    std::vector<std::pair<unsigned char, std::vector<unsigned char>>> sorted_codes  = get_sorted_codes(fin_path, number_of_ch, flag, total_input);
    if (!sorted_codes.empty()) {
        write_to_file_binary(fin_path, fout_path, sorted_codes, number_of_ch, total_aux, total_coded);
    }
    std::cout << total_input << std::endl;
    std::cout << total_coded << std::endl;
    std::cout << total_aux << std::endl;
    if (flag_v) {
        print_sorted_codes(sorted_codes);
    }
    fin.close();
    fout.close();
}
void run_coding_or_decoding(std::string& path1, std::string& path2, bool f_v, bool f_c_d) {
    if (f_c_d) {
        huffman(path1, path2, f_v);
    } else {
        huffman_decode(path1, path2, f_v);
    }
}/*
int main(int argc, char* argv[]) {
    setlocale(0,"");
    std::vector<std::string> my_argv(argc);
    for (int i = 0; i < argc; ++i) {
        my_argv[i] = std::string(argv[i]);
    }
    if ((argc < 4) || ((argc == 5) && (my_argv[1] != "-v"))) {
        std::cout << "wrong args" << std::endl;
        return 0;
    }
    bool flag_v = (argc == 5) ? (my_argv[1] == "-v") : (false);
    bool flag_c_d = (argc == 5) ? (my_argv[2] == "-c") : (my_argv[1] == "-c");
    run_coding_or_decoding(my_argv[argc - 2], my_argv[argc - 1], flag_v, flag_c_d);
    return 0;
}*/




