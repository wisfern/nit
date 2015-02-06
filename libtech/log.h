/*
 * log.h
 *
 *  Created on: 2014Äê11ÔÂ2ÈÕ
 *      Author: wisfern
 */

#ifndef LIBTECH_LOG_H_
#define LIBTECH_LOG_H_

#include <noncopyable.h>

__NIT_NAMESPACE_BEGIN

#define LOG

class NIT_API log : public noncopyable {
public:
	log();
	virtual ~log();


};

__NIT_NAMESPACE_END

#endif /* LIBTECH_LOG_H_ */
