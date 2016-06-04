#include "stdafx.h"
#include "multiThreading.h"

void MultiThread::StartMultiThread (boost::asio::io_service &ioService, boost::thread_group &threadGroup)
{
	for (unsigned int r= 0; r< boost::thread::hardware_concurrency(); r++)
	{
		threadGroup.create_thread (boost::bind (&boost::asio::io_service::run, &ioService));
	}
}

void MultiThread::EndMultiThread (boost::asio::io_service &ioService, boost::thread_group &threadGroup)
{
	ioService.stop ();
	threadGroup.join_all ();
}