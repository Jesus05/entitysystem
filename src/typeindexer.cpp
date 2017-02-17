#include "typeindexer.h"

#include <algorithm>
#include <mutex>

#include "debugmacros.h"

TypeIndexer* TypeIndexer::m_instance = std::nullptr_t();

long long TypeIndexer::indexInner(const std::type_index &index)
{
  std::vector<std::type_index>::const_iterator iter = std::find(m_indexes.cbegin(), m_indexes.cend(), index);
  if (iter != m_indexes.cend())
  {
//    std::cout << V(std::distance(m_indexes.cbegin(), iter)) << V(iter->name()) << std::endl;
    return std::distance(m_indexes.cbegin(), iter);
  }
  m_indexes.push_back(index);
//  std::cout << V(m_indexes.size()-1) << V(index.name()) << std::endl;
  return m_indexes.size() - 1;
}

long long TypeIndexer::index(const std::type_index &index)
{
//  static std::mutex mutex;
//  std::lock_guard<std::mutex> guard(mutex);
  if (!m_instance) m_instance = new TypeIndexer();
  return m_instance->indexInner(index);
}
