#ifndef MULTI_THREADING_H
#define MULTI_THREADING_H

#include <boost\asio.hpp>
#include <boost/thread/thread.hpp>
#include "cgalnterpolation.h"
#include <glm\glm.hpp>

class MultiThread 
{
public:
	template <typename F> static void ProcessFunction (F func, CgalInterp::SharedPtr cgal, std::vector <glm::vec3> &container);
	static void StartMultiThread (boost::asio::io_service &ioService, boost::thread_group &threadGroup);
	template <typename F> static void PushJob (F func, CgalInterp::SharedPtr cgal, glm::vec3 vertex, boost::asio::io_service &io_service);
	static void EndMultiThread (boost::asio::io_service &ioService, boost::thread_group &threadGroup);

private:
	
};

template <typename F>
void MultiThread::ProcessFunction (F func, CgalInterp::SharedPtr cgal, std::vector <glm::vec3> &container)
{
	boost::asio::io_service io_service;
	boost::asio::io_service::work work_ (io_service);
	boost::thread_group thread_group;

	StartMultiThread (io_service, thread_group);

	for (unsigned int i = 0; i < container.size (); i++)
		PushJob (func, cgal, container.at(i), io_service);

	EndMultiThread (io_service, thread_group);
}

template <typename F>
void MultiThread::PushJob (F func, CgalInterp::SharedPtr cgal, glm::vec3 vertex, boost::asio::io_service &io_service)
{
	io_service.post(boost::bind (func, cgal, vertex));
}
#endif

