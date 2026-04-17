#include <iostream>
#include <vector>
#include "containers.h"

int main(int, char **)
{
    try
    {
        SequenceContainer< int > sequence_container;

        for ( int i = 0 ; i < 10 ; ++i )
        {
            sequence_container.push_back( i );
        }

        std::cout << "Sequence container:" << std::endl;

        for ( size_t i = 0 ; i < sequence_container.size() ; ++i )
        {
            std::cout << sequence_container[ i ] << " ";  // ← БЫЛО: << std::endl
        }
        std::cout << std::endl;  // ← ДОБАВЛЕНО: перенос после всего вывода

        std::cout << "sequence_container size: " << sequence_container.size() << std::endl;

        sequence_container.erase( 2 );
        sequence_container.erase( 4 );
        sequence_container.erase( 6 );

        for ( size_t i = 0 ; i < sequence_container.size() ; ++i )
        {
            std::cout << sequence_container[ i ] << " ";  // ← ИЗМЕНЕНО
        }
        std::cout << std::endl;  // ← ДОБАВЛЕНО

        sequence_container.insert( 0 , 10 );

        for ( size_t i = 0 ; i < sequence_container.size() ; ++i )
        {
            std::cout << sequence_container[ i ] << " ";  // ← ИЗМЕНЕНО
        }
        std::cout << std::endl;  // ← ДОБАВЛЕНО

        sequence_container.insert( (size_t)( sequence_container.size() / 2 - 0.5 ) , 20 );

        for ( auto iter = sequence_container.begin() ; iter != sequence_container.end() ; ++iter )
        {
            std::cout << *iter << " ";  // ← ИЗМЕНЕНО
        }
        std::cout << std::endl;  // ← ДОБАВЛЕНО

        sequence_container.push_back( 30 );
        
        for ( auto iter = sequence_container.begin() ; iter != sequence_container.end() ; ++iter )
        {
            std::cout << *iter << " ";  // ← ИЗМЕНЕНО
        }
        std::cout << std::endl;  // ← ДОБАВЛЕНО

        std::cout << std::endl;

        ListContainer< int > list_container;

        for ( int i = 0 ; i < 10 ; ++i )
        {
            list_container.push_back( i );
        }

        std::cout << "List container:" << std::endl;

        for ( size_t i = 0 ; i < list_container.size() ; ++i )
        {
            std::cout << list_container[ i ] << " ";  // ← ИЗМЕНЕНО
        }
        std::cout << std::endl;  // ← ДОБАВЛЕНО

        std::cout << "list_container size: " << list_container.size() << std::endl;

        for ( size_t i = 0 ; i < list_container.size() ; ++i )
        {
            std::cout << list_container[ i ] << " ";  // ← ИЗМЕНЕНО
        }
        std::cout << std::endl;  // ← ДОБАВЛЕНО

        list_container.insert( 0 , 10 );

        for ( size_t i = 0 ; i < list_container.size() ; ++i )
        {
            std::cout << list_container[ i ] << " ";  // ← ИЗМЕНЕНО
        }
        std::cout << std::endl;  // ← ДОБАВЛЕНО

        list_container.insert( (size_t)( list_container.size() / 2 - 0.5 ) , 20 );

        for ( auto iter = list_container.begin() ; iter != list_container.end() ; ++iter )
        {
            std::cout << *iter << " ";  // ← ИЗМЕНЕНО
        }
        std::cout << std::endl;  // ← ДОБАВЛЕНО

        list_container.push_back( 30 );

        for ( auto iter = list_container.begin() ; iter != list_container.end() ; ++iter )
        {
            std::cout << *iter << " ";  // ← ИЗМЕНЕНО
        }
        std::cout << std::endl;  // ← ДОБАВЛЕНО
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch( const char* message )
    {
        std::cerr << message << std::endl;
    }

    return 0;
}