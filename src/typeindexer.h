#ifndef TYPEINDEXER_H
#define TYPEINDEXER_H

#include <typeindex>
#include <vector>

class TypeIndexer
{
  private:
    std::vector<std::type_index> m_indexes;
    static TypeIndexer* m_instance;
    long long indexInner(const std::type_index &index);
  public:
    static long long index(const std::type_index &index);
};

#endif // TYPEINDEXER_H
