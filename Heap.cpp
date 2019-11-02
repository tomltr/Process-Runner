#include "Heap.h"

Heap::Heap(const int capacity)
{
  this->current_time = 0;
  this->heap_list.reserve(capacity);
  this->original_data.reserve(capacity);
}

int Heap::get_current_time() const
{
  return this->current_time;
}

void Heap::set_current_time(int current_time)
{
  this->current_time = current_time;
}

void Heap::swap_processes(int first, int second)
{
  this->heap_list[first].exchange(this->heap_list[second]);
}

void Heap::add(Process &process, int current_time)
{
  this->heap_list.push_back(process);
   int current = this->heap_list.size()-1;
    while( (current-1)  >= 0)
    {
      if (this->heap_list[current].get_burst() <  this->heap_list[(current-1)/2].get_burst())
      {
	this->swap_processes(current, (current-1)/2);
      }
      --current;
      current /= 2;
    }
} 

void Heap::add_highest_priority(Process &process, int current_time)
{
  this->heap_list.push_back(process);
   int current = this->heap_list.size()-1;
    
    while( (current-1)  >= 0)
    {
      if (this->heap_list[current].get_priority() <  this->heap_list[(current-1)/2].get_priority())
      {
	this->swap_processes(current, (current-1)/2);
      }
      --current;
      current /= 2;
    }
  
} 
Process Heap::extract_highest_priority(vector<Process> &heap_list, int current_time)
{
  if (heap_list.size()> 0)
  {
    Process min = heap_list.front();
    heap_list.front().exchange(heap_list[heap_list.size()-1]);
    heap_list.pop_back();
    int i = 0;
    while( (i*2+1) < heap_list.size())
    {
      if (i*2 + 2 < heap_list.size())
      {
	if (heap_list[i*2+1].get_priority() < heap_list[i*2+2].get_priority())
	{
	  this->swap_processes(i, (i*2)+1);
	  i*=2;
	  ++i;
	}
	else
	{
	  this->swap_processes(i, (i*2)+2);
	  i*=2;
	  i+=2;
	}
      }
      else if(i*2+1 < heap_list.size())
      {
	if(heap_list[i*2+1].get_priority() < heap_list[i].get_priority())
	{
	  this->swap_processes(i, (i*2)+1);
	  i*=2;
	  ++i;
	}
	i*=2;
	++i;
      }
    }
    return min;
  }

  return Process{0,0,0,0};
}


Process Heap::extract_min(vector<Process> &heap_list, int current_time)
{
  if (this->heap_list.size()>= 0)
  {
    Process min = heap_list.front();
    heap_list.front().exchange(heap_list[heap_list.size()-1]);
    heap_list.pop_back();
    int i = 0;
    while( (i*2+1) < heap_list.size())
    {
      if (i*2 + 2 < heap_list.size())
      {
	if (heap_list[i*2+1].get_burst() < heap_list[i*2+2].get_burst() || (heap_list[i*2+1].get_burst() == heap_list[i*2+2].get_burst() && heap_list[i*2+1].get_arrival() < heap_list[i*2+2].get_arrival()))
	{
	  this->swap_processes(i, (i*2)+1);
	  i*=2;
	  ++i;
	}
	else
	{
	  this->swap_processes(i, (i*2)+2);
	  i*=2;
	  i+=2;
	}
      }
      else if(i*2+1 < heap_list.size())
      {
	if(heap_list[i*2+1].get_burst() < heap_list[i].get_burst() || (heap_list[i*2+1].get_burst() == heap_list[i].get_burst() && heap_list[i*2+1].get_arrival() < heap_list[i].get_arrival()))
	{
	  this->swap_processes(i, (i*2)+1);
	  i*=2;
	  ++i;
	}
	i*=2;
	++i;
      }
    }
    return min;
  }

  return Process{0,0,0,0};

}

void Heap::build_shortest_burst( vector<Process> &process_list)
{
  int i = 0, j = 0, previous_arrival = 0;
  while(i < process_list.size())
  {
      if(heap_list.size() == 0)
      {
	previous_arrival = process_list[j].get_arrival(); 
	while(j < process_list.size() && process_list[j].get_arrival() > this->get_current_time() && (process_list[j].get_arrival() == previous_arrival))
	{
	  this->set_current_time(this->get_current_time() + (process_list[j].get_arrival() - this->get_current_time()));
	  this->add(process_list[j++], this->get_current_time());
	}
      }
      while(j < process_list.size() && process_list[j].get_arrival() <= this->get_current_time())
      {
	this->add(process_list[j++], this->get_current_time());
      }
    
    Process min = extract_min(this->heap_list, this->get_current_time());
    this->set_current_time(this->get_current_time() + min.get_burst());
    process_list[i].exchange(min);
    ++i;
  }
}

void Heap::build_highest_priority(vector<Process> &process_list)
{
  this->set_current_time(0);
  int i = 0, j = 0, previous_arrival = 0;
  while(i < process_list.size())
  {
    if(this->heap_list.size() == 0)
    {
      previous_arrival = process_list[j].get_arrival();
      while(j < process_list.size() && process_list[j].get_arrival() > this->get_current_time() && (process_list[j].get_arrival() == previous_arrival))
      {
	this->set_current_time(this->get_current_time() + (process_list[j].get_arrival() - this->get_current_time()));
	this->add_highest_priority(process_list[j++], this->get_current_time());
      }
    }
    while(j < process_list.size() && process_list[j].get_arrival() <= this->get_current_time())
    {
      this->add_highest_priority(process_list[j++], this->get_current_time());
    }
    Process min = extract_highest_priority(this->heap_list, this->get_current_time());
    this->set_current_time(this->get_current_time() + min.get_burst());
   
    process_list[i].exchange(min);
    ++i;
  }
}

void Heap::save_original_data(const vector<Process> &process_list)
{
  for(int i = 0; i < process_list.size(); ++i)
  {
    this->original_data.push_back(process_list[i]);
  }
}

void Heap::revert_to_original(vector<Process> &process_list)
{
  for(int i = 0; i < this->original_data.size(); ++i)
  {
    process_list[i] = this->original_data[i];
  }
}

