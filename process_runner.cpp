#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include "Process.cpp"
#include "Heap.cpp"

using std::fstream;
using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::getline;
using std::cin;
using std::stoi;
using std::deque;

// Parsing process line by line from a file
void add_new_process(vector<Process> &processes, string &line)
{
  int id, arrival, burst, priority, position = -1;
  string value = "";
  for(int i = 0; i < line.size(); ++i)
  {
    if (!isspace(line[i]))
    {
      value.push_back(line[i]);
    }
      else if ( value.size() > 0 && (isspace(line[i]) ))
      {
	++position;
	
	switch(position)
	{
	  case 0:	
	    id = stoi(value);
	    break;
	  case 1:	
	    arrival = stoi(value);
	    break;
	  case 2:	
	    burst = stoi(value);
	    break;
	  default:
	    break;
      }
      value.clear();
    }
  }

  priority = stoi(value);
  processes.push_back(Process(id, arrival, burst, priority));
}

// print processes that are stored in processes list
void print_processes(const vector<Process> &processes) 
{
  cout << "List of Processes!\n";
  for(int i = 0; i < processes.size(); ++i)
  {
    cout << "id: " << processes[i].get_id() << ", arrival: " << processes[i].get_arrival() << ", burst: " << processes[i].get_burst() << ", priority: " << processes[i].get_priority() << endl;
  }

}

// first come first serve method
void first_in_first_out(const vector<Process> &processes )
{
  cout << "first in first out begin :)" << endl;
  int current_time = 0;
  for(int i = 0; i < processes.size(); ++i)
  {
    if (processes[i].get_arrival() > current_time)
    {
      current_time += (processes[i].get_arrival() - current_time);
    }
    current_time += processes[i].get_burst();
  }
  cout << "first in first out done!" << endl;
}

// run the processes in the modified list 
void run_in_order(const vector<Process> &processes, fstream &writing)
{
  cout << "\nwriting to file" << endl;
  int current_time = 0;
  for(int i = 0; i < processes.size(); ++i)
  {
    if (processes[i].get_arrival() > current_time)
    {
      current_time += (processes[i].get_arrival() - current_time);
    }
    current_time += processes[i].get_burst();
    writing << processes[i].get_id() << " " << current_time << endl;
  }
  cout << "finished" << endl;
}

// build processes list using the HEAP. 
// SJF and Highest Priority function
void build(Heap &heap, vector<Process> &processes, string mode)
{
  if(mode == "shortest job first")
  {
    cout << "\nBuilding shortest job first Heap " << endl;
    heap.build_shortest_burst(processes);
    cout << "Finished building! " << endl;
  }
  else if(mode == "highest priority first")
  {
    cout << "\nBuilding highest priority first Heap " << endl;
    heap.build_highest_priority(processes);
    cout << "Finished building! " << endl;
  }
  else
  {
    cout << "Invalid mode! " << endl;
  }
  
}

// run process based on given mode
void run_by_mode(string &mode, string &file_name, Heap &heap, vector<Process> &process_list, fstream &writing)
{
    cout << "\nMode: " << mode << endl;
  if (mode == "first in first out")
  {
    run_in_order(process_list, writing);
    writing.close();
  }
  else if (mode == "shortest job first")
  {
    file_name.append(" ");
    file_name.append(mode);
    writing.open(file_name, fstream::out);
    writing << "--- Process# Finished ---\n";
    build(heap,process_list, mode);
    run_in_order(process_list, writing);
    writing.close();
  }
  else if (mode == "highest priority first")
  {
    file_name.append(" ");
    file_name.append(mode);
    writing.open(file_name, fstream::out);
    writing << "--- Process# Finished ---\n";
    build(heap, process_list, mode);
    run_in_order(process_list, writing);
    writing.close();
  }
  else
  {
    cout << "Invalid Mode!\n Exiting the program now...\n" << endl;
  }

}

// processes ran by round robin algorithm
void round_robin(vector<Process> &process_list, int quantum_time, fstream &writing, string file_name)
{
  cout << "\nProcessing Round Robin... " << endl;
  int current_time = process_list[0].get_arrival(), remaining_process = process_list.size();
  deque<Process> deque;
  deque.push_back(process_list[0]);
  Process next;
  file_name.append(" round robin");
  writing.open(file_name, fstream::out);
  writing << "--- Process# Finished ---\n";

  for(int i = 1; remaining_process > 0;)
  {
    while(!deque.empty())
    {
      next = deque.front();
      deque.pop_front();
      if (next.get_burst() <= quantum_time)
      {	
	current_time += (next.get_burst());
	next.set_burst(0);
	--remaining_process;
	writing << next.get_id() << " " << current_time << endl;
      }
      else
      {
	current_time += quantum_time;
	next.set_burst(next.get_burst() - quantum_time);
      }
	while(i < process_list.size() && process_list[i].get_arrival() <= current_time)
	{
	  deque.push_back(process_list[i++]);
	}
	if (next.get_burst() > 0)
	{
	  deque.push_back(next);
	}
	if (deque.empty() && remaining_process > 0 )
	{
	  deque.push_back(process_list[i++]);
	  current_time = process_list[i-1].get_arrival();
	}
      }
  }
    cout << "Finished Round Robin! " << endl;
}



int main(int argc, char* argv[])
{
  
  if (argc == 2)
  {
    fstream reading, writing;
    string file_name = argv[1];

    reading.open(file_name, fstream::in);
    string mode = "first in first out";
    file_name.append(" ");
    file_name.append(mode);
    writing.open(file_name, fstream::out);
    writing << "--- Process# Finished ---\n";

    const int MAX = 10;
    vector<Process> process_list;
    process_list.reserve(MAX);
    Heap heap(MAX);
    int current_time = 0;

    if (reading.is_open())
    {
      string line;
      cout << "Loading data: " << endl;
      while(getline(reading, line ))
      {
	if (line[0] != '-')
	{
	  add_new_process(process_list, line);
	}

      }
    }

    cout << "\nSaving data to original_data list in heap" << endl;
    heap.save_original_data(process_list);

    reading.close();
    run_by_mode(mode, file_name, heap, process_list, writing);

    mode = "shortest job first";
    file_name = argv[1];
    run_by_mode(mode, file_name, heap, process_list, writing);

    cout << "\nReverting back to original" << endl;
    heap.revert_to_original(process_list);

    mode = "highest priority first";
    file_name = argv[1];
    run_by_mode(mode, file_name, heap, process_list, writing);

    cout << "\nReverting back to original" << endl;
    heap.revert_to_original(process_list);

    cout << "\nFor Round Robin, please enter quantum time: ";
    string quantum;
    getline(cin, quantum);
    int quantum_time = stoi(quantum);
    cout << "quantum time: " << quantum_time << endl;
    file_name = argv[1];
    round_robin(process_list, quantum_time, writing, file_name);

    cout << "Done!" << endl;
  }
  else
  {
    cout << "Please enter a file name to process!\nExiting the program now ..." << endl; 
  }
}
