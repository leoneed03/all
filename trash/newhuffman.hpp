#pragma once
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
    node(unsigned char new_frequency, unsigned char new_character);
    node(node*, node*);
    node();
    unsigned char get_frequency() const;
    unsigned char get_character() const;
    node* get_left_child() const;
    node* get_right_child() const;
    void set_left_child(node* child);
    void set_right_child(node* child);
    bool is_character() const;
    void set_is_character();
    void set_character(unsigned char c);
    unsigned char find_path(std::map<unsigned char, std::vector<unsigned char>>& paths, std::vector<std::pair<unsigned char, std::vector<unsigned char>>>& codes, std::vector<unsigned char>& path) const;
    ~node();
};
struct less_than_by_frequency {
    bool operator()(node* lhs, node* rhs) const;
};
std::pair<unsigned char, bool> find_in_tree(node* my_node, std::vector<char>& path, int i);
void insert_in_tree(unsigned char let, node* my_node, std::vector<unsigned char>& path, int i);
std::pair<std::map<unsigned char, unsigned char>, int> get_map_of_characters(const std::string& s, std::uint32_t& total_input);
unsigned char get_byte(const std::vector<unsigned char>& arr);
void write_to_file_binary(const std::string& f_in_path, const std::string& f_out_path, std::vector<std::pair<unsigned char, std::vector<unsigned char>>>& codes, int number_of_ch, std::uint32_t& total_aux, std::uint32_t& total_input);
std::vector<unsigned char> get_vector_from_int(unsigned char c);
node* get_tree_of_codes(std::ifstream& fin, std::uint32_t& number, std::uint32_t& number_of_ch, std::uint32_t& total_aux);
void print_to_file_decoded_characters(std::ifstream &fin, std::ofstream &fout, node *root_of_tree, std::uint32_t &number_of_ch, std::uint32_t &total_input);
std::vector<std::pair<unsigned char, std::vector<unsigned char>>> get_sorted_codes_from_tree(node* root_of_tree, std::uint32_t& total_input, std::uint32_t& number_of_ch);
void huffman_decode(const std::string &f_in_path, const std::string &f_out_path);
node* get_tree_of_characters(const std::string& fin_path, int& number_of_ch, bool& flag, std::uint32_t& total_input);
std::vector<std::pair<unsigned char, std::vector<unsigned char>>> get_sorted_codes(const std::string& fin_path, int& number_of_ch, bool& flag, std::uint32_t&);
void print_sorted_codes(const std::vector<std::pair<unsigned char, std::vector<unsigned char>>>& codes);
void huffman(const std::string& fin_path, const std::string& fout_path, bool);
void run_coding_or_decoding(std::string& path1, std::string& path2, bool f_v, bool f_c_d);


