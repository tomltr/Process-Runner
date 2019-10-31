#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Process.cpp"
#include "Heap.cpp"

using std::fstream;
using std::string;
using std::cout;
using std::endl;
using std::vector;

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
void run_in_order(const vector<Process> &processes, fstream &file)
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
    file << processes[i].get_id() << " " << current_time << endl;
  }
  cout << "finished" << endl;
}

// build processes list using the HEAP. 
// SJF and Highest Priority function
void build(vector<Process> &processes, string mode)
{
  Heap heap(processes.size());
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
void run_by_mode(string &mode, string &file_name,vector<Process> &process_list, fstream &writing)
{
    cout << "Mode: " << mode << endl;
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
    build(process_list, mode);
    run_in_order(process_list, writing);
    writing.close();
  }
  else if (mode == "highest priority first")
  {
    file_name.append(" ");
    file_name.append(mode);
    writing.open(file_name, fstream::out);
    writing << "--- Process# Finished ---\n";
    build(process_list, mode);
    run_in_order(process_list, writing);
    writing.close();
  }
  else
  {
    cout << "Invalid Mode!\n Exiting the program now...\n" << endl;
  }

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
    reading.close();
    run_by_mode(mode, file_name, process_list, writing);

    mode = "shortest job first";
    file_name = argv[1];
    run_by_mode(mode, file_name, process_list, writing);

    mode = "highest priority first";
    file_name = argv[1];
    run_by_mode(mode, file_name, process_list, writing);

    cout << "Done!" << endl;
  }
  else
  {
    cout << "Please enter a file name to process!\nExiting the program now ..." << endl; 
  }
}
