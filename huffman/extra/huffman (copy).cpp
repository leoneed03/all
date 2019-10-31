#include "huffman.hpp"


node::node(unsigned char new_frequency, unsigned char new_character):
            frequency(new_frequency),
            character(new_character),
            is_letter_node(true),
            left_child(nullptr),
            right_child(nullptr) {}
node::node(unsigned char new_frequency):
            frequency(new_frequency),
            character('_'),
            is_letter_node(false),
            left_child(nullptr),
            right_child(nullptr) {}
node::node(node* l_child, node* r_child):
            frequency((l_child -> get_frequency()) + (r_child -> get_frequency())),
            character('_'),
            is_letter_node(false),
            left_child(l_child),
            right_child(r_child) {}
node::node():
            frequency(0),
            character('_'),
            is_letter_node(false),
            left_child(nullptr),
            right_child(nullptr) {}
    unsigned char node::get_frequency() {
        return frequency;
    }
    unsigned char node::get_character() {
        return character;
    }
    node* node::get_left_child() {
        return left_child;
    }
    node* node::get_right_child() {
        return right_child;
    }
    void node::set_left_child(node* child) {
        left_child = child;
    }
    void node::set_right_child(node* child) {
        right_child = child;
    }
    bool node::is_character() {
        return is_letter_node;
    }
    void node::set_is_character() {
        is_letter_node = true;
    }
    void node::set_character(unsigned char c) {
        character = c;
    }
    unsigned char node::find_path(std::map<unsigned char, std::vector<unsigned char>>& paths, std::vector<std::pair<unsigned char, std::vector<unsigned char>>>& codes, std::vector<unsigned char>& path) {
        if (is_letter_node) {
            if (paths.count(character) > 0) {
                paths[character] = path;
            }
            else {
                paths.insert({character, path});
            }
            codes.push_back({character, path});
            return character;
        }
        std::vector<unsigned char> left_path(path);
        std::vector<unsigned char> right_path(path);
        left_path.push_back(0);
        right_path.push_back(1);left_child -> find_path(paths, codes, left_path);
        right_child -> find_path(paths, codes, right_path);
        return 0;
    }

    node::~node() {
        if (left_child)
            delete(left_child);
        if (right_child)
            delete(right_child);
    }

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
        std::cout << "*";
    }
    if (my_node -> is_character()) {
        std::cout << lr << " " << my_node->get_character() << std::endl;
    } else {
        std::cout << lr << " " << std::endl;
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
             }
        else {
            my_node -> set_right_child(new node());
            new_dir = my_node -> get_right_child();
            }
    } else {
        if (my_node -> get_left_child()) {
            new_dir = my_node -> get_left_child();
            }
        else {
            my_node -> set_left_child(new node());
            new_dir = my_node -> get_left_child();
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
        std::cout << "File can not be opened" << std::endl;
    else {
        while(!(fin.eof())) {
            unsigned char buff[1];
            buff[0] = 0;
            unsigned char temp;
            fin.read(reinterpret_cast<char*>(buff), 1);
            if(fin.eof())
                break;
            ++total_input;
            temp = buff[0];
            ++number;
            if (my_map.find(temp) != my_map.end()) {
                ++my_map[temp];
            }
            else {
                my_map.insert({temp, 1});
            }
        }
    }
    fin.close();
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
        return (lhs -> get_frequency()) > (rhs -> get_frequency());
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
void write_to_file_binary(std::string f_in_path, std::string& f_out_path, std::vector<std::pair<unsigned char, std::vector<unsigned char>>>& codes, int number_of_ch, std::uint32_t& total_input, std::uint32_t& total_aux, std::uint32_t& total_coded) {
    std::ofstream fout(f_out_path, std::ios::binary);
    std::ifstream fin(f_in_path, std::ios::binary);
    std::map<unsigned char, std::vector<unsigned char>> my_map;
    for (const auto& e: codes) {
        my_map.insert(e);
    }
    if (!fin.is_open() || !fout.is_open())
        std::cout << "File can not be opened" << std::endl;
    else {
        fout << number_of_ch << '\n';
        fout << (unsigned char)codes.size() << '\n';
        for (const auto& e: codes) {
            fout << (unsigned char) e.first << ' ';
            for (const auto& c: e.second) {
                fout << (unsigned char)c;
            }
            fout << '\n';
        }
        std::vector<unsigned char> buffer(8,0);
        int ptr = -1;
        while (!fin.eof()) {
            unsigned char buf[1];
            buf[0] = 0;
            fin.read(reinterpret_cast<char*>(buf), 1);
            if (fin.eof())
                break;
            std::vector<unsigned char> temp(8,0);
            std::cout << "   ";
            std::cout << std::endl;
            for (int i = 0; i < temp.size(); ++i) {
                ++ptr;
                if (ptr == 8) {
                    ptr = 0;
                    fout << (unsigned char)get_byte(buffer);
                }
                buffer[ptr] = temp[i];
            }
        }
        if (ptr > 0) {
            for (int i = ptr + 1; i < buffer.size(); ++i)
                buffer[i] = 0;
            fout << (unsigned char) get_byte(buffer);
        }

    }
    fin.close();
    fout.close();
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
//print from here

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

////delete till here


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
std::uint32_t huffman_decode(std::string &f_in_path, std::string &f_out_path) {

    std::ifstream fin(f_in_path, std::ios::binary);
    std::ofstream fout(f_out_path, std::ios::binary);
    std::map<unsigned char, std::vector<unsigned char>> codes;
    node* root_of_tree = new node();
    unsigned char number = 0;
    unsigned char lit;
    std::uint32_t number_of_ch = 0;
    if (!fin.is_open())
        std::cout << "File can not be opened" << std::endl;
    else {
        unsigned char buf[1];
        fin >> number_of_ch;
        fin.read(reinterpret_cast<char*>(buf), 1);
        std::cout << "Number of characters is:" << (long)number_of_ch << std::endl;
        fin.read(reinterpret_cast<char*>(buf), 1);
        number = buf[0];
        std::cout << "Number is " << (int)number << std::endl;

        fin.read(reinterpret_cast<char*>(buf), 1);
        std::cout << "Number is " << (int)number << std::endl;
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
    }
    node* root = root_of_tree;
    std::cout << "PRINTING TREE" << std::endl;
    print_me(root_of_tree);
    int i = 0;
    int count = 0;
    while (!fin.eof() && (count < number_of_ch)) {
        unsigned char buf[1];
        unsigned char c;
        fin.read(reinterpret_cast<char*>(buf), 1);
        c = buf[0];
        std::cout << (int) c << " ";

        auto vector_form_of_ch = get_vector_from_int(c);

        for (const auto& e: vector_form_of_ch) {
            std::cout << (int)e;
        }
        std::cout << std::endl;

        for (int j = 0; j < 8; ++j) {
            node* child;
            if (vector_form_of_ch[j] == 0)
                root = root -> get_left_child();
            else root = root -> get_right_child();

            if (root -> is_character()) {
                std::cout << "number "  << count << " current letter is " <<(char) root -> get_character() << " path to it is: ";
                print_one_path(root, root_of_tree);
                fout << (char) root -> get_character();
                root = root_of_tree;
                ++count;
                if (count >= number_of_ch)
                    break;
            }
        }
    }
    fin.close();
    fout.close();
    delete root_of_tree;
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
    std::cout << "here: " << pq.size() <<  "\n";
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
    std::cout << "popped\n" << "\n";
    std::cout << "got element?\n" << "\n";
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
            res->find_path(paths, sorted_codes, path);
        } else {
            unsigned char letter = res->get_character();
            paths.insert({letter, {0}});
            sorted_codes.push_back({letter, {0}});
        }
        return sorted_codes;
    }
    return sorted_codes;
}

void huffman(std::string& fin_path, std::string& fout_path, bool v, bool cd) {
    std::ifstream fin(fin_path, std::ios::binary);
    std::ofstream fout(fout_path, std::ios::binary);
    int number_of_ch = 0;
    bool flag = false;
    std::uint32_t total_input = 0;
    std::uint32_t total_aux = 0;
    std::uint32_t total_coded = 0;
    std::vector<std::pair<unsigned char, std::vector<unsigned char>>> sorted_codes  = get_sorted_codes(fin_path, number_of_ch, flag, total_input);
    if (!sorted_codes.empty()) {
        write_to_file_binary(fin_path, fout_path, sorted_codes, number_of_ch, total_input, total_aux, total_coded);
    }
    fin.close();
    fout.close();
}

int main() {
    setlocale(0,"");
    std::string path1 = "input.txt";
    std::string path_res = "binary.bin";
    /*int number_of_ch = 0;
    bool flag = false;
    std::vector<std::pair<unsigned char, std::vector<unsigned char>>> sorted_codes  = get_sorted_codes(path1, number_of_ch, flag);
    */
    huffman(path1, path_res, true, true);

/*
    std::cout << std::endl;
    std::vector<unsigned char> v = {0,1,0,0,0};
    std::cout << get_byte(v) << std::endl;
    std::cout << "==========================";*/
   /////// write_to_file_binary(path_input, path_res, sorted_codes, number_of_ch);
    /*
    std::cout << std::endl;
    std::cout << (int)get_byte(v);*/

    std::string path_out_result = "output.txt";
    huffman_decode(path_res, path_out_result);
    /*
    std::cout << "TEST TREE ==================\n";
    node* new_node = new node();
    std::vector<unsigned char> path_ex1 = {0,1,1,0};
    insert_in_tree('a', new_node, path_ex1, 0);
    std::vector<unsigned char> path_ex2 = {1,1,1,1};
    insert_in_tree('b', new_node, path_ex2, 0);
    std::vector<unsigned char> path_ex3 = {1,1,0,1};
    insert_in_tree('c', new_node, path_ex3, 0);*/
    //////////////delete res;
    //delete new_node;
   /* int a = 13;
    auto r = get_vector_from_int(a);
    for (const auto& e: r) {
        std::cout << (int) e;
    }
    std::ifstream ifs(path3, std::ios::binary);
    std::cout << "Revert " << (int)get_byte(r) << std::endl;*/
    return 0;
}




