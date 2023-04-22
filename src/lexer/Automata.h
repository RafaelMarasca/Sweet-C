/**
 * @file auto.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef AUTOMATA_H_
#define AUTOMATA_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

struct info
{
    bool is_valid;
    bool is_accepting;
    std::string state;
};

struct Transition
{
    std::string source;
    char action [2] = {0,0};
    std::string destination;
};

class FDA
{
    private:
        std::string _initial_state;
        std::string _current_state;
        std::unordered_set<std::string> _accepting_states;
        std::unordered_map<std::string, std::unordered_map<char, std::string>> _transition_table;

    public:
        FDA(std::string initial_state, std::vector<std::string> accepting_states);
        ~FDA();

        void addTransition(std::string source, char action, std::string destination);
        void addTransition(Transition t);

        bool isAccepted(std::string input);
        info step(char action);

        void clear(){_current_state = _initial_state;}

};

FDA::FDA(std::string initial_state, std::vector<std::string> accepting_states)
{
    _initial_state = initial_state;
    _current_state = initial_state;

    for(auto s = accepting_states.begin(); s != accepting_states.end(); s++)
    {
        _accepting_states.insert(*s);
    }
}

FDA::~FDA(){}

void FDA::addTransition(std::string source, char action, std::string destination)
{
    if(_transition_table.find(source) == _transition_table.end())
        _transition_table[source] = std::unordered_map<char, std::string>();
    

    _transition_table[source][action] = destination;
}

void FDA::addTransition(Transition t)
{
    if(_transition_table.find(t.source) == _transition_table.end())
        _transition_table[t.source] = std::unordered_map<char, std::string>();
    
    if(t.action[1] > t.action[0])
    {
        for(char action = t.action[0]; action < t.action[1]; action++)
            _transition_table[t.source][action] = t.destination;
    }

     _transition_table[t.source][t.action[0]] = t.destination;
}


bool FDA::isAccepted(std::string input)
{
    info step_info = {false, false, ""}; 
    _current_state = _initial_state;

    for(auto ch : input)
    {
        step_info = step(ch);

        if(!step_info.is_valid)
            return false;
    }

    return step_info.is_accepting;
}

info FDA::step(char action)
{
    info step_info{false,false, ""};

    if(_transition_table[_current_state].find(action) != _transition_table[_current_state].end())
    {
        _current_state = _transition_table[_current_state][action];
        step_info.is_valid = true;
        step_info.state = _current_state;

        if(_accepting_states.find(_current_state) != _accepting_states.end())
            step_info.is_accepting = true;
    }

    return step_info;
}


class PDA
{
    private:
        std::string _initial_state;
        std::string _current_state;
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> _transition_table;

    public:
        PDA(std::string initial_state, std::vector<std::string> accepting_states);
        ~PDA();

        void addTransition(std::string action, std::string destination);

        bool isAccepted();
        info step();
};

#endif //AUTOMATA_H_