/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * COPYRIGHT MSG GOES HERE...
 */

#ifndef CHRONOS_COMMON_HPP
#define CHRONOS_COMMON_HPP

#include "config.h"

#ifdef WITH_TESTS
#define VIRTUAL_WITH_TESTS virtual
#define PUBLIC_WITH_TESTS_ELSE_PROTECTED public
#define PUBLIC_WITH_TESTS_ELSE_PRIVATE public
#define PROTECTED_WITH_TESTS_ELSE_PRIVATE protected
#else
#define VIRTUAL_WITH_TESTS
#define PUBLIC_WITH_TESTS_ELSE_PROTECTED protected
#define PUBLIC_WITH_TESTS_ELSE_PRIVATE private
#define PROTECTED_WITH_TESTS_ELSE_PRIVATE private
#endif

#include <cstddef>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <string>

#include <ndn-cxx/common.hpp>
#include <ndn-cxx/interest.hpp>
#include <ndn-cxx/data.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/noncopyable.hpp>
#include <boost/property_tree/ptree.hpp>

namespace chronos {

using std::size_t;

using boost::noncopyable;

using ndn::shared_ptr;
using ndn::weak_ptr;
using ndn::enable_shared_from_this;
using ndn::make_shared;
using ndn::static_pointer_cast;
using ndn::dynamic_pointer_cast;
using ndn::const_pointer_cast;
using ndn::function;
using ndn::bind;
using ndn::ref;
using ndn::cref;

using ndn::Interest;
using ndn::Data;
using ndn::Name;
using ndn::Exclude;
using ndn::Block;
using ndn::Signature;
using ndn::KeyLocator;

namespace tlv {
using namespace ndn::Tlv;
}

namespace name = ndn::name;
namespace time = ndn::time;

} // namespace chronos

#endif // CHRONOS_COMMON_HPP
