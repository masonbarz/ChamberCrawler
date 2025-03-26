#ifndef TREASURE_H
#define TREASURE_H
#include <string>

class Treasure {
 protected:
    int value; 
    bool isGuarded;
    std::string type;

    int w_location;
    int h_location;
 public:
    Treasure(int value, bool isGuarded, std::string type, int w_location, int h_location);
    ~Treasure() = default;
	int getValue();
	bool getIsGuarded();
    void removeGuarded();
    int getWLocation();
    int getHLocation();
	std::string getType();
};

class Normal: public Treasure {
public:
	Normal(int w_location, int h_location);
};

class SmallHorde: public Treasure {
 public:
	SmallHorde(int w_location, int h_location);
};

class MerchantHorde: public Treasure {
 public:
	MerchantHorde(int w_location, int h_location);
};

class DragonHorde: public Treasure {
 public:
	DragonHorde(int w_location, int h_location);
};

class BarrierSuit: public Treasure {
 public:
    BarrierSuit(int w_location, int h_location);
};

class Compass: public Treasure {
 public:
    Compass(int w_location, int h_location);
};

#endif
