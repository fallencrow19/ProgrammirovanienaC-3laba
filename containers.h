#pragma once

#include <iostream>

#include <memory>
#include <cmath>

template <typename T>
class SequenceContainer
{
    const float EXPANSION_COEFFICIENT = 1.5F;
    std::shared_ptr< T[] > container;
    size_t capacity_;
    size_t size_;

    public:

    struct iterator
    {
        size_t index;
        SequenceContainer* sequence_container;

        iterator( size_t index_ , SequenceContainer* sequence_container_ )
        {
            index = index_;
            sequence_container = sequence_container_;
        }

        auto& operator ++ ()
        {
            index += 1;
            return *this;
        }

        auto operator != ( const SequenceContainer::iterator& container_iter ) const
        {
            return container_iter.index != index;
        }

        auto& operator * () const
        {
            if ( index >= sequence_container->size_ )
            {
                throw "Out of size";
            }

            return sequence_container->container[ index ];
        }
    };

    auto begin()
    {
        return iterator( 0 , this );
    }

    auto end()
    {
        return iterator( size_ , this );
    }

    /**
     * @brief
     * Конструктор класса
     */
    SequenceContainer()
    {
        capacity_ = 2;
        size_ = 0;

        // Умный указатель на контейнер
        container = std::make_shared< T[] >( capacity_ );
    }

    /**
     * @brief
     * Конструктор перемещения
     */
    SequenceContainer( SequenceContainer&& old_container )
    {
        container = old_container.container;
        capacity_ = old_container.capacity_;
        size_ = old_container.size_;
    }

    /**
     * @brief
     * Оператор присваивания с перемещением
     * 
     * @param old_container
     * старый контейнер, из которого перемещаем
     * 
     * @return
     * Возвращает ссылку на новый контейнер
     */
    auto operator = ( SequenceContainer&& old_container )
    {
        if ( &old_container != this )
        {
            container = old_container.container;
            size_ = old_container.size_;
            capacity_ = old_container.capacity_;
        }

        return *this;
    }

    /**
     * @brief
     * Метод добавления элемента в конец
     * 
     * @param element
     * элемент, который нужно вставить
     */
    void push_back( const T& element )
    {
        std::shared_ptr< T[] > temp;

        if ( capacity_ >= ( size_ + 1 ) )
        {
            container[ size_++ ] = element;
        }
        else
        {
            size_t new_capacity = (size_t)std::round( capacity_ * EXPANSION_COEFFICIENT );

            temp = std::make_shared< T[] >( new_capacity );

            for ( size_t i = 0 ; i < capacity_ ; ++i )
            {
                temp[i] = container[i];
            }

            container = temp;
            capacity_ = new_capacity;

            temp[ size_++ ] = element;
        }

        return;
    }

    /**
     * @brief
     * Метод вставки элемента в произвольную позицию
     * 
     * @param index
     * индекс, на который нужно вставить элемент
     * @param element
     * элемент, который нужно вставить
     */
    void insert( const size_t index , const T& element )
    {
        if( index > size_ )
        {
            throw "Out of size";
        }

        if ( index == size_ )
        {
            push_back( element );

            return;
        }

        std::shared_ptr< T[] > temp;

        if ( capacity_ >= ( size_ + 1 ) )
        {
            temp = std::make_shared< T[] >( capacity_ );
        }
        else
        {
            size_t new_capacity = (size_t)std::round( capacity_ * EXPANSION_COEFFICIENT );

            temp = std::make_shared< T[] >( new_capacity );

            capacity_ = new_capacity;
        }

        for ( size_t i = 0 , j = 0 ; i < size_ ; ++i , ++j )
        {
            if ( i == index )
            {
                temp[i++] = element;
                ++size_;
            }

            temp[i] = container[j];
        }

        container = temp;

        return;
    }

    /**
     * @brief
     * Метод удаления элемента(-ов)
     * 
     * @param index
     * индекс, с которого нужно начать удалять элемент(-ы)
     * 
     * @param size_
     * количество элементов для удаления (начальное значение равно 1)
     */
    void erase( const size_t index , const size_t size_ = 1 )
    {
        if ( ( index + size_ ) > this->size_ )
        {
            throw "Out of size";
        }

        std::shared_ptr< T[] > temp = std::make_shared< T[] >( capacity_ );

        for ( size_t i = 0 ; i < index ; ++i )
        {
            temp[i] = container[i];
        }

        for ( size_t i = index , j = ( index + size_ ) ; j < this->size_ ; ++i , ++j )
        {
            temp[i] = container[j];
        }

        this->size_ -= size_;

        container = temp;

        return;
    }
    
    /**
     * @brief
     * Получение текущего размера контейнера
     * 
     * @return
     * Возвращает текущий размер контейнера
     */
    auto capacity() const
    {
        return capacity_;
    }

    /**
     * @brief
     * Получение текущего количества элементов в контейнере
     * 
     * @return
     * Возвращает текущее количество элементов в контейнере
     */
    auto size() const
    {
        return size_;
    }

    /**
     * @brief
     * Переопределение оператора []
     * 
     * @param index
     * индекс элемента
     * 
     * @return
     * Возвращает элемент, находящийся под заданным индексом
     */
    auto& operator [] ( const size_t index ) const
    {
        if ( index >= size_ )
        {
            throw "Out of size";
        }

        return container[ index ];
    }

    /**
     * @brief
     * Деструктор класса
     */
    ~SequenceContainer()
    {
        
    }
};

template< typename T >
struct Node
{
    std::shared_ptr< Node > next;
    std::shared_ptr< Node > preveous; 
    T data;
};

template< typename T >
class ListContainer
{
    std::shared_ptr< Node< T > > head;
    std::shared_ptr< Node< T > > tail;
    size_t size_;

    public:

    struct iterator
    {
        size_t index;
        ListContainer* list_container;
        std::shared_ptr< Node< T > > node;

        iterator( size_t index_ , ListContainer* list_container_ )
        {
            index = index_;
            list_container = list_container_;

            node = list_container_->head;

            for ( size_t i = 0 ; i < index ; ++i )
            {
                node = node->next;
            }
        }

        auto& operator ++ ()
        {
            index += 1;

            node = node->next;

            return *this;
        }

        auto operator != ( const ListContainer::iterator& container_iter )
        {
            return container_iter.index != index;
        }

        auto& operator * ()
        {
            if ( index >= list_container->size_ )
            {
                throw "Out of size";
            }

            return node->data;
        }
    };

    auto begin()
    {
        return iterator( 0 , this );
    }

    auto end()
    {
        return iterator( size_ , this );
    }

    /**
     * @brief
     * Конструктор класса
     */
    ListContainer()
    {
        head = nullptr;
        tail = nullptr;
        size_ = 0;
    }

    /**
     * @brief
     * Метод добавления элемента в конец
     * 
     * @param element
     * элемент, который нужно вставить
     */
    void push_back( const T& element )
    {
        std::shared_ptr< Node< T > > node = std::make_shared< Node< T > >();

        node->data = element;

        if ( size_ == 0 )
        {
            head = node;
        }
        else
        {
            tail->next = node;
        }

        tail = node;
        ++size_;
    }

    /**
     * @brief
     * Метод вставки элемента в произвольную позицию
     * 
     * @param index
     * индекс, на который нужно вставить элемент
     * @param element
     * элемент, который нужно вставить
     */
    void insert( const size_t index , const T& element )
    {
        if( index > size_ )
        {
            throw "Out of size";
        }

        if ( index == size_ )
        {
            push_back( element );

            return;
        }

        std::shared_ptr< Node< T > > new_node = std::make_shared< Node< T > >();

        new_node->data = element;

        if ( index == 0 )
        {
            new_node->next = head;
            head = new_node;

            ++size_;

            return;
        }

        std::shared_ptr< Node< T > > node_before = head;

        for ( size_t i = 0 ; i < ( index - 1 ) ; ++i )
        {
            node_before = node_before->next;
        }

        std::shared_ptr< Node< T > > node_after = node_before->next;
        node_before->next = new_node;
        new_node->next = node_after;

        ++size_;

        return;
    }

    /**
     * @brief
     * Метод удаления элемента(-ов)
     * 
     * @param index
     * индекс, с которого нужно начать удалять элемент(-ы)
     * 
     * @param size_
     * количество элементов для удаления (начальное значение равно 1)
     */
    void erase( const size_t index , const size_t size_ = 1 )
    {
        if ( ( index + size_ ) > this->size_ )
        {
            throw "Out of size";
        }

        std::shared_ptr< Node< T > > node_after;

        if ( index == 0 )
        {
            node_after = head;

            for ( size_t i = 0 ; i < size_ ; ++i )
            {
                node_after = node_after->next;
            }

            head = node_after;

            this->size_ -= size_;

            return;
        }

        std::shared_ptr< Node< T > > node_before = head;

        for ( size_t i = 0 ; i < ( index - 1 ) ; ++i )
        {
            node_before = node_before->next;
        }

        node_after = node_before->next;

        for ( size_t i = 0 ; i < size_ ; ++i )
        {
            node_after = node_after->next;
        }

        node_before->next = node_after;

        this->size_ -= size_;

        return;
    }

    /**
     * @brief
     * Получение текущего количества элементов в контейнере
     * 
     * @return
     * Возвращает текущее количество элементов в контейнере
     */
    auto size() const
    {
        return size_;
    }

    /**
     * @brief
     * Переопределение оператора []
     * 
     * @param index
     * индекс элемента
     * 
     * @return
     * Возвращает элемент, находящийся под заданным индексом
     */
    auto& operator [] ( const size_t index ) const
    {
        if ( index >= size_ )
        {
            throw "Out of size";
        }

        std::shared_ptr< Node< T > > node = head;

        for ( size_t i = 0 ; i < index ; ++i )
        {
            node = node->next;
        }

        return node->data;
    }

    /**
     * @brief
     * Деструктор класса
     */
    ~ListContainer()
    {

    }
};