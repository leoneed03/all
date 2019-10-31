#pragma once
#include <fstream>
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <array>

class Node {
private:
    std::uint32_t frequency;
    unsigned char character;
    bool is_letter_node;
    Node* left_child;
    Node* right_child;
public:
    Node(std::uint32_t new_frequency, unsigned char new_character);
    Node(Node*, Node*);
    Node();
    std::uint32_t get_frequency() const;
    unsigned char get_character() const;
    Node* get_left_child() const;
    Node* get_right_child() const;
    void set_left_child(Node* child);
    void set_right_child(Node* child);
    bool is_character() const;
    void set_is_character();
    void set_character(unsigned char c);
    unsigned char find_path(std::map<unsigned char, std::vector<unsigned char>>& paths, std::vector<std::pair<unsigned char, std::vector<unsigned char>>>& codes, std::vector<unsigned char>& path) const;
    ~Node();
};
struct less_than_by_frequency {
    bool operator()(Node* lhs, Node* rhs) const;
};
std::pair<unsigned char, bool> find_in_tree(Node* my_node, std::vector<char>& path, std::uint32_t current_byte);
void insert_in_tree(unsigned char character, Node* my_node, std::vector<unsigned char>& path, std::uint32_t current_byte);
std::pair<std::map<unsigned char, std::uint32_t>, std::uint32_t> get_map_of_characters(const std::string& path, std::uint32_t& total_input);
unsigned char get_byte(const std::array<unsigned char, 8>& arr);
void write_to_file_binary(const std::string& f_in_path, const std::string& f_out_path, std::vector<std::pair<unsigned char, std::vector<unsigned char>>>& codes, std::uint32_t number_of_ch, std::uint32_t& total_aux, std::uint32_t& total_coded);
std::array<unsigned char, 8> get_array_from_int(unsigned char current_char);
Node* get_tree_of_codes(std::ifstream& fin, std::uint32_t& number, std::uint32_t& number_of_ch, std::uint32_t& total_aux);
void print_to_file_decoded_characters(std::ifstream& fin, std::ofstream& fout, Node *root_of_tree, std::uint32_t& number_of_ch, std::uint32_t& total_input);
std::vector<std::pair<unsigned char, std::vector<unsigned char>>> get_sorted_codes_from_tree(Node* root_of_tree, std::uint32_t& total_input, std::uint32_t& number_of_ch);
void huffman_decode(const std::string& f_in_path, const std::string& f_out_path);
Node* get_tree_of_characters(const std::string& fin_path, std::uint32_t& number_of_ch, bool& flag, std::uint32_t & total_input);
std::vector<std::pair<unsigned char, std::vector<unsigned char>>> get_sorted_codes(const std::string& fin_path, std::uint32_t& number_of_ch, bool& flag, std::uint32_t& total);
void print_sorted_codes(const std::vector<std::pair<unsigned char, std::vector<unsigned char>>>& codes);
void huffman(const std::string& fin_path, const std::string& fout_path, bool);
void run_coding_or_decoding(std::string& path1, std::string& path2, bool f_v, bool f_c_d);