#ifndef HEAP_H
#define HEAP_H

#include <vector>
using std::vector;
using std::cout;
using std::endl;


class Heap
{
  private: 
    int current_time;
    vector<Process> heap_list;
    vector<Process> original_data;

    int get_current_time() const;
    void set_current_time(int current_time);
    void swap_processes(int first, int second);
    void add(Process &process, int current_time);
    void add_highest_priority(Process &process, int current_time);
    Process extract_min(vector<Process> &heap_list, int current_time);
    Process extract_highest_priority(vector<Process> &heap_list, int current_time);

  public:
    Heap(const int capacity);
    void build_shortest_burst( vector<Process> &process_list);
    void build_highest_priority( vector<Process> &process_list);
    void save_original_data(const vector<Process> &process_list);
    void revert_to_original(vector<Process> &process_list);
};

#endif
