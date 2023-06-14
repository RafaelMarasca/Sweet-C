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


namespace Automata
{
    struct transition_info_t
    {
        bool is_valid;
        bool is_accepting;
        std::string state;
    };

    struct transition_t
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
            void addTransition(transition_t t);

            bool isAccepted(std::string input);
            transition_info_t step(char action);

            void clear(){_current_state = _initial_state;}

    };


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
            transition_info_t step();
    };

} // namespace Automata

#endif //AUTOMATA_H_