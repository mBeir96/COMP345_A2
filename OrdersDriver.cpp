#include <iostream>
#include <vector>
#include "Orders.h"

int main()
{
    OrdersList l;
    l.listOrders;
    
    
    std::cout << "Here are my list of orders." << std::endl;
    

    // for(int i = 0; i < (int)l.listOrders.size(); i++)
    // {
    //     std::cout << (i + 1) << ". " << l.listOrders[i]->getName() << " is " << ((l.listOrders[i]->getVal() == 1) ? "valid." : "not valid.") << std::endl;
    // }

    // l.move(1, 2);
    // for(int i = 0; i < (int)l.listOrders.size(); i++)
    // {
    //     std::cout << (i + 1) << ". " << l.listOrders[i]->getName() << " is " << ((l.listOrders[i]->getVal() == 1) ? "valid." : "not valid.") << std::endl;
    // }
    // l.remove(1);
    // for(int i = 0; i < (int)l.listOrders.size(); i++)
    // {
    //     std::cout << (i + 1) << ". " << l.listOrders[i]->getName() << " is " << ((l.listOrders[i]->getVal() == 1) ? "valid." : "not valid.") << std::endl;
    // }
    
    return 0;
}