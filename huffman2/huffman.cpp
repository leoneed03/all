#include "huffman.hpp"

template <class T> using character_and_codes =
    std::vector<std::pair<T, std::vector<T>>>;
template <class T> using priority_queue_of_nodes =
    std::priority_queue<T, std::vector<T>, less_than_by_frequency>;
Node::Node(std::uint32_t new_frequency, unsigned char new_character):
        frequency(new_frequency),
        character(new_character),
        is_letter_node(true),
        left_child(nullptr),
        right_child(nullptr) {}
Node::Node(Node* l_child, Node* r_child):
        frequency((l_child -> get_frequency()) + (r_child -> get_frequency())),
        character('_'),
        is_letter_node(false),
        left_child(l_child),
        right_child(r_child) {}
Node::Node():
        frequency(0),
        character('_'),
        is_letter_node(false),
        left_child(nullptr),
        right_child(nullptr) {}
Node::~Node() {
    if (left_child)
        delete(left_child);
    if (right_child)
        delete(right_child);
}

std::uint32_t Node::get_frequency() const {
    return frequency;
}
unsigned char Node::get_character() const {
    return character;
}
Node* Node::get_left_child() const {
    return left_child;
}
Node* Node::get_right_child() const {
    return right_child;
}
void Node::set_left_child(Node* child) {
    left_child = child;
}
void Node::set_right_child(Node* child) {
    right_child = child;
}
bool Node::is_character() const {
    return is_letter_node;
}
void Node::set_is_character() {
    is_letter_node = true;
}
void Node::set_character(unsigned char c) {
    character = c;
}
//get codes of all character by a detour of the tree
unsigned char Node::find_path(std::map<unsigned char, std::vector<unsigned char>>& paths, character_and_codes<unsigned char>& codes, std::vector<unsigned char>& path) const {
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
    right_path.push_back(1);
    if (left_child)
        left_child -> find_path(paths, codes, left_path);
    if (right_child)
        right_child -> find_path(paths, codes, right_path);
    return 0;
}

//for using std::priority_queue we need a way to compare two nodes
bool less_than_by_frequency::operator()(Node* lhs, Node* rhs) const {
    return (lhs -> get_frequency()) > (rhs -> get_frequency());
}
//find a character by the path to it in the tree
std::pair<unsigned char, bool> find_in_tree(Node* my_node, std::vector<char>& path, std::uint32_t current_byte) {
    if (current_byte >= static_cast<std::uint32_t>(path.size()))
        return {0, false};
    if (my_node -> is_character())
        return {my_node -> get_character(), true};
    if (path[current_byte] == 0) {
        return find_in_tree(my_node -> get_left_child(), path, current_byte + 1);
    }
    else {
        return find_in_tree(my_node -> get_right_child(), path, current_byte + 1);
    }
}
//insert a new Node in the tree by the path to it
void insert_in_tree(unsigned char let, Node* my_node, std::vector<unsigned char>& path, std::uint32_t current_byte) {
    if (current_byte == static_cast<std::uint32_t>(path.size()))
        return;
    Node* new_dir;
    if (path[current_byte] == 1) {
        if (my_node -> get_right_child()) {
            new_dir = my_node -> get_right_child();
        }
        else {
            my_node -> set_right_child(new Node());
            new_dir = my_node -> get_right_child();
        }
    } else {
        if (my_node -> get_left_child()) {
            new_dir = my_node -> get_left_child();
        }
        else {
            my_node -> set_left_child(new Node());
            new_dir = my_node -> get_left_child();
        }
    }
    if (current_byte == static_cast<std::uint32_t>(path.size()) - 1) {
        new_dir -> set_character(let);
        new_dir -> set_is_character();
        return;
    }
    insert_in_tree(let, new_dir, path, current_byte + 1);
}
//returns a map of frequencies to all the characters from the input file
std::pair<std::map<unsigned char, std::uint32_t>, std::uint32_t> get_map_of_characters(const std::string& path, std::uint32_t& total_input) {
    std::map<unsigned char, std::uint32_t> map_of_frequencies;
    std::uint32_t number = 0;
    total_input = 0;
    std::ifstream fin(path, std::ios::binary);
    if (!fin.is_open()) {
    }
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
            if (map_of_frequencies.find(temp) != map_of_frequencies.end()) {
                ++map_of_frequencies[temp];
            }
            else {
                map_of_frequencies.insert({temp, 1});
            }
        }
    }
    return {map_of_frequencies, number};
}
unsigned char get_byte(const std::array<unsigned char, 8>& arr) {
    unsigned char resulting_byte = 0;
    for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(arr.size()); ++i) {
        resulting_byte += static_cast<unsigned char>((arr[arr.size() - 1 - i]) ? (pow(2, i)) : (0));
    }
    return resulting_byte;
}
//gets 2 paths - input and output files and writes auxiliary tables and coded sequence to the output file
//also prints size of used memory to the console
void write_to_file_binary(const std::string& f_in_path, const std::string& f_out_path, character_and_codes<unsigned char>& codes, std::uint32_t number_of_ch, std::uint32_t& total_aux, std::uint32_t& total_coded) {
    std::ofstream fout(f_out_path, std::ios::binary);
    std::ifstream fin(f_in_path, std::ios::binary);
    std::map<unsigned char, std::vector<unsigned char>> map_of_codes;
    for (const auto& code: codes) {
        map_of_codes.insert(code);
    }
    if (fin.is_open() && fout.is_open()) {
        fout << static_cast<std::uint32_t>(number_of_ch) << '\n';
        fout << static_cast<std::uint32_t>(codes.size()) << '\n';
        for (const auto& code: codes) {
            fout << code.first << ' ';
            for (const auto& c: code.second) {
                fout << static_cast<unsigned char>(c);
            }
            fout << '\n';
        }
        std::array<unsigned char, 8> buffer;
        buffer.fill(8);
        std::int32_t ptr = -1;
        total_aux = static_cast<std::uint32_t>(fout.tellp());
        while (!fin.eof()) {
            unsigned char buff[1];
            buff[0] = 0;
            fin.read(reinterpret_cast<char*>(buff), 1);
            if (fin.eof())
                break;
            std::vector<unsigned char> current_code = map_of_codes[buff[0]];
            for (const auto& current_byte: current_code) {
                ++ptr;
                if (ptr == 7) {
                    buffer[ptr % 8] = current_byte;
                    ptr = -1;
                    fout << get_byte(buffer);
                } else {
                    buffer[ptr] = current_byte;
                }
            }
        }
        if (ptr >= 0) {
            for (std::int32_t i = ptr + 1; i < static_cast<std::int32_t>(buffer.size()); ++i)
                buffer[i] = 0;
            fout << get_byte(buffer);
        }
    }
    total_coded = static_cast<std::uint32_t>(fout.tellp());
    total_coded -= total_aux;
}
//gets binary representation of std::uint32_teger
std::array<unsigned char, 8> get_array_from_int(unsigned char current_char) {
    std::array<unsigned char, 8> resulting_array;
    resulting_array.fill(0);
    if (current_char == 0) {
        return resulting_array;
    }
    std::uint32_t j = 1;
    while (current_char > 0) {
        resulting_array[8 - j] = static_cast<unsigned char>(current_char % 2);
        current_char = current_char / 2;
        ++j;
    }
    return resulting_array;
}
void print_sorted_codes(const character_and_codes<unsigned char>& codes) {
    for (const auto& pair: codes) {
        for (const auto& current_byte: pair.second) {
            std::cout << static_cast<std::uint32_t>(current_byte);
        }
        std::cout << " " << static_cast<std::uint32_t>(pair.first) << std::endl;;
    }
}
Node* get_tree_of_codes(std::ifstream& fin, std::uint32_t& number, std::uint32_t& number_of_ch, std::uint32_t& total_aux) {
    unsigned char character = 0;
    Node* root_of_tree = new Node();
    if (fin.is_open()) {
        unsigned char buff[1];
        fin >> number_of_ch;
        fin.read(reinterpret_cast<char *>(buff), 1);
        if (!fin.eof()) {
            fin >> number;
            fin.read(reinterpret_cast<char *>(buff), 1);
            for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(number); ++i) {
                std::vector<unsigned char> path;
                fin.read(reinterpret_cast<char *>(buff), 1);
                character = buff[0];
                fin.read(reinterpret_cast<char *>(buff), 1);
                unsigned char current_char = 0;
                std::uint32_t counter = 0;
                while ((current_char != '\n') && (counter < 100)) {
                    fin.read(reinterpret_cast<char *>(buff), 1);
                    if (buff[0] != '\n')
                        path.push_back(buff[0]);
                    current_char = buff[0];
                    ++counter;
                }
                insert_in_tree(character, root_of_tree, path, 0);
            }
            total_aux = static_cast<std::uint32_t>(fin.tellg());
        }
    }
    return root_of_tree;
}
void print_to_file_decoded_characters(std::ifstream& fin, std::ofstream& fout, Node *root_of_tree, std::uint32_t& number_of_ch, std::uint32_t& total_input) {
    std::uint32_t count = 0;
    Node* root = root_of_tree;
    while (!fin.eof() && (count < static_cast<std::uint32_t>(number_of_ch))) {
        unsigned char buff[1];
        unsigned char current_char = 0;
        fin.read(reinterpret_cast<char*>(buff), 1);
        if (!fin.eof()) {
            current_char = buff[0];
            auto array_form_of_ch = get_array_from_int(current_char);
            for (std::uint32_t j = 0; j < 8; ++j) {
                if (array_form_of_ch[j] == 0) {
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
                    fout << root -> get_character();
                    root = root_of_tree;
                    ++count;
                    if (count >= static_cast<std::uint32_t>(number_of_ch))
                        break;
                }
            }
        }
        total_input = static_cast<std::uint32_t>(fin.tellg());
    }
}
//get codes in lexicography order by detour
character_and_codes<unsigned char> get_sorted_codes_from_tree(Node* root_of_tree, std::uint32_t& total_input, std::uint32_t& number_of_ch) {
    character_and_codes<unsigned char> sorted_codes;
    std::map<unsigned char, std::vector<unsigned char>> paths;
    std::vector<unsigned char> path;
    Node* temp_node = root_of_tree;
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
    return sorted_codes;
}
std::uint32_t huffman_decode(const std::string& f_in_path, const std::string& f_out_path, bool flag_v) {
    std::uint32_t total_input = 0;
    std::uint32_t total_aux = 0;
    std::uint32_t total_coded = 0;
    std::ifstream fin(f_in_path, std::ios::binary);
    std::ofstream fout(f_out_path, std::ios::binary);
    std::uint32_t number = 0;
    std::uint32_t number_of_ch = 0;
    Node* root_of_tree = get_tree_of_codes(fin, number, number_of_ch, total_aux);
    print_to_file_decoded_characters(fin, fout, root_of_tree, number_of_ch, total_input);
    total_coded = static_cast<std::uint32_t>(fout.tellp());
    total_input -= total_aux;
    character_and_codes<unsigned char> sorted_codes = get_sorted_codes_from_tree(root_of_tree, total_aux, number);
    delete root_of_tree;
    std::cout << total_input << std::endl;
    std::cout << total_coded << std::endl;
    std::cout << total_aux << std::endl;
    if (flag_v) {
        print_sorted_codes(sorted_codes);
    }
    return number_of_ch;
}
//build Huffman tree
Node* get_tree_of_characters(const std::string& fin_path, std::uint32_t& number_of_ch, bool& flag, std::uint32_t& total_input) {
    std::ifstream fin(fin_path, std::ios::binary);
    auto map_of_chars_with_amount = get_map_of_characters(fin_path, total_input);
    auto map_of_characters = map_of_chars_with_amount.first;
    number_of_ch = map_of_chars_with_amount.second;
    priority_queue_of_nodes<Node*> current_priority_queue;
    for (const auto& pair: map_of_characters) {
        current_priority_queue.push((new Node(pair.second, pair.first)));
    }
    flag = false;
    if (current_priority_queue.size() == 1)
        flag = true;
    while (current_priority_queue.size() > 1) {
        auto p1 = current_priority_queue.top();
        current_priority_queue.pop();
        auto p2 = current_priority_queue.top();
        current_priority_queue.pop();
        auto n = new Node(p1, p2);
        current_priority_queue.push(n);
    }
    if (current_priority_queue.empty()) {
        return nullptr;
    }
    Node* root = current_priority_queue.top();
    return root;
}
character_and_codes<unsigned char> get_sorted_codes(const std::string& fin_path, std::uint32_t& number_of_ch, bool& flag, std::uint32_t& total_input) {
    character_and_codes<unsigned char> sorted_codes;
    Node* res = get_tree_of_characters(fin_path, number_of_ch, flag, total_input);
    std::map<unsigned char, std::vector<unsigned char>> paths;
    std::vector<unsigned char> path;
    if (res) {
        if (!flag) {
            res -> find_path(paths, sorted_codes, path);
        } else {
            unsigned char letter = res -> get_character();
            paths.insert({letter, {0}});
            sorted_codes.push_back({letter, {0}});
        }
        delete res;
        return sorted_codes;
    }
    return sorted_codes;
}
void huffman(const std::string& fin_path, const std::string& fout_path, bool flag_v) {
    std::ifstream fin(fin_path, std::ios::binary);
    std::ofstream fout(fout_path, std::ios::binary);
    std::uint32_t number_of_ch = 0;
    bool flag = false;
    std::uint32_t total_input = 0;
    std::uint32_t total_aux = 0;
    std::uint32_t total_coded = 0;
    character_and_codes<unsigned char> sorted_codes  = get_sorted_codes(fin_path, number_of_ch, flag, total_input);
    if (!sorted_codes.empty()) {
        write_to_file_binary(fin_path, fout_path, sorted_codes, number_of_ch, total_aux, total_coded);
    }
    std::cout << total_input << std::endl;
    std::cout << total_coded << std::endl;
    std::cout << total_aux << std::endl;
    if (flag_v) {
        print_sorted_codes(sorted_codes);
    }
}
void run_coding_or_decoding(std::string& path1, std::string& path2, bool f_v, bool f_c_d) {
    if (f_c_d) {
        huffman(path1, path2, f_v);
    } else {
        huffman_decode(path1, path2, f_v);
    }
}