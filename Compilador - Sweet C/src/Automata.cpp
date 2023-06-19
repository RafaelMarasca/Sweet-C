#include "Automata.h"

namespace Automata
{
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

    void FDA::addTransition(transition_t t)
    {
        
        if(t.action[1] > t.action[0])
        {
            for(unsigned char action = t.action[0]; action <= t.action[1]; action++)
                addTransition(t.source, action, t.destination);
        }else
        {
            addTransition(t.source, t.action[0], t.destination);
        }        
    }


    bool FDA::isAccepted(std::string input)
    {
        transition_info_t step_info = {false, false, ""}; 
        _current_state = _initial_state;

        for(auto ch : input)
        {
            step_info = step(ch);

            if(!step_info.is_valid)
                return false;
        }

        return step_info.is_accepting;
    }

    transition_info_t FDA::step(char action)
    {
        transition_info_t step_info{false,false, ""};

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
} // namespace Automata


