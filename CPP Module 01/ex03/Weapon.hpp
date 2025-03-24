#ifndef WEAPON_HPP
# define WEAPON_HPP

# include <string>

class Weapon {
private:
    std::string _type;

public:
    //constructor and destructor
    Weapon(const std::string& type); //when we create a Weapon object, we say what type of weapon it is
    ~Weapon(); //destructor
    
    //getter
    const std::string& getType() const; //its return type is const std::string&, which means it returns a constant reference to a string
    
    //setter
    void setType(const std::string& type);
};

#endif 