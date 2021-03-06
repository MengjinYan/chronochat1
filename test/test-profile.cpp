/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
/**
 * Copyright (C) 2013 Regents of the University of California.
 * @author: Yingdi Yu <yingdi@cs.ucla.edu>
 * See COPYING for copyright and distribution information.
 */

#include <boost/test/unit_test.hpp>

#include "profile.hpp"
#include <ndn-cxx/encoding/buffer-stream.hpp>

namespace chronos {

using std::string;

BOOST_AUTO_TEST_SUITE(TestProfile)

BOOST_AUTO_TEST_CASE(EncodeDecodeProfile)
{
  Name identity("/ndn/ucla/yingdi");
  Profile profile(identity);
  profile["name"] = "Yingdi Yu";
  profile["school"] = "UCLA";

  ndn::OBufferStream os;
  profile.encode(os);

  ndn::ConstBufferPtr encoded = os.buf();

  boost::iostreams::stream
    <boost::iostreams::array_source> is(reinterpret_cast<const char*>(encoded->buf()),
                                        encoded->size ());

  Profile decodedProfile;
  decodedProfile.decode(is);

  BOOST_CHECK_EQUAL(decodedProfile.getIdentityName().toUri(), string("/ndn/ucla/yingdi"));
  BOOST_CHECK_EQUAL(decodedProfile["name"], string("Yingdi Yu"));
  BOOST_CHECK_EQUAL(decodedProfile["school"], string("UCLA"));
}

BOOST_AUTO_TEST_SUITE_END()

} // namespace chronos
