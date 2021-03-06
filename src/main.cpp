/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) 2013, Regents of the University of California
 *                     Yingdi Yu
 *
 * BSD license, See the LICENSE file for more information
 *
 * Author: Yingdi Yu <yingdi@cs.ucla.edu>
 */

#include <QApplication>
// #include <QSystemTrayIcon>

#include "controller.hpp"
#include "logging.h"
#include <ndn-cxx/face.hpp>
#include <boost/thread/thread.hpp>

class NewApp : public QApplication
{
public:
  NewApp(int& argc, char** argv)
    : QApplication(argc, argv)
  {
  }

  bool
  notify(QObject* receiver, QEvent* event)
  {
    try {
        return QApplication::notify(receiver, event);
    }
    catch (std::exception& e) {
      std::cerr << "Exception thrown:" << e.what() << std::endl;
      return false;
    }

  }
};

void
runIO(boost::asio::io_service& ioService)
{
  try {
    ioService.run();
  }
  catch (std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
  }
}

int main(int argc, char *argv[])
{
  NewApp app(argc, argv);

  ndn::shared_ptr<ndn::Face> face = ndn::make_shared<ndn::Face>();
  chronos::Controller controller(face);

  app.setQuitOnLastWindowClosed(false);

  boost::thread(runIO, boost::ref(face->getIoService()));

  return app.exec();
}
