#pragma once
#ifndef KVMAP_H
#define KVMAP_H


namespace oak
{
  template <typename K, typename V>
  struct kvmap;

  //key value nodde
  template <typename K, typename V>
  struct kvnode
  {
    friend struct kvmap<K,V>;

    kvnode(const K _key, const V val) : key(_key)
    {
      this->val = val;
    }
    ~kvnode()
    {

    }

    const K key;
    V val;

    private:
      kvnode* next = nullptr;
  };

  //key value map
  template <typename K, typename V>
  struct kvmap
  {
    typedef kvnode<K, V> Node;

    kvmap()
    {
      m_front = nullptr;
      m_back = nullptr;
      m_size = 0;
    }

    ~kvmap()
    {
      m_iterator.node = m_front;
      while (m_front != nullptr)
      {
        m_iterator++;
        delete m_front;
        m_front = m_iterator.node;
      }
    }

    //insert element
    void add(const K key, const V val)
    {
      Node* node = new Node( key, val );
      if (m_front == nullptr)
      {
        m_front = node;
        m_back = node;
        m_iterator.node = m_front;
      }
      else
      {
        m_back->next = node;
        m_back = m_back->next;
      }

      m_size++;
    }

    //access element
    V& at(const K key)
    {
      bool reachedEndOnce = false;
      while (true)
      {
        if (m_iterator.node == nullptr)
        {
          if (reachedEndOnce)
          {
            throw std::invalid_argument("key not found");
          }
          reachedEndOnce = true;
          m_iterator.node = m_front;
        }
        if (m_iterator.node->key == key)
        {
          return m_iterator.node->val;
        }

        m_iterator++;
      }
    }

    //access element
    V& operator[](const K key)
    {
      bool reachedEndOnce = false;
      while (true)
      {
        if (m_iterator.node == nullptr)
        {
          if (reachedEndOnce)
          {
            throw std::invalid_argument("key not found");
          }
          reachedEndOnce = true;
          m_iterator.node = m_front;
        }
        if (m_iterator.node->key == key)
        {
          return m_iterator.node->val;
        }

        m_iterator++;
      }
    }

    //remove element
    void remove(const K key)
    {
      m_iterator.node = m_front;
      Node* prevNode = nullptr;

      while (true)
      {
        if (m_iterator.node->key == key)
        {
          if (prevNode == nullptr)
          {
            m_front = m_iterator.node->next;
            m_iterator.node = m_front;
          }
          else
          {
            prevNode->next = m_iterator.node->next;
            delete m_iterator.node;
            m_iterator.node = prevNode;
          }
          
          m_size--;
          return;
        }
        prevNode = m_iterator.node;
        m_iterator++;
      }
    }

    //number of elements
    unsigned int size()
    {
      return m_size;
    }

    //iterator
    //----------------------------
    struct iterator
    {
      friend struct kvmap<K, V>;
      typedef iterator self_type;
      typedef Node value_type;
      typedef Node& reference;
      typedef Node* pointer;

      iterator(Node* node)
      {
        this->node = node;
      }

      //next
      void operator++()
      {
        node = node->next;
      }

      self_type operator+(unsigned int n)
      {
        while (n > 0)
        {
          node = node->next;
          n--;
        }
        return *this;
      }

      //next
      void operator++(int junk)
      {
        node = node->next;
      }

      //comparision
      bool operator==(const self_type& rhs)
      {
        return node == rhs.node;
      }

      //negative comparision
      bool operator!=(const self_type& rhs)
      {
        return node != rhs.node;
      }

      //get reference
      reference operator*()
      {
        return *node;
      }

      //get pointer
      pointer operator->()
      {
        return &node;
      }

    private:
      Node* node;
    };

    //----------------------------

    //returns the iterator pointed at the front
    iterator& begin()
    {
      m_iterator.node = m_front;
      return m_iterator;
    }

    //returns the end iterator
    const iterator& end()
    {
      return END_ITERATOR;
    }

    //searches for an element with a matching key, if not found nullptr is returned
    const Node* find(const K key)
    {
      m_iterator.node = m_front;
      while (m_iterator.node != nullptr)
      {
        if (m_iterator.node->key == key)
        {
          return m_iterator.node;
        }
        m_iterator++;
      }
      return nullptr;
    }

  private:
    Node* m_front;
    Node* m_back;
    unsigned int m_size;
    const iterator END_ITERATOR = iterator(nullptr);
    iterator m_iterator = iterator(nullptr);
  };

}

#endif