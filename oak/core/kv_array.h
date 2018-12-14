#ifndef KV_ARRAY_H
#define KV_ARRAY_H

//Key Value array
//acts similar to a fixed sized std::map
//note: 
//key must be a number value (char, short, int, etc) and be a non-zero value
//as zero is reserved for null

namespace oak
{
  template <typename KEY, typename VAL>
  struct kv_node
  {
    KEY key = 0; //null == 0
    VAL value;
  };

  template <typename KEY, typename VAL>
  struct kv_array_iterator
  {
    kv_node<KEY, VAL>* node;
    unsigned int index;
    bool hasEnded = true;
  };

  template <typename KEY, typename VAL, const unsigned int size>
  struct kv_array
  {
    //insert new kv
    void insert(KEY key, VAL value)
    {
      for (unsigned int i = 0; i < m_size; i++)
      {
        if (nodes[i].key == 0)
        {
          nodes[i].key = key;
          nodes[i].value = value;
          return;
        }
      }
    }

    //returns value by key
    VAL at(KEY key) const
    {
      for (unsigned int i = 0; i < m_size; i++)
      {
        if (nodes[i].key == key)
        {
          return nodes[i].value;
        }
      }
      return nullptr;
    }

    VAL operator [](KEY key) const
    {
      return this->at(key);
    }

    //remove value by key
    void remove(KEY key)
    {
      for (unsigned int i = 0; i < m_size; i++)
      {
        if (nodes[i].key == key)
        {
          nodes[i].key = 0;
        }
      }
    }

    kv_array_iterator<KEY, VAL>* begin()
    {
      for (unsigned int i = 0; i < m_size; i++)
      {
        if (nodes[i].key != 0)
        {
          it.hasEnded = false;
          it.index = i;
          it.node = &nodes[i];
          return &it;
        }
      }
      return &it;
    }

    void next()
    {
      for (unsigned int i = it.index + 1; i < m_size; i++)
      {
        if (nodes[i].key != 0)
        {
          it.index = i;
          it.node = &nodes[i];
          return;
        }
      }
      it.hasEnded = true;
    }

    bool end()
    {
      return !it.hasEnded;
    }

    private:
      kv_node<KEY,VAL> nodes[size];
      const unsigned int m_size = size;
      kv_array_iterator<KEY, VAL> it;
  };
}

#endif