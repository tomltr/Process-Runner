#include "Process.h"

Process::Process()
{
  this->id = 0;
  this->arrival = 0;
  this->burst = 0;
  this->priority = 0;
}

int Process::get_id() const
{
  return this->id;
}

int Process::get_arrival() const
{
  return this->arrival;
}

int Process::get_burst() const
{
  return this->burst;
}

int Process::get_priority() const
{
  return this->priority;
}

void Process::set_id(int id)
{
  this->id = id;
}

void Process::set_arrival(int arrival)
{
  this->arrival = arrival;
}

void Process::set_burst(int burst)
{
  this->burst = burst;
}

void Process::set_priority(int priority)
{
  this->priority = priority;
}

void Process::exchange(Process &process)
{
  int temp_id = this->id, temp_arrival = this->arrival,
      temp_burst = this->burst, temp_priority = this->priority;

  this->set_id(process.get_id());
  this->set_arrival(process.get_arrival());
  this->set_burst(process.get_burst());
  this->set_priority(process.get_priority());

  process.set_id(temp_id);
  process.set_arrival(temp_arrival);
  process.set_burst(temp_burst);
  process.set_priority(temp_priority);
}


