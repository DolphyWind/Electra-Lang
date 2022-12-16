#include "Electra.hpp"


Electra::Electra()
{
    m_components['-'] = new Cable( {Direction::WEST, Direction::EAST} );
    m_components['|'] = new Cable( {Direction::NORTH, Direction::SOUTH} );
    m_components['/'] = new Cable( {Direction::SOUTHWEST, Direction::NORTHEAST} );
    m_components['\\'] = new Cable( {Direction::SOUTHEAST, Direction::NORTHWEST} );
    m_components['+'] = new Cable( {Direction::WEST, Direction::EAST, Direction::NORTH, Direction::SOUTH} );
    m_components['X'] = new Cable( {Direction::SOUTHEAST, Direction::SOUTHWEST, Direction::NORTHEAST, Direction::NORTHWEST} );
}

Electra::~Electra()
{
    for(auto& p : m_components)
    {
        delete p.second;
    }
    m_components.clear();
}

void Electra::run()
{
    
}
