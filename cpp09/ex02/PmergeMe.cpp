#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{};


PmergeMe::PmergeMe(const PmergeMe& other)
{
    *this = other;
};

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
    {
        vec_container  = other.vec_container;
        deck_container = other.deck_container;
        basevec        = other.basevec;
    }
    return *this;
};

PmergeMe::PmergeMe(char** args, size_t size)
{
    std::string arg;
    std::stringstream ss;
    long nm = 0;

    for (size_t i = 1; i < size; i++)
    {
        ss.clear();
        ss.str(args[i]);
        while (ss >> arg)
        {
            for (size_t j = 0; j < arg.size(); j++)
            {
                if (!isdigit(arg[j]))
                    throw std::runtime_error("bad argument");
            }

            ss.clear();
            ss.str(arg);
            if (!(ss >> nm) || nm <= 0 || nm > 2147483647L)
                throw std::runtime_error("bad argument");
            int val = static_cast<int>(nm);
            if (std::find(vec_container.begin(), vec_container.end(), val) != vec_container.end())
                throw std::runtime_error("duplicates arg");

            vec_container.push_back(val);
            deck_container.push_back(val);
        }
    }
};


std::vector<size_t> PmergeMe::vecRight_order(size_t wSize)
{
    std::vector<size_t> other;
    if (wSize < 2)
        return (other); // needs explain
    std::vector<size_t> jacobs;
    jacobs.push_back(1);
    jacobs.push_back(1);
    size_t i = 1;
    while (jacobs[i] < wSize)
    {
        i++;
        jacobs.push_back(jacobs[i-1]+2*jacobs[i-2]);
    }
    size_t prev = 1;
    size_t l = 0;
    for (size_t i = 2; i < jacobs.size(); i++)
    {
        l = std::min(jacobs[i], wSize);
        for (size_t j = l; j > prev; j--)
            other.push_back(j);
        prev = l;
    }
    return (other);
}



void PmergeMe::setVec(std::vector<int> &vec)
{
    vec_container = sortedVec(vec);
}

std::vector<int> PmergeMe::sortedVec(std::vector<int> &veContainer)
{
    if (veContainer.size() <= 1)
        return(veContainer);
    bool leftOver = false;
    int a = 0, b = 0, temp = 0, leftOverRes = 0;
    size_t vecsize = veContainer.size();
    std::vector<std::pair<int, int> > pairsVec;
    std::vector<int> winners, main_chain, pending;
    size_t winners_index = 0, pending_index = 0;
    int pending_val = 0, winners_val = 0;

    if (vecsize % 2 != 0)
        leftOver = true;

    for (size_t i = 0; (i+1) < vecsize; i+=2)
    {
        a = veContainer[i];
        b = veContainer[i+1];
        if (a < b)
        {
            temp = a;
            a = b;
            b = temp;
        }
        pairsVec.push_back(std::make_pair(a, b));
    }

    if (leftOver)
        leftOverRes = veContainer[vecsize -1];
    
    for (size_t i = 0; i < pairsVec.size(); i++)
        winners.push_back(pairsVec[i].first);
    
    winners = sortedVec(winners);
    main_chain.push_back(winners[0]);

    for (size_t i = 0; i < pairsVec.size(); i++)
    {
        if (pairsVec[i].first == winners[0])
        {
            main_chain.insert(main_chain.begin(), pairsVec[i].second);
            break;
        }
    }
    //inserting the first loser
    for (size_t i = 1; i < winners.size(); i++)
        main_chain.push_back(winners[i]);
    //pushing back the rest of the winners

    for (size_t i = 1; i < winners.size(); i++)
    {
        for (size_t j = 0; j < pairsVec.size(); j++)
        {
            if (pairsVec[j].first == winners[i])
            {
                pending.push_back(pairsVec[j].second);
                break;
            }
        }
    }
    std::vector<size_t> loser_order = vecRight_order(winners.size());

    for (size_t i = 0; i < loser_order.size(); i++)
    {
        winners_index = loser_order[i];
        pending_index = winners_index - 2;
        pending_val = pending[pending_index];
        winners_val = winners[winners_index-1];
    
        std::vector<int>::iterator bound = std::lower_bound(main_chain.begin(), main_chain.end(), winners_val);
        std::vector<int>::iterator it    = std::lower_bound(main_chain.begin(), bound, pending_val);
        main_chain.insert(it, pending_val);
    }
    if (leftOver)
    {
        std::vector<int>::iterator it = std::lower_bound(main_chain.begin(), main_chain.end(), leftOverRes);
        main_chain.insert(it, leftOverRes);
    }
    return (main_chain);
}

void PmergeMe::setdeck(std::deque<int> &deck)
{
    deck_container = sorteDeck(deck);
}

// std::deque<size_t> PmergeMe::deckRight_order(size_t wSize)
// {
//     std::deque<size_t> other;
//     if (wSize < 2)
//         return (other); // needs explain
//     std::deque<size_t> jacobs;
//     jacobs.push_back(1);
//     jacobs.push_back(1);
//     size_t i = 1;
//     while (jacobs[i] < wSize)
//     {
//         i++;
//         jacobs.push_back(jacobs[i-1]+2*jacobs[i-2]);
//     }
//     size_t prev = 1;
//     size_t l = 0;
//     for (size_t i = 2; i < jacobs.size(); i++)
//     {
//         l = std::min(jacobs[i], wSize);
//         for (size_t j = l; j > prev; j--)
//             other.push_back(j);
//         prev = l;
//     }
//     return (other);
// }


std::deque<int> PmergeMe::sorteDeck(std::deque<int> &deckContainer)
{
    if (deckContainer.size() <= 1)
        return(deckContainer);
    bool leftOver = false;
    int a = 0, b = 0, temp = 0, leftOverRes = 0;
    size_t vecsize = deckContainer.size();
    std::deque<std::pair<int, int> > pairsVec;
    std::deque<int> winners, main_chain, pending;
    size_t winners_index = 0, pending_index = 0;
    int pending_val = 0, winners_val = 0;

    if (vecsize % 2 != 0)
        leftOver = true;

    for (size_t i = 0; (i+1) < vecsize; i+=2)
    {
        a = deckContainer[i];
        b = deckContainer[i+1];
        if (a < b)
        {
            temp = a;
            a = b;
            b = temp;
        }
        pairsVec.push_back(std::make_pair(a, b));
    }

    if (leftOver)
        leftOverRes = deckContainer[vecsize -1];
    
    for (size_t i = 0; i < pairsVec.size(); i++)
        winners.push_back(pairsVec[i].first);
    
    winners = sorteDeck(winners);
    main_chain.push_back(winners[0]);

    for (size_t i = 0; i < pairsVec.size(); i++)
    {
        if (pairsVec[i].first == winners[0])
        {
            main_chain.insert(main_chain.begin(), pairsVec[i].second);
            break;
        }
    }
    //inserting the first loser
    for (size_t i = 1; i < winners.size(); i++)
        main_chain.push_back(winners[i]);
    //pushing back the rest of the winners

    for (size_t i = 1; i < winners.size(); i++)
    {
        for (size_t j = 0; j < pairsVec.size(); j++)
        {
            if (pairsVec[j].first == winners[i])
            {
                pending.push_back(pairsVec[j].second);
                break;
            }
        }
    }

    std::vector<size_t> loser_order = vecRight_order(winners.size());

    for (size_t i = 0; i < loser_order.size(); i++)
    {
        winners_index = loser_order[i];
        pending_index = winners_index - 2;
        pending_val = pending[pending_index];
        winners_val = winners[winners_index-1];
    
        std::deque<int>::iterator bound = std::lower_bound(main_chain.begin(), main_chain.end(), winners_val);
        std::deque<int>::iterator it    = std::lower_bound(main_chain.begin(), bound, pending_val);
        main_chain.insert(it, pending_val);
    }
    if (leftOver)
    {
        std::deque<int>::iterator it = std::lower_bound(main_chain.begin(), main_chain.end(), leftOverRes);
        main_chain.insert(it, leftOverRes);
    }
    return (main_chain);
}

std::vector<int>& PmergeMe::get_Vec_Con()
{
    return vec_container;
};
std::deque<int>& PmergeMe::get_deck_Con()
{
    return deck_container;
};


PmergeMe::~PmergeMe()
{};
