#include <iostream>
#include <map>
#include <array>   
#include <vector>   
#include <list>   
#include <deque>   
#include <algorithm> 
#include <iostream>

class type
{
    private:
        int c;
    public:
        type(){};
        ~type(){};
};

int main()
{
    {
        // std::map<std::string, std::string> m;
        // m.insert(std::make_pair("qwerty", "qwerty"));
        // m.insert(std::make_pair("qwerty", "qwert1y"));

        // for (std::map<std::string, std::string>::iterator it = m.begin(); it != m.end(); it++)
        // {
        //     // std::cout << it->first << ", " << it->second << std::endl;

        // }
        // std::map<std::string, std::string>::iterator it = m.find("qwert1y");
        // std::cout << it->second<<"\n";
        // //  std::find(begin(m), end(m), "werty");
    }

    {
        // std::vector<int> vec;
        // std::list<int> vec1;
        // std::deque<int> vec2;
        // vec.push_back(1);vec.push_back(2);vec.push_back(3);
        // // std::vector<int>::value_type value = vec;
        // std::vector<int>::iterator it = vec.begin();
        // std::list<int>::iterator it1 = vec1.begin();
        // std::deque<int>::iterator it2 = vec2.begin();
        // std::sort(vec.begin(), vec.end());
        // std::sort(vec2.begin(), vec2.end());
        // // std::sort(vec1.begin(), vec1.end()); // can use it on list

        // std::array<int, 10> b;
        // b[17] = 10;

        // std::cout << b.size() << "\n";
        // std::cout << b.data() << "\n";
    }

    {
        std::vector<int> vec(3,12);
        std::cout << vec.size() << "\n";
        std::cout << vec.capacity() << "\n";
        vec.push_back(10);
        std::cout << vec.size() << " : 2 \n";
        std::cout << vec.capacity() << " : 2\n";
        vec.push_back(12);
        std::cout << vec.size() << " : 3 \n";
        std::cout << vec.capacity() << " : 3\n";
        vec.push_back(12);
        std::cout << vec.size() << " : 4 \n";
        std::cout << vec.capacity() << " : 4\n";        

        vec.push_back(12);
        vec.push_back(12);
        vec.push_back(12);
        vec.push_back(12);
        vec.push_back(12);
        vec.push_back(12);
        vec.push_back(12);


        std::cout << vec.size() << "\n";
        std::cout << vec.capacity() << "\n";
        std::vector<int>::iterator it = vec.begin();
        std::vector<int> vec2;
        vec.reserve(20);
        std::cout << vec.size() << "\n";
        std::cout << vec.capacity() << "\n";
        for (size_t i=0; i != 50; ++i)
        {
            vec.push_back(0);
        }
        vec.insert(it, 10);
        std::deque<int> deck;
        deck.push_back(10);
        deck.push_back(11);
        int& ref = deck.front();
        std::deque<int>::iterator dit= deck.begin();
        std::cout << ref << "\n";
        std::cout << *dit << "\n";
        deck.push_front(13);
        deck.push_front(13);
        deck.push_front(13);
        deck.push_front(13);
        deck.push_front(13);
        deck.push_front(13);
        std::cout << ref << "\n";
        std::cout << *dit << "\n";
    }
    return 0;
}
