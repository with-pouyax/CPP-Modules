#ifndef BASE_HPP
#define BASE_HPP

class Base {
public:
    // we don't have a constructor because we don't want to initialize the object
    // we have only a virtual destructor
    virtual ~Base();
};

Base* generate(void); // generate a random object of A, B or C
void identify(Base* p); 
void identify(Base& p);

#endif 