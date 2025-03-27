#ifndef HARL_HPP
#define HARL_HPP

#include <string>

class Harl {
private:
    void _debug(void);
    void _info(void);
    void _warning(void);
    void _error(void);

public:
    //constructor and destructor
    Harl(void);
    ~Harl(void);
    
    //this function will call the appropriate function based on the level
    void complain(std::string level);
};

#endif // HARL_HPP 