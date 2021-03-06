/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
/**
 * Copyright (C) 2013 Regents of the University of California.
 * @author: Yingdi Yu <yingdi@cs.ucla.edu>
 * See COPYING for copyright and distribution information.
 */

#include <boost/test/unit_test.hpp>

#include "contact-storage.hpp"
#include "cryptopp.hpp"
#include <boost/filesystem.hpp>

namespace chronos {

using std::string;
namespace fs = boost::filesystem;

BOOST_AUTO_TEST_SUITE(TestContactStorage)

const string dbName("chronos-20e9530008b27c661ad3429d1956fa1c509b652dce9273bfe81b7c91819c272c.db");

BOOST_AUTO_TEST_CASE(InitializeTable)
{
  Name identity("/TestContactStorage/InitializeTable");

  ContactStorage contactStorage(identity);
  fs::path dbPath = fs::path(getenv("HOME")) / ".chronos" / dbName;

  BOOST_CHECK(boost::filesystem::exists(dbPath));
}

BOOST_AUTO_TEST_SUITE_END()

} // namespace chronos
