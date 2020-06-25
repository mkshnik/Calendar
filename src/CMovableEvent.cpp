//
// Created by mkshnik on 27.05.20.
//

#include "CMovableEvent.hpp"

bool                              CMovableEvent::Edit             ()
{

    std::cout << "You can add/edit following attributes to your event:\n"
                 "| 1. Location | 2. Repeat |\n"
                 "Press corresponding number to choose section to add or '0' to save event:\n";
    std::map<std::string,bool> attributes;
    attributes["location"]     = false;
    attributes["description"]  = false;
    while(true)
    {
        int num = CScanner::ScanNumber(0, 2);
        if (num == 1 && attributes["location"])     continue;
        if (num == 4 && attributes["repeat"])       continue;
        if (num == 0) break;
        switch (num)
        {
            case 1:
                if (ScanLocation())
                    attributes["location"] = true;
                break;
            case 2:
                if (Repeat())
                    attributes["repeat"]   = true;
                break;
        }
        if (attributes["location"] && attributes["participants"] && attributes["description"] && attributes["repeat"])
            break;
        std::cout << "Do you want to add anything else? Press '0' if not or corresponding key to add section.\n| ";
        if (!attributes["location"])      std::cout << "1. Location | ";
        if (!attributes["repeat"])		  std::cout << "2. Repeat | ";
        std::cout << '\n';
    }
    return true;
}
