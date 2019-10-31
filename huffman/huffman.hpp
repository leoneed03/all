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
    node(unsigned char new_frequency);
    node(node*, node*);
    node();
    unsigned char get_frequency();
    unsigned char get_character();
    node* get_left_child();
    node* get_right_child();
    void set_left_child(node* child);
    void set_right_child(node* child);
    bool is_character();
    void set_is_character();
    void set_character(unsigned char c);
    unsigned char find_path(std::map<unsigned char, std::vector<unsigned char>>& paths, std::vector<std::pair<unsigned char, std::vector<unsigned char>>>& codes, std::vector<unsigned char>& path);
    ~node();
    friend std::ostream& operator<< (std::ostream& os, const node& obj);
};

void print_tree(node* my_node, int level, char lr);
std::pair<unsigned char, bool> find_in_tree(node* my_node, std::vector<char>& path, int i);
void insert_in_tree(unsigned char let, node* my_node, std::vector<unsigned char>& path, int i);
//
std::pair<std::map<unsigned char, unsigned char>, int> get_map_of_characters(std::string& s, std::uint32_t& total_input);
std::vector<std::pair<unsigned char, std::vector<unsigned char>>> get_vector_from_map_of_paths(std::map<unsigned char, std::vector<unsigned char>> my_map);
std::vector<std::pair<unsigned char, unsigned char>> get_vector_from_map(const std::map<unsigned char, unsigned char>& my_map);
void sort_vector_of_pairs(std::vector<std::pair<unsigned char, unsigned char>>& my_vector);
unsigned char get_byte(std::vector<unsigned char> arr);
//
void write_to_file_binary(std::string f_in_path, std::string& f_out_path, std::vector<std::pair<unsigned char, std::vector<unsigned char>>>& codes, int number_of_ch, std::uint32_t&, std::uint32_t& total_input);
std::vector<unsigned char> get_vector_from_int(unsigned char c);

void print_paths_v(node* root, std::vector<int> path1);

void print_path(node* my_node, node* root, std::string path1);
void print_one_path(node* my_node, node* root);

void print_paths(node* root, std::string path1);
void print_me(node* root);
void print_me_v(node* root);


std::pair<node*, bool> find_in_tree_one_step(node* my_node, unsigned char step);
void huffman_decode(std::string &f_in_path, std::string &f_out_path);
node* get_tree_of_characters(std::string& fin_path, int& number_of_ch, bool& flag, std::uint32_t& total_input);
std::vector<std::pair<unsigned char, std::vector<unsigned char>>>
//
 get_sorted_codes(std::string& fin_path, int& number_of_ch, bool& flag, std::uint32_t&);
 
void read_file_to_console(std::string&);
 void print_sorted_codes(std::vector<std::pair<unsigned char, std::vector<unsigned char>>>& codes);
 //1
void run_coding_or_decoding(std::string& path1, std::string& path2, bool f_v, bool f_c_d);
void huffman(std::string& fin_path, std::string& fout_path, bool);


